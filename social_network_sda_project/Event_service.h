#pragma once
#include "Event_repo.h"
#include "Event_validator.h"
class Event_service
{
private:
	Event_repo& event_repo;
	Event_validator& event_validator;
public:
	Event_service(Event_repo& event_repo, Event_validator& event_validator);
	~Event_service();

	vector<Event*> get_all_events();

	void add_event(const char* name, const char* date, const char* place);
	void update_event(const char* name, const char* date, const char* place, const char* updated_name, const char* updated_date, const char* updated_place);
	void delete_event(const char* name, const char* date, const char* place);
	bool exists(const char* name, const char* date, const char* place);
};