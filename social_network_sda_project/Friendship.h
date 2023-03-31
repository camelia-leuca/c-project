#pragma once
#include"Multimap.h"
#include "User.h"
class Friendship
{
private:
	User&sender, &receiver;
	int id;

	void set_id(int id);
public:
	Friendship(User&sender,User&receiver);
	Friendship(const Friendship&f);
	~Friendship();

	int get_id();
	User& get_sender();
	User& get_receiver();

	void set_sender(User&sender);
	void set_receiver(User&receiver);

	Friendship& operator=(const Friendship& f);
	bool operator==(const Friendship& f);


	friend ostream& operator<<(ostream& os, const Friendship& f);
};