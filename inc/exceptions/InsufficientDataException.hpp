#ifndef INSUFFICIENT_DATA_EXCEPTION
#define INSUFFICIENT_DATA_EXCEPTION

#include <exception>

class InsufficientDataException: public std::exception{
	virtual const char* what() const throw(){
		return "Insufficient data provided.";
	}
};


#endif
