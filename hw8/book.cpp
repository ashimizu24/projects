#include <sstream>
#include <iomanip>
#include <string>
#include "product.h"
#include "util.h"
#include "book.h"


Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) : 
	Product(category, name, price, qty), 
	isbn_(isbn), 
	author_(author)
{
}

Book::~Book(){
}

/**
* Returns the appropriate keywords that this product should be associated with
*/
std::set<std::string> Book::keywords() const{
	std::set<std::string> key = parseStringToWords(name_);
	std::set<std::string> temp = parseStringToWords(author_);
	for(std::set<std::string>::iterator it = temp.begin(); it!=temp.end(); ++it){
		key.insert(*it);
	}
	key.insert(isbn_);

	return key;
}

/**
* Returns a string to display the product info for hits of the search
*/
std::string Book::displayString() const{
	std::string info = ""+this->name_+"\n"+"Author: "+this->author_+" ISBN: "+this->isbn_+"\n";
	double p = getPrice();
	stringstream ss;
    ss << p;
    std::string actual_p(ss.str());
    stringstream s;
	int q = getQty();
	s << q;
    std::string actual_q(s.str());
	info += (actual_p+" "+actual_q+" left.");

	return info;
}

/**
* Outputs the product info in the database format
*/
 void Book::dump(std::ostream& os) const{
 	os << "book" << endl << name_ << endl << price_ << endl;
 	os << qty_ << endl << isbn_ << endl << author_ << endl;
 }