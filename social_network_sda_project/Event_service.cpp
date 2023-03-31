#include "Event_service.h"
#include "Exception.h"

Event_service::Event_service(Event_repo& event_repo, Event_validator& event_validator):event_repo(event_repo), event_validator(event_validator)
{
}

Event_service::~Event_service()
{
}

vector<Event*> Event_service::get_all_events()
{
	return this->event_repo.get_all_events();
}

void Event_service::add_event(const char* name, const char* date, const char* place)
{
	Event event(name, date, place);
	if (this->event_validator.validate(event) == 0)
		this->event_repo.add_event(event);
	else
		throw Validation_exception(event_validator.get_message());
}

void Event_service::update_event(const char* name, const char* date, const char* place, const char* updated_name, const char* updated_date, const char* updated_place)
{
	Event event(name, date, place);
	Event updated_event(updated_name, updated_date, updated_place);
	if (this->event_validator.validate(updated_event) == 0)
		this->event_repo.update_event(event, updated_event);
	else
		throw Validation_exception(event_validator.get_message());
}

void Event_service::delete_event(const char* name, const char* date, const char* place)
{
	Event event(name, date, place);
	this->event_repo.delete_event(event);
}

bool Event_service::exists(const char* name, const char* date, const char* place)
{
	Event event(name, date, place);
	return this->event_repo.exists(event);
}
