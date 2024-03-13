#include "bits/stdc++.h"
using namespace std;
#include "User_classes.h"

class online_book_reader {
private:
	User_manager user_manager;
	Book_manager book_manager;
public:

	const void run() {
		user_manager.load_database();
		user_manager.load_database2();
		book_manager.load_database();
		while (1) {
			user_manager.aceess_system(book_manager);
		}
	}
};

int main() {	
	online_book_reader object;
	object.run();

}
