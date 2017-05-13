#include "book.h"
#include "util.h"
#include <sstream>
#include <iostream>

Book::Book(const std::string category, const std::string name, double price, 
	int qty, std::string isbn, std::string author)
		: Product(category, name, price, qty)
		, mISBN(isbn)
		, mAuthor(author)
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
	std::set<std::string> keys;
	std::set<std::string> name_keys;
	std::set<std::string> author_name_keys;

	name_keys = parseStringToWords(name_);
	author_name_keys = parseStringToWords(mAuthor);

	keys = setUnion(name_keys, author_name_keys);

	keys.insert(mISBN);

	return keys;
}

std::string Book::displayString() const
{
	std::ostringstream os;
	os << name_ << '\n' << "Author: " << mAuthor 
		<< " ISBN: " << mISBN << '\n' << price_ << " " 
		<< qty_ << " left." << '\n';

	std::string output = os.str();

	return output;
}

void Book::dump(std::ostream& os) const
{
	os << category_ << '\n' << name_ << '\n' << price_ << '\n' 
		<< qty_ << '\n' << mISBN << '\n' 
		<< mAuthor << '\n';
}

std::string Book::getName()
{
	return name_;
}
