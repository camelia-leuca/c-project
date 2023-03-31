#pragma once
#include "User.h"
#include "Message.h"
#include "Multimap.h"
class Message_repo
{
private:
	Multimap<User&, Message>& message_multimap;
public:
	Message_repo(Multimap<User&, Message>& message_multimap);
	~Message_repo();

	vector<Message> get_all_messages();

	void add_message(Message& message);
	void delete_message(Message& message);
	void remove_from_messages(User& user);

	bool message_exists(User& user);
	bool message_exists(Message& message);
};