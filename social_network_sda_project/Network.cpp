#include "Network.h"

int Network::current_id = 1000;

Network::Network(User_service& user_service, Friendship_service& friendship_service, Message_service& message_service, Event_service& event_service):user_service(user_service), friendship_service(friendship_service), message_service(message_service), event_service(event_service)
{

}

Network::~Network()
{
}

void Network::add_user(const char* username, const char* password)
{
	if (this->user_service.user_exists(username))
		throw("Numele de utilizator este folosit de altcineva!");
	this->user_service.add_user(username, password);
}

void Network::delete_user(const char* username, const char* password)
{
	if (this->user_service.user_exists(username) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	if (this->user_service.user_exists(username,password) == false)
		throw("Parola este gresita!");

	User* user = &this->user_service.get_user_by_username(username);
	if (this->friendship_service.friendship_exists(*user))
	{
		vector<Friendship> friendships = this->friendship_service.get_all_friends_for_user(*user);
		for (int i = 0; i < friendships.size(); i++)
		{
			this->friendship_service.delete_friendship(friendships[i].get_sender(), friendships[i].get_receiver());
		}
		this->friendship_service.remove_from_friendships(*user);
	}
	if (this->message_service.message_exists(*user))
	{
		vector<Message> messages = this->message_service.get_all_messages_for_user(*user);
		for (int i = 0; i < messages.size(); i++)
		{
			this->message_service.delete_message(messages[i].get_sender(), messages[i].get_receiver(),messages[i].get_message());
		}
		this->message_service.remove_from_messages(*user);
	}
	this->user_service.delete_user(username, password);
}

void Network::update_user(const char* username, const char* password, const char* updated_username, const char* updated_password)
{
	if (this->user_service.user_exists(username) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	if (this->user_service.user_exists(username, password) == false)
		throw("Parola este gresita!");
	if (this->user_service.user_exists(updated_username) == true)
		throw("Numele de utilizator este folosit de altcineva!");
	this->user_service.update_user(username, password, updated_username, updated_password);
}

vector<User*> Network::get_all_users()
{
	return this->user_service.get_all_users();
}

void Network::add_friend(const char* sender_username, const char* receiver_username)
{
	if (this->user_service.user_exists(sender_username) == false)
		throw("Utilizatorul cu numele dat care adauga un prieten nu exista!");

	if (this->user_service.user_exists(receiver_username) == false)
		throw("Utilizatorul de adaugat la lista de prieteni nu exista!");
	User* sender = &this->user_service.get_user_by_username(sender_username);
	User* receiver = &this->user_service.get_user_by_username(receiver_username);
	if (this->friendship_service.friendship_exists(*sender, *receiver) or this->friendship_service.friendship_exists(*sender, *receiver))
			throw("Utilizatorii dati sunt prieteni!");
	this->friendship_service.add_friendship(*sender, *receiver);
}

void Network::delete_friend(const char* username, const char* username_to_delete)
{
	if (this->user_service.user_exists(username) == false)
		throw("Utilizatorul cu numele dat care sterge un prieten nu exista!");

	if (this->user_service.user_exists(username_to_delete) == false)
		throw("Utilizatorul de sters din lista de prieteni nu exista!");

	User* user = &this->user_service.get_user_by_username(username);
	User* friend_to_delete = &this->user_service.get_user_by_username(username_to_delete);

	if (this->friendship_service.friendship_exists(*user, *friend_to_delete))
		this->friendship_service.delete_friendship(*user, *friend_to_delete);
	else
		if (this->friendship_service.friendship_exists(*friend_to_delete, *user))
			this->friendship_service.delete_friendship(*friend_to_delete, *user);
		else
			throw("Utilizatorii dati nu sunt prieteni!");

	if (this->friendship_service.get_all_friends_for_user(*user).size() == 0)
		this->friendship_service.remove_from_friendships(*user);
}

vector<Friendship> Network::get_all_friendships()
{
	return this->friendship_service.get_all_friendships();
}

vector<Friendship> Network::get_all_friendships_for_user(const char* username)
{
	if (this->user_service.user_exists(username) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	User* user = &this->user_service.get_user_by_username(username);
	return this->friendship_service.get_all_friends_for_user(*user);
}

vector<Friendship> Network::get_all_common_friendships_for_users(const char* username1, const char* username2)
{
	if (this->user_service.user_exists(username1) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	if (this->user_service.user_exists(username2) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	User* user1 = &this->user_service.get_user_by_username(username1);
	User* user2 = &this->user_service.get_user_by_username(username2);
	return this->friendship_service.get_all_common_friends_for_users(*user1, *user2);
}

void Network::send_message(const char* sender_username, const char* receiver_username,const char* message)
{
	if (this->user_service.user_exists(sender_username) == false)
		throw("Utilizatorul cu numele dat care trimite un mesaj nu exista!");

	if (this->user_service.user_exists(receiver_username) == false)
		throw("Utilizatorul care primeste un mesaj nu exista!");

	User* sender = &this->user_service.get_user_by_username(sender_username);
	User* receiver = &this->user_service.get_user_by_username(receiver_username);
	this->message_service.send_message(*sender, *receiver, message);
}

void Network::delete_message(const char* sender_username, const char* receiver_username,const char* message_to_delete)
{
	if (this->user_service.user_exists(sender_username) == false)
		throw("Utilizatorul cu numele dat a trimits mesajul de sters nu exista!");

	if (this->user_service.user_exists(receiver_username) == false)
		throw("Utilizatorul care a primit mesajul de sters nu exista!");

	User* sender = &this->user_service.get_user_by_username(sender_username);
	User* receiver = &this->user_service.get_user_by_username(receiver_username);

	if (this->message_service.message_exists(*sender, *receiver, message_to_delete) == false)
		throw("Mesajul de sters nu exista!");
	this->message_service.delete_message(*sender, *receiver, message_to_delete);

	if (this->message_service.get_all_messages_for_user(*sender).size() == 0)
		this->message_service.remove_from_messages(*sender);
	if (this->message_service.get_all_messages_for_user(*receiver).size() == 0)
		this->message_service.remove_from_messages(*receiver);
}

vector<Message> Network::get_all_messages()
{
	return this->message_service.get_all_messages();
}

vector<Message> Network::get_all_messages_for_user(const char* username)
{
	if (this->user_service.user_exists(username) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	User* user = &this->user_service.get_user_by_username(username);
	return this->message_service.get_all_messages_for_user(*user);
}

vector<Message> Network::get_all_messages_for_users(const char* username1, const char* username2)
{
	if (this->user_service.user_exists(username1) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	if (this->user_service.user_exists(username2) == false)
		throw("Utilizatorul cu numele dat nu exista!");
	User* user1 = &this->user_service.get_user_by_username(username1);
	User* user2 = &this->user_service.get_user_by_username(username2);
	return this->message_service.get_all_messages_for_users(*user1, *user2);
}

void Network::add_event(const char* name, const char* date, const char* place)
{
	this->event_service.add_event(name, date, place);
}

void Network::delete_event(const char* name, const char* date, const char* place)
{
	if (this->event_service.exists(name, date, place)==false)
		throw("Evenimentul dat nu exista!");
	this->event_service.delete_event(name, date, place);
}

void Network::update_event(const char* name, const char* date, const char* place, const char* updated_name, const char* updated_date, const char* updated_place)
{
	if (this->event_service.exists(name, date, place)==false)
		throw("Evenimentul dat nu exista!");
	this->event_service.update_event(name, date, place, updated_name, updated_date, updated_place);
}

vector<Event*> Network::get_all_events()
{
	return this->event_service.get_all_events();
}
