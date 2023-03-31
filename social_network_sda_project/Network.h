#pragma once
#include "User_service.h"
#include "Friendship_service.h"
#include "Message_service.h"
#include "Event_service.h"

class Network
{
private:
	User_service& user_service;
	Friendship_service& friendship_service;
	Message_service& message_service;
	Event_service& event_service;

public:
	static int current_id;
	Network(User_service& user_service, Friendship_service& friendship_service, Message_service& message_service, Event_service& event_service);
	~Network();

	void add_user(const char* username, const char* password);
	void delete_user(const char* username, const char* password);
	void update_user(const char* username, const char* password, const char* updated_username, const char* updated_password);
	vector<User*> get_all_users();

	void add_friend(const char* sender_username, const char* receiver_username);
	void delete_friend(const char* username, const char* username_to_delete);
	vector<Friendship> get_all_friendships();
	vector<Friendship> get_all_friendships_for_user(const char* username);
	vector<Friendship> get_all_common_friendships_for_users(const char* username1, const char* username2);

	void send_message(const char* sender_username, const char* receiver_username,const char* message);
	void delete_message(const char* sender_username, const char* receiver_username,const char* message);
	vector<Message> get_all_messages();
	vector<Message> get_all_messages_for_user(const char* username);
	vector<Message> get_all_messages_for_users(const char* username1, const char* username2);

	void add_event(const char* name, const char* date, const char* place);
	void delete_event(const char* name, const char* date, const char* place);
	void update_event(const char* name, const char* date, const char* place, const char* updated_name, const char* updated_date, const char* updated_place);
	vector<Event*> get_all_events();
};