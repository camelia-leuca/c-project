#pragma once
#include "Friendship_repo.h"
#include "List.h"
#include "Friendship_validator.h"
class Friendship_service
{
private:
	Friendship_repo& friendship_repo;
	Friendship_validator& friendship_validator;
public:
	Friendship_service(Friendship_repo& friendship_repo, Friendship_validator& friendship_validator);
	~Friendship_service();
	
	vector<Friendship> get_all_friendships();

	void add_friendship(User&sender, User&receiver);
	void delete_friendship(User& user, User& friend_to_delete);
	void remove_from_friendships(User& user);

	bool friendship_exists(User& user1, User& user2);
	bool friendship_exists(User& user);

	vector<Friendship> get_all_friends_for_user(User& user);
	vector<Friendship> get_all_common_friends_for_users(User& user1, User& user2);
};