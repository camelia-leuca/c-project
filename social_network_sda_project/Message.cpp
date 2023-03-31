#include "Message.h"
#include "Network.h"

void Message::set_id(int id)
{
	this->id = id;
}

Message::Message(User& sender, User& receiver,const char* message): sender(sender), receiver(receiver)
{
	Network::current_id++;
	this->id = Network::current_id;


	if (message == NULL)
		this->message = NULL;
	else
	{
		this->message = new char[strlen(message) + 1];
		strcpy_s(this->message, strlen(message) + 1, message);
	}
}

Message::Message(const Message& m): sender(m.sender), receiver(m.receiver)
{
	this->id = m.id;
	if (m.message == NULL)
		this->message = NULL;
	else
	{
		this->message = new char[strlen(m.message) + 1];
		strcpy_s(this->message, strlen(m.message) + 1, m.message);
	}
}

Message::~Message()
{
}

int Message::get_id()
{
	return this->id;
}

User& Message::get_sender()
{
	return this->sender;
}

User& Message::get_receiver()
{
	return this->receiver;
}

char* Message::get_message()
{
	return this->message;
}

void Message::set_sender(User& sender)
{
	this->sender = sender;
}

void Message::set_receiver(User& receiver)
{
	this->receiver = receiver;
}

void Message::set_message(char* message)
{
	if (message == NULL)
		this->message = NULL;
	else
	{
		this->message = new char[strlen(message) + 1];
		strcpy_s(this->message, strlen(message) + 1, message);
	}
}

Message& Message::operator=(const Message& m)
{
	if (this != &m)
	{
		this->set_sender(m.sender);
		this->set_receiver(m.receiver);
		this->set_message(m.message);
		this->set_id(m.id);
	}
	return *this;

}

bool Message::operator==(const Message& m)
{
	return m.sender==this->get_sender() and m.receiver==this->get_receiver() and strcmp(m.message,this->get_message())==0;
}

ostream& operator<<(ostream& os, const Message& m)
{
	if (m.sender.get_username() and m.receiver.get_username() and m.message)
		os << "Message(id: " << m.id << ", sender: " << m.sender << ", receiver: " << m.receiver << ", message: " << m.message << ")";
	return os;
}
