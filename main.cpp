//#include "stdafx.h"
#include "state.h"

using namespace std;

void go_home() {};
void change_price_type() {};
void exit_all() {};
void bets() {};
void create_bet() {};
void show_logs() {};
void reName() {};

bool isDigit(string s) {

	for (size_t n = 0; n < s.length(); n++) {
		if (!isdigit(s[n])) {
			return false;
			break;
		}
	}
	return true;
}

void navigation(Currentstate& c) {

	string s;
	bool isdig;

	cin >> s;
	isdig = isDigit(s);

	if (isdig)
		c.levelChange(s, "app");
	else
		c.receiveOperation(s);
}

void write_database(string& username, string& password, string& fullname, int type) {
	ifstream users("users.csv");
	//Find the last id of the .csv file
	string line, cell;
	getline(users, line);
	while (true) {

		getline(users, line);
		stringstream lineStream(line);
		getline(lineStream, cell, ',');
		if (users.eof())
			break;
	}
	int id;
	stringstream convert(cell);
	convert >> id;
	id++;

	ofstream database;
	database.open("users.csv", ios::app);      //append mode(go to the end and add)

	database << id << "|" << username << "|" << fullname << "|" << password << "|" << type << ",,,\n";
	return;
}

//return 0 if nothing exist , -1 if only username exist else typeofuser
int check_database(string& username, string& password, vector<string>& table) {
	ifstream database("users.csv");
	string line;
	string cell;
	getline(database, line);
	while (true) {
		getline(database, line);
		istringstream is(line);
		getline(is, cell, '|');
		getline(is, cell, '|');
		if (username == cell) {
			getline(is, cell, '|');
			getline(is, cell, '|');
			if (password == cell) {
				stringstream lineStream2(line);
				while (getline(lineStream2, cell, '|')) {
					table.push_back(cell);
				}
				return 1;
			}
		}
		if (database.eof()) break;

	}
	return 0;
}

int login(vector<string>& table) {
	string username, password;

	while (1) {
		cout << "\n\nWelcome to BetYourHome.gr" << endl;
		cout << "For login please instert your credentials. For Guest user insert Enter or guest:guest" << endl;

		cout << "Username :";
		getline(cin, username);
		cout << "Password :";
		getline(cin, password);

		if (!(username.compare("") || password.compare("")) || (username == "guest" && password == "guest")) {         //User = Guest
			return 0;
		}
		else {       //User != Guest
			int user_type;

			if (user_type = check_database(username, password, table)) {      //check the database if the credentials are correct
				cout << "Successful login\n" << endl;
				return user_type;
			}
			else
				cout << "Wrong password!\n\n\n\n";
		}
	}
}

bool sign_up() {
	string username, password;
	vector<string> table;

	cout << "\n\nSign up for BetYourHome.gr\n" << endl;

	cout << "Username :";
	getline(cin, username);
	cout << "Password :";
	getline(cin, password);

	if (check_database(username, password, table) != 0) {
		cout << "\n\nUsername already exist\n\n";
		return false;
	}
	else {
		string fullname;
		cout << "Fullname :";
		getline(cin, fullname);

		write_database(username, password, fullname, 1);
		return true;
	}
}

int main(int argc, char** argv) {
	//Manipulate arguments
	Currentstate *currentstate;
	if (argc <= 1) {                      // No argument = login
		vector<string> user_details;
		int user = login(user_details);

		if (user != 0) {

			if (atoi((user_details[4].c_str())) == 1) {

				string cell;
				istringstream checkplayer(user_details[5]);
				getline(checkplayer, cell, ' ');

				if (cell == "L") {
					getline(checkplayer, cell);
					cout << "The player is banned because of " << cell << endl;
					return 0;
				}
			}
			currentstate = new Currentstate(user_details);
		}
		else
			currentstate = new Currentstate;

		ofstream log;
		log.open("audit.log", ios::app);
		log << user_details[1] << " logged in " << endl;
		
		while (true) {
			if (system("CLS")) system("clear");
			currentstate->showOperations();
			navigation(*currentstate);
		}


	}
	else {
		string argv1 = argv[1];

		if (argv1.compare("-R") == 0) {

			if (!sign_up())      //if username already exist
				return 0;
		}
		else {
			cout << "-no arguments for login\n" << "-R argument for sign up" << endl;
			return 0;
		}
	}
	getchar();
}