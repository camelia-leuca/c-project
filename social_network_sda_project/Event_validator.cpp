#include "Event_validator.h"

Event_validator::Event_validator()
{
}

Event_validator::~Event_validator()
{
}

int Event_validator::validate(Event& e)
{
    this->no_errors = 0;
    this->message = "";

    if (strlen(e.get_name()) == 0)
    {
        this->no_errors++;
        this->message += "Numele evenimentului trebuie completat!";
    }
    if (strlen(e.get_date()) == 0)
    {
        this->no_errors++;
        this->message += "Data evenimentului trebuie completata!";
    }
    if (strlen(e.get_place()) == 0)
    {
        this->no_errors++;
        this->message += "Locul unde se tine evenimentul trebuie completat!";
    }
    return this->no_errors;
}

int Event_validator::get_no_errors()
{
    return this->no_errors;
}

string Event_validator::get_message()
{
    return this->message;
}
