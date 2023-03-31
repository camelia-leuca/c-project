#include "Message_validator.h"

Message_validator::Message_validator()
{
}

Message_validator::~Message_validator()
{
}

int Message_validator::validate(Message& m)
{
    this->no_errors = 0;
    this->message = "";
    if (m.get_receiver() == m.get_sender())
    {
        this->no_errors++;
        this->message += "Numele utilizatorilor trebuie sa fie diferite!";
    }
    if (strlen(m.get_message())==0)
    {
        this->no_errors++;
        this->message += "Mesajul trebuie completat!";
    }
    return this->no_errors;
}

int Message_validator::get_no_errors()
{
    return this->no_errors;
}

string Message_validator::get_message()
{
    return this->message;
}
