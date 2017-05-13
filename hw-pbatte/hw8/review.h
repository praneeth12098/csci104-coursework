#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <iostream>
#include <sstream>

struct Review
{
    Review() :  prodName(), rating(), username(), date(), reviewText()
    { }
    Review(const std::string& prod,
           int rate,
           const std::string& u,
           const std::string& d,
           const std::string& review_text) :
        prodName(prod),
        rating(rate),
        username(u),
        date(d),
        reviewText(review_text)
    { }

    std::string prodName;
    int rating;
    std::string username;
    std::string date;
    std::string reviewText;

    void dump(std::ostream& os) const
    {
      os << prodName << '\n' << rating << " " << username 
        << " " << date << " " << reviewText << '\n';
    }

    std::string displayString() const
    {
      std::ostringstream os;
      os << prodName << '\n' << "Rating: " << rating << ' ' << "username: " << username 
        << ' ' << date << '\n' << reviewText << '\n';

      std::string output = os.str();

      return output;
    }
};

#endif
