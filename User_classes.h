#include "bits/stdc++.h"
using namespace std;
#include "Book_classes.h"
class User {
private:
	string user_name;
	string password;
	string name;
	string email;
	bool admin = 0;
public:
	User(const User&) = delete;
	void operator=(const User&) = delete;

	User() {};
	User(const string& user_name, const string& password, const string& name, const string& email, const bool& admin) :
		user_name(user_name), password(password), name(name), email(email), admin(admin) {};

	const void set_user_name(const string& new_user_name) {
		this->user_name = new_user_name;
	}
	const string& get_user_name()const {
		return user_name;
	}

	const void set_password(const string& new_password) {
		this->password = new_password;
	}
	const string& get_password()const {
		return password;
	}

	const void set_name(const string& new_name) {
		this->name = new_name;
	}
	const string& get_name() const {
		return name;
	}

	const void set_email(const string& new_email) {
		this->email = new_email;
	}
	const string& get_email() const {
		return email;
	}

	const bool &get_admin() const {
		return this->admin;
	}
	const void set_admin(const bool &admin) {
		this->admin = admin;
	}

	const void view_profile() const {
		cout << "\nName: " << get_name() << "\n";
		cout << "Email: " << get_email() << "\n";
		cout << "User name: " << get_user_name() << "\n";
		cout << (get_admin() ? "Admin" : "User") << "\n";
	}
	void update_profile() {
		vector<string>menu;
		menu.push_back("Update password: ");
		menu.push_back("Update name: ");
		menu.push_back("Update email: ");
		int choice = show_menu(menu);
		if (choice == 1)
			update_password();
		else if (choice == 2)
			update_name();
		else
			update_email();
		cout << "\nProfile updated\n";
	}
	void update_password() {
		string password;
		while (1) {
			cout << "Enter new password (No spaces): "; cin >> password;
			string old_password;
			cout << "Enter old password to confirm "; cin >> old_password;
			if (old_password == get_password()) {
				break;
			}
			else {
				cout << "\nIncorrect password. Please try again\n";
			}
		}
		set_password(password);
	}
	void update_name() {
		string name;
		cout << "Enter new name (No spaces): "; cin >> name;
		set_name(name);
	}
	void update_email() {
		string email;
		while (1) {
			cout << "Enter new email (No spaces): "; cin >> email;
			if (valid_email(email))break;
			else
				cout << "\nInvalid email. Try again\n";
		}
		set_email(email);
	}
	virtual const void menu(Book_manager& book_manager) {};
};
class customer : public User {
private:
	vector<reading_book>history;
public:
	customer() {};
	customer(const string& user_name, const string& password, const string& name, const string& email, const bool& admin):
		User(user_name, password, name, email, admin) {}
	void select_from_history() {
		if (history.empty()) {
			cout << "\nYour history is empty\n";
			return;
		}
		for (int g = 0; g < history.size(); g++) {
			cout << g + 1 << ": " << history[g].get_book().get_title() << " ";
			cout << " Page: ";
			history[g].show_current_page();
		}
		cout << "\nWhich session to open? :\n";
		int idx = read_int(1, history.size());
		history[idx - 1].session();
	}
	const void clear_history() {
		history.clear();
	}
	void list_available_books(const  map<string, Book>& available_books) {
		int i = 1;
		for (auto& it : available_books) {
			cout << i++ << " " << it.first << "\n";
		}
		cout << "\nWhich book to read ?:\n";
		int idx = read_int(1, i - 1);
		i = 1;
		for (auto& it : available_books) {
			if (i == idx) {
				history.push_back(reading_book(it.second));
				history.back().session();
				break;
			}
			else
				i++;
		}
	}
	const void menu(Book_manager& book_manager){
		vector<string> menu;
		menu.push_back("View Profile");
		menu.push_back("Update Profile");
		menu.push_back("List & Select from My Reading History");
		menu.push_back("Clear My Reading History");
		menu.push_back("List & Select from Available Books");
		menu.push_back("Logout");
		while (1) {
			int idx = show_menu(menu);
			if (idx == 1)
				view_profile();
			else if (idx == 2) {
				update_profile();
			}
			else if (idx == 3) {
				select_from_history();
			}
			else if (idx == 4) {
				clear_history();
			}
			else if (idx == 5) {
				list_available_books(book_manager.available_bboks());
			}
			else return;
		}
	}
};
class admin :public User {
public:
	admin() {};
	admin(const string& user_name, const string& password, const string& name, const string& email, const bool& admin) :
		User(user_name, password, name, email, admin) {}

	const void menu(Book_manager& book_manager) {
		vector<string> menu;
		menu.push_back("View Profile");
		menu.push_back("Update Profile");
		menu.push_back("Add Book");
		menu.push_back("Search Book");
		menu.push_back("Logout");
		while (1) {
			int idx = show_menu(menu);
			if (idx == 1) {
				view_profile();
			}
			else if (idx == 2) {
				update_profile();
			}
			else if (idx == 3) {
				book_manager.add_book();
			}
			else if (idx == 4) {
				book_manager.search();
			}
			else
				return;
		}
	}
};
class User_manager {
private:
	map<string, User*>users_database;
	User* current_user;
	void free_database() {
		for (auto pair : users_database) {
			delete pair.second;
		}
		users_database.clear();
		current_user = nullptr;
	}

public:
	User_manager(const User_manager&) = delete;
	void operator=(const User_manager&) = delete;
	User_manager() {
		free_database();
	};
	~User_manager() {
		free_database();
	}
	void load_database() {
		free_database();
	//	cout << "UsersManager: load_database\n";
		User* user1 = new admin();
		user1->set_user_name("georgegg");
		user1->set_password("123");
		user1->set_name("george");
		user1->set_email("georgemagde14@gmail.com");
		user1->set_admin(true);
		users_database[user1->get_user_name()] = user1;

		User* user2 = new admin();
		user2->set_user_name("omaranalog");
		user2->set_password("1234");
		user2->set_name("omar");
		user2->set_email("omar14@gmail.com");
		user2->set_admin(true);
		users_database[user2->get_user_name()] = user2;

		User* user3 = new admin();
		user3->set_user_name("anas_maged");
		user3->set_password("12345");
		user3->set_name("anas");
		user3->set_email("anas14@gmail.com");
		user3->set_admin(true);
		users_database[user3->get_user_name()] = user3;
		load_database2();

	}
	void load_database2() {
	//	cout << "UsersManager: load_database2\n";
		User* user1 = new customer();
		user1->set_user_name("3b3z");
		user1->set_password("321");
		user1->set_name("abdalazim");
		user1->set_email("3b3zsbaka@gmail.com");
		user1->set_admin(false);
		users_database[user1->get_user_name()] = user1;

		User* user2 = new customer();
		user2->set_user_name("eslam22");
		user2->set_password("4321");
		user2->set_name("eslam");
		user2->set_email("terstegen@gmail.com");
		user2->set_admin(false);
		users_database[user2->get_user_name()] = user2;

		User* user3 = new customer();
		user3->set_user_name("minaraouf");
		user3->set_password("54321");
		user3->set_name("mina");
		user3->set_email("mina555555@gmail.com");
		user3->set_admin(false);
		users_database[user3->get_user_name()] = user3;

		User* user4 = new customer();
		user4->set_user_name("ahmedashraf");
		user4->set_password("654321");
		user4->set_name("ashraf");
		user4->set_email("ashraf1700@gmail.com");
		user4->set_admin(false);
		users_database[user4->get_user_name()] = user4;
	}
	void update_database() {
		users_database[current_user->get_user_name()] = current_user;
		current_user = nullptr;
	}
	void aceess_system(Book_manager& book_manager) {
		int choice = show_menu({ "Login", "Sign Up" });
		if (choice == 1)
			login();
		else
			sign_up();
		cout << "\nHello " << current_user->get_name() << " | " << (current_user->get_admin() ? "Admin" : "User" )<< " View\n";
		current_user->menu(book_manager);
		update_database();
	}
	bool valid_user_name(string user_name) {
		if (users_database.count(user_name))return 0;
		return 1;
	}
	void sign_up(bool is_admin = 0) {
		cout << "\n";
		string user_name, password, name, email;
		while (1) {
			cout << "Enter user name (No spaces): ";
			cin >> user_name;
			if (valid_user_name(user_name))break;
			else
				cout << "Already used. Try again\n";
		}
		cout << "Enter password (No spaces): "; cin >> password;
		cout << "Enter name (No spaces): "; cin >> name;
		while (1) {
			cout << "Enter email (No spaces): "; cin >> email;
			if (valid_email(email))break;
			else
				cout << "Invalid email. Try again\n";
		}
		if (is_admin)
			current_user = new admin(user_name, password, name, email, is_admin);
		else
			current_user = new customer(user_name, password, name, email, is_admin);
	}
	void login() {
		cout << "\n";
		while (1) {
			string user_name, password;
			cout << "Enter user name (No spaces): "; cin >> user_name;
			cout << "Enter password (No spaces): "; cin >> password;
			if (!users_database.count(user_name)) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			User* tmp_user = users_database[user_name];
			if (tmp_user->get_password() != password) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
	
			current_user = tmp_user;
			break;
		}

	}
};