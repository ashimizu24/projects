#include <sstream>
#include <iomanip>
#include <string>
#include "product.h"
#include "util.h"
#include "clothing.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : 
	Product(category, name, price, qty), 
	size_(size), 
	brand_(brand)
{

}

Clothing::~Clothing(){
}

	/**
     * Returns the appropriate keywords that this product should be associated with
     */
std::set<std::string> Clothing::keywords() const{
    	std::set<std::string> key = parseStringToWords(name_);
		std::set<std::string> temp = parseStringToWords(brand_);
		for(std::set<std::string>::iterator it = temp.begin(); it!=temp.end(); ++it){
			key.insert(*it);
		}
		return key;
}

    /**
     * Returns a string to display the product info for hits of the search
     */
std::string Clothing::displayString() const{
    	std::string info = ""+name_+"\n"+"Brand: "+brand_+" Size: "+size_+"\n";
		double p = getPrice();
		stringstream ss;
	    ss << p;
	    string actual_p(ss.str());
	    stringstream s;
		int q = getQty();
		s << q;
	    string actual_q(s.str());
		info += (actual_p+" "+actual_q+" left.");

		return info;
}

    /**
     * Outputs the product info in the database format
     */void Clothing::dump(std::ostream& os) const{
    	os << "clothing" << endl << name_ << endl << price_ << endl;
 		os << qty_ << endl << size_ << endl << brand_ << endl;
}
