#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mydatastore.h"
#include "product.h"
#include "loginWindow.h"
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

#include <QCalendarWidget>
#include <QDate>

#include <vector>

class MainWindow : public QWidget
{
	Q_OBJECT
public:

	MainWindow(MyDataStore& mystore, std::string nameOfUser);
	~MainWindow();

private slots:
	void logout();

	void displaySearch();
	void setSearchAND();
	void setSearchOR();
	void reviewDisplay(int productIndex);
	void selectProduct(int productIndex);
	void addToCart();
	void prodSort(int sortNum);
	void showProductSearch();
	void saveFile();
	void quitApp();

//VIEWCART
	void setupWindow();
	void closeViewcart();
	void selectItemViewCart(int item);
	void removeItem();
	void buycart();
	void openViewcart();

//ADD REVIEW
	void writeReviewButtonClicked();
	void setDate();
	void setRating1();
	void setRating2();
	void setRating3();
	void setRating4();
	void setRating5();
	void readReview();
	void addReview();
	void closeAddReview();

//RECOMMENDATIONS
	void displayRecommendations();
	void closeSuggestions();

private:
	//Layouts
	QVBoxLayout* overallLayout;

	//Search Layouts
	QVBoxLayout* searchLayout;
	QHBoxLayout* searchBoxLayout;
	QHBoxLayout* searchButtonLayout;
	QHBoxLayout* productReviewLayout;
	QHBoxLayout* addCartsortLayout;
	QLabel* title;
	QLineEdit* searchInput;
	QRadioButton* searchAnd;
	QRadioButton* searchOr;
	QPushButton* searchButton;
	QListWidget* searchResults;
	QComboBox* searchSortOptions;

	//List of Reviews Layout
	QVBoxLayout* reviewLayout;
	QLabel* productReview;
	QLabel* averageReview;
	QPushButton* writeReviewButton;

 	//Username Layout
 	QListWidget* allUsers;
 	QPushButton* addToCartButton;
 	QPushButton* viewcartButton;

 	//Exiting Layout
 	QVBoxLayout* exitingLayout;
 	QHBoxLayout* fileLayout;
 	QLineEdit* outputFilename;
 	QPushButton* saveButton;
 	QPushButton* quitButton;


//VIEWCART
 	QWidget* viewcartWidget;
 	QListWidget* cartWidget;
	QHBoxLayout* buttons;
	QPushButton* removeButton;
	QPushButton* buycartButton;
	QPushButton* quitViewcartButton;
	int _removeCurrProd;

//ADD REVIEW
	QLabel* reviewTitle;
	QWidget* reviewWidget;
	QCalendarWidget* calendar;
	std::string _date;
	QLabel* rateTitle;
	QHBoxLayout* buttonLayout;
	QRadioButton* rate1;
	QRadioButton* rate2;
	QRadioButton* rate3;
	QRadioButton* rate4;
	QRadioButton* rate5;
	int _rating;
	QLabel* writeTitle;
	QLineEdit* reviewText;
	QPushButton* submitButton;
	std::string _text;
	QPushButton* closeReviewWindowButton;

//PRODUCT RECOMMENDATIONS
	QPushButton* recommendationsButton;
	QWidget* recommendationsWidget;
	QListWidget* recommendationsList;
	QPushButton* doneButton;

//LOGIN
	QPushButton* logoutButton;
	LoginWindow* loginWindow;



//MAIN WINDOW DATA MEMBERS
 	
 	MyDataStore _store;
 	std::vector<Product*> hits;
 	std::vector<std::string> terms;
 	User* currUser;
 	int currProduct;
 	int searchValue;
 	int _sortNum;
 	std::vector<Product*> _cart;
 	std::string searchText;
};

#endif