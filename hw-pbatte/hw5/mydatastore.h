#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "review.h"
#include <map>

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

	void addReview(Review* r);

	std::vector<User*> getUsernames();

	std::vector<Review*> getReviews();

	void averageRatings();

	std::map<User*, std::vector<Product*> > getCart();

	std::vector<Product*> getProducts();

	void resetRatings();

private:
	std::vector<Product*> products;
	std::vector<User*> users;
	std::map<User*, std::vector<Product*> > uCart;
	std::vector<Review*> reviews;
};

#endif