#pragma once
#include "Event.h"
class Event_validator
{
private:
	int no_errors;
	string message;
public:
	Event_validator();
	~Event_validator();

	int validate(Event& e);
	int get_no_errors();
	string get_message();
};