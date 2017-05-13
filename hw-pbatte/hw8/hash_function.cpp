// #include <string>
// #include <vector>
// #include <iostream>
// #include <math.h>

// unsigned long long hash_function(std::string password)
// {
// 	std::vector<int> char_values;
// 	std::string::iterator it = password.begin();

// 	for(; it != password.end(); ++it)
// 	{
// 		char letter = *it;
// 		int val = int (letter);	
// 		char_values.push_back(val);
// 	}

// 	unsigned long long value = 0;

// 	for(unsigned i = 0; i < password.size(); i++)
// 	{
// 		long long e = pow(128, i);
// 		value += (char_values[char_values.size()-1-i])*e;
// 	}
	
// 	unsigned int digits[4];

// 	digits[3] = value % 65521;
//    	digits[2] = (value/65521) % 65521;
// 	digits[1] = (value/65521/65521) % 65521;
// 	digits[0] = (value/65521/65521/65521) % 65521;

// 	unsigned long long result = (45912*digits[0] + 35511*digits[1] + 65169*digits[2] + 4625*digits[3]) % 65521;

// 	return result;
// }

// int main()
// {
// 	std::string example = "csci104";

// 	int p = hash_function(example);

// 	std::cout << p << std::endl;
// }