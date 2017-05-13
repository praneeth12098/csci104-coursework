#include "movie.h"
#include "util.h"
#include <sstream>

#include <iostream>

Movie::Movie(const std::string category, const std::string name, double price, 
	int qty, std::string genre, std::string rating)
		: Product(category, name, price, qty)
		, mGenre(genre)
		, mRating(rating)
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
	std::set<std::string> keys;
	std::set<std::string> name_keys;
	std::set<std::string> genre_keys;

	name_keys = parseStringToWords(name_);
	genre_keys = parseStringToWords(mGenre);

	keys = setUnion(name_keys, genre_keys);

	return keys;
}

std::string Movie::displayString() const
{
	std::ostringstream os;
	os << name_ << '\n' << "Genre: " << mGenre << ' ' << "Rating: " << mRating 
		<< '\n' << price_ << ' ' << qty_ << " left." << '\n';

	std::string output = os.str();

	return output;
}


void Movie::dump(std::ostream& os) const
{
	os << category_ << '\n' << name_ << '\n' << price_ 
		<< '\n' << qty_ << '\n' << mGenre << '\n' << mRating << '\n';
}
