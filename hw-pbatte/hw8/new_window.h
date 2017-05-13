#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>


#include <string>
#include <vector>
#include <iostream>

#include "mydatastore.h"

class NewWindow : public QWidget
{
	Q_OBJECT
public:
	NewWindow(MyDataStore *ds, User* u, std::map<User*, std::vector<Product*> > cart);
	~NewWindow();

private slots:
	void buyCartItems();
	void showPopup();
	void removeItem();

private:
	// // UI

	//Layout
	QHBoxLayout* overallLayout;

	//QLabel* cartLabel;

	QListWidget* cartList;

	QVBoxLayout* cartButtonLayout;

	QPushButton* buyCart;

	QPushButton* removeFromCart;


	//data store pointer
	MyDataStore* ds;
	User* u;
	std::vector<Product*> prods;
	std::map<User*, std::vector<Product*> > cart;

};