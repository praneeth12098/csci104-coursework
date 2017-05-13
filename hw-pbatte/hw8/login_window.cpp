#include "login_window.h"

LoginWindow::LoginWindow(MyDataStore *ds)
{
	setWindowTitle("Login Window");

	//data store initialization
	this->ds = ds;
	//newUser = 0;

	//mW = new MainWindow(ds, currentUser);

	//overall layout
	overallayout = new QVBoxLayout();

	//user name layout
	userEntryLayout = new QHBoxLayout();
	overallayout->addLayout(userEntryLayout);

	//user entry fields
	uName = new QLabel("Username: ");
	userEntryLayout->addWidget(uName);

	userEntry = new QLineEdit();
	userEntryLayout->addWidget(userEntry);

	//password layout
	passwordEntryLayout = new QHBoxLayout();
	overallayout->addLayout(passwordEntryLayout);

	//password entry fields
	pWord = new QLabel("Password: ");
	passwordEntryLayout->addWidget(pWord);

	passwordEntry = new QLineEdit();
	passwordEntryLayout->addWidget(passwordEntry);

	//logInButton
	logInButton = new QPushButton("Log In");
	connect(logInButton, SIGNAL(clicked()), this, SLOT(logIn()));
	overallayout->addWidget(logInButton);

	//New User Option
	newUserButton = new QPushButton("New User");
	connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUser()));
	overallayout->addWidget(newUserButton);

	//quit button
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitWindow()));
	overallayout->addWidget(quitButton);



	setLayout(overallayout);
}

LoginWindow::~LoginWindow()
{
	delete ds;
}

void LoginWindow::newUser()
{ 
	std::vector<User*> tempusers = ds->getUsernames();

	if(userEntry->text().isEmpty()) return;
	if(passwordEntry->text().isEmpty()) return;

	std::string username = userEntry->text().toStdString();
	std::string password = passwordEntry->text().toStdString();
	unsigned long long pass = hash_function(password);


	std::vector<User*>::iterator uit = tempusers.begin();

	bool userFound = false;
	bool passOkay = false;
	for(; uit != tempusers.end(); ++uit)
	{
		std::string tempUserName = (*uit)->getName();
		if(tempUserName == username) userFound = true;
	}
	if(userFound)
	{
		QMessageBox errorMsg(this);
		errorMsg.setText("Username Already Exists");
		errorMsg.exec();

		userEntry->clear();
		passwordEntry->clear();
	}

	if(password.length() > 8)
	{
		QMessageBox errorMsg(this);
		errorMsg.setText("Password Greater than 8 Characters");
		errorMsg.exec();

		userEntry->clear();
		passwordEntry->clear();
	}
	else
	{
		passOkay = true;
	}

	if(!userFound && passOkay)
	{
		User* u = new User(username, 100, 0, pass);
		currentUser = u;
		ds->addUser(currentUser);

		this->close();
		mW = new MainWindow(ds, currentUser);
		mW->show();
	}
}

void LoginWindow::quitWindow()
{
	this->close();
}

void LoginWindow::logIn()
{
	std::vector<User*> tempusers = ds->getUsernames();

	if(userEntry->text().isEmpty()) return;
	if(passwordEntry->text().isEmpty()) return;

	std::string username = userEntry->text().toStdString();
	std::string password = passwordEntry->text().toStdString();
	unsigned long long pass = hash_function(password);


	std::vector<User*>::iterator uit = tempusers.begin();

	bool userFound = false;
	bool correctpass = false;
	for(; uit != tempusers.end(); ++uit)
	{
		std::string tempUserName = (*uit)->getName();
		if(tempUserName == username)
		{
			userFound = true;
			currentUser = (*uit);
			unsigned long long tempPass = (*uit)->getPassword();
			if(tempPass == pass)
			{
				correctpass = true;
			}
			else
			{
				QMessageBox errorMsg(this);
				errorMsg.setText("Incorrect Password");
				errorMsg.exec();

				passwordEntry->clear();
			}
		}
	}
	if(!userFound)
	{
		QMessageBox errorMsg(this);
		errorMsg.setText("Incorrect Username");
		errorMsg.exec();

		userEntry->clear();
	}

	if(userFound && correctpass)
	{
		this->close();
		mW = new MainWindow(ds, currentUser);
		mW->show();
	}
}

unsigned long long LoginWindow::hash_function(std::string password)
{
	std::vector<int> char_values;
	std::string::iterator it = password.begin();

	for(; it != password.end(); ++it)
	{
		char letter = *it;
		int val = int (letter);	
		char_values.push_back(val);
	}

	unsigned long long value = 0;

	for(unsigned i = 0; i < password.size(); i++)
	{
		long long e = pow(128, i);
		value += (char_values[char_values.size()-1-i])*e;
	}
	
	unsigned int digits[4];

	digits[3] = value % 65521;
   	digits[2] = (value/65521) % 65521;
	digits[1] = (value/65521/65521) % 65521;
	digits[0] = (value/65521/65521/65521) % 65521;

	unsigned long long result = (45912*digits[0] + 35511*digits[1] + 65169*digits[2] + 4625*digits[3]) % 65521;

	return result;
}