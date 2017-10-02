#ifndef MOVIE_H
#define MOVIE_H
#include <sstream>
#include <iomanip>
#include <string>
#include "product.h"


class Movie : public Product {
public:

	Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);

    virtual ~Movie();
	/**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;

private:
	string genre_;
	string rating_;
};

#endif