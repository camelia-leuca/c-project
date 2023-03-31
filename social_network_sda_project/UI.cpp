#include "UI.h"
#include "Exception.h"
using namespace std;
UI::UI(Network& network): network(network)
{
}

UI::~UI()
{
}

void UI::ui_run_menu()
{
	char option[10];
	bool invalid_option;


	while (true)
	{

		this->display_menu();
		cin >> option;
		invalid_option = true;
		if (strcmp(option, "1") == 0)
		{
			this->ui_add_user();
			invalid_option = false;
		}
		if (strcmp(option, "2") == 0)
		{
			this->ui_delete_user();
			invalid_option = false;
		}
		if (strcmp(option, "3") == 0)
		{
			this->ui_update_user();
			invalid_option = false;
		}
		if (strcmp(option, "au") == 0)
		{
			this->ui_show_all_users();
			invalid_option = false;
		}
		if (strcmp(option, "4") == 0)
		{
			this->ui_add_friend();
			invalid_option = false;
		}
		if (strcmp(option, "5") == 0)
		{
			this->ui_delete_friend();
			invalid_option = false;
		}
		if (strcmp(option, "6") == 0)
		{
			this->ui_show_all_friendships_for_user();
			invalid_option = false;
		}
		if (strcmp(option, "7") == 0)
		{
			this->ui_show_all_common_friendships_for_users();
			invalid_option = false;
		}
		if (strcmp(option, "af") == 0)
		{
			this->ui_show_all_friendships(this->network.get_all_friendships());
			invalid_option = false;
		}
		if (strcmp(option, "8") == 0)
		{
			this->ui_send_message();
			invalid_option = false;
		}
		if (strcmp(option, "9") == 0)
		{
			this->ui_delete_message();
			invalid_option = false;
		}
		if (strcmp(option, "10") == 0)
		{
			this->ui_show_all_messages_for_user();
			invalid_option = false;
		}
		if (strcmp(option, "11") == 0)
		{
			this->ui_show_all_messages_for_users();
			invalid_option = false;
		}
		if (strcmp(option, "am") == 0)
		{
			this->ui_show_all_messages(this->network.get_all_messages());
			invalid_option = false;
		}
		if (strcmp(option, "12") == 0)
		{
			this->ui_add_event();
			invalid_option = false;
		}
		if (strcmp(option, "13") == 0)
		{
			this->ui_update_event();
			invalid_option = false;
		}
		if (strcmp(option, "14") == 0)
		{
			this->ui_delete_event();
			invalid_option = false;
		}
		if (strcmp(option, "ae") == 0)
		{
			this->ui_show_all_events();
			invalid_option = false;
		}
		if (strcmp(option, "x") == 0)
		{
			break;
		}
		if (invalid_option)
		{
			cout << "Optiune gresita! Reincercati!"<<endl;
		}
	}
}

void UI::display_menu()
{
	cout << "1. Adauga utilizator." << endl;
	cout << "2. Sterge un utilizator." << endl;
	cout << "3. Modifica un utilizator." << endl;
	cout << "au. Arata toti utilizatorii." << endl;
	cout << endl;
	cout << "4. Adauga prieten." << endl;
	cout << "5. Stergere prieten." << endl;
	cout << "6. Arata toti prietenii unui utilizator." << endl;
	cout << "7. Arata toti prietenii comuni pentru doi utilizatori." << endl;
	cout << "af. Arata toate prieteniile." << endl;
	cout << endl;
	cout << "8. Adauga mesaj." << endl;
	cout << "9. Stergere mesaj." << endl;
	cout << "10. Arata toate mesajele ale unui utilizator." << endl;
	cout << "11. Arata toate mesajele dintre doi utilizatori." << endl;
	cout << "am. Arata toate mesajele." << endl;
	cout << endl;
	cout << "12. Adauga eveniment." << endl;
	cout << "13. Modifica eveniment." << endl;
	cout << "14. Stergere eveniment." << endl;
	cout << "ae. Arata toate evenimentele." << endl;
	cout << endl;
	cout << "x. Iesire." << endl;
	cout << "Optiune: ";
}

void UI::ui_add_user()
{
	try
	{
		char username[50], password[50];
		cout << "Dati numele de utilizator: ";
		cin.get();
		cin.getline(username, 50);
		cout << "Dati parola: ";
		cin.getline(password, 50);
		this->network.add_user(username, password);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_delete_user()
{
	try
	{
		char username[50], password[50];
		cout << "Dati numele utilizatorului de sters: ";
		cin.get();
		cin.getline(username, 50);
		cout << "Dati parola utilizatorului de sters: ";
		cin.getline(password, 50);
		this->network.delete_user(username, password);
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_update_user()
{
	try
	{
		char username[50], password[50], updated_username[50], updated_password[50];
		cout << "Dati numele utilizatorului de modificat: ";
		cin.get();
		cin.getline(username, 50);
		cout << "Dati parola utilizatorului de modificat: ";
		cin.getline(password, 50);
		cout << "Dati noul nume de utilizator: ";
		cin.getline(updated_username, 50);
		cout << "Dati noua parola: ";
		cin.getline(updated_password, 50);
		this->network.update_user(username, password, updated_username, updated_password);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_show_all_users()
{
	vector<User*> users = this->network.get_all_users();
	for (int i = 0; i < users.size(); i++)
		cout << *users[i] << endl;
}

void UI::ui_add_friend()
{
	try
	{
		char sender[50], receiver[50];
		cout << "Dati numele utilizatorului care trimeite cererea de prietenie: ";
		cin.get();
		cin.getline(sender, 50);
		cout << "Dati numele utilizatorului care primeste cererea de prietenie: ";
		cin.getline(receiver, 50);
		this->network.add_friend(sender, receiver);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_delete_friend()
{
	try
	{
		char username[50], username_to_delete[50];
		cout << "Dati numele utilizatorului care sterge un prieten: ";
		cin.get();
		cin.getline(username, 50);
		cout << "Dati numele de utilizatorului de sters: ";
		cin.getline(username_to_delete, 50);
		this->network.delete_friend(username, username_to_delete);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_show_all_friendships_for_user()
{
	try
	{
		char username[50];
		cout << "Dati numele de utilizator: ";
		cin.get();
		cin.getline(username, 50);
		this->ui_show_all_friendships(this->network.get_all_friendships_for_user(username));
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_show_all_common_friendships_for_users()
{
	try
	{
		char username1[50], username2[50];
		cout << "Dati numele primului utilizator: ";
		cin.get();
		cin.getline(username1, 50);
		cout << "Dati numele celui de-al doilea utilizator: ";
		cin.getline(username2, 50);
		this->ui_show_all_friendships(this->network.get_all_common_friendships_for_users(username1,username2));
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_show_all_friendships(vector<Friendship> friendships)
{
	for (int i = 0; i < friendships.size(); i++)
		cout << friendships[i]<<endl;
}

void UI::ui_send_message()
{
	try
	{
		char sender[50], receiver[50], message[50];
		cout << "Dati numele utilizatorului care trimite un mesaj: ";
		cin.get();
		cin.getline(sender, 50);
		cout << "Dati numele utilizatorului care primeste mesajul: ";
		cin.getline(receiver, 50);
		cout << "Dati mesajul de trimis: ";
		cin.getline(message, 50);
		this->network.send_message(sender, receiver, message);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_delete_message()
{
	try
	{
		char sender[50], receiver[50], message[50];
		cout << "Dati numele utilizatorului care a trimis mesajul de sters: ";
		cin.get();
		cin.getline(sender, 50);
		cout << "Dati numele utilizatorului care a primit mesajul de sters: ";
		cin.getline(receiver, 50);
		cout << "Dati mesajul de sters: ";
		cin.getline(message, 50);
		this->network.delete_message(sender, receiver, message);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_show_all_messages(vector<Message> messages)
{
	int i = messages.size() -1;
	for (;i>=0; i--)
		cout << messages[i]<< endl;
}

void UI::ui_show_all_messages_for_user()
{
	try
	{
		char username[50];
		cout << "Dati numele de utilizator: ";
		cin.get();
		cin.getline(username, 50);
		this->ui_show_all_messages(this->network.get_all_messages_for_user(username));
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_show_all_messages_for_users()
{
	try
	{
		char username1[50], username2[50];
		cout << "Dati numele primului utilizator: ";
		cin.get();
		cin.getline(username1, 50);
		cout << "Dati numele celui de-al doilea utilizator: ";
		cin.getline(username2, 50);
		this->ui_show_all_messages(this->network.get_all_messages_for_users(username1, username2));
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_add_event()
{
	try
	{
		char name[50], date[50], place[50];
		cout << "Dati numele evenimentului: ";
		cin.get();
		cin.getline(name, 50);
		cout << "Dati data in care se tine evenimentul (dd/mm/yyyy): ";
		cin.getline(date, 50);
		cout << "Dati locul unde se tine evenimentul: ";
		cin.getline(place, 50);
		this->network.add_event(name, date, place);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_delete_event()
{
	try
	{
		char name[50], date[50], place[50];
		cout << "Dati numele evenimentului de sters: ";
		cin.get();
		cin.getline(name, 50);
		cout << "Dati data in care se tine evenimentul de sters (dd/mm/yyyy): ";
		cin.getline(date, 50);
		cout << "Dati locul unde se tine evenimentul de sters: ";
		cin.getline(place, 50);
		this->network.delete_event(name, date, place);
	}
	catch (const char* e)
	{
		cout << "exception: " << e<< endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_update_event()
{
	try
	{
		char name[50], date[50], place[50], updated_name[50], updated_date[50], updated_place[50];
		cout << "Dati numele evenimentului de modificat: ";
		cin.get();
		cin.getline(name, 50);
		cout << "Dati data in care se tine evenimentul de modificat (dd/mm/yyyy): ";
		cin.getline(date, 50);
		cout << "Dati locul unde se tine evenimentul de modificat: ";
		cin.getline(place, 50);

		cout << "Dati noul nume al evenimentului: ";
		cin.getline(updated_name, 50);
		cout << "Dati noua data in care se tine evenimentul (dd/mm/yyyy): ";
		cin.getline(updated_date, 50);
		cout << "Dati noul loc in care se tine evenimentul: ";
		cin.getline(updated_place, 50);
		this->network.update_event(name, date, place, updated_name, updated_date, updated_place);
	}
	catch (Validation_exception e)
	{
		cout << "exception: " << e.what() << endl;
	}
	catch (const char* e)
	{
		cout << "exception: " << e << endl;
	}
	catch (...)
	{
		cout << "other exception..." << endl;
	}
}

void UI::ui_show_all_events()
{
	vector<Event*> events = this->network.get_all_events();
	for (int i = 0; i < events.size(); i++)
		cout << *events[i] << endl;
}

