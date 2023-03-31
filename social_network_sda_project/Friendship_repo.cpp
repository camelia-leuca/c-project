#include "Friendship_repo.h"

Friendship_repo::Friendship_repo(Multimap<User&, Friendship>& friendship_multimap):friendship_multimap(friendship_multimap)
{
}

Friendship_repo::~Friendship_repo()
{
}

vector<Friendship> Friendship_repo::get_all_friendships()
{
	return this->friendship_multimap.get_all();
}

void Friendship_repo::add_friendship(Friendship& friendship)
{
	this->friendship_multimap.put(friendship.get_sender(), friendship);
	this->friendship_multimap.put(friendship.get_receiver(), friendship);
}

void Friendship_repo::delete_friendship(Friendship& friendship)
{
	this->friendship_multimap.remove(friendship.get_sender(),friendship);
	this->friendship_multimap.remove(friendship.get_receiver(),friendship);
}

void Friendship_repo::remove_from_friendships(User& user)
{
	this->friendship_multimap.remove(user);
}

bool Friendship_repo::friendship_exists(Friendship& friendship)
{
	return this->friendship_multimap.exists(friendship.get_sender(), friendship);
}

bool Friendship_repo::friendship_exists(User& user)
{
	return this->friendship_multimap.exists(user);
}
