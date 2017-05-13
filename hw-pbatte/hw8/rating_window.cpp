#include "rating_window.h"

RatingWindow::RatingWindow(MyDataStore* ds, Product* p)
{
	//initializing data members
	this->ds = ds;
	this->p = p;

	products = ds->getProducts();

	//overall layout
	overallLayout = new QVBoxLayout();

	//cartname
	setWindowTitle("Review Form");

	//product names layout
	//pNames = new QComboBox();

	//date layout
	yearLayout = new QHBoxLayout();
	overallLayout->addLayout(yearLayout);

	yearLabel = new QLabel("Year (YYYY): ");
	//yearLabel->setStyleSheet("QLabel { background-color : lightGray; color : darkRed; }");
	yearLayout->addWidget(yearLabel);

	year = new QLineEdit();
	yearLayout->addWidget(year);

	monthLayout = new QHBoxLayout();
	overallLayout->addLayout(monthLayout);

	monthLabel = new QLabel("Month (MM): ");
	//monthLabel->setStyleSheet("QLabel { background-color : lightGray; color : darkRed; }");
	monthLayout->addWidget(monthLabel);

	month = new QLineEdit();
	monthLayout->addWidget(month);

	dayLayout = new QHBoxLayout();
	//dayLabel->setStyleSheet("QLabel { background-color : lightGray; color : darkRed; }");
	overallLayout->addLayout(dayLayout);

	dayLabel = new QLabel("Day (DD): ");
	dayLayout->addWidget(dayLabel);

	day = new QLineEdit();
	dayLayout->addWidget(day);

	//username Layout
	uLayout = new QHBoxLayout();
	overallLayout->addLayout(uLayout);

	uLabel = new QLabel("Username (from file): ");
	//uLabel->setStyleSheet("QLabel { background-color : lightGray; color : darkRed; }");
	uLayout->addWidget(uLabel);

	username = new QLineEdit();
	uLayout->addWidget(username);

	//rating Layout
	ratingLayout = new QHBoxLayout();
	overallLayout->addLayout(ratingLayout);

	ratingLabel = new QLabel("Rating (1-5): ");
	//ratingLabel->setStyleSheet("QLabel { background-color : lightGray; color : darkRed; }");
	ratingLayout->addWidget(ratingLabel);

	rating = new QLineEdit();
	ratingLayout->addWidget(rating);

	//reviewText Layout
	rTextLayout = new QHBoxLayout();
	overallLayout->addLayout(rTextLayout);

	rTextLabel = new QLabel("Your Review");
	//rTextLabel->setStyleSheet("QLabel { background-color : lightGray; color : darkRed; }");
	rTextLayout->addWidget(rTextLabel);

	rText = new QLineEdit();
	rTextLayout->addWidget(rText);

	//submit button layout
	submitButton = new QPushButton("Submit Review");
	connect(submitButton, SIGNAL(clicked()), this, SLOT(submitReview()));
	overallLayout->addWidget(submitButton);

	//close button layout
	closeButton = new QPushButton("Close");
	connect(closeButton, SIGNAL(clicked()), this, SLOT(reviewPopup()));
	overallLayout->addWidget(closeButton);

    setLayout(overallLayout);
}

RatingWindow::~RatingWindow()
{
	delete ds;
	//delete products;

	std::vector<Product*>::iterator prods = products.begin();
	for(; prods != products.end(); ++prods)
		delete *prods;

	delete p;
	delete rating;
	delete ratingLabel;
	delete ratingLayout;
	delete rText;
	delete rTextLabel;
	delete rTextLayout;
	delete day;
	delete dayLabel;
	delete dayLayout;
	delete month;
	delete monthLabel;
	delete monthLayout;
	delete year;
	delete yearLabel;
	delete yearLayout;
	//delete pNames;
	delete overallLayout;
}

void RatingWindow::submitReview()
{
	//std::cout << p->getName() << std::endl;

	std::string y = year->text().toStdString();
	std::string m = month->text().toStdString();
	std::string d = month->text().toStdString();
	std::string rev = rText->text().toStdString();
	std::string rat = rating->text().toStdString();
	std::string user = username->text().toStdString();
	std::string prodName = p->getName();

	int ratingNumber = atoi(rat.c_str());
	std::string date = y + "-" + m + "-" + d;

	if(ratingNumber < 1 || ratingNumber > 5) 
	{
		showPopup();
	}
	else
	{
		Review* r = new Review(prodName, ratingNumber, user, date, rev);
		ds->addReview(r);
	}
}


void RatingWindow::showPopup()
{
	// Create message box
	QMessageBox msgBox;

	// Set message box text values
	msgBox.setWindowTitle("Error");
	msgBox.setText("\"Input Valid Rating!!!\"");

	// Add buttons to message box
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);

	msgBox.exec();
}

void RatingWindow::reviewPopup()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Review Submission");
	msgBox.setText("\"Review Submitted!!!\"");

	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);

	msgBox.exec();

	this->close();
}