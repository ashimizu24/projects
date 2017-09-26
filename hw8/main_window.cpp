#include "main_window.h"
#include "product.h"
#include "msort.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <QApplication>

MainWindow::MainWindow(MyDataStore& mystore, std::string nameOfUser)
{
	_store = mystore;
	loginWindow = new LoginWindow(_store);
	std::vector<User*> users = _store.get_all_users();
	for(int i=0; (unsigned)i<users.size(); i++){
		if(nameOfUser == users[i]->getName()){
			currUser = users[i];
		}
	}
	

//LOGOUT
	logoutButton = new QPushButton("Logout");

//MAIN WINDOW
	//overall Layout
	overallLayout = new QVBoxLayout();
	title = new QLabel("Amazon");
	QFont titleFont;
      titleFont.setPointSize(25);
      title->setFont(titleFont);
    logoutButton->setMaximumWidth(100);
    overallLayout->addWidget(logoutButton);
    overallLayout->addWidget(title);
    title->setAlignment(Qt::AlignCenter);

    connect(logoutButton, SIGNAL(clicked()), this, SLOT(logout()));

	//Search layout
	searchLayout = new QVBoxLayout();
	overallLayout->addLayout(searchLayout);
	searchInput = new QLineEdit();
	searchAnd = new QRadioButton("AND", this);
	searchOr = new QRadioButton("OR", this);
	searchButton = new QPushButton("Search");
	searchResults = new QListWidget(this);
	searchSortOptions = new QComboBox(this);
	searchSortOptions->addItem("Alphabetically (A-Z)");
	searchSortOptions->addItem("Highest to Lowest Rating");
	searchAnd->toggle();

	searchBoxLayout = new QHBoxLayout();
	searchBoxLayout->addWidget(searchInput);
	searchBoxLayout->addWidget(searchButton); 
	searchLayout->addLayout(searchBoxLayout);

	searchButtonLayout = new QHBoxLayout();
	searchButtonLayout->addWidget(searchAnd);
	searchButtonLayout->addWidget(searchOr);
	searchLayout->addLayout(searchButtonLayout);
	searchButtonLayout->addStretch(1);

	connect(searchAnd, SIGNAL(clicked()), this, SLOT(setSearchAND())); //AND 0
	connect(searchOr, SIGNAL(clicked()), this, SLOT(setSearchOR())); // OR 1
	connect(searchButton, SIGNAL(clicked()), this, SLOT(displaySearch()));
	connect(searchResults, SIGNAL(currentRowChanged(int)), this, SLOT(selectProduct(int)));

	searchLayout->addStretch();

	//Reviews
	reviewLayout = new QVBoxLayout();
	productReview = new QLabel("");
	averageReview = new QLabel("");

	reviewLayout->addWidget(productReview);
	reviewLayout->addWidget(averageReview);

	productReviewLayout = new QHBoxLayout();
	productReviewLayout->addWidget(searchResults);
	recommendationsButton = new QPushButton("View Recommended Products");
	productReviewLayout->addWidget(recommendationsButton);
	productReviewLayout->addLayout(reviewLayout);
	searchLayout->addLayout(productReviewLayout);

	addCartsortLayout = new QHBoxLayout();
	addCartsortLayout->addWidget(searchSortOptions);
	addToCartButton = new QPushButton("Add Product To Cart");
	addCartsortLayout->addWidget(addToCartButton);
	searchLayout->addLayout(addCartsortLayout);
	writeReviewButton = new QPushButton("Write Review");
	addCartsortLayout->addWidget(writeReviewButton);

	connect(searchResults, SIGNAL(currentRowChanged(int)), this, SLOT(reviewDisplay(int)));
	connect(searchSortOptions, SIGNAL(currentIndexChanged(int)), this, SLOT(prodSort(int)));
	//make product results be sorted alphabetically by default
	_sortNum = 0;

	//Username Layout
 	viewcartButton = new QPushButton("Viewcart");
 	overallLayout->addWidget(viewcartButton);
 	saveButton = new QPushButton("Save");
 	quitButton = new QPushButton("Quit");
 	overallLayout->addWidget(saveButton);
 	overallLayout->addWidget(quitButton);

 	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addToCart()));
 	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
 	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitApp()));

//VIEWCART WINDOW
 	QVBoxLayout* viewcartLayout = new QVBoxLayout;
 	viewcartWidget = new QWidget;
 	cartWidget = new QListWidget(this);
	viewcartLayout->addWidget(cartWidget);

	removeButton = new QPushButton("Remove item");
	buycartButton = new QPushButton("Buycart");
	quitViewcartButton = new QPushButton("Close");

	buttons = new QHBoxLayout();
	buttons->addWidget(removeButton);
	buttons->addWidget(buycartButton);
	buttons->addWidget(quitViewcartButton);
	viewcartLayout->addLayout(buttons);
	//making default product in cart the first item
	_removeCurrProd = 1;
	cartWidget->setCurrentRow(1);

	connect(viewcartButton, SIGNAL(clicked()), this, SLOT(openViewcart()));
	connect(quitViewcartButton, SIGNAL(clicked()), this, SLOT(closeViewcart()));
	connect(cartWidget, SIGNAL(currentRowChanged(int)), this, SLOT(selectItemViewCart(int)));
	connect(removeButton, SIGNAL(clicked()), this, SLOT(removeItem()));
	connect(buycartButton, SIGNAL(clicked()), this, SLOT(buycart()));

  	viewcartWidget->setLayout(viewcartLayout);

//ADD REVIEW WINDOW
  	connect(writeReviewButton, SIGNAL(clicked()), this, SLOT(writeReviewButtonClicked()));
  	QVBoxLayout* reviewWindow = new QVBoxLayout();
  	reviewWidget = new QWidget;

	//title
	reviewTitle = new QLabel("Write A Review");
	QFont titleFont2;
      titleFont2.setPointSize(15);
      title->setAlignment(Qt::AlignCenter);
    reviewWindow->addWidget(reviewTitle);

    //calendar
	calendar = new QCalendarWidget();
		calendar->setMinimumDate(QDate(2017, 1, 1));
    	calendar->setMaximumDate(QDate(2030, 1, 1));
    	calendar->setGridVisible(true);
    reviewWindow->addWidget(calendar);
    setDate();
    //create default date
    connect(calendar, SIGNAL(clicked(QDate)), this, SLOT(setDate()));

    //rating product
    rateTitle = new QLabel("Rate Product");
    reviewWindow->addWidget(rateTitle);
    rate1 = new QRadioButton("1");
    rate2 = new QRadioButton("2");
    rate3 = new QRadioButton("3");
    rate4 = new QRadioButton("4");
    rate5 = new QRadioButton("5");
    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(rate1);
    buttonLayout->addWidget(rate2);
    buttonLayout->addWidget(rate3);
    buttonLayout->addWidget(rate4);
    buttonLayout->addWidget(rate5);
    reviewWindow->addLayout(buttonLayout);

    connect(rate1, SIGNAL(clicked()), this, SLOT(setRating1()));
    connect(rate2, SIGNAL(clicked()), this, SLOT(setRating2()));
    connect(rate3, SIGNAL(clicked()), this, SLOT(setRating3()));
    connect(rate4, SIGNAL(clicked()), this, SLOT(setRating4()));
    connect(rate5, SIGNAL(clicked()), this, SLOT(setRating5()));

     //write review
    writeTitle = new QLabel("Write a Review");
    reviewWindow->addWidget(writeTitle);
    reviewText = new QLineEdit();
    reviewWindow->addWidget(reviewText);

    //submit review
    submitButton = new QPushButton("Submit Review");
    reviewWindow->addWidget(submitButton);
    reviewWidget->setLayout(reviewWindow);
    connect(submitButton, SIGNAL(clicked()), this, SLOT(addReview()));

    closeReviewWindowButton = new QPushButton("Close");
    reviewWindow->addWidget(closeReviewWindowButton);
    connect(closeReviewWindowButton, SIGNAL(clicked()), this, SLOT(closeAddReview()));


//PRODUCT RECOMMENDATIONS WINDOW
	recommendationsWidget = new QWidget;
	QVBoxLayout* recommendationsWindow = new QVBoxLayout();
	recommendationsList = new QListWidget(this);
	recommendationsWindow->addWidget(recommendationsList);
	doneButton = new QPushButton("Done");
	recommendationsWindow->addWidget(doneButton);

	recommendationsWidget->setLayout(recommendationsWindow);

	connect(recommendationsButton, SIGNAL(clicked()), this, SLOT(displayRecommendations()));
	connect(doneButton, SIGNAL(clicked()), this, SLOT(closeSuggestions()));

	//Setting overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow(){

}

void MainWindow::displaySearch(){
	if(searchInput->text().isEmpty())
	{ //don't do anything if nothing in search bar was typed
		return;
	}
	if(searchText != searchInput->text().toStdString()){
		searchText = "";
		searchText = searchInput->text().toStdString();
		terms.clear();	//clear the vector of keywords to search for

		stringstream ss(searchText);
		string product;
		while(ss >> product){
			terms.push_back(product);
		}
		hits = _store.search(terms, searchValue);

		//sort the hits - if a button wasn't selected this will make
		//it sorted alphabetically by default
		prodSort(_sortNum);

		showProductSearch();
	}
	else{
		hits = _store.search(terms, searchValue);
		showProductSearch();
	}
}

void MainWindow::showProductSearch(){
	//clear the list widget
	searchResults->clear();
	std::vector<Product*>::iterator it = hits.begin();
	for(; it != hits.end(); ++it){
		std::string info = (*it)->displayString();
		searchResults->addItem(QString::fromStdString(info));
	}
}

void MainWindow::setSearchAND(){
	searchValue = 0;
}

void MainWindow::setSearchOR(){
	searchValue = 1;
}

void MainWindow::reviewDisplay(int productIndex){
	if(currProduct == -1){
		return;
	}
	std::string name = hits[productIndex]->getName();
	std::vector<Review*> product_reviews = _store.searchReview(name);
	Product* p = _store.find_product(name);
	//sort the reviews most to least recent
	reviewComp comp;
	mergeSort(product_reviews, comp);

	if(product_reviews.size() != 0){
		QString reviewText;
		//go through reviews and have them be in one string to look at
			for(int i=0; (unsigned)i<product_reviews.size(); i++){
				Review* r = product_reviews[i];
				int rating = r->rating;
				std::ostringstream os;
				os << rating;
				std::string rating_str = os.str();
	
				reviewText += QString::fromStdString(rating_str);
				reviewText += QString::fromStdString(" ");
				reviewText += QString::fromStdString(r->date);
				reviewText += QString::fromStdString(" ");
				reviewText += QString::fromStdString(r->reviewText);
				reviewText += QString::fromStdString("\n");
				reviewText += QString::fromStdString("\n");
	
			}
			productReview->setText(reviewText);
			double avgRating = p->getAvgRating();
			std::ostringstream os2;
			os2 << avgRating;
			std::string review_str = os2.str();
			QString avgReviewText;
			avgReviewText += QString::fromStdString("Average Rating: ");
			avgReviewText += QString::fromStdString(review_str);
			averageReview->setText(avgReviewText);
		}
		else{
	//if the product doesn't have any reviews, it will just show up as
	//having an average rating of 0
			productReview->setText(QString::fromStdString(" "));
			double avgRating = p->getAvgRating();
			std::ostringstream os2;
			os2 << avgRating;
			std::string review_str = os2.str();
			QString avgReviewText;
			avgReviewText += QString::fromStdString("Average Rating: ");
			avgReviewText += QString::fromStdString(review_str);
			averageReview->setText(avgReviewText);
		}
}

void MainWindow::addToCart(){
	std::string name = currUser->getName();
	_store.add(name, currProduct, hits);
	_cart = _store.get_cart(currUser->getName());
}

void MainWindow::selectProduct(int productIndex){
//when a product is selected it will set it to the product's index in the list widget
	currProduct = productIndex;
}

void MainWindow::prodSort(int sortNum){
	if(sortNum == 0){
		//alphabetical search
		_sortNum = 0;
		prodNameComp comp;
		mergeSort(hits, comp);
		showProductSearch();

	}
	else if(sortNum == 1){
		//average review search
		_sortNum = 1;
		prodReviewComp comp2;
		mergeSort(hits, comp2);
		showProductSearch();
	}
}

void MainWindow::saveFile(){
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
			".", tr("Text (*.txt)"));
	std::ofstream os2(filename.toStdString().c_str());
	_store.dump(os2);
}

void MainWindow::quitApp(){
	QApplication::exit();
}

void MainWindow::writeReviewButtonClicked(){
	if((unsigned)currProduct < hits.size()){
		//change button so once window's open you can't keep clicking
		//because then multiple windows will come up
		writeReviewButton->setEnabled(false);
		reviewWidget->setFixedSize(500,500);
		reviewWidget->show();
	}
}

void MainWindow::setDate(){
	QDate date = calendar->selectedDate();
	int day = date.day();
	int month = date.month();
	int year = date.year();

	std::string inputDate = "";
	std::ostringstream os;
	os << year;
	std::string year_str = os.str();
	inputDate += (year_str + "-");
	os.str("");
	os << month;
	std::string month_str = os.str();
	inputDate += (month_str + "-");
	os.str("");
	os << day;
	std::string day_str = os.str();
	inputDate += (day_str);
	_date = inputDate;
}

void MainWindow::setRating1(){
	_rating = 1;
}
void MainWindow::setRating2(){
	_rating = 2;
}
void MainWindow::setRating3(){
	_rating = 3;
}
void MainWindow::setRating4(){
	_rating = 4;
}
void MainWindow::setRating5(){
	_rating = 5;
}

void MainWindow::readReview(){
	if(reviewText->text().isEmpty())
	{
		return;
	}
	_text = reviewText->text().toStdString();
}

void MainWindow::addReview(){
	readReview();
	if(_text.empty()){
		return;
	}
	else if(_rating < 1){
		return;
	}
	else{
		Review* add = new Review(hits[currProduct]->getName(), _rating, currUser->getName(), _date, _text);
		_store.addReview(add);
	}
}

void MainWindow::closeAddReview(){
	writeReviewButton->setEnabled(true);
	reviewWidget->hide();
//re-set window so when write a review is opened again there's no text
	reviewText->setText("");
	reviewDisplay(currProduct);
}

void MainWindow::openViewcart(){
	viewcartButton->setEnabled(false);
	viewcartWidget->setFixedSize(500,500);
	viewcartWidget->show();
	setupWindow();
}

void MainWindow::setupWindow(){
//When viewcart opens have the products of the cart on the screen
	for(int i=0; (unsigned)i<_cart.size(); i++){
		std::string itemName = _cart[i]->displayString();
		cartWidget->addItem(QString::fromStdString(itemName));
	}
}

void MainWindow::selectItemViewCart(int item){
//when item in cart is selected, make that the current product
	_removeCurrProd = item;
}

void MainWindow::removeItem(){
	if(_removeCurrProd >= 0 && _cart.size() != 0){
		_cart.erase(_cart.begin() + _removeCurrProd);
	}
//"re-load" the window to show cart with removed item
	cartWidget->clear();
	setupWindow();
}

void MainWindow::buycart(){
	_store.buy(currUser->getName());
	//"re-load" the cart showing the products still in the user's cart
	//that weren't bought
	_cart = _store.get_cart(currUser->getName());
	cartWidget->clear();
	setupWindow();
}

void MainWindow::closeViewcart(){
	//change button so you're able to click it again
	viewcartButton->setEnabled(true);
	viewcartWidget->hide();
	cartWidget->clear();
}

void MainWindow::displayRecommendations(){
	std::vector<std::pair<std::string, double> > suggestions = _store.makeSuggestion(currUser->getName());
	suggestionsComp comp;
	mergeSort(suggestions, comp);

	std::ofstream file("rec.txt");
    std::string products = "";
	products += currUser->getName();

	//if there are suggestions
	if(suggestions.size() > 0){
		recommendationsButton->setEnabled(false);
		recommendationsWidget->setFixedSize(500,500);
		recommendationsWidget->show();

		recommendationsList->clear();
		products += "\n";

		for(int i=0; (unsigned)i<suggestions.size(); i++){
			std::string info = "";
			double rating = suggestions[i].second;
			std::ostringstream os;
			os << setprecision(3) << rating;
			std::string rating_str = os.str();
			info += rating_str;
			products += rating_str;
			info += " ";
			products += " ";
			info += suggestions[i].first;
			products += suggestions[i].first;
			products += "\n";
			recommendationsList->addItem(QString::fromStdString(info));
		}
	}
	else{
		
		QMessageBox::information(this, "Product Recommendations", "No recommendations available");
	}

    file << products;
}

void MainWindow::logout(){
	this->hide();
	loginWindow->show();
}

void MainWindow::closeSuggestions(){
	recommendationsButton->setEnabled(true);
	recommendationsWidget->hide();
}

