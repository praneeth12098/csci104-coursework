#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "mydatastore.h"
#include "new_window.h"
#include "rating_window.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(MyDataStore *ds);
	~MainWindow();

private slots:
	void searchBox();
	void AndSelection();
	void OrSelection();
	void setUser(int index);
	void sortBy(int index);
	void addCart();
	void openCartWindow();
	void showPopup();
	void sortReviews(int index);
	void save();
	void addReview();
	void refreshReview();
	void showReview(int index);

private:
	// // UI

	//Layout
	QVBoxLayout* overallLayout;

	//searchbox
	QHBoxLayout* searchLayout;
	QLineEdit* searchField;
	QLabel* searchLabel;

	QVBoxLayout* searchButtonLayout;
	QRadioButton* orButton;
	QRadioButton* andButton;

	QPushButton* searchButton;

	//search results
	QListWidget* searchResults;
	QHBoxLayout* resultsAndButtons;


	//sortby, add-to-cart, view-cart
	QVBoxLayout* sortAndCartLayout;
	QComboBox* sortByBox;
	QPushButton* addToCartButton;
	QPushButton* viewCartButton;

	//addReview 
	QHBoxLayout* addReviewLayout;
	QPushButton* addReviewButton;

	//select user, save file
	QHBoxLayout* saveLayout;
	QComboBox* selectUser;
	QPushButton* saveButton;

	//reviews
	QHBoxLayout* reviewLayout;
	QVBoxLayout* reviewOptionsLayout;
	QListWidget* reviewResults;
	QComboBox* reviewSort;
	QPushButton* refreshReviews;

	//Cart Window
	NewWindow* new_window;
	RatingWindow* rating_window;


	//data store pointer
	MyDataStore* ds;
	int AndOr;
	User* u;
	std::vector<Product*> searchproducts;
	bool user_picked = false;
	std::map<User*, std::vector<Product*> > cart;
	std::vector<Review*> reviews;
	int currReviewCount;
	int prodindex;
	Product* PROD;
	int currReviewSize;
};