#include "Tests.h"
#include"User.h"
#include"List.h"
#include"User_service.h"
#include<cassert>
#include <cstring>
#include "Multimap.h"
#include "Friendship.h"
#include "Message.h"
#include "Event.h"
#include "Friendship_repo.h"
#include "Message_repo.h"
#include "Event_repo.h"
#include "Friendship_service.h"
#include "Message_service.h"
#include "Event_service.h"
#include "Network.h"
void test_user()
{
	User u1;
	assert(u1.get_id() == 1001);
	assert(u1.get_username() == NULL);
	assert(u1.get_password() == NULL);

	u1.set_username("username1");
	u1.set_password("password1");

	assert(strcmp(u1.get_username(), "username1") == 0);
	assert(strcmp(u1.get_password(), "password1") == 0);

	User u2("username2", "password2");
	assert(u2.get_id() == 1002);
	assert(strcmp(u2.get_username(), "username2") == 0);
	assert(strcmp(u2.get_password(), "password2") == 0);

	User u3 = u1;
	assert(u3 == u1);
}

void test_friendship()
{
	User u1("username1", "password1");
	User u2("username2", "password2");

	Friendship f1(u1,u2);
	assert(f1.get_id() == 1005);
	assert(f1.get_sender() == u1);
	assert(f1.get_receiver() == u2);

	Friendship f2 = f1;
	assert(f1 == f2);
}

void test_message()
{
	User u1("username1", "password1");
	User u2("username2", "password2");
	char message1[] = "message1";
	Message m1(u1, u2, message1);

	assert(m1.get_id() == 1008);
	assert(m1.get_sender() == u1);
	assert(m1.get_receiver() == u2);
	assert(strcmp(m1.get_message(), message1)==0);

	Message m2 = m1;
	assert(m1 == m2);
}

void test_event()
{
	Event e1("event1", "1/1/2022", "place1");
	assert(e1.get_id() == 1009);
	assert(strcmp(e1.get_name(), "event1")==0);
	assert(strcmp(e1.get_date(), "1/1/2022") == 0);
	assert(strcmp(e1.get_place(), "place1") == 0);

	Event e2 = e1;
	assert(e2 == e1);
}

void test_list()
{
	List<User>* list = new List<User>();

	User u1("username1", "password1");
	User u2("username2", "password2");
	User u3("username3", "password3");

	list->add(u1);
	list->add(u3);
	vector<User*> users = list->get_all();
	assert(list->exists(u1) == true);
	assert(list->exists(u2) == false);
	assert(list->exists(u3) == true);
	assert(users.size() == 2);
	assert(*users[0] == u1);
	assert(*users[1] == u3);

	list->remove(u3);
	users = list->get_all();
	assert(list->exists(u1) == true);
	assert(list->exists(u3) == false);
	assert(users.size() == 1);
	assert(*users[0] == u1);

	list->update(u1, u2);
	assert(list->exists(u1) == false);
	assert(list->exists(u2) == true);
	assert(users.size() == 1);
	assert(*users[0] == u2);

	list->remove(u2);
	users = list->get_all();
	assert(list->exists(u2) == false);
	assert(users.size() == 0);
}

void test_multimap()
{
	Multimap<User, Friendship> multimap ;

	User u1("username1", "password1");
	User u2("username2", "password2");
	User u3("username3", "password3");
	User u4("username4", "password4");

	Friendship f12(u1, u2);
	Friendship f23(u2, u3);
	Friendship f13(u1, u3);

	multimap.put(u1, f12);
	multimap.put(u2, f12);
	multimap.put(u2, f23);
	multimap.put(u3, f23);

	vector<Friendship> friendships = multimap.get_all();

	assert(friendships.size() == 2);
	assert(friendships[0] == f12);
	assert(friendships[1] == f23);

	assert(multimap.exists(u1, f12) == true);
	assert(multimap.exists(u1, f23) == false);
	assert(multimap.exists(u1, f13) == false);

	assert(multimap.exists(u2, f12) == true);
	assert(multimap.exists(u2, f23) == true);
	assert(multimap.exists(u2, f13) == false);

	assert(multimap.exists(u3, f12) == false);
	assert(multimap.exists(u3, f23) == true);
	assert(multimap.exists(u3, f13) == false);

	multimap.remove(u1, f12);
	multimap.remove(u2, f12);

	friendships = multimap.get_all();
	assert(friendships.size() == 1);
	assert(friendships[0] == f23);

	assert(multimap.exists(u1, f12) == false);
	assert(multimap.exists(u2, f12) == false);
	assert(multimap.exists(u2, f23) == true);
	assert(multimap.exists(u3, f12) == false);
	assert(multimap.exists(u3, f23) == true);
	assert(multimap.exists(u3, f13) == false);

	multimap.remove(u2);
	friendships = multimap.get_all();
	assert(friendships.size() == 1);
	assert(multimap.exists(u2, f23) == false);
	assert(multimap.exists(u3, f23) == true);

	multimap.remove(u3);
	friendships = multimap.get_all();
	assert(friendships.size() == 0);
	assert(multimap.exists(u3, f23) == false);
}

void test_repo_user()
{
	List<User>* list = new List<User>();
	User_repo user_repo(list);

	User u1("username1", "password1");
	User u2("username2", "password2");

	user_repo.add_user(u1);
	vector<User*> users = user_repo.get_all_users();
	assert(users.size() == 1);
	assert(*users[0] == u1);
	assert(user_repo.user_exists(u1)==true);
	assert(user_repo.user_exists(u2) == false);

	user_repo.update_user(u1, u2);
	assert(*users[0] == u2);
	assert(user_repo.user_exists(u1) == false);
	assert(user_repo.user_exists(u2) == true);

	user_repo.delete_user(u2);
	users = user_repo.get_all_users();
	assert(users.size() == 0);
	assert(user_repo.user_exists(u2) == false);
}

void test_repo_friendship()
{
	User u1("username1", "password1");
	User u2("username2", "password2");
	User u3("username3", "password3");

	Friendship f12(u1, u2);
	Friendship f23(u2, u3);

	Multimap<User&, Friendship> multimap;
	Friendship_repo friendship_repo(multimap);

	friendship_repo.add_friendship(f12);
	vector<Friendship>friendships = friendship_repo.get_all_friendships();
	assert(friendships.size() == 1);
	assert(friendships[0] == f12);
	assert(friendship_repo.friendship_exists(f12) == true);
	assert(friendship_repo.friendship_exists(f12) == true);

	friendship_repo.add_friendship(f23);
	friendships = friendship_repo.get_all_friendships();
	assert(friendships.size() == 2);
	assert(friendships[0] == f12);
	assert(friendships[1] == f23);
	assert(friendship_repo.friendship_exists(f12) == true);
	assert(friendship_repo.friendship_exists(f23) == true);

	friendship_repo.delete_friendship(f23);
	friendships = friendship_repo.get_all_friendships();
	assert(friendships.size() == 1);
	assert(friendships[0] == f12);
	assert(friendship_repo.friendship_exists(f12) == true);
	assert(friendship_repo.friendship_exists(f23) == false);

	friendship_repo.delete_friendship(f12);
	friendships = friendship_repo.get_all_friendships();
	assert(friendships.size() == 0);
	assert(friendship_repo.friendship_exists(f12) == false);
}

void test_repo_message()
{
	User u1("username1", "password1");
	User u2("username2", "password2");

	char message1[] = "message1";

	Message m1(u1, u2, message1);

	Multimap<User&, Message> multimap;
	Message_repo message_repo(multimap);
	vector<Message> messages = message_repo.get_all_messages();
	assert(messages.size() == 0);
	assert(message_repo.message_exists(m1) == false);

	message_repo.add_message(m1);
	messages = message_repo.get_all_messages();
	assert(messages.size() == 1);
	assert(messages[0] == m1);
	assert(message_repo.message_exists(m1) == true);

	message_repo.delete_message(m1);
	messages = message_repo.get_all_messages();
	assert(messages.size() == 0);
	assert(message_repo.message_exists(m1) == false);
}

void test_repo_event()
{
	Event e1("event1", "1/1/2022", "place1");
	Event e2("event2", "2/2/2022","place2");

	List<Event>*list =new List<Event>();

	Event_repo event_repo(list);
	vector<Event*> events = event_repo.get_all_events();
	assert(events.size() == 0);

	event_repo.add_event(e1);
	events = event_repo.get_all_events();
	assert(events.size() == 1);
	assert(*events[0] == e1);
	assert(event_repo.exists(e1)==true);
	assert(event_repo.exists(e2)==false);

	event_repo.update_event(e1, e2);
	assert(events.size() == 1);
	assert(*events[0] == e2);
	assert(event_repo.exists(e1) == false);
	assert(event_repo.exists(e2) == true);

	event_repo.delete_event(e2);
	events = event_repo.get_all_events();
	assert(events.size() == 0);
	assert(event_repo.exists(e2) == false);
}

void test_service_user()
{
	List<User>* list = new List<User>();
	User_validator user_validator;
	User_repo user_repo(list);
	User_service user_service(user_repo,user_validator);

	vector<User*> users = user_service.get_all_users();
	assert(users.size() == 0);

	user_service.add_user("username1", "password1");
	users = user_service.get_all_users();
	assert(users.size() == 1);
	assert(*users[0] == User("username1", "password1"));
	assert(user_service.get_user_by_username("username1")== User("username1", "password1"));
	assert(user_service.user_exists("username1")== true);
	assert(user_service.user_exists("username1", "password1") == true);
	assert(user_service.user_exists("username2", "password2") == false);

	user_service.update_user("username1", "password1", "username2", "password2");
	assert(users.size() == 1);
	assert(*users[0] == User("username2", "password2"));
	assert(user_service.get_user_by_username("username2") == User("username2", "password2"));
	assert(user_service.user_exists("username1") == false);
	assert(user_service.user_exists("username1", "password1") == false);
	assert(user_service.user_exists("username2", "password2") == true);

	user_service.delete_user("username2", "password2");
	users = user_service.get_all_users();
	assert(users.size() == 0);
	assert(user_service.user_exists("username2") == false);
	assert(user_service.user_exists("username2", "password2") == false);
}

void test_service_friendship()
{
	User u1("username1", "password1");
	User u2("username2", "password2");

	Multimap<User&, Friendship> multimap;
	Friendship_validator friendship_validator;
	Friendship_repo friendship_repo(multimap);
	Friendship_service friendship_service(friendship_repo, friendship_validator);

	vector<Friendship> friendships = friendship_service.get_all_friendships();
	assert(friendships.size() == 0);

	friendship_service.add_friendship(u1, u2);
	friendships = friendship_service.get_all_friendships();
	assert(friendships.size() == 1);
	assert(friendships[0] == Friendship(u1, u2));
	assert(friendship_service.friendship_exists(u1, u2) == true);
	assert(friendship_service.friendship_exists(u1) == true);
	assert(friendship_service.friendship_exists(u2) == true);

	vector<Friendship> friendships_for_user = friendship_service.get_all_friends_for_user(u1);
	assert(friendships_for_user.size() == 1);
	assert(friendships_for_user[0] == Friendship(u1, u2));

	friendship_service.get_all_friends_for_user(u2);
	assert(friendships_for_user.size() == 1);
	assert(friendships_for_user[0] == Friendship(u1, u2));

	friendship_service.delete_friendship(u1, u2);
	friendships = friendship_service.get_all_friendships();
	assert(friendships.size() == 0);
	assert(friendship_service.friendship_exists(u1, u2) == false);
	assert(friendship_service.friendship_exists(u1) == true);
	assert(friendship_service.friendship_exists(u2) == true);

	friendships_for_user = friendship_service.get_all_friends_for_user(u1);
	assert(friendships_for_user.size() == 0);

	friendship_service.get_all_friends_for_user(u2);
	assert(friendships_for_user.size() == 0);

	friendship_service.remove_from_friendships(u1);
	friendship_service.remove_from_friendships(u2);
	assert(friendship_service.friendship_exists(u1) == false);
	assert(friendship_service.friendship_exists(u2) == false);

	friendships = friendship_service.get_all_friendships();
	assert(friendships.size() == 0);

	User u3("username3", "password3");
	User u4("username4", "password4");
	User u5("username5", "password5");
	User u6("username6", "password6");

	friendship_service.add_friendship(u1, u2);

	friendship_service.add_friendship(u2, u3);
	friendship_service.add_friendship(u1, u3);

	friendship_service.add_friendship(u4, u2);
	friendship_service.add_friendship(u4, u5);

	friendship_service.add_friendship(u6, u1);
	friendship_service.add_friendship(u2, u6);

	friendship_service.add_friendship(u5, u1);

	vector<Friendship>common = friendship_service.get_all_common_friends_for_users(u1, u2);
	assert(common.size() == 4);
	assert(common[0] == Friendship(u6, u1));
	assert(common[1] == Friendship(u2, u6));
	assert(common[2] == Friendship(u1, u3));
	assert(common[3] == Friendship(u2, u3));
}

void test_service_message()
{
	User u1("username1", "password1");
	User u2("username2", "password2");

	char message1[] = "message1";
	Multimap<User&, Message> multimap;
	Message_repo message_repo(multimap);
	Message_validator message_validator;
	Message_service message_service(message_repo, message_validator);

	vector<Message> messages = message_service.get_all_messages();
	assert(messages.size() == 0);

	message_service.send_message(u1, u2, message1);
	messages = message_service.get_all_messages();
	assert(messages.size() == 1);
	assert(messages[0] == Message(u1,u2,message1));
	assert(message_service.message_exists(u1, u2, message1) == true);
	assert(message_service.message_exists(u1) == true);
	assert(message_service.message_exists(u1) == true);

	vector<Message> messages_for_user = message_service.get_all_messages_for_user(u1);
	assert(messages_for_user.size() == 1);
	assert(messages_for_user[0] == Message(u1, u2, message1));
	
	messages_for_user = message_service.get_all_messages_for_user(u2);
	assert(messages_for_user.size() == 1);
	assert(messages_for_user[0] == Message(u1, u2, message1));

	message_service.delete_message(u1, u2, message1);
	messages = message_service.get_all_messages();
	assert(messages.size() == 0);
	assert(message_service.message_exists(u1, u2, message1) == false);
	assert(message_service.message_exists(u1) == true);
	assert(message_service.message_exists(u1) == true);

	messages_for_user = message_service.get_all_messages_for_user(u1);
	assert(messages_for_user.size() == 0);

	messages_for_user = message_service.get_all_messages_for_user(u2);
	assert(messages_for_user.size() == 0);

	message_service.remove_from_messages(u1);
	message_service.remove_from_messages(u2);
	assert(message_service.message_exists(u1) == false);
	assert(message_service.message_exists(u1) == false);

	messages = message_service.get_all_messages();
	assert(messages.size() == 0);

	User u3("username3", "password3");

	message_service.send_message(u1, u2,"m1");
	message_service.send_message(u2, u3,"m2");
	message_service.send_message(u2, u1,"m3");
	message_service.send_message(u1, u2,"m1");
	message_service.send_message(u3, u1,"m5");

	vector<Message>messages_for_users = message_service.get_all_messages_for_users(u1, u2);
	assert(messages_for_users.size() == 3);
	assert(messages_for_users[0] == Message(u1, u2, "m1"));
	assert(messages_for_users[1] == Message(u2, u1, "m3"));
	assert(messages_for_users[2] == Message(u1, u2, "m1"));
}

void test_service_event()
{
	List<Event>* list = new List<Event>();

	Event_repo event_repo(list);
	Event_validator event_validator;
	Event_service event_service(event_repo, event_validator);

	vector<Event*> events = event_service.get_all_events();
	assert(events.size() == 0);

	event_service.add_event("name1", "1/1/2022", "place1");
	events = event_service.get_all_events();
	assert(events.size() == 1);
	assert(*events[0]==Event("name1", "1/1/2022", "place1"));
	assert(event_service.exists("name1", "1/1/2022","place1") == true);

	event_service.update_event("name1", "1/1/2022","place1", "name2", "2/2/2022", "place2");
	assert(events.size() == 1);
	assert(*events[0] == Event("name2", "2/2/2022", "place2"));
	assert(event_service.exists("name1", "1/1/2022", "place1") == false);
	assert(event_service.exists("name2", "2/2/2022", "place2") == true);

	event_service.delete_event("name2", "2/2/2022", "place2");
	events = event_service.get_all_events();
	assert(events.size() == 0);
	assert(event_service.exists("name2", "2/2/2022", "place2") == false);
}

void test_network()
{
	List<User>* user_list = new List<User>();
	User_validator user_validator;
	User_repo user_repo(user_list);
	User_service user_service(user_repo, user_validator);
	Multimap<User&, Friendship> friendship_multimap;
	Friendship_repo friendship_repo(friendship_multimap);
	Friendship_validator friendship_validator;
	Friendship_service friendship_service(friendship_repo, friendship_validator);
	Multimap<User&, Message> message_multimap;
	Message_repo message_repo(message_multimap);
	Message_validator message_validator;
	Message_service message_service(message_repo, message_validator);
	List<Event>* event_list = new List<Event>();
	Event_repo event_repo(event_list);
	Event_validator event_validator;
	Event_service event_service(event_repo, event_validator);
	Network network(user_service, friendship_service, message_service, event_service);

	vector<User*> users = network.get_all_users();
	vector<Friendship> friendships = network.get_all_friendships();
	vector<Message> messages = network.get_all_messages();
	vector<Event*> events = network.get_all_events();
	assert(users.size() == 0);
	assert(friendships.size() == 0);
	assert(messages.size() == 0);
	assert(events.size() == 0);

	network.add_user("username1", "password1");
	users = network.get_all_users();
	assert(users.size() == 1);
	assert(*users[0] == User("username1", "password1"));

	network.update_user("username1", "password1", "username2", "password2");
	users = network.get_all_users();
	assert(users.size() == 1);
	assert(*users[0] == User("username2", "password2"));

	network.delete_user("username2", "password2");
	users = network.get_all_users();
	assert(users.size() == 0);

	network.add_user("username1", "password1");
	network.add_user("username2", "password2");
	User u1("username1", "password1"), u2("username2", "password2");
	users = network.get_all_users();
	assert(users.size() == 2);
	assert(*users[0] == u1);
	assert(*users[1] == u2);

	network.add_friend("username1", "username2");
	friendships = network.get_all_friendships();
	assert(friendships.size() == 1);
	assert(friendships[0] == Friendship(u1,u2));

	vector<Friendship> friendships_for_user = network.get_all_friendships_for_user("username1");
	assert(friendships_for_user.size() == 1);
	assert(friendships_for_user[0] == Friendship(u1, u2));
	friendships_for_user = network.get_all_friendships_for_user("username2");
	assert(friendships_for_user.size() == 1);
	assert(friendships_for_user[0] == Friendship(u1, u2));

	User u3("username3", "password3");
	network.add_user("username3", "password3");
	network.add_friend("username1", "username3");
	network.delete_friend("username2", "username1");
	friendships = network.get_all_friendships();
	assert(friendships.size() == 1);
	assert(friendships[0] == Friendship(u1, u3));

	friendships_for_user = network.get_all_friendships_for_user("username1");
	assert(friendships_for_user.size() == 1);
	assert(friendships_for_user[0] == Friendship(u1, u3));
	friendships_for_user = network.get_all_friendships_for_user("username3");
	assert(friendships_for_user.size() == 1);
	assert(friendships_for_user[0] == Friendship(u1, u3));
	friendships_for_user = network.get_all_friendships_for_user("username2");
	assert(friendships_for_user.size() == 0);

	network.send_message("username1", "username3","message1");
	messages = network.get_all_messages();
	assert(messages.size() == 1);
	assert(messages[0] == Message(u1, u3, "message1"));

	vector<Message> messages_for_user = network.get_all_messages_for_user("username1");
	assert(messages_for_user.size() == 1);
	assert(messages_for_user[0] == Message(u1, u3, "message1"));
	messages_for_user = network.get_all_messages_for_user("username3");
	assert(messages_for_user.size() == 1);
	assert(messages_for_user[0] == Message(u1, u3, "message1"));

	network.delete_message("username1", "username3", "message1");
	messages = network.get_all_messages();
	assert(messages.size() == 0);

	messages_for_user = network.get_all_messages_for_user("username1");
	assert(messages_for_user.size() == 0);
	messages_for_user = network.get_all_messages_for_user("username3");
	assert(messages_for_user.size() == 0);

	network.add_event("event1", "date1", "place1");
	events = network.get_all_events();
	assert(events.size() == 1);
	assert(*events[0] == Event("event1", "date1", "place1"));

	network.update_event("event1", "date1", "place1", "event1", "date2", "place2");
	assert(events.size() == 1);
	assert(*events[0] == Event("event1", "date2", "place2"));

	network.delete_event("event1", "date2", "place2");
	events = network.get_all_events();
	assert(events.size() == 0);
}

void test_all()
{
	test_user();
	test_friendship();
	test_message();
	test_event();

	test_list();
	test_multimap();

	test_repo_user();
	test_repo_friendship();
	test_repo_message();
	test_repo_event();

	test_service_user();
	test_service_friendship();
	test_service_message();
	test_service_event();

	test_network();
}
