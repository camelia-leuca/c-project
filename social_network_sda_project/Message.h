#pragma once
#include "User.h"
#include <string>
using namespace std;
class Message
{
private:
	int id;
	User& sender, & receiver;
	char* message;

	void set_id(int id);
public:
	Message(User& sender, User& receiver,const char* message);
	Message(const Message&m);
	~Message();

	int get_id();
	User& get_sender();
	User& get_receiver();
	char* get_message();

	void set_sender(User& sender);
	void set_receiver(User& receiver);
	void set_message(char* message);

	Message& operator=(const Message& m);
	bool operator==(const Message& m);

	friend ostream& operator<<(ostream& os, const Message& m);
};