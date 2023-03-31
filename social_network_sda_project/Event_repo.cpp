#include "Event_repo.h"

Event_repo::Event_repo(List<Event>*& event_list):event_list(event_list)
{
}

Event_repo::~Event_repo()
{
}

vector<Event*> Event_repo::get_all_events()
{
	return this->event_list->get_all();
}

void Event_repo::add_event(const Event& event)
{
	this->event_list->add(event);
}

void Event_repo::update_event(const Event& event, const Event& updated_event)
{
	this->event_list->update(event, updated_event);
}

void Event_repo::delete_event(const Event& event)
{
	this->event_list->remove(event);
}

bool Event_repo::exists(const Event& event)
{
	return this->event_list->exists(event);
}
