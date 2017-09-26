#include <string>
#include <set>
#include <vector>
#include <cmath>
#include <iostream>
#include "heap.h"
#include "product.h"
#include "user.h"
#include "mydatastore.h"
#include "map"
#include "util.h"
#include "msort.h"

using namespace std;

MyDataStore::MyDataStore(){
}

MyDataStore::~MyDataStore(){
	for(int i=0; (unsigned)i<all_products.size(); i++){
		delete all_products[i];
	}
	for(int j=0; (unsigned)j<all_users.size(); j++){
		delete all_users[j];
	}
	reviews.clear();
	user_reviews.clear();
}

    /**
     * Adds a product to the data store
     */
void MyDataStore::addProduct(Product* p){
	set<string> p_key = p->keywords();
	set<string>::iterator it = p_key.begin();
	//iterate through all the keywords of the product and add them to the map
	for(; it != p_key.end(); ++it){
		map<string, set<Product*> >::iterator mit = all_keywords.find(*it);
		if(mit == all_keywords.end()){ //keyword doesn't already exist
			set<Product*> s1;
			s1.insert(p);
			all_keywords.insert(make_pair(*it, s1));
		}
		else{
			mit->second.insert(p);
		}
	}

	all_products.push_back(p);
}

    /**
     * Adds a user to the data store
     */
void MyDataStore::addUser(User* u){
	vector<Product*> cart;
	users.insert(make_pair(u->getName(), cart));

	all_users.push_back(u);
}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	vector<Product*> searches;
	set<Product*> both_terms;
	set<Product*> term1;
	set<Product*> term2;
	string word = "";
		
	int count = 0;
	for(int i=0; (unsigned int)i<terms.size(); i++){
		word = terms[i];
		word = convToLower(word);
		map<string, set<Product*> >::iterator it = all_keywords.find(word);
		bool notFound = false;
		int notFoundAdd = -1;
		if(it == all_keywords.end()){ //one of the terms doesn't exist as a keyword
			//still account for the word, but since it doesn't exist as a keyword 
			//we have to search in a different way 
			if(terms.size() == 1){
				break;
			} 
			notFound = true;
			if(i==0){
				notFoundAdd = 0;
				count++;
			}
			else{
				notFoundAdd = 1;
				count++;
			}
		}
		else{
			if(i == 0){ // beginning
				term1 = it->second;
				count++;
				if(terms.size() == 1){
					//if there's only 1 term, search with itself
					if(type == 1){
						both_terms = setUnion(term1, term1);
					}
					if(type == 0){
						both_terms = setIntersection(term1, term1);
					}
					break;
				}
			}
			else if(i == 1){
				term2 = it->second;
				count++;
			}
			else{
				term2 = it->second;
				count++;
			}
		}

		if(count == 2){
			//search when you've looked at 2 terms
			if(type == 1){
				if(notFound == true){
					//search differently if a term didn't exist
					if(notFoundAdd==0){
						both_terms = setUnion(term2, term2);
						term1 = both_terms;
					}
					else if(notFoundAdd==1){
						both_terms = setUnion(term1, term1);
						term1 = both_terms;
					}
				}
				else{
					both_terms = setUnion(term1, term2);
					term1 = both_terms;
				}
			}
			if(type == 0){
				both_terms = setIntersection(term1, term2);
				term1 = both_terms;
			}
			count = 1;
		}
	//}
	}

	set<Product*>::iterator u = both_terms.begin();
	for(; u!= both_terms.end(); ++u){
		searches.push_back(*u);
	}
	return searches;
}

    /**
     * Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << "\n";
	for(int i=0; (unsigned)i<all_products.size(); i++){
		all_products[i]->dump(ofile);
	}
	ofile << "</products>" << "\n" << "<users>" << "\n";
	for(int i=0; (unsigned)i<all_users.size(); i++){
		all_users[i]->dump(ofile);
	}
	ofile << "</users>" << "\n" << "<reviews>" << "\n";
	map<string, vector<Review*> >::iterator it = reviews.begin();
	for(; it != reviews.end(); ++it){
		vector<Review*> prod_rev = it->second;
		for(int i=0; (unsigned)i<prod_rev.size(); i++){
			Review* r = prod_rev[i];
			ofile << r->prodName << "\n";
			ofile << r->rating << " " << r->username << " " << r->date << " " << r->reviewText << "\n";
		}
	}
	ofile << "</reviews>";
}

void MyDataStore::add(std::string username, int search_num, vector<Product*> product_hits){
	//search_num = search_num -1;
	map<string, vector<Product*> >::iterator it = users.find(username);
	if(it == users.end()){ //invalid user
		cout << "Invalid request user" << endl;
		return;
	}
	else if(product_hits.size() == 0){ //no previous searches
		cout << "Invalid request size" << endl;
		return;
	}
	else if(search_num < 0 || (unsigned)search_num >= product_hits.size()){ //is search_num isn't in hits
		cout << "Invalid request not in hits" << endl;
		return;
	}
	else{ //add product to user's cart
		Product* p = product_hits[search_num];
		it->second.push_back(p);
	}
}

void MyDataStore::view(std:: string username){
	map<string, vector<Product*> >::iterator it = users.find(username);
	if(it == users.end()){ //invalid user
		cout << "Invalid request" << endl;
		return;
	}
	else{
		vector<Product*> cart = it->second;
		for(int i=0; (unsigned)i<cart.size(); i++){
			cout << cart[i]->displayString() << endl;
		}
	}
}

void MyDataStore::buy(std::string username){
	map<string, vector<Product*> >::iterator it = users.find(username);

		User* person = all_users[0];
		for(int j=0; (unsigned)j<all_users.size(); j++){
			if(all_users[j]->getName() == username){
				person = all_users[j];
				break;
			}
		}

		vector<Product*>& cart = it->second;
		for(int i=0; (unsigned)i<cart.size(); i++){
			Product* p = cart[i];
			if(p->getQty() == 0){
			} //not in stock
			else if(p->getPrice() > person->getBalance()){
			}//doesn't have enough money
			else{
				cart.erase(cart.begin()+i);
				p->subtractQty(1);
				person->deductAmount(p->getPrice());
				i--;
			}
		}
	}


void MyDataStore::addReview(Review* r){
	std::string name = r->prodName;
	map<string, vector<Review*> >::iterator it = reviews.find(name);
	if(it != reviews.end()){ //product already has a review
		it->second.push_back(r);
	}
	else{
		vector<Review*> added_prod;
		added_prod.push_back(r);
		reviews.insert(make_pair(name, added_prod));
	}

	double avg = 0.0;
	map<string, vector<Review*> >::iterator it2 = reviews.find(name);
    std::vector<Review*> p1review = it2->second;
    for(int i=0; (unsigned)i<p1review.size(); i++){
    	avg = avg + p1review[i]->rating;
    }
    avg = avg/(double)p1review.size();

    for(int j=0; (unsigned)j<all_products.size(); j++){
    	if(all_products[j]->getName() == name){
    		all_products[j]->setAvgRating(avg);
    		break;
    	}
    }

    std::string user = r->username;
    map<string, vector<Review*> >::iterator it3 = user_reviews.find(user);
	if(it3 != user_reviews.end()){ //user has already written review
		it3->second.push_back(r);
	}
	else{
		vector<Review*> added_prod_;
		added_prod_.push_back(r);
		user_reviews.insert(make_pair(user, added_prod_));
	}
}

std::vector<Review*> MyDataStore::searchReview(std::string name){
	std::vector<Review*> r;
	map<std::string, std::vector<Review*> >::iterator it = reviews.find(name);
	if(it != reviews.end()){
		return it->second;
	}
	return r;
}

std::vector<User*> MyDataStore::get_all_users() const{
	return all_users;
}

std::vector<Product*> MyDataStore::get_cart(std::string username){
	map<std::string, std::vector<Product*> >::iterator it = users.find(username);
	vector<Product*> p;
	if(it != users.end()){
		return it->second;
	}
	return p;
}

Product* MyDataStore::find_product(std::string username){
	for(int i=0; (unsigned)i<all_products.size(); i++){
		if(all_products[i]->getName() == username){
			return all_products[i];
		}
	}
	Product* p = all_products[0];
	return p;
}

double MyDataStore::basicSimilarity(std::string currentUser, std::string user){
	std::set<std::string> currUser;
	std::vector<Review*> currUserReviews = get_user_reviews(currentUser);
	for(int i=0; (unsigned)i<currUserReviews.size(); i++){
		currUser.insert(currUserReviews[i]->prodName);
	}

//basic similarities s(B,A)
	std::set<std::string> user_set;
	std::vector<Review*> currentReviews = get_user_reviews(user);
	for(int i=0; (unsigned)i<currentReviews.size(); i++){
		user_set.insert(currentReviews[i]->prodName);
	}

	double similarity = 0.0;
	std::set<std::string> intersectionUsers = setIntersection(currUser, user_set);
	
	if(intersectionUsers.size() > 0){ //non-empty set
		std::set<std::string>::iterator userIt = intersectionUsers.begin();
		for(; userIt != intersectionUsers.end(); ++userIt){
			similarity += (double)(fabs(find_rating(*userIt, user) - find_rating(*userIt, currentUser))/4);
		}
		similarity = similarity/(double)intersectionUsers.size();
	}
	else similarity = 1.0; //basic similary 1 for empty sets

	return similarity;
}


std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser){
	std::vector<std::pair<std::string, double> > possible_products;
	std::map<std::string, double> userSimilarities;
	std::map<std::string, std::map<std::string, double> > neighbors;

	//if user has already reviewed all the products, return an empty vector
	if(get_user_reviews(currentUser).size() == all_products.size() || get_user_reviews(currentUser).size() == 0){
		return possible_products;
	}

	//building graph - finding connections of all users 
	for(int i=0; (unsigned)i<all_users.size(); i++){
	   std::string user_name = all_users[i]->getName();
	   std::map<std::string, double> userSimilarities;
	   
	   for(int j=0; (unsigned)j<all_users.size(); j++){
		   	std::string neighbor = all_users[j]->getName();
		   	if(neighbor != user_name){
		   		double similarity = basicSimilarity(user_name, neighbor);
	      		userSimilarities.insert(make_pair(neighbor, similarity));
		   	}
		}

	   neighbors.insert(make_pair(user_name, userSimilarities));
	}

	//initializing shortest path map
	std::map<std::string, double> shortestPath; //the final shortest path from current user
	shortestPath.insert(make_pair(currentUser, 0.0));
	//currentUser's immediate neighbors to know who has gone into the heap
	std::map<std::string, double> pathToCurrUser = (neighbors.find(currentUser))->second; 
	std::map<std::string, double> priorities; //all user's current priority to the currentUser
	priorities.insert(make_pair(currentUser, 0));
	std::map<std::string, double>::iterator it = pathToCurrUser.begin();
	for(; it != pathToCurrUser.end(); ++it){
		priorities.insert(make_pair(it->first, 1.0));
	}

	//Dijkstra
	Heap<std::string> heap;
	std::set<std::string> inHeap;
	heap.push(0, currentUser);
	inHeap.insert(currentUser);
	while(!heap.empty()){
		std::string top_user = heap.top();
		double top_priority = priorities.find(top_user)->second;
		shortestPath.insert(make_pair(top_user, top_priority));
		std::vector<Review*> userReviews = get_user_reviews(top_user);
	   	for(int j=0; (unsigned)j<userReviews.size(); j++){
	   		std::vector<Review*> prodReviews = searchReview(userReviews[j]->prodName);
	   		for(int k=0; (unsigned)k<prodReviews.size(); k++){
	   			std::string user_friend = prodReviews[k]->username;
		   		//looking at map of all users and their neighbors to get their basic similarity
		   		if(top_user != user_friend){
		   			std::map<std::string, std::map<std::string, double> >::iterator it2 = neighbors.find(top_user);
			   		double path = (neighbors.find(top_user)->second).find(user_friend)->second;
			   		//if a shorter path was found
			   		if(top_priority+path < priorities.find(user_friend)->second){
			   			if(inHeap.find(user_friend) == inHeap.end()){ //has not been put in heap
			   				priorities.find(user_friend)->second = top_priority+path;
			   				heap.push(top_priority+path, user_friend);
			   				inHeap.insert(user_friend);
			   				shortestPath.insert(make_pair(user_friend, top_priority+path));
			   			}
			   			else{
			   				priorities.find(user_friend)->second = top_priority+path;
			   				heap.decreaseKey(top_priority+path, user_friend);
			   				shortestPath.find(user_friend)->second =  top_priority+path;
			   			}
			   		}
		   		}
	   		}
	   	}
	   	heap.pop();
	}

	//set of products the currentUser has already reviewed
	std::set<std::string> currUser;
	std::vector<Review*> currUserReviews = get_user_reviews(currentUser);
	for(int i=0; (unsigned)i<currUserReviews.size(); i++){
		currUser.insert(currUserReviews[i]->prodName);
	}

	for(int i=0; (unsigned)i<all_products.size(); i++){
		if(currUser.find(all_products[i]->getName()) == currUser.end()){ //user has not reviewed
			if(reviews.find(all_products[i]->getName()) != reviews.end()){ //if the product has been reviewed by someone
				double sumR = 0.0; 
				double sumW = 0.0;
				std::vector<Review*> prod_reviews = searchReview(all_products[i]->getName());
				for(int j=0; (unsigned)j<prod_reviews.size(); j++){
					int ratingR = find_rating(all_products[i]->getName(), prod_reviews[j]->username); //r(B,P)
					double sim = shortestPath.find(prod_reviews[j]->username)->second; //s(B,A)
					sumR += (1-sim)*(double)ratingR; //R(P)
					sumW += 1-sim; //W
				}

				double final_rating = 0.0;
				if(sumW == 0.0)
				{
					final_rating = 0.0;
				} 
				else final_rating = (sumR / sumW);

				if(possible_products.size() == 0){
					possible_products.push_back(make_pair(all_products[i]->getName(), final_rating));
				}
				else{
					bool same = false;
					for(int l=0; (unsigned)l<possible_products.size(); l++){
						if(possible_products[l].first == all_products[i]->getName()){ //if product was already suggested
							same = true;
							if(final_rating > possible_products[l].second){ //replace if smaller rating for product was found
								possible_products[l].second = final_rating;
								break;
							}
						}
					}
					if(!same){
						possible_products.push_back(make_pair(all_products[i]->getName(), final_rating));
					}
				}
			}
		}
	}
	return possible_products;
}

int MyDataStore::find_rating(std::string product_name, std::string username){
	std::vector<Review*> product = searchReview(product_name);
	for(int i=0; (unsigned)i<product.size(); i++){
		if(product[i]->username == username){
			return product[i]->rating;
		}
	}
	return 0;
}

std::vector<Review*> MyDataStore::get_user_reviews(std::string username){
	std::vector<Review*> r;
	map<std::string, std::vector<Review*> >::iterator it = user_reviews.find(username);
	if(it != user_reviews.end()){
		return it->second;
	}
	return r;
}

