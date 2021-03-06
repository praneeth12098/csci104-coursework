#include "main_window.h"
#include "util.h"
#include "math.h"
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(MyDataStore *ds, User* currentUser)
{
	setWindowTitle("The OG Market");

	//data store initialization
	this->ds = ds;
	this->currentUser = currentUser;
	currReviewCount = 0;

	reviews = ds->getReviews();
	currReviewSize = reviews.size();

	new_window = new NewWindow(ds, u, cart);

	rating_window = new RatingWindow(ds, PROD);

	//rating calculation
	ds->averageRatings();

	//overall layout
	overallLayout = new QVBoxLayout();

	// // search functionality

	//search layout 
	searchLayout = new QHBoxLayout();
	overallLayout->addLayout(searchLayout);

	selectUser = new QComboBox();
	std::string currUser = currentUser->getName();
	QString qCurrUser = QString::fromStdString(currUser);
	selectUser->addItem(qCurrUser);

	overallLayout->addWidget(selectUser);

	//search label layout
	searchLabel = new QLabel("Search:");
	searchLabel->setStyleSheet("QLabel { background-color : lightGray; color : darkRed; }");
	searchLayout->addWidget(searchLabel);

	//search field layout
	searchField = new QLineEdit();
	searchLayout->addWidget(searchField);

	//and, or button layout
	searchButtonLayout = new QVBoxLayout();
	searchLayout->addLayout(searchButtonLayout);

	//and button layout
	andButton = new QRadioButton("AND");
	connect(andButton, SIGNAL(clicked()), this, SLOT(AndSelection()));
	searchButtonLayout->addWidget(andButton);

	//or button layout
	orButton = new QRadioButton("OR");
	connect(orButton, SIGNAL(clicked()), this, SLOT(OrSelection()));
	searchButtonLayout->addWidget(orButton);

	//search button layout
	searchButton = new QPushButton("Go!");
	connect(searchButton, SIGNAL(clicked()), this, SLOT(searchBox()));
	searchLayout->addWidget(searchButton);

	//search results and buttons layout
	resultsAndButtons = new QHBoxLayout;
	overallLayout->addLayout(resultsAndButtons);

	//search results list widget layout
	searchResults = new QListWidget();
	connect(searchResults, SIGNAL(currentRowChanged(int)), this, SLOT(showReview(int)));
	resultsAndButtons->addWidget(searchResults);

	//sort and cart buttons layout
	sortAndCartLayout = new QVBoxLayout();
	resultsAndButtons->addLayout(sortAndCartLayout);

	//sort by drop down combo box
	sortByBox = new QComboBox();
	sortByBox->addItem("sort by..");
	sortByBox->addItem("Product Name A-Z");
	sortByBox->addItem("Rating High-Low");
	connect(sortByBox, SIGNAL(currentIndexChanged(int)),this,SLOT(sortBy(int)));
	sortAndCartLayout->addWidget(sortByBox);


	//add to cart button layout
	addToCartButton = new QPushButton("Add to Cart");
	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addCart()));
	sortAndCartLayout->addWidget(addToCartButton);

	//view cart button layout
	viewCartButton = new QPushButton("View Cart");
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(openCartWindow()));
	sortAndCartLayout->addWidget(viewCartButton);

	//reviews overall layout
	reviewLayout = new QHBoxLayout();
	overallLayout->addLayout(reviewLayout);

	//review list layout
	reviewResults = new QListWidget();

	reviewLayout->addWidget(reviewResults);

	//review options layout
	reviewOptionsLayout = new QVBoxLayout();
	reviewLayout->addLayout(reviewOptionsLayout);

	//review sort layout
	reviewSort = new QComboBox();
	reviewSort->addItem("sort by..");
	reviewSort->addItem("Date New-Old");
	connect(reviewSort, SIGNAL(currentIndexChanged(int)),this,SLOT(sortReviews(int)));
	reviewOptionsLayout->addWidget(reviewSort);

	//refresh button layout
	refreshReviews = new QPushButton("Refresh Reviews");
	connect(refreshReviews, SIGNAL(clicked()), this, SLOT(refreshReview()));
	reviewOptionsLayout->addWidget(refreshReviews);

	//review button layout
	addReviewLayout = new QHBoxLayout;
	overallLayout->addLayout(addReviewLayout);

	addReviewButton = new QPushButton("Add Review");
	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReview()));
	addReviewLayout->addWidget(addReviewButton);

	//product reccomendation layout
	productRecLayout = new QHBoxLayout;
	overallLayout->addLayout(productRecLayout);

	productRecButton = new QPushButton("Product Reccomendations");
	connect(productRecButton, SIGNAL(clicked()), this, SLOT(productReccomendation()));
	productRecLayout->addWidget(productRecButton);


	//save button layout
	saveLayout = new QHBoxLayout;
	overallLayout->addLayout(saveLayout);

	saveButton = new QPushButton("Save");
	connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
	saveLayout->addWidget(saveButton);

	//quit button layout
	quitLayout = new QHBoxLayout;
	overallLayout->addLayout(quitLayout);

	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
	quitLayout->addWidget(quitButton);


	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	delete ds;

	std::vector<Product*>::iterator prods = searchproducts.begin();
	for(; prods != searchproducts.end(); ++prods)
		delete *prods;

	std::vector<Review*>::iterator r = reviews.begin();
	for(; r != reviews.end(); ++r)
		delete *r;

	std::map<User*, std::vector<Product*> >::iterator mapit = cart.begin();
	for(; mapit != cart.end(); ++mapit)
	{
		User* u = mapit->first;
		std::vector<Product*> prod = mapit->second;
		std::vector<Product*>::iterator p = prod.begin();
		for(; p != prod.end(); ++p)
			delete *p;
		delete u;
	}
	cart.clear();

	delete u;

	delete saveButton;
	delete saveLayout;
	delete addReviewButton;
	delete addReviewLayout;
	delete reviewResults;
	delete reviewLayout;
	delete viewCartButton;
	delete addToCartButton;
	delete sortByBox;
	delete sortAndCartLayout;
	delete searchResults;
	delete resultsAndButtons;
	delete searchButton;
	delete orButton;
	delete andButton;
	delete searchButtonLayout;
	delete searchField;
	delete searchLabel;
	delete selectUser;
	delete searchLayout;
	delete overallLayout;
}

void MainWindow::AndSelection(){ AndOr = 0; }

void MainWindow::OrSelection(){ AndOr = 1; }

void MainWindow::searchBox()
{
	searchResults->clearSelection();
	disconnect(searchResults, SIGNAL(currentRowChanged(int)), this, SLOT(showReview(int)));

	if(searchField->text().isEmpty()) return;

	reviews = ds->getReviews();

	if(currReviewSize < reviews.size())
	{
		ds->resetRatings();
		ds->averageRatings();
	}

	//calcRating = true;

	std::string sterms = searchField->text().toStdString();
	
	std::set<std::string> searchset = parseStringToWords(sterms);
	std::vector<std::string> searchvector;

	std::set<std::string>::iterator it = searchset.begin();
	for(; it != searchset.end(); ++it)
	{
		searchvector.push_back(*it);
	}

	if(searchproducts.size() > 0)
	{
		for(int i = searchproducts.size(); i >= 0; i--)
		{
			searchResults->takeItem(i);
		}
	}

	searchproducts = ds->search(searchvector, AndOr);

	std::vector<Product*>::iterator sprods = searchproducts.begin();

	for(; sprods != searchproducts.end(); ++sprods)
	{
		std::string tempinfo = (*sprods)->displayString();
		QString temp = QString::fromStdString(tempinfo);
		searchResults->addItem(temp);
	}
	connect(searchResults, SIGNAL(currentRowChanged(int)), this, SLOT(showReview(int)));
}	

void MainWindow::sortBy(int index)
{
	disconnect(searchResults, SIGNAL(currentRowChanged(int)), this, SLOT(showReview(int)));
	if(index == 2)
	{
		RatingComp comp;
		mergeSort(searchproducts, comp);

		for(int i = searchproducts.size(); i >= 0; i--)
		{
			searchResults->takeItem(i);
		}

		std::vector<Product*>::iterator sprods = searchproducts.begin();

		for(; sprods != searchproducts.end(); ++sprods)
		{
			std::string tempinfo = (*sprods)->displayString();
			QString temp = QString::fromStdString(tempinfo);
			searchResults->addItem(temp);
		}

		//calcRating = false;
	}
	if(index == 1)
	{
		AlphaStrComp comp;
		mergeSort(searchproducts, comp);

		for(int i = searchproducts.size(); i >= 0; i--)
		{
			searchResults->takeItem(i);
		}

		std::vector<Product*>::iterator sprods = searchproducts.begin();

		for(; sprods != searchproducts.end(); ++sprods)
		{
			std::string tempinfo = (*sprods)->displayString();
			QString temp = QString::fromStdString(tempinfo);
			searchResults->addItem(temp);
		}
	}
	connect(searchResults, SIGNAL(currentRowChanged(int)), this, SLOT(showReview(int)));
}

void MainWindow::sortReviews(int index)
{
	if(index == 1)
	{
		DateComp comp;
		reviews = ds->getReviews();
		for(int i = currReviewCount; i >= 0; i--)
		{
			reviewResults->takeItem(i);
		}

		Product* p = searchproducts[prodindex];
		mergeSort(reviews, comp);
		std::vector<Review*>::iterator r = reviews.begin();

		for(; r != reviews.end(); ++r)
		{
			if((*r)->prodName == p->getName())
			{
				std::string tempinfo = (*r)->displayString();
				QString temp = QString::fromStdString(tempinfo);
				reviewResults->addItem(temp);
			}	
		}
		currReviewCount = reviews.size();
	}
}

void MainWindow::addCart()
{
	QModelIndexList indexes = searchResults->selectionModel()->selectedIndexes();
 
	std::vector<int> indexList;
	foreach(QModelIndex index, indexes)
	{
		indexList.push_back(index.row());
	}

	if(indexList.size() == 0 || !user_picked) {showPopup();}
	else {
		int i = indexList[0];
	 	ds->addToCart(u, searchproducts[i]);
	}
}

void MainWindow::showReview(int index)
{
	reviews = ds->getReviews();
	for(int i = currReviewCount; i >= 0; i--)
	{
		reviewResults->takeItem(i);
	}

	Product* p = searchproducts[index];
	PROD = p;
	prodindex = index;
	std::vector<Review*>::iterator r = reviews.begin();

	for(; r != reviews.end(); ++r)
	{
		if((*r)->prodName == p->getName())
		{
			std::string tempinfo = (*r)->displayString();
			QString temp = QString::fromStdString(tempinfo);
			reviewResults->addItem(temp);
		}	
	}
	currReviewCount = reviews.size();
}

void MainWindow::openCartWindow()
{
	if(!user_picked) {showPopup();}

	if(new_window->isVisible()){
		new_window->update();
		new_window->show();
	}
	else{
		new_window = new NewWindow(ds, u, cart);
		new_window->show();
	}
}

void MainWindow::addReview()
{
		if(rating_window->isVisible()){
		rating_window->update();
		rating_window->show();
	}
	else{
		rating_window = new RatingWindow(ds, PROD);
		rating_window->show();
	}
}

void MainWindow::showPopup()
{
	// Create message box
	QMessageBox msgBox;

	// Set message box text values
	msgBox.setWindowTitle("Error");
	msgBox.setText("\"Select An Option First!!!\"");

	// Add buttons to message box
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);

	msgBox.exec();
}

void MainWindow::save()
{
	QString filename = QFileDialog::getSaveFileName();
	string file = filename.toStdString();
	ofstream ofile(file.c_str());
    ds->dump(ofile);
    ofile.close();
}

void MainWindow::refreshReview()
{
	reviews = ds->getReviews();
	for(int i = currReviewCount; i >= 0; i--)
	{
		reviewResults->takeItem(i);
	}

	Product* p = searchproducts[prodindex];
	std::vector<Review*>::iterator r = reviews.begin();

	for(; r != reviews.end(); ++r)
	{
		if((*r)->prodName == p->getName())
		{
			std::string tempinfo = (*r)->displayString();
			QString temp = QString::fromStdString(tempinfo);
			reviewResults->addItem(temp);
		}	
	}
	currReviewCount = reviews.size();
}

void MainWindow::quit()
{
	this->close();
}

void MainWindow::productReccomendation()
{
	recWindow = new QWidget();
	recLayout = new QVBoxLayout();

	recWindow->setLayout(recLayout);

	recList = new QListWidget();
	recLayout->addWidget(recList);
	doneButton = new QPushButton("Done");
	connect(doneButton, SIGNAL(clicked()), this, SLOT(hideRecWindow()));
	recLayout->addWidget(doneButton);

	recWindow->show();

	std::string uName = currentUser->getName();
	std::vector<std::pair<std::string, double> > pRecs;
	pRecs = ds->makeSuggestion(uName);

	ofstream file("rec.txt");
	file << currentUser->getName() << '\n';

	if(pRecs.size() == 0)
	{
		std::string msg = "No Recommendations";
		QString qmsg = QString::fromStdString(msg);
		QListWidgetItem* item = new QListWidgetItem();
		item->setText(qmsg);
		recList->addItem(item);
	}
	else
	{
		std::vector<std::pair<std::string, double> >::iterator it = pRecs.begin();
		for(; it != pRecs.end(); ++it)
		{
			std::string pName = (*it).first;
			QString temp = QString::fromStdString(pName);

			double r = (*it).second;
			double scale = 0.01;
			r = (int)(r/scale)*scale;
			QString rate = QString::number(r);

			file << r << " " << pName << '\n';
			
			QListWidgetItem* item = new QListWidgetItem();
			item->setText(rate + " " + temp);
			recList->addItem(item);
		}
	}
}

void MainWindow::hideRecWindow()
{
	recWindow->hide();
}