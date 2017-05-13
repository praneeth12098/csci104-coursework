#include "new_window.h"

NewWindow::NewWindow(MyDataStore* ds, User* u, std::map<User*, std::vector<Product*> > cart)
{
	//initializing data members
	this->ds = ds;
	this->u = u;
	this->cart = cart;

	//overall layout
	overallLayout = new QHBoxLayout();

	//cartname
	setWindowTitle("Your Cart");

	//cart layout
	//cartLabel = new QLabel(QString::fromStdString(cartname));
	//overallLayout->addWidget(cartLabel);

	//cart list layout
	cartList = new QListWidget();
	overallLayout->addWidget(cartList);

	//cart buttons layout
	cartButtonLayout = new QVBoxLayout();

	buyCart = new QPushButton("Buy Cart");
	connect(buyCart, SIGNAL(clicked()), this, SLOT(buyCartItems()));
	cartButtonLayout->addWidget(buyCart);

	removeFromCart = new QPushButton("Remove Item");
	connect(removeFromCart, SIGNAL(clicked()), this, SLOT(removeItem()));
	cartButtonLayout->addWidget(removeFromCart);

	overallLayout->addLayout(cartButtonLayout);

	cartList->update();
	cart = ds->getCart();

	std::map<User*, std::vector<Product*> >::iterator mapit;
    mapit = cart.find(u);

    if(mapit != cart.end())
    {
    	prods = mapit->second;
    	std::vector<Product*>::iterator it = prods.begin();
       	for(; it != prods.end(); ++it)
    	{
    	   	//std::cout << "it gets here" << std::endl;

    		std::string tempstr = (*it)->displayString();
    		//std::cout << tempstr << std::endl;
    		QString temp = QString::fromStdString(tempstr);
    		cartList->addItem(temp);
    	}
    }

    setLayout(overallLayout);
}

NewWindow::~NewWindow()
{
	delete ds;

	std::vector<Product*>::iterator pr = prods.begin();
	for(; pr != prods.end(); ++pr)
		delete *pr;

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
	delete removeFromCart;
	delete buyCart;
	delete cartButtonLayout;
	delete cartList;
	delete overallLayout;
}

void NewWindow::buyCartItems()
{
	cart = ds->getCart();
	ds->buyCart(u);

	std::map<User*, std::vector<Product*> >::iterator mapit;
    mapit = cart.find(u);

    std::vector<Product*> cartItems;

    if(mapit != cart.end()) cartItems = mapit->second;

	for(int i = cartItems.size(); i >= 0; i--)
	{
		cartList->takeItem(i);
	}
}

void NewWindow::removeItem()
{
	QModelIndexList indexes = cartList->selectionModel()->selectedIndexes();
 
	std::vector<int> indexList;
	foreach(QModelIndex index, indexes)
	{
		indexList.push_back(index.row());
	}

	if(indexList.size() == 0) {showPopup();}
	else {
		int i = indexList[0];
		ds->removeFromCart(u, prods[i]);
		cartList->takeItem(i);
	}

}

void NewWindow::showPopup()
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