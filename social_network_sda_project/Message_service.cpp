#include "Message_service.h"
#include "Exception.h"

Message_service::Message_service(Message_repo& message_repo, Message_validator& message_validator): message_repo(message_repo),message_validator(message_validator)
{
}

Message_service::~Message_service()
{
}

vector<Message> Message_service::get_all_messages()
{
	return this->message_repo.get_all_messages();
}

void Message_service::send_message(User& sender, User& receiver,const char* message)
{
	Message m(sender, receiver, message);
	if (this->message_validator.validate(m) == 0)
		this->message_repo.add_message(m);
	else
		throw Validation_exception(message_validator.get_message());
}

void Message_service::delete_message(User& sender, User& receiver,const char* message)
{
	Message m(sender, receiver, message);
	if (this->message_validator.validate(m) == 0)
		this->message_repo.delete_message(m);
	else
		throw Validation_exception(message_validator.get_message());
}

void Message_service::remove_from_messages(User& user)
{
	this->message_repo.remove_from_messages(user);
}

bool Message_service::message_exists(User& sender, User& receiver,const char* message)
{
	Message m(sender, receiver, message);
	return this->message_repo.message_exists(m);
}

bool Message_service::message_exists(User& user)
{
	return this->message_repo.message_exists(user);
}

vector<Message> Message_service::get_all_messages_for_user(User&user)
{
	vector<Message> result;
	vector<Message> messages = this->message_repo.get_all_messages();
	for (int i = 0; i < messages.size(); i++)
		if (messages[i].get_sender() == user or messages[i].get_receiver() == user)
			result.push_back(messages[i]);
	if (result.size())
		return result;
	return vector<Message>();
}

vector<Message> Message_service::get_all_messages_for_users(User& user1, User& user2)
{
	vector<Message> result;
	vector<Message> messages = this->message_repo.get_all_messages();
	for (int i = 0; i < messages.size(); i++)
		if ((messages[i].get_sender() == user1 or messages[i].get_receiver() == user1) and (messages[i].get_sender() == user2 or messages[i].get_receiver() == user2))
			result.push_back(messages[i]);
	if (result.size())
		return result;
	return vector<Message>();
}
