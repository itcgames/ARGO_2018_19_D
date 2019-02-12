#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace pu {
	std::vector<std::string> Split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		std::string stringV;
		std::istringstream f(s);

		while (std::getline(f, stringV, delim)) {
			elems.push_back(stringV);
		}
		return elems;
	}
}

#endif //!PARSEUTILS_H

