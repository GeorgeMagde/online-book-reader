#include "bits/stdc++.h"
using namespace std;
int read_int(int low, int high) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;
	cin >> value;
	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return read_int(low, high);
}
int show_menu(const vector<string>& choices) {
	cout << "\nMenu:\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return read_int(1, choices.size());
}
bool valid_email(const string& email) {
	int idx = -1;
	for (int g = 0; g < email.size(); g++) {
		if (email[g] == '@') {
			if (idx == -1)
				idx = g;
			else
				return 0;
		}
	}
	if (idx == 0 or idx == email.size() - 1 or idx == -1)return 0;
	return 1;
}
class Book {
private :
	string isbn;
	string title;
	string author;
	vector<string>pages;
public:
	void read() {
		string str;
		cout << "Enter ISBN: "; cin >> str;
		set_isbn(str);

		cout << "Enter Title: "; cin >> str;
		set_title(str);

		cout << "Enter Author Name: "; cin >> str;
		set_author(str);

		cout << "Enter How many pages: ";
		int number_of_pages; cin >> number_of_pages;
		vector<string>pages(number_of_pages);

		for (int page = 0; page < number_of_pages; ++page) {
			cout << "Enter page # " << page + 1 << ": ";
			cin >> pages[page];
		}
		set_pages(pages);
	}
	const void set_isbn(const string& isbn) {
		this->isbn = isbn;
	}
	const string& get_isbn() const {
		return this->isbn;
	}

	const void set_title(const string& title) {
		this->title = title;
	}
	const string& get_title() const {
		return this->title;
	}

	const void set_author(const string& author_name) {
		this->author = author_name;
	}
	const string& get_author() const {
		return this->author;
	}

	const void set_pages(const vector<string>& pages) {
		this->pages = pages;
	}
	const vector<string>& get_pages()const {
		return this->pages;
	}

	const int get_number_of_pages() const {
		return this->pages.size();
	}

};
class reading_book {
private:
	Book book;
	int current_page;
public:
	reading_book(const Book &book) :book(book), current_page(1) {};
	const Book& get_book()const  {
		return this->book;
	}
	const void show_current_page()const  {
		cout << current_page << " / " << book.get_number_of_pages() << "\n";
	}
	const int& get_current_page()const {
		return current_page;
	}
	 const void next_page()  {
		if (current_page == book.get_number_of_pages()) {
			cout << "\nYou are at last page already\n";
			return;
		}
		else
			current_page++;
	}
	const void previous_page() {
		if (current_page == 1) {
			cout << "\nYou are at first page already\n";
			return;
		}
		else
			current_page--;
	}
	const string& current_page_content()const {
		return book.get_pages()[current_page - 1];
	}
	const void session()  {
		vector<string>menu;
		menu.push_back("Next Page");
		menu.push_back("Previos page");
		menu.push_back("Stop Reading");
		while (1) {
			cout << "Current page : ";show_current_page();
			cout << current_page_content() << "\n";
			int idx = show_menu(menu);
			if (idx == 1) {
				next_page();
			}
			else if (idx == 2) {
				previous_page();
			}
			else break;
		}
	}

};
class Book_manager {
private:
	map<string, Book>books;
public:
	void load_database() { // function to add some books initialy
	//	cout << "BooksManager: load_database\n";
		Book book1;
		book1.set_isbn("00001");
		book1.set_author("Omar abdo");
		book1.set_title("C++ how to program");
		vector<string> pages1 = { "A C++", "B C++", "C C++", "D C++", "E C++" };
		book1.set_pages(pages1);
		add_book(book1);

		Book book2;
		book2.set_isbn("00002");
		book2.set_author("George");
		book2.set_title("Intro to algo");
		vector<string> pages2 = { "A Algo", "B Algo", "C Algo", "D Algo", "E " };
		book2.set_pages(pages2);
		add_book(book2);

		Book book3;
		book3.set_isbn("00003");
		book3.set_author("George");
		book3.set_title("Data Structures in C++");
		vector<string> page3 = { "A Data", "B Data", "C Data", "D Data", "E Data" };
		book3.set_pages(page3);
		add_book(book3);
	}
	const void add_book(const Book& book) {
		books[book.get_title()] = book;
	}
	const void add_book() {
		Book book;
		book.read();
		books[book.get_title()] = book;
		cout << "Book added successfully\n";
	}
	const void search() {
		cout << "\nEnter title of the book you are searching :";
		string title; cin >> title;
		if (!books.count(title)) {
			cout << "\nNo such book.\n";
			return;
		}
		cout << "\nYes we have this book .\n";
	}
	const  map<string, Book>&available_bboks() const {
		return books;
	}
};
