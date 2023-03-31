#pragma once
#include "Message_repo.h"
#include "Message_validator.h"
class Message_service
{
private:
	Message_repo& message_repo;
	Message_validator& message_validator;
public:
	Message_service(Message_repo& message_repo, Message_validator& message_validator);
	~Message_service();

	vector<Message> get_all_messages();

	void send_message(User& sender, User& receiver,const char* message);
	void delete_message(User& sender, User& receiver,const char* message);
	void remove_from_messages(User& user);

	bool message_exists(User& sender, User& receiver,const char* message);
	bool message_exists(User& user);

	vector<Message> get_all_messages_for_user(User&user);
	vector<Message> get_all_messages_for_users(User&user1, User&user2);
};