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

Product* MyDataStore::getProduct(std::string product)
{
	std::vector<Product*>::iterator it = products.begin();
	Product* p; bool check = false;
	for(; it != products.end(); ++it)
	{
		if((*it)->getName() == product)
		{
			p = *it;
			check = true;
		}
	}
	if(!check)
		std::cout << "Invalid Product" << std::endl;
	return p;
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
		for(unsigned int i = 0; i < products.size(); i++)
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

std::vector<User*> MyDataStore::getUsers()
{
	return users;
}

std::map< std::pair<std::string, std::string>, double> MyDataStore::basicSims()
{
	//similarity stuff initialization
	std::map< std::pair<std::string, std::string>, double> sims;

	std::vector<User*> currUsers = this->getUsers();
	for(unsigned int i = 0; i < currUsers.size(); i++)
	{
		for(unsigned int j = i + 1; j < currUsers.size(); j++)
		{
			std::pair<std::string, std::string> uPair = std::make_pair(currUsers[i]->getName(), currUsers[j]->getName());
			sims.insert(std::make_pair(uPair, 1.0));
			num_prods.insert(std::make_pair(uPair, 0));
		}
	}

	std::vector<Product*>::iterator pit = products.begin();
	for(; pit != products.end(); ++pit)
	{
		std::vector<std::pair<std::string, int> > temp_list;
		pReviews.insert(std::make_pair((*pit), temp_list));
	}

	std::vector<Review*>::iterator r = reviews.begin();
	for(; r != reviews.end(); ++r)
	{
		std::string uName = (*r)->username;
		std::string prod = (*r)->prodName;
		int rate = (*r)->rating;

		Product* temp_prod = this->getProduct(prod);
		std::map<Product*, std::vector< std::pair<std::string, int> > >::iterator pr = pReviews.begin();
		bool exists = false;
		for(; pr != pReviews.end(); ++pr)
		{
			if((*pr).first == temp_prod) 
			{
				(pReviews[temp_prod]).push_back(std::make_pair(uName, rate));
			}
		}
	}

	std::map< std::pair<std::string, std::string>, double> totalSims;
	std::map<Product*, std::vector< std::pair<std::string, int> > >::iterator pr = pReviews.begin();

	while(pr != pReviews.end())
	{
		std::vector<std::pair<std::string, int> > temp_list = (*pr).second;
		if(temp_list.size() == 0)
		{
			pr = pReviews.erase(pr);
		}
		else ++pr;
	}

	pr = pReviews.begin();
	for(; pr != pReviews.end(); ++pr)
	{
		std::vector< std::pair<std::string, int> > temp_user_pairs = (*pr).second;
		std::vector< std::pair<std::string, int> >::iterator temp = temp_user_pairs.begin();

		std::vector< std::pair<std::string, std::string> > pairs;

		for(unsigned int i = 0; i < temp_user_pairs.size(); i++)
		{
			for(unsigned int j = i + 1; j < temp_user_pairs.size(); j++)
			{
				pairs.push_back(std::make_pair(temp_user_pairs[i].first, temp_user_pairs[j].first));
			}
		}

		bool u1 = false; 
		bool u2 = false;

		std::vector< std::pair<std::string, std::string> >::iterator p = pairs.begin();
		for(; p!= pairs.end(); ++p)
		{
			sims[*p] = 1.0;
			std::vector< std::pair<std::string, int> >::iterator vit = temp_user_pairs.begin();

			int aRating;
			int bRating;
			for(; vit != temp_user_pairs.end(); ++vit)
			{
				if((*vit).first == (*p).first)
				{
					aRating = (*vit).second;
					u1 = true;
				}
				if((*vit).first == (*p).second)
				{
					bRating = (*vit).second;
					u2 = true;
				}
			}
			double simTotal = abs(aRating-bRating)/(double)4.0;

			totalSims[*p] += simTotal;
			if(u1 && u2)
			{
				num_prods[*p] = num_prods[*p] + 1;
			}
		}
	}

	std::map< std::pair<std::string, std::string>, double>::iterator tsit = totalSims.begin();
	for(; tsit != totalSims.end(); ++tsit)
	{
		std::pair<std::string, std::string> temp = tsit->first;
		sims[temp] = (double)(*tsit).second/(double)num_prods[temp];
	}
	return sims;
}

double MyDataStore::refineSims(std::string u1, std::string u2)
{
	Heap<std::string> heap;

	std::map<std::string, double> distances;

	std::map< std::pair<std::string, std::string>, double> sims = basicSims();

	distances.insert(std::make_pair(u1, 0.0));
	heap.push(0.0, u1);


	for(unsigned int i = 0; i < users.size(); i++)
	{
		if(users[i]->getName() != u1)
		{
			distances.insert(std::make_pair((users[i]->getName()), 1.0));
			heap.push(1.0, users[i]->getName());
		}
	}

	while(!heap.empty())
	{
		std::string user1 = heap.top();
		heap.pop();

		std::map<std::string, double>::iterator dit = distances.begin();

		for(; dit != distances.end(); ++dit)
		{
			if(dit->first != u1)
			{
				std::pair<std::string, std::string> key = std::make_pair(u1, dit->first);
				std::map<std::pair<std::string, std::string>, double>::iterator it = sims.find(key);
				double bsim = it->second;
				double dist = dit->second;
				if(dist > distances[user1] + bsim)
				{
					heap.decreaseKey(distances[user1] + bsim, dit->first);
					dit->second = distances[user1] + bsim;
				}
			}
		}
	}
	return distances[u2];
}

std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser)
{
	std::map< std::pair<std::string, std::string>, double> sims = basicSims();

	std::map<Product*, std::vector< std::pair<std::string, int> > > pUserNotReviewed;

	std::map<Product*, std::vector< std::pair<std::string, int> > >::iterator pr = pReviews.begin();
	for(; pr != pReviews.end(); ++pr)
	{
		std::vector<std::pair<std::string, int> > usersWhoReviewed = (*pr).second;
		std::vector<std::pair<std::string, int> >::iterator uwrit = usersWhoReviewed.begin();
		bool hasReviewed = false;
		for(; uwrit != usersWhoReviewed.end(); ++uwrit)
		{
			if((*uwrit).first == currentUser) hasReviewed = true;
		}
		if(!hasReviewed)
		{
			pUserNotReviewed.insert(std::make_pair(((*pr).first), (*pr).second));
		}
	}
	std::vector<std::pair<std::string, double> > productRatings;

	std::map<Product*, std::vector< std::pair<std::string, int> > >::iterator pnr = pUserNotReviewed.begin();
	for(; pnr != pUserNotReviewed.end(); ++pnr)
	{
		std::vector<std::pair<std::string, int> > usersAndRatings = (*pnr).second;
		std::vector<std::pair<std::string, int> >::iterator uR = usersAndRatings.begin();
		double sumRating = 0;
		double W = 0;
		for(; uR != usersAndRatings.end(); ++uR)
		{
			std::string user = (*uR).first;
			int userRating = (*uR).second;
			double similarity = refineSims(currentUser, user);
			sumRating += (double)(1-similarity)*(double)userRating;
			W += (double)(1-similarity);
		}
		double rating = sumRating/W;

		std::string productName = (*pnr).first->getName();
		std::pair<std::string, double> pairing = std::make_pair(productName, rating);
		productRatings.push_back(pairing);
	}

	PairComp comp;
	mergeSort(productRatings, comp);

	return productRatings;
}