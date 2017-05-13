#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "mydatastore.h"

class RatingWindow : public QWidget
{
	Q_OBJECT
public:
	RatingWindow(MyDataStore *ds, Product* p);
	~RatingWindow();

private slots:
	void submitReview();
	//void getProd(int index);
	void showPopup();
	void reviewPopup();

private:
	// // UI

	//Layout
	QVBoxLayout* overallLayout;

	//product names layout
	//QComboBox* pNames;

	//date layout
	QHBoxLayout* yearLayout;
	QLabel* yearLabel;
	QLineEdit* year;

	QHBoxLayout* monthLayout;
	QLabel* monthLabel;
	QLineEdit* month;

	QHBoxLayout* dayLayout;
	QLabel* dayLabel;
	QLineEdit* day;

	//username layout
	QHBoxLayout* uLayout;
	QLabel* uLabel;
	QLineEdit* username;

	//rating Layout
	QHBoxLayout* ratingLayout;
	QLabel* ratingLabel;
	QLineEdit* rating;

	//reviewText Layout
	QHBoxLayout* rTextLayout;
	QLabel* rTextLabel;
	QLineEdit* rText;

	//submit button
	QPushButton* submitButton;

	//close button
	QPushButton* closeButton;

	//data store pointer
	MyDataStore* ds;
	std::vector<Product*> products;
	Product* p;

};