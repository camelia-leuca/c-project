#include "User_validator.h"

User_validator::User_validator()
{
}

User_validator::~User_validator()
{
}

int User_validator::validate(User& u)
{
    this->no_errors = 0;
    this->message = "";

    if (strlen(u.get_username()) == 0)
    {
        this->no_errors++;
        this->message += "Numele de utilizator trebuie completat!";
    }
    if (strstr(u.get_username()," "))
    {
        this->no_errors++;
        this->message += "Numele de utilizator nu poate contine spatii!";
    }
    if (strstr(u.get_password()," "))
    {
        this->no_errors++;
        this->message += "Parola nu poate contine spatii!";
    }
    if (strlen(u.get_password()) == 0)
    {
        this->no_errors++;
        this->message += "Parola trebuie completata!";
    }
    return this->no_errors;
}

int User_validator::get_no_errors()
{
    return this->no_errors;
}

string User_validator::get_message()
{
    return this->message;
}
