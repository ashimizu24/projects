#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "map"
#include "util.h"


class MyDataStore : public DataStore {
public:
    MyDataStore();

    virtual ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);

    /**
    * Adds a review
    */
    virtual void addReview(Review* r);

    virtual std::vector<Review*> searchReview(std::string name);

    void add(std::string username, int search_num, std::vector<Product*> product_hits);

    void view(std::string username);

    void buy(std::string username);

    void clean();

    std::vector<User*> get_all_users() const;

    std::vector<Product*> get_cart(std::string username);

    Product* find_product(std::string username);

    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);

    std::vector<Review*> get_user_reviews(std::string username);

    int find_rating(std::string product_name, std::string username);

    double basicSimilarity(std::string currentUser, std::string user);


private:
	std::map<std::string, std::set<Product*> > all_keywords;
	std::vector<Product*> all_products;
	std::vector<User*> all_users;
    std::map<std::string, std::vector<Review*> > reviews;
    std::map<std::string, std::vector<Review*> > user_reviews;
	map<std::string, std::vector<Product*> > users; //map of each user's cart
};

#endif