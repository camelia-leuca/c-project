#include "Friendship.h"
#include "Network.h"

void Friendship::set_id(int id)
{
	this->id = id;
}

Friendship::Friendship(User&sender, User&receiver):sender(sender), receiver(receiver)
{
	Network::current_id++;
	this->id = Network::current_id;
}

Friendship::Friendship(const Friendship& f): sender(f.sender), receiver(f.receiver)
{
	this->id = f.id;
}

Friendship::~Friendship()
{
}

int Friendship::get_id()
{
	return this->id;
}

User& Friendship::get_sender()
{
	return this->sender;
}

User& Friendship::get_receiver()
{
	return this->receiver;
}

void Friendship::set_sender(User&sender)
{
	this->sender = sender;
}

void Friendship::set_receiver(User&receiver)
{
	this->receiver = receiver;
}

Friendship& Friendship::operator=(const Friendship& f)
{
	if (this !=&f)
	{
		this->set_sender(f.sender);
		this->set_receiver(f.receiver);
		this->set_id(f.id);
	}
	return *this;
}

bool Friendship::operator==(const Friendship& f)
{
	return f.sender==this->get_sender() and f.receiver==this->get_receiver();
}

ostream& operator<<(ostream& os, const Friendship& f)
{
	if (f.sender.get_username() and f.receiver.get_username())
		os << "Friendship(id: " << f.id << ", sender: " << f.sender << ", receiver: " << f.receiver << ")";
	return os;
}
