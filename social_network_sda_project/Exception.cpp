#include "Exception.h"

Validation_exception::Validation_exception()
{
}

Validation_exception::Validation_exception(string message)
{
	this->message = message;
}

Validation_exception::~Validation_exception()
{
}

const char* Validation_exception::what() const throw()
{
	return this->message.c_str();
}
