#pragma once
#include "Network.h"
class UI
{
private:
	Network& network;
public:
	UI(Network& network);
	~UI();

	void ui_run_menu();

private:

	void display_menu();

	void ui_add_user();
	void ui_delete_user();
	void ui_update_user();
	void ui_show_all_users();

	void ui_add_friend();
	void ui_delete_friend();
	void ui_show_all_friendships_for_user();
	void ui_show_all_common_friendships_for_users();
	void ui_show_all_friendships(vector<Friendship> friendships);

	void ui_send_message();
	void ui_delete_message();
	void ui_show_all_messages(vector<Message> messages);
	void ui_show_all_messages_for_user();
	void ui_show_all_messages_for_users();

	void ui_add_event();
	void ui_delete_event();
	void ui_update_event();
	void ui_show_all_events();
};