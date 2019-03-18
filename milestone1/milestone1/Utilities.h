//	program    : Utilities.h
//	programmer : Yathavan, Parameshwaran
//	date       : March 4, 2019
//	professor  : Chris, Szalwinski

#ifndef SICT_UTILITIES_H
#define SICT_UTILITIES_H

#include <string>
#include <iomanip>

namespace sict
{
	class Utilities
	{
		static char myDelim;
		static size_t myFieldWidth;
	public:
		Utilities();
		const std::string extractToken(const std::string& str, size_t& next_pos);
		const char getDelimiter() const;
		size_t getFieldWidth() const;
		static void setDelimiter(const char d);
		void setFieldWidth(size_t t);
	};
}

#endif //SICT_UTILITIES_H