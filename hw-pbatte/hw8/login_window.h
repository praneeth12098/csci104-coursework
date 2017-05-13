#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>


#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "mydatastore.h"
#include "main_window.h"

class LoginWindow : public QWidget
{
	Q_OBJECT
public:
	LoginWindow(MyDataStore *ds);
	~LoginWindow();

private slots:
	void newUser();
	void logIn();
	void quitWindow();

private:
	// // UI

	//Layout
	QVBoxLayout* overallayout;

	//User name entry
	QHBoxLayout* userEntryLayout;
	QLabel* uName;
	QLineEdit* userEntry;

	//Password entry
	QHBoxLayout* passwordEntryLayout;
	QLabel* pWord;
	QLineEdit* passwordEntry;

	//New User Option
	QPushButton* newUserCheck;

	//logIn Button
	QPushButton* logInButton;

	//newUser Button
	QPushButton* newUserButton;

	//Quit Button
	QPushButton* quitButton;

	//main window
	MainWindow* mW;

	//private methods
	unsigned long long hash_function(std::string password);


	//MyDataStore pointer
	MyDataStore* ds;
	User* currentUser;
	///int newUser;
	//std::vector<User*> userList;
};