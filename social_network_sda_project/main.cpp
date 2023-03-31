#include <iostream>
#include "List.h"
#include "User.h"
#include <string>
#include "Multimap.h"
#include "User_service.h"
#include"Tests.h"
#include "Friendship.h"
#include "Network.h"
#include "UI.h"

int main()
{
    test_all();

	List<User>* user_list = new List<User>();
	User_validator user_validator;
	User_repo user_repo(user_list);
	User_service user_service(user_repo,user_validator);

	Multimap<User&, Friendship> friendship_multimap;
	Friendship_validator friendship_validator;
	Friendship_repo friendship_repo(friendship_multimap);
	Friendship_service friendship_service(friendship_repo, friendship_validator);

	Multimap<User&, Message> message_multimap;
	Message_repo message_repo(message_multimap);
	Message_validator message_validator;
	Message_service message_service(message_repo, message_validator);

	List<Event>* event_list = new List<Event>();
	Event_validator event_validator;
	Event_repo event_repo(event_list);
	Event_service event_service(event_repo, event_validator);

	Network network(user_service, friendship_service, message_service, event_service);

	UI ui(network);

	ui.ui_run_menu();

    return 0;
}
