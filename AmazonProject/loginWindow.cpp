#include "loginWindow.h"
#include "heap.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <QApplication>
#include <QMessageBox>

#include "main_window.h"

unsigned long long LoginWindow::hasherFunc(std::string password){
    unsigned long long value = 0;

    if(password.length() > 8) return -1; //invalid size
    int p=0;
    for(int i = password.length()-1; i>=0; i--){
        value += ((unsigned long long)pow(128,p)) * (unsigned long long)(int)password[i];
        p++;

    }

    unsigned int wNum[4];

    int j = 3;
    while(j >= 0){
        wNum[j] = value % 65521;
        value = value / 65521;
        j--;
    }

    value = (45912 * wNum[0] + 35511 * wNum[1] + 65169 * wNum[2] + 4625 * wNum[3]) % 65521;

    return value;
}


LoginWindow::LoginWindow(MyDataStore& mystore){
	_store = mystore;

	overallLayout = new QVBoxLayout();
	title = new QLabel("Log into your Amazon Account");
	QFont titleFont;
      titleFont.setPointSize(25);
      title->setFont(titleFont);
    overallLayout->addWidget(title);
    title->setAlignment(Qt::AlignCenter);

    usernameTitle = new QLabel("Username");
    username = new QLineEdit();
    overallLayout->addWidget(usernameTitle);
    overallLayout->addWidget(username);

    passwordTitle = new QLabel("Password");
    password = new QLineEdit();
    overallLayout->addWidget(passwordTitle);
    overallLayout->addWidget(password);

    buttonLayout = new QHBoxLayout();
    loginButton = new QPushButton("Login");
    addUserButton = new QPushButton("Create New User");
    quitButton = new QPushButton("Quit");
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(addUserButton);
    buttonLayout->addWidget(quitButton);
    overallLayout->addLayout(buttonLayout);

    connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(addUserButton, SIGNAL(clicked()), this, SLOT(showCreateUser()));

    addUserWidget = new QWidget;
    QVBoxLayout* addUserLayout = new QVBoxLayout();
    addUserTitle = new QLabel("Create New User");
    titleFont.setPointSize(15);
    addUserLayout->addWidget(addUserTitle);
    addUserTitle->setAlignment(Qt::AlignCenter);

    addNameTitle = new QLabel("Username");
    addUserLayout->addWidget(addNameTitle);
    add_username = new QLineEdit();
    addUserLayout->addWidget(add_username);
    addPasswordTitle = new QLabel("Password");
    addUserLayout->addWidget(addPasswordTitle);
    add_password = new QLineEdit();
    addUserLayout->addWidget(add_password);
    createButton = new QPushButton("Create User");
    addUserLayout->addWidget(createButton);
    closeCreateUserButton = new QPushButton("Close");
    addUserLayout->addWidget(closeCreateUserButton);

    connect(createButton, SIGNAL(clicked()), this, SLOT(createUser()));
    connect(closeCreateUserButton, SIGNAL(clicked()), this, SLOT(closeCreateUser()));

    addUserWidget->setLayout(addUserLayout);

    setLayout(overallLayout);

}

LoginWindow::~LoginWindow(){

}

void LoginWindow::showMain(){
	MainWindow* mainWindow = new MainWindow(_store, currUser);
    mainWindow->show();
    mainWindow->setFixedWidth(1000);
    this->hide();
}

void LoginWindow::login(){
	if(username->text().isEmpty() || password->text().isEmpty())
	{
		return;
	}

	string _username = username->text().toStdString();
	string _password = password->text().toStdString();

	//finding the user
	std::vector<User*> all_users = _store.get_all_users();
	User* user;
	bool successful = false;
	for(int i=0; (unsigned)i<all_users.size(); i++){
		if(all_users[i]->getName() == _username){ //user is valid
			user = all_users[i];
			unsigned long long code = hasherFunc(_password);
			if(code == user->getCode()){
				currUser = all_users[i]->getName();
				showMain();
			}
            if(!successful){
                QMessageBox::information(this, "Login Attempt", "Login Failed!");
                username->setText(QString::fromStdString(" "));
                password->setText(QString::fromStdString(" "));
            }
			successful = true;
			break;
		}
	}	

	if(!successful){
		QMessageBox::information(this, "Login Attempt", "Login Failed!");
        username->setText(QString::fromStdString(" "));
        password->setText(QString::fromStdString(" "));
	}
}

void LoginWindow::quit(){
    this->close();
}

void LoginWindow::showCreateUser(){
    addUserWidget->show();
    this->hide();
}

void LoginWindow::createUser(){
    if(add_username->text().isEmpty() || add_password->text().isEmpty())
    {
        return;
    }

    string _username = add_username->text().toStdString();
    std::vector<User*> all_users = _store.get_all_users();
    for(int i=0; (unsigned)i<all_users.size(); i++){
        if(all_users[i]->getName() == _username){ //user is valid
            QMessageBox::information(this, "Attempt to Create New User", "Username already exists");
            add_username->setText(QString::fromStdString(" "));
            add_password->setText(QString::fromStdString(" "));
            return;
        }
    }   

    std::string _password = add_password->text().toStdString();
    if(_password.size() > 8){
        QMessageBox::information(this, "Password Attempt", "Password must not exceed 8 characters");
        add_username->setText(QString::fromStdString(" "));
        add_password->setText(QString::fromStdString(" "));
        return;
    }

    unsigned long long userCode = hasherFunc(_password);
    User* createdUser = new User(_username, 100.00, 0, userCode);
    _store.addUser(createdUser);
    currUser = _username;
    showMain();
    addUserWidget->hide();
}   

void LoginWindow::closeCreateUser(){
    addUserWidget->hide();
    this->show();
}