#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>

class MyDataStore : public DataStore
{
public:
	virtual ~MyDataStore();

	virtual void addProduct(Product* p);

	virtual void addUser(User* u);

	virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

	virtual void dump(std::ostream& ofile);

	void addToCart(std::string username, std::vector<Product*> hits, int hit_no);

	void viewCart(std::string username);

	void buyCart(std::string username);

	User* getUser(std::string username);

private:
	std::vector<Product*> products;
	std::vector<User*> users;
	std::map<User*, std::vector<Product*> > uCart;
};

#endif