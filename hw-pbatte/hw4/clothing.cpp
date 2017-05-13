#include "clothing.h"
#include "util.h"
#include <sstream>

#include <iostream>

Clothing::Clothing(const std::string category, const std::string name, double price, 
	int qty, std::string size, std::string brand)
		: Product(category, name, price, qty)
		, mSize(size)
		, mBrand(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> keys;
	std::set<std::string> name_keys;
	std::set<std::string> brand_keys;

	name_keys = parseStringToWords(name_);
	brand_keys = parseStringToWords(mBrand);

	keys = setUnion(name_keys, brand_keys);

	return keys;
}

std::string Clothing::displayString() const
{
	std::ostringstream os;

	os << name_ << '\n' << "Size: " << mSize << ' ' << "Brand: " << mBrand 
		<< '\n' << price_ << ' ' << qty_ << " left." << '\n';

	std::string output = os.str();

	return output;
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << '\n' << name_ << '\n' << price_ 
		<< '\n' << qty_ << '\n' << mSize << '\n' << mBrand << '\n';
}
