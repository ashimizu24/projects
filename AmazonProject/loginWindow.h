#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "mydatastore.h"
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QListWidget>
#include <QComboBox>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>

class LoginWindow : public QWidget
{
	Q_OBJECT
public:
	LoginWindow(MyDataStore& mystore);																																																																																																								
	~LoginWindow();
	unsigned long long hasherFunc(std::string password);

public slots:
	void login();
	void showMain();
	void quit();
	void createUser();
	void showCreateUser();
	void closeCreateUser();

private:
	QVBoxLayout* overallLayout;
	QLabel* title;

	QLabel* usernameTitle;
	QLineEdit* username;
	QLabel* passwordTitle;
	QLineEdit* password;

	QHBoxLayout* buttonLayout;
	QPushButton* loginButton;
	QPushButton* addUserButton;
	QPushButton* quitButton;


//ADD USER
	QWidget* addUserWidget;
	QLabel* addUserTitle;
	QLabel* addNameTitle;
	QLabel* addPasswordTitle;
	QLineEdit* add_username;
	QLineEdit* add_password;
	QPushButton* createButton;
	QPushButton* closeCreateUserButton;


	MyDataStore _store;
	std::string currUser;
};

#endif