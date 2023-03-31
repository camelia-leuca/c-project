#include "Event.h"
#include "Network.h"

void Event::set_id(int id)
{
	this->id = id;
}

Event::Event()
{
	Network::current_id++;
	this->id = Network::current_id;
	this->name = NULL;
	this->date = NULL;
	this->place = NULL;
}

Event::Event(const char* name, const char* date, const char* place)
{
	Network::current_id++;
	this->id = Network::current_id;

	if (name == NULL)
		this->name = NULL;
	else
	{
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	if (date == NULL)
		this->date = NULL;
	else
	{
		this->date = new char[strlen(date) + 1];
		strcpy_s(this->date, strlen(date) + 1, date);
	}

	if (place == NULL)
		this->place = NULL;
	else
	{
		this->place = new char[strlen(place) + 1];
		strcpy_s(this->place, strlen(place) + 1, place);
	}
}

Event::Event(const Event& e)
{
	this->id = e.id;

	if (e.name == NULL)
		this->name = NULL;
	else
	{
		this->name = new char[strlen(e.name) + 1];
		strcpy_s(this->name, strlen(e.name) + 1, e.name);
	}

	if (e.date == NULL)
		this->date = NULL;
	else
	{
		this->date = new char[strlen(e.date) + 1];
		strcpy_s(this->date, strlen(e.date) + 1, e.date);
	}

	if(e.place == NULL)
		this->place = NULL;
	else
	{
		this->place = new char[strlen(e.place) + 1];
		strcpy_s(this->place, strlen(e.place) + 1, e.place);
	}
}

Event::~Event()
{
	if (this->name)
		delete[]this->name;

	if (this->date)
		delete[]this->date;

	if (this->place)
		delete[]this->place;
}


int Event::get_id()
{
	return this->id;
}

char* Event::get_date()
{
	return this->date;
}

char* Event::get_name()
{
	return this->name;
}

char* Event::get_place()
{
	return this->place;
}


void Event::set_name(const char* name)
{
	if (name == NULL)
		this->name = NULL;
	else
	{
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}
}

void Event::set_date(const char* date)
{
	if (date == NULL)
		this->date = NULL;
	else
	{
		this->date = new char[strlen(date) + 1];
		strcpy_s(this->date, strlen(date) + 1, date);
	}
}

void Event::set_place(const char* place)
{
	if (place == NULL)
		this->place = NULL;
	else
	{
		this->place = new char[strlen(place) + 1];
		strcpy_s(this->place, strlen(place) + 1, place);
	}
}

bool Event::operator==(const Event& e)
{
	return strcmp(this->name, e.name) == 0 and strcmp(this->date, e.date) == 0 and strcmp(this->place, e.place)==0;
}

Event& Event::operator=(const Event& e)
{
	if (this != &e)
	{
		this->set_id(e.id);
		this->set_name(e.name);
		this->set_date(e.date);
		this->set_place(e.place);
	}
	return *this;
}

ostream& operator<<(ostream& os, const Event& e)
{
	if (e.name and e.date and e.place)
		os << "Event(id : "<<e.id<<", name : " << e.name << ", date : " << e.date << ", place : " << e.place<<")";
	return os;
}
