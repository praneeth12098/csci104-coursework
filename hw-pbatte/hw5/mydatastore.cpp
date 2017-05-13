#include "mydatastore.h"
#include "util.h"

MyDataStore::~MyDataStore()
{
	std::vector<Product*>::iterator prods = products.begin();
	for(; prods != products.end(); ++prods)
		delete *prods;

	std::vector<User*>::iterator u = users.begin();
	for(; u != users.end(); ++u)
		delete *u;

	uCart.clear();
}

void MyDataStore::addProduct(Product* p)
{
	products.push_back(p);
}

void MyDataStore::addUser(User* u)
{
	users.push_back(u);
	std::vector<Product*> products;
	uCart.insert(std::make_pair(u, products));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	std::set<std::string> sTerms;
	for(unsigned int i = 0; i < terms.size(); i++)
	{
		sTerms.insert(terms[i]);
	}
	if(type == 0)
	{
		std::vector<Product*> searched_products;
		std::set<std::string> keys;
		std::vector<Product*>::iterator it = products.begin();
		for(; it != products.end(); ++it)
		{
			std::set<std::string> temp = (*it)->keywords();
			keys = setIntersection(sTerms, temp);
			if(keys.size() == sTerms.size())
				searched_products.push_back(*it);
			keys.clear();
		}
		return searched_products;
	}
	else
	{
		std::vector<Product*> searched_products;
		std::set<std::string> keys;
		std::set<std::string> temp;
		std::vector<Product*>::iterator it = products.begin();
		for(; it != products.end(); ++it)
		{
			temp = (*it)->keywords();
			unsigned int temp_size = temp.size();
			keys = setUnion(sTerms, temp);
			if(keys.size() < temp_size + sTerms.size())
				searched_products.push_back(*it);
		}
		return searched_products;
	}
}

void MyDataStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << '\n';
	std::vector<Product*>::iterator it = products.begin();
	for(; it != products.end(); ++it)
		(*it)->dump(ofile);

	ofile << "</products>" << '\n' << "<users>" << '\n';
	std::vector<User*>::iterator it2 = users.begin();
	for(; it2 != users.end(); ++it2)
		(*it2)->dump(ofile);

	ofile << "</users>" << '\n';

	std::vector<Review*>::iterator it3 = reviews.begin();
	for(; it3 != reviews.end(); ++it3)
		(*it3)->dump(ofile);

	ofile << "</reviews>" << '\n';
}

User* MyDataStore::getUser(std::string username)
{
	std::vector<User*>::iterator it = users.begin();
	User* u; bool check = false;
    for(; it != users.end(); ++it)
    {
        if((*it)->getName() == username)
        {
            u = *it;
            check = true;
        }
    }
    if(!check)
    	std::cout << "Invalid Username" << std::endl;
    return u;
}

void MyDataStore::addToCart(User* u, Product* p)
{
    std::map<User*, std::vector<Product*> >::iterator mapit;
    mapit = uCart.find(u);

    if(mapit != uCart.end())
    {
    	(mapit->second).push_back(p);
    	//std::cout << "item added" << std::endl;
    }

}

void MyDataStore::removeFromCart(User* u, Product* p)
{
	int index = -1; 
	std::map<User*, std::vector<Product*> >::iterator mapit;
	mapit = uCart.find(u);

	if(mapit != uCart.end())
	{
		std::vector<Product*>& temp1 = mapit->second;
		for(unsigned int i = 0; i < temp1.size(); i++)
		{
			if(p->getName() == temp1[i]->getName())
				index = i;
		}
		if(index >= 0)
		{
			std::cout << "num items in cart: " << temp1.size() << std::endl;
			std::vector<Product*>::iterator p;
			p = std::find(temp1.begin(), temp1.end(), temp1[index]);
			if(p != temp1.end())
			{
				temp1.erase(p);
				std::cout << "erasing" << std::endl;
			}
			std::cout << "num items in cart: " << temp1.size() << std::endl;
			std::cout << "item removed" << std::endl;
		}
	}
}

void MyDataStore::viewCart(User* u)
{
	std::map<User*, std::vector<Product*> >::iterator mapit;
    mapit = uCart.find(u);

    if(mapit != uCart.end())
    {
    	std::vector<Product*> prods = mapit->second;
    	std::vector<Product*>::iterator it = prods.begin();
    	int i = 1;
    	for(; it != prods.end(); ++it)
    	{
    		//std::cout << "Item " << i << std::endl;
    		std::cout << (*it)->displayString() << std::endl;
    		i++;
    	}
    }
}

void MyDataStore::buyCart(User* u)
{
	std::map<User*, std::vector<Product*> >::iterator mapit;
    mapit = uCart.find(u);

    //to ensure uCart is maintained in FIFO order
    std::vector<Product*> popped_products;

    if(mapit != uCart.end())
    {
    	std::vector<Product*>& prods = mapit->second;
    	std::vector<Product*>::iterator it = prods.begin();
    	for(; it != prods.end();)
    	{
    		if(((*it)->getQty() > 0) && (u->getBalance() > (*it)->getPrice()))
    		{
    			(*it)->subtractQty(1);
    			u->deductAmount((*it)->getPrice());
    			it = prods.erase(it);
    		}
    		else
    		{
    			Product* tempprod = *it;
    			it = prods.erase(it);
    			popped_products.push_back(tempprod);
    		}
    	}
    	prods = popped_products;
    }
}

void MyDataStore::addReview(Review* r)
{
	reviews.push_back(r);
}

std::vector<User*> MyDataStore::getUsernames()
{
	return users;
}

std::vector<Review*> MyDataStore::getReviews()
{
	return reviews;
}

void MyDataStore::averageRatings()
{
	std::vector<Review*>::iterator rit = reviews.begin();
	for(; rit != reviews.end(); ++rit)
	{
		std::string name = (*rit)->prodName;
		for(int i = 0; i < products.size(); i++)
		{
			if(name == products[i]->getName())
			{
				products[i]->setRating((*rit)->rating);
				//std::cout << products[i]->getName() << ": " << products[i]->getRating() << std::endl;
			}
		}
	}
}

void MyDataStore::resetRatings()
{
	std::vector<Product*>::iterator pit = products.begin();
	for(; pit != products.end(); ++pit)
	{
		(*pit)->setRating(0);
	}
}

std::map<User*, std::vector<Product*> > MyDataStore::getCart()
{
	return uCart;
}

std::vector<Product*> MyDataStore::getProducts()
{
	return products;
}