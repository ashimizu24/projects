#include <sstream>
#include <iomanip>
#include <string>
#include "product.h"
#include "util.h"
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) : 
    Product(category, name, price, qty), 
    genre_(genre), 
    rating_(rating)
{

}

Movie::~Movie(){
}
    /**
     * Returns the appropriate keywords that this product should be associated with
     */

std::set<std::string> Movie::keywords() const{
        set<string> key = parseStringToWords(name_);
        set<string> temp = parseStringToWords(genre_);
        for(set<string>::iterator it = temp.begin(); it!=temp.end(); ++it){
            key.insert(*it);
        }

        return key;
    }

    /**
     * Returns a string to display the product info for hits of the search
     */
std::string Movie::displayString() const{
        stringstream ss;
        stringstream s;
        string info = ""+name_+"\n"+"Genre: "+genre_+" Rating: "+rating_+"\n";
        double p = getPrice();
        ss << p; 
        string actual_p(ss.str());
        info += actual_p+" ";
        int q = getQty();
        s << q;
        string actual_q(s.str());
        info += actual_q+" left.";
        
        return info;
    }

    /**
     * Outputs the product info in the database format
     */
void Movie::dump(std::ostream& os) const{
        os << "movie" << endl << name_ << endl << price_ << endl;
        os << qty_ << endl << genre_ << endl << rating_ << endl;
    }