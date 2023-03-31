#pragma once
#include <exception>
#include <string>
using namespace std;

class Validation_exception : public exception
{
private:
	string message;
public:
	Validation_exception();
	Validation_exception(string message);
	~Validation_exception();
	const char* what()const throw();
};
