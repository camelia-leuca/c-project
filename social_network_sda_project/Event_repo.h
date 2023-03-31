#pragma once
#include "List.h"
#include "Event.h"
class Event_repo
{
private:
	List<Event>*& event_list;
public:
	Event_repo(List<Event>*& event_list);
	~Event_repo();

	vector<Event*> get_all_events();

	void add_event(const Event& event);
	void update_event(const Event& event, const Event& updated_event);
	void delete_event(const Event& event);
	bool exists(const Event& event);
};