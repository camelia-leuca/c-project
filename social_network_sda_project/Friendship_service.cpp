#include "Friendship_service.h"
#include "Exception.h"

Friendship_service::Friendship_service(Friendship_repo& friendship_repo, Friendship_validator& friendship_validator): friendship_repo(friendship_repo), friendship_validator(friendship_validator)
{
}

Friendship_service::~Friendship_service()
{
}

vector<Friendship> Friendship_service::get_all_friendships()
{
	return this->friendship_repo.get_all_friendships();
}

void Friendship_service::add_friendship(User& sender, User& receiver)
{
	Friendship friendship = Friendship(sender, receiver);
	if (this->friendship_validator.validate(friendship) == 0)
		this->friendship_repo.add_friendship(friendship);
	else
		throw Validation_exception(friendship_validator.get_message());
}

void Friendship_service::delete_friendship(User& sender, User& receiver)
{
	Friendship friendship = Friendship(sender, receiver);
	if (this->friendship_validator.validate(friendship) == 0)
		this->friendship_repo.delete_friendship(friendship);
	else
		throw Validation_exception(friendship_validator.get_message());
}

void Friendship_service::remove_from_friendships(User& user)
{
	this->friendship_repo.remove_from_friendships(user);
}

bool Friendship_service::friendship_exists(User& user1, User& user2)
{
	Friendship friendship = Friendship(user1, user2);
	return this->friendship_repo.friendship_exists(friendship);
}

bool Friendship_service::friendship_exists(User& user)
{
	return this->friendship_repo.friendship_exists(user);
}

vector<Friendship> Friendship_service::get_all_friends_for_user(User& user)
{
	vector<Friendship> result;
	vector<Friendship> friendships = this->friendship_repo.get_all_friendships();
	for (int i = 0; i < friendships.size(); i++)
		if (friendships[i].get_sender() == user or friendships[i].get_receiver() == user)
			result.push_back(friendships[i]);
	if (result.size())
		return result;
	return vector<Friendship>();
}

vector<Friendship> Friendship_service::get_all_common_friends_for_users(User& user1, User& user2)
{
	vector<Friendship> result;
	vector<Friendship> friendships1 = this->get_all_friends_for_user(user1);
	vector<Friendship> friendships2 = this->get_all_friends_for_user(user2);
	int size1 = friendships1.size();
	int size2 = friendships2.size();
	for (int i = 0; i < size1; i++)
	{
		User sender1 = friendships1[i].get_sender();
		User receiver1 = friendships1[i].get_receiver();
		if(!((sender1==user1 and receiver1 == user2)or(sender1 == user2 and receiver1 == user1))) // skips over the friendship between user1 and user2
			for (int j = 0; j < size2; j++)
			{
				User sender2 = friendships2[j].get_sender();
				User receiver2 = friendships2[j].get_receiver();
				if(sender1==user1)
					if (receiver1 == sender2 or receiver1 == receiver2) // a common friend is found
					{
						result.push_back(friendships1[i]);
						result.push_back(friendships2[j]);
						j = size2;
					}
				if(receiver1==user1)
					if (sender1 == sender2 or sender1 == receiver2)// a common friend is found
					{
						result.push_back(friendships1[i]);
						result.push_back(friendships2[j]);
						j = size2;
					}
			}
	}
	if (result.size())
		return result;
	return vector<Friendship>();
}
