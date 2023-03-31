#pragma once
#include <ostream>
#include <istream>
using namespace std;

class Event
{
private:
	int id;
	char* name;
	char* date;
	char* place;

	void set_id(int id);
public:
	Event();
	Event(const char* name, const char*date, const char* place);
	Event(const Event& e);

	~Event();

	int get_id();
	char* get_date();
	char* get_name();
	char* get_place();

	void set_name(const char* name);
	void set_date(const char* date);
	void set_place(const char* place);

	bool operator==(const Event& e);
	Event& operator=(const Event& e);

	friend ostream& operator<<(ostream& os, const Event& e);
};