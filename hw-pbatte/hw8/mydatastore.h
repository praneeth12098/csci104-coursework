#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "review.h"
#include "heap.h"
#include "msort.h"
#include <map>
#include <vector>

class MyDataStore : public DataStore
{
public:
	virtual ~MyDataStore();

	virtual void addProduct(Product* p);

	virtual void addUser(User* u);

	virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

	virtual void dump(std::ostream& ofile);

	void addToCart(User* u, Product* p);

	void removeFromCart(User* u, Product* p);

	void viewCart(User* u);

	void buyCart(User* u);

	User* getUser(std::string username);

	Product* getProduct(std::string product);

	void addReview(Review* r);

	std::vector<User*> getUsernames();

	std::vector<Review*> getReviews();

	void averageRatings();

	std::map<User*, std::vector<Product*> > getCart();

	std::vector<Product*> getProducts();

	std::vector<User*> getUsers();

	void resetRatings();

	std::map< std::pair<std::string, std::string>, double> basicSims();
	double refineSims(std::string, std::string);
	std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);

private:
	std::vector<Product*> products;
	std::vector<User*> users;
	std::map<User*, std::vector<Product*> > uCart;
	std::vector<Review*> reviews;

	//std::map< std::pair<std::string, std::string>, double> sims;
	// std::map<std::string, double> distances;
	std::map< std::pair<std::string, std::string>, double> num_prods;
	std::map<Product*, std::vector< std::pair<std::string, int> > > pReviews;
};

#endif