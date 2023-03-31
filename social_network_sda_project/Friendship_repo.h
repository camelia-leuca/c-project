#pragma once
#include "User.h"
#include "Multimap.h"
#include "Friendship.h"
class Friendship_repo
{
private:
	Multimap<User&,Friendship>&friendship_multimap;
public:
	Friendship_repo(Multimap<User&, Friendship>& friendship_multimap);
	~Friendship_repo();

	vector<Friendship> get_all_friendships();

	void add_friendship(Friendship& friendship);
	void delete_friendship(Friendship& friendship);
	void remove_from_friendships(User& user);

	bool friendship_exists(Friendship& friendship);
	bool friendship_exists(User& user);
};