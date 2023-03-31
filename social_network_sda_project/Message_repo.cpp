#include "Message_repo.h"

Message_repo::Message_repo(Multimap<User&, Message>& message_multimap): message_multimap(message_multimap)
{
}

Message_repo::~Message_repo()
{
}

vector<Message> Message_repo::get_all_messages()
{
	vector<Message> duplicates = this->message_multimap.get_all(1); // identical messages between the same sender and receiver have different ids
	vector<Message> result;
	for (int i = 0; i < duplicates.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < result.size(); j++)
			if (duplicates[i].get_id() == result[j].get_id())
				found = true, j = result.size();
		if (!found)
			result.push_back(duplicates[i]);
	}
	return result;
}

void Message_repo::add_message(Message& message)
{
	this->message_multimap.put(message.get_sender(), message);
	this->message_multimap.put(message.get_receiver(), message);
}

void Message_repo::delete_message(Message& message)
{
	this->message_multimap.remove(message.get_sender(), message);
	this->message_multimap.remove(message.get_receiver(), message);
}

void Message_repo::remove_from_messages(User& user)
{
	this->message_multimap.remove(user);
}

bool Message_repo::message_exists(User& user)
{
	return this->message_multimap.exists(user);
}

bool Message_repo::message_exists(Message& message)
{
	return this->message_multimap.exists(message.get_sender(), message); // a message is deleted for both users
}
