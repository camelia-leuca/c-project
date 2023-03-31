#include "Friendship_validator.h"

Friendship_validator::Friendship_validator()
{
}

Friendship_validator::~Friendship_validator()
{
}

int Friendship_validator::validate(Friendship& f)
{
    this->no_errors = 0;
    this->message = "";
    if (f.get_receiver() == f.get_sender())
    {
        this->no_errors++;
        this->message += "Numele utilizatorilor trebuie sa fie diferite!";
    }
    return this->no_errors;
}

int Friendship_validator::get_no_errors()
{
    return this->no_errors;
}

string Friendship_validator::get_message()
{
    return this->message;
}
