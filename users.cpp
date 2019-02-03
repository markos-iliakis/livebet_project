//#include "stdafx.h"
#include "users.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

bool is_digit(string s) {

    for (size_t n = 0; n < s.length(); n++) {
        if (!isdigit(s[n])) {
            return false;
            break;
        }
    }
    return true;
}

string to_Str(double a) {

	stringstream ss;

	ss << a;

	return ss.str();
}


User::User(string username, string realname, string password, int id) :
		username(username), realname(realname), password(password), id(id) {
}
User::User(string username, string password) :
		username(username), realname(""), password(password), id(0){}

void User::showOperations(string level){
	cout << "Choose:" << endl <<
	"The ID of the node you wish to enter" << endl <<
	"H(Home),  to return to the main menu" << endl <<
	"T(Toggle), to change Prices" << endl <<
	"X(Exit), exiting from system "<< endl;
}


void User::getOperation(User *user, string operation, string& level, string price){}
void User::makeOperation(Player *player, string operation, string& level){}
void User::makeOperation(Guest *guest, string operation, string& level){}
void User::makeOperation(Booker *booker, string operation, string& level, string price){}
void User::makeOperation(Director *director, string operation, string& level){}

int User::recogniseUser(User *){return 0;}
bool User::recogniseDirector(User *){return true;}
int User::identity_of_user(Guest *){return 0;}
int User::identity_of_user(Player *){return 0;}
int User::identity_of_user(Booker *){return 0;}
int User::identity_of_user(Director *){return 0;}
bool User::identity_of_director(Guest *){return true;}
bool User::identity_of_director(Player *){return true;}
bool User::identity_of_director(Booker *){return true;}
bool User::identity_of_director(Director *){return true;}

string User::getUsername(){ return username;}

string User::getRealname(){ return realname;}

string User::getPassword(){ return password;}

void User::setUsername(string newusername){ username = newusername; }

void User::setPassword(string newpassword){ password = newpassword; }

int User::getId(){ return id; }

User::~User(){}

Guest::Guest(string username, string password) : User(username, password){
}

void Guest::getOperation(User *user, string operation, string& level, string price){
	user->makeOperation(this, operation, level);
}

void Guest::makeOperation(Guest *guest, string operation, string& level){
}

bool Guest::recogniseDirector(User * user){ return user->identity_of_director(this); }

bool Guest::identity_of_director(Guest *){ return false; }

int Guest::recogniseUser(User * user){ return user->identity_of_user(this); }

int Guest::identity_of_user(Guest *guest){ return 0;}


Wallet::Wallet(float remain) : remain(remain){

}

Wallet::Wallet(float remain, string allfreebets) : remain(remain){
	string cell1, cell2;
	istringstream bets(allfreebets);
	int number_of_freebets = 0;
	getline(bets, cell1, ',');
	while(cell1 != cell2){
        number_of_freebets++;
        cell2 = cell1;				//count number of freebets
        getline(bets, cell1, ',');
	}
	
	istringstream bets2(allfreebets);
	for (int i = 0; i < number_of_freebets; i++)
	{
		getline(bets2, cell1, ',');
		freebets.push_back(atof(cell1.c_str()));
		//cout << freebets[i] << endl;
	}
}

float Wallet::getRemain(){ return remain;}

vector<float> Wallet::getFreebets(){
	vector<float> copy;
	for (vector<float>::iterator it = freebets.begin() ; it != freebets.end(); ++it){
		copy.push_back(*it);
	}
	return copy;
}

void Wallet::increament(float freshmoney){
	remain += freshmoney;
}

int Wallet::getSize(){ return freebets.size(); }

void Wallet::showfreebets(){
	char index = 'a';
	for (vector<float>::iterator i = freebets.begin(); i != freebets.end(); ++i){
		cout << index << ".  " << *i << endl;
		index++;
	}
}

void Wallet::decreament(float bet){
	remain -= bet;
}

void Wallet::eraseFreebet(int position){
	freebets[position] = 0;
}

float Wallet::getFreebet(int position){ return freebets[position]; }

Wallet::~Wallet(){}

Guest::~Guest() {
	// TODO Auto-generated destructor stub
}

void Guest::showOperations(string level){
	this->User::showOperations(level);
}

Player::Player(string status, string username, string realname, string password, int id, float remain, string freebets) : User(username, realname, password, id), wallet(remain, freebets), status(status){
}

Player::Player(string status, string username, string realname, string password, int id, float remain) : User(username, realname, password, id), wallet(remain), status(status){
}

void Player::showOperations(string level){
	this->User::showOperations(level);
	istringstream tmp(level);
    string temp1;
    int counter = 0;

    while (getline(tmp, temp1, '.'))            //example of s: .1.1.2
        counter++;
	cout << "A(Account), to manage your account" << endl;
	if(counter == 5)
		cout << "P(Place), to place a bet" << endl;
}

void Player::getOperation(User *user, string operation, string& level, string price){
	user->makeOperation(this, operation, level);
}

void Player::makeOperation(Player *player, string operation, string& level){
	if(operation == "A" || operation == "Account"){
		this->enterAccount();
	}
	else if(operation == "P" || operation == "Place"){
		this->placeBet(level);
		fstream usersdatabase("users.csv");
		ofstream newdatabase("new.csv");
		string line, cell;
		getline(usersdatabase, line);
		newdatabase << line << endl;
		while(true){
			getline(usersdatabase, line);
			istringstream is(line);
			getline(is, cell, '|');
			if(this->getId() == atoi(cell.c_str())){
				newdatabase << this->getId() << '|' << this->getUsername() << '|' << this->getRealname() << '|' <<
				this->getPassword() << '|' << 1 << '|' << status << '|' << wallet.getRemain();
				if(wallet.getSize() > 0){
					vector<float> copy = wallet.getFreebets();
					newdatabase << '|';
					for (int i = 0; i < copy.size(); ++i){
						if(i == copy.size() - 1)
							newdatabase << copy[i] << endl;
						else
							newdatabase << copy[i] << ',';
					}
				}
					
				else
					newdatabase << endl;
			}
			else
				newdatabase << line << endl;
			if(usersdatabase.eof()) break;
		}
		usersdatabase.close();
		newdatabase.close();
		remove("users.csv");
		rename("new.csv", "users.csv");
	}
}

int Player::recogniseUser(User *user){return user->identity_of_user(this); }

bool Player::recogniseDirector(User * user){ return user->identity_of_director(this); }

bool Player::identity_of_director(Player *){ return false; }

int Player::identity_of_user(Player *player){ return 1; }

Wallet& Player::getWallet(){
	return wallet;
}

void Player::enterAccount(){
	if (system("CLS")) system("clear");
	cout << "Player: " << this->getRealname() << " and username: " << this->getUsername() << endl;
	Wallet w = this->getWallet();
	cout << "Available remain: " << w.getRemain() << endl;
	cout << "Coupons' List: ";
	vector<float> myvector = w.getFreebets();
	for (vector<float>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		cout << *it << " ";
	cout << endl << endl;
	
	string operation;
	bool flag = true;
	while(flag == true){
		cout << "Choices: " << endl <<
		"R(Rename), to change name" << endl <<
		"P(Password), to change your password" << endl <<
		"B(Bets), to show history of bets" << endl <<
		"D(Deposit), to refill your account and increase the remain" << endl;
		getline(cin, operation);
		if(operation == "R" || operation == "Rename"){
			flag = false;
			this->renamePlayer();
		}
		else if(operation == "P" || operation == "Password"){
			flag = false;
			this->changePassword();
		}
		else if(operation == "B" || operation == "Bets"){
			this->betsHistory();
			flag = false;
		}
		else if(operation == "D" || operation == "Deposit"){
			this->refillAccount();
			flag = false;
		}
		else
			cout << "Wrong code of operation, Please try again" << endl;
	}
	fstream usersdatabase("users.csv");
	ofstream newdatabase("new.csv");
	string line, cell;
	getline(usersdatabase, line);
	newdatabase << line << endl;
	while(true){
		getline(usersdatabase, line);
		istringstream is(line);
		getline(is, cell, '|');
		if(this->getId() == atoi(cell.c_str())){
			newdatabase << this->getId() << '|' << this->getUsername() << '|' << this->getRealname() << '|' <<
			this->getPassword() << '|' << 1 << '|' << status << '|' << wallet.getRemain();
			if(wallet.getSize() > 0){
				vector<float> copy = wallet.getFreebets();
				newdatabase << '|';
				for (int i = 0; i < copy.size(); ++i){
					if(i == copy.size() - 1)
						newdatabase << copy[i] << endl;
					else
						newdatabase << copy[i] << ',';
				}
			}
				
			else
				newdatabase << endl;
		}
		else
			newdatabase << line << endl;
		if(usersdatabase.eof()) break;
	}
	usersdatabase.close();
	newdatabase.close();
	remove("users.csv");
	rename("new.csv", "users.csv");
}

void Player::renamePlayer(){
	bool  flag = true, found = true;
	string name, line, cell;
	ifstream database("users.csv");
	ofstream newdatabase("new.csv");
	getline(database, line);
	while(flag == true){
		found = true;
		cout << "Please Give the new Name" << endl;
		cin >> name;
		if(name == "guest"){
			cout << "Not valid name please try again" << endl;
			found = false;
	    }
		while(true){
			getline(database, line);
			istringstream is(line);
			getline(is, cell, '|');
	        getline(is, cell, '|');
	        if(name == cell){
	        	cout << "The name you entered already exists. Please try again" << endl;
	        	found = false;
	        }
	        if ( database.eof())
	        	break;
	        
		}
		if(found == true)
			flag = false;	
		
	}
	int size = wallet.getSize();
	if(found == true){		//the name is valid make the change at the users.csv
		ifstream database("users.csv");
		getline(database, line);
		newdatabase << line << endl;
		while(true){
			getline(database, line);
			istringstream is(line);
			getline(is, cell, '|');
			if(this->getId() == atoi(cell.c_str())){
				newdatabase << cell << '|' << name << '|';
				getline(is, cell, '|');
				for (int i = 0; i < 4; ++i){
					getline(is, cell, '|');
					newdatabase << cell << '|';
				}
				getline(is, cell, '|');
				newdatabase << cell;
				if(size != 0){
					newdatabase << '|';
					getline(is, cell, '|');
					newdatabase << cell;
				}
				
				
				newdatabase << endl;
			}
			else
				newdatabase << line << endl;
			if ( database.eof() ) break;
		}
	}

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Rename " << "changed to " << name << endl;


	database.close();
	newdatabase.close();
	remove("users.csv");
	rename("new.csv", "users.csv");
	this->setUsername(name);

	 
}

void Player::changePassword(){
	string password1, password2, cell, line;
	int id;
	ifstream database("users.csv");
	ofstream newdatabase("new.csv");
	do{
		cout << "Please enter the new password" << endl;
	cin >> password1;
	cout << "Please re-enter the password" << endl;
	cin >> password2;
	if(password1 != password2)
		cout << "The 2 password you entered don't match, please try again" << endl;
	}while(password1 != password2);
	id = this->getId();
	getline(database, line);
	newdatabase << line << endl;
	int size = wallet.getSize();
	while(true){
		getline(database, line);
		istringstream is(line);
		getline(is, cell, '|');
		if(id == atoi(cell.c_str())){
				newdatabase << cell << '|';
				for (int i = 0; i < 2; ++i){
					getline(is, cell, '|');
					newdatabase << cell << '|';
				}
				newdatabase << password1 << '|';
				getline(is, cell, '|');
				for (int i = 0; i < 3; ++i){
					getline(is, cell, '|');
					if(i == 2)
						newdatabase << cell;
					else
						newdatabase << cell << '|';
				}
				if(size != 0){
					getline(is, cell, '|');
					newdatabase << '|' << cell;
				}
				
				
				newdatabase << endl;

		}
		else
			newdatabase << line << endl;
		if ( database.eof() ) break;
	}

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Password " << "changed to " << password1 << endl;
	database.close();
	newdatabase.close();
	remove("users.csv");
	rename("new.csv", "users.csv");
	this->setPassword(password1);
}

void Player::betsHistory(){
	string cell, line;
	ifstream database("bets.csv");
	getline(database, line);
	while(true){
		getline(database, line);
		istringstream is(line);
		getline(is, cell, '|');
		getline(is, cell, '|');
		if(this->getId() == atoi(cell.c_str())){
			istringstream newline(line);
			string bet;
			for(int j = 0; j < 5; j++){
		    	getline(newline, bet, '|');
		    	cout << setw (10) << bet << " | ";
		    }
		    cout << endl;
		}

		if ( database.eof() ) break;
	}
	string pause;
	getline(cin, pause);
	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Bets " << "Player viewed his bets" << endl;
}

void Player::refillAccount(){
	string money;
	cout << "Please enter the amount of money you wish to store to your account" << endl;
	getline(cin, money);
	wallet.increament(atof(money.c_str()));

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Deposit " << "Player refilled his wallet with " << money << endl;
}

void Player::placeBet(string currentlevel){				//prepei edw na grafeis meta sto istoriko kai sto bets.csv
	string eventchoice, bet, line, cell;
	ifstream database("bets.csv");
	while(true){
		getline(database, line);
		istringstream is(line);
		getline(is, cell, '|');
		if ( database.eof() ) break;
	}
	
	
	bool type_of_bet; //true for money false for freebet;
	bool succes_bet = false;
	char index;
	cout << "Available remain in account: " << wallet.getRemain() << endl;
	if(eventchoice == "cancel")
		return;
	else{
		while(succes_bet == false){
			if(wallet.getSize() != 0){
				wallet.showfreebets();
				cout << "Please give the amount of money you want to bet or the number of freebet" << endl;
			}
			else{
				cout << "No available freebets" << endl;
				cout << "Please give the amount of money you want to bet" << endl;
			}
			cin >> bet;
			type_of_bet = is_digit(bet);
			if(type_of_bet == true){
				if(wallet.getRemain() == 0){
					cout << "No money in the wallet, please enter your account to refill" << endl;
					return;
				}
				else if(atof(bet.c_str()) > wallet.getRemain()){
					cout << "Sorry, not enough money in the wallet, please try again" << endl;
					return;
				}

				else{
					wallet.decreament(atoi(bet.c_str()));
					succes_bet = true;
				}
			}
			else{
				cout << "Please enter the letter of the freebet you want to use" << endl;
				cin >> index;
				wallet.eraseFreebet(index- 'a');
				succes_bet = true;
			}
		}
	}
	currentlevel +=  eventchoice;
	currentlevel.erase(currentlevel.begin(), currentlevel.begin()+1);
	ofstream out;
	out.open("bets.csv", ios::app); //append mode
	out << endl << atoi(cell.c_str() + 1) << '|' << this->getId() << '|' << currentlevel << '|';
	if(type_of_bet == true)
		out << bet << "|-";
	else
		out << wallet.getFreebet(index - 'a') << "|-";

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Place ";
	if(type_of_bet)
		logfile << "Player placed the amount of money " << bet << endl;
	else
		logfile << "Player placed a freebet" << endl;

}

Player::~Player() {
}

Booker::Booker(string username, string realname, string password, int id) : User(username, realname, password, id){
}

void Booker::showOperations(string level){
	this->User::showOperations(level);
	cout << "B(Bets) to show the last 20 bets" << endl <<
	"F(Freebets), to give a freebet to a player" << endl;
	istringstream tmp(level);
    string temp1;
    int counter = 0;

    while (getline(tmp, temp1, '.'))            //example of s: .1.1.2
        counter++;
    if(counter == 5)
		cout << "V(Void), to cancel a choice" << endl <<
		"S(Settle), to define a choice winning or losing" << endl;

}

void Booker::getOperation(User *user, string operation, string& level, string price){
	user->makeOperation(this, operation, level, price);
}

void Booker::makeOperation(Booker *booker, string operation, string& level, string price){
	if(operation == "B" || operation == "Bets")
		this->showBets();
	else if(operation == "F" || operation == "Freebets"){
		this->giveFreebet();
	}
	else if(operation == "V" || operation == "Void"){
		this->cancelBet(level);
	}
	else if(operation == "S" || operation == "Settle"){
		this->settleBet(level, price);
	}
}

int Booker::recogniseUser(User *user){return user->identity_of_user(this); }

bool Booker::recogniseDirector(User * user){ return user->identity_of_director(this); }

bool Booker::identity_of_director(Booker *){ return false; }

int Booker::identity_of_user(Booker *player){ return 2; }

void Booker::showBets(){
	if (system("CLS")) system("clear");
	ifstream database("bets.csv");
	string line;
    string cell;
    int i = 0;
    while(true || i<20){
    	getline(database, line);
    	istringstream is(line);
    	for(int j = 0; j < 5; j++){
	    	getline(is, cell, '|');
	    	cout << setw (10) << cell << " | ";
	    }
    	cout << endl;
    	if ( database.eof() ) break;
    }
    getchar();
    getchar();

    ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Bets " << "Booker viewed the list of bets" << endl;
}

void Booker::giveFreebet(){
	if (system("CLS")) system("clear");
	string username, freebet;
	bool found = false;
	ifstream database("users.csv");
	ofstream newdatabase("new.csv");
	while(found == false){
		cout << "Please Give the name of the player you wish to give a freebet" << endl;
		cin >> username;
		
		string line, cell, cell2;
		getline(database, line);
		newdatabase << line << endl;
		while(true){
			getline(database, line);
			newdatabase << line;
			istringstream is(line);
			getline(is, cell, '|');
	        getline(is, cell, '|');
	        if(username == cell){
	        	found = true;
	        	cout << "Please Give the amount of money you wish place:" << endl;
	        	cin >> freebet;
	        	istringstream is2(line);
	        	for (int i = 0; i < 6; ++i){
	        		getline(is, cell, '|');
	        		getline(is2, cell2, '|');
	        	}
	        	getline(is2, cell2, '|');
	        	if(cell2 != cell)
	        		newdatabase << ',' << freebet << endl;
	        	else 
	        		newdatabase << '|' << freebet << endl;
	        }
	        else
	        	newdatabase << endl;
	        if ( database.eof() ) break;
		}
	}
	database.close();
	newdatabase.close();
	remove("users.csv");
	rename("new.csv", "users.csv");

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Freebets " << "Booker gave a freebet to " << username << " with amount " << freebet << endl;

}

void Booker::cancelBet(string& level){
	ifstream database("bets.csv");
	ifstream database3("bets.csv");
	ofstream newdatabase("new.csv");
	ofstream newdatabase2("new2.csv");
	fstream database2("users.csv");
	fstream betsdatabase("bets.csv");
	string line, selection, cell, user_id, lvl, money;
	string line2, cell2, cell3;
	bool flag = true;
	cout << "Which selection do you wish to cancel ?" << endl;
	cin >> selection;
	level  += selection + ".";
	lvl = level;
	lvl.erase(lvl.begin(), lvl.begin() + 1);
	lvl.erase(lvl.end() - 1, lvl.end());
	bool bet_found = false;
	while(!bet_found){
		getline(database3, line);
		istringstream is(line);
		getline(is, cell, '|');
		getline(is, cell, '|');
		getline(is, cell, '|');
		if(lvl == cell){
			bet_found = true;
		}
		if ( database3.eof() ) break;
	}
	if (bet_found){
		getline(betsdatabase, line);
		newdatabase2 << line << endl;
		while(true){
			getline(betsdatabase, line);
			istringstream is3(line);
			for (int i = 0; i < 3; ++i)
				getline(is3, cell2, '|');
			if(lvl == cell2){
				istringstream is3(line);
				for (int i = 0; i < 4; ++i){
					getline(is3, cell2, '|');
					newdatabase2 << cell2 << '|';
				}
				newdatabase2 << "V" << endl;
			}
			else
				newdatabase2 << line << endl;
			if ( betsdatabase.eof() ) break;
		}
		
		getline(database, line);
		while(true){
			getline(database, line);
			istringstream is(line);
			getline(is, cell, '|');
			getline(is, cell, '|');
			user_id = cell;
			getline(is, cell, '|');
			if(cell == lvl){
				getline(is, cell, '|');
				money = cell;
				getline(database2, line2);
				newdatabase << line2 << endl;
				while(true){
					getline(database2, line2);
					istringstream is2(line2);
					getline(is2, cell2, '|');
					if(cell2 == user_id){
						newdatabase << user_id << '|';
						for(int i =0; i < 5; i++){
							getline(is2, cell2, '|');
							newdatabase << cell2 << '|';
						}
						getline(is2, cell2, '|');
						newdatabase << atof(money.c_str()) + atof(cell2.c_str());
						getline(is2, cell3, '|') ;
						
						if(cell3 ==  "")
							newdatabase << endl; 
						else
							newdatabase << '|' << cell3 << endl;
					}
					else
						newdatabase << line2 << endl;
					if ( database2.eof() ) break;
				}
			}
			if ( database.eof() ) break;
		}
		database.close();
		database2.close();
		database3.close();
		newdatabase.close();
		remove("users.csv");
		rename("new.csv", "users.csv");
		betsdatabase.close();
		newdatabase2.close();
		remove("bets.csv");
		rename("new2.csv", "bets.csv");
	}

	

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Void " << "Booker canceled the node " << lvl << endl;
}

void Booker::settleBet(string& level, string price){
	float total_money=0;
	string sublevel, money;
	string lvl = level;
	lvl.erase(lvl.begin(), lvl.begin() + 1);
	lvl.erase(lvl.end() - 1, lvl.end());
	//cout << "level " << lvl << "price " << price<< endl;
	ifstream database("bets.csv");
	ofstream newdatabase("new.csv");
	string cell, line, line2, cell2, cell3;
	getline(database, line);
	bool bet_found = false;
	while(!bet_found){
		getline(database, line);
		istringstream is(line);
		getline(is, cell, '|');
		getline(is, cell, '|');
		getline(is, cell, '|');
		if(lvl == cell){
			bet_found = true;
		}
		if(bet_found == true){
			sublevel = lvl;
			sublevel.erase(sublevel.end() - 2, sublevel.end());
			ifstream database2("bets.csv");
			getline(database2, line2);
			newdatabase << line2 << endl;
			while(true){
				getline(database2, line2);
				istringstream is2(line2);
				for (int i = 0; i < 3; ++i)
					getline(is2, cell2, '|');
				string test_sublevel = cell2;
				if(cell2 != "")
					test_sublevel.erase(test_sublevel.end() - 2, test_sublevel.end());
				if(lvl == cell2){
					istringstream is3(line2);
					for (int i = 0; i < 4; ++i){
						getline(is3, cell2, '|');
						newdatabase << cell2 << '|';
					}
					newdatabase << "W" << endl;
				}
				
				else if(test_sublevel == sublevel){
					istringstream is3(line2);
					for (int i = 0; i < 4; ++i){
						getline(is3, cell2, '|');
						newdatabase << cell2 << '|';
					}
					getline(is3, cell2, '|');
					if(cell2 != "V")
						newdatabase << "L" << endl;
					else
						newdatabase << cell2 << endl;
				}
				else
					newdatabase << line2 << endl;
				

				if ( database2.eof() ) break;
			}
		}
		
		if ( database.eof() ) break;
	}
	if(bet_found){
		database.close();
		newdatabase.close();
		remove("bets.csv");
		rename("new.csv", "bets.csv");
		string user_id, winner_id;
		ifstream usersdatabase("users.csv");
		ifstream checkbets("bets.csv");
		ofstream newdatabase2("new2.csv");
		getline(usersdatabase, line2);
		newdatabase2 << line2 << endl;
		getline(checkbets, line);
		bool flag = true;
		while(true){
			getline(checkbets, line);
			istringstream is(line);
			getline(is, cell, '|');
			getline(is, cell, '|');
			user_id = cell;
			getline(is, cell, '|');
			if(lvl == cell){
				winner_id = user_id;
				getline(is, cell, '|');
				money = cell;
				total_money += atof(money.c_str());
				flag = true;
				while(flag){
					getline(usersdatabase, line2);
					istringstream users(line2);
					getline(users, cell2, '|');
					user_id = cell2;
					if(winner_id == cell2){
						newdatabase2 << cell2 << '|';
						for (int i = 0; i < 5; ++i){
						 	getline(users, cell2, '|');
						 	newdatabase2 << cell2 << '|';
						}
						getline(users, cell2, '|');
						newdatabase2 << atof(cell2.c_str()) + atof(money.c_str()) *0.95;
						getline(users, cell3, '|');
						if(cell3 == "")
							newdatabase2 << endl;
						else{
							newdatabase2 << '|' << cell3 << endl;
						}
						flag = false;
					}
					else
						newdatabase2 << line2 << endl;
					if ( usersdatabase.eof()) break;
				}
			}
			if ( checkbets.eof() ) break;
		}
		price = to_Str(total_money);
		usersdatabase.close();
		checkbets.close();
		newdatabase2.close();
		remove("users.csv");
		rename("new2.csv", "users.csv");
	}
	


	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Settle " << "Booker settled the node:  " << lvl << " to winning " << endl;
}

Booker::~Booker() {
	// TODO Auto-generated destructor stub
}

Director::Director(string username, string realname, string password, int id) :  User(username, realname, password, id){
}

void Director::showOperations(string level){
	Booker b("", "", "", 0);
	b.showOperations(level);
	cout << "S(Save) to save current state and sync the data files" << endl << endl <<
	"Management:" << endl <<
	"L(Logs), to show the last 25 actions on the system" << endl<<
	"U(Users), to manage the users" << endl <<
	"V(Visibility), to change visibility of a node" << endl <<
	"R(Rename), to change the name of a node" << endl <<
	"N(New), to create a node" << endl <<
	"C(Copy), to copy a node (as non-visible)" << endl <<
	"D(Delete), to delete a node" << endl;
}

void Director::getOperation(User *user, string operation, string& level, string price){
	user->makeOperation(this, operation, level);
}

void Director::makeOperation(Director *director, string operation, string& level){
	if(operation == "U" || operation == "Users")
		this->manageUsers();
	else if (operation == "L" || operation == "Logs")
		showLog();
	else if (operation == "B" || operation == "Bets"){
		this->showBets();
	}
	else if (operation == "F" || operation == "Freebets"){
		this->giveFreebet();
	}
}

void Director::manageUsers() {
	if (system("CLS")) system("clear");
	string choice;
	cout << "Choices:" << endl << endl << "V(View), to show the users" << endl <<
		"S(Search), to search a user" << endl <<
		"L(Lock), to change the status of a user\n" << endl;
	cin >> choice;
	if (choice == "V" || choice == "View")
		this->showUsers();
	else if (choice == "L" || choice == "Lock")
		this->lockUser();
	else if (choice == "S" || choice == "Search")
		this->searchUser();
}

void Director::showUsers(){

	if (system("CLS")) system("clear");
	ifstream database("users.csv");
	string line, cell;
	while (getline(database, line)) {

		cout << "\n| " << line;
	}
	cout << endl;
	string pause;
	getchar();
	getchar();

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << "Director " << this->getUsername() << " Viewed the users of the system" << endl;
}

void Director::lockUser() {
	string username, status;
	int type;
	if (system("CLS")) system("clear");
	cout << "Lock - Unlock User" << endl;

	cout << "Give the username : ";
	cin >> username;

	if (system("CLS")) system("clear");
	type = searchUser(username);
	if (type == 1) {	//if it's a player
		
		string status, comment;

		cout << "Give the status : ";
		cin >> status;
		cout << "\nGive a comment : ";
		getchar();
		getline(cin, comment);

		status += " " + comment;

		ifstream database("users.csv");
		ofstream newdatabase("new.csv");

		string line, cell, cell2;
		getline(database, line);
		newdatabase << line << endl;
		while (true) {

			getline(database, line);
			istringstream is(line);
			getline(is, cell2, '|');
			getline(is, cell, '|');

			if (username == cell) {

				newdatabase << cell2 << '|';
				newdatabase << cell << '|';

				for (int i = 0; i < 3; ++i) {
					getline(is, cell, '|');
					newdatabase << cell << '|';
				}

				newdatabase << status << '|';
				getline(is, cell, '|');

				getline(is, cell, '\n');
				newdatabase << cell;

				newdatabase << endl;
			}
			else
				newdatabase << line << endl;
			if (database.eof()) break;
		}
		database.close();
		newdatabase.close();
		remove("users.csv");
		rename("new.csv", "users.csv");

		cout << "Done !";
	}
	else if (type != 0)
		cout << "Not a Player !" << endl;
	
	string pause;
	getline(cin, pause);

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << "Director " << this->getUsername() << " changed the status of "<< username << " to " << status << endl;
}

int Director::searchUser(string user) {
	string username;
	int type = 0;
	if (user == "") {
		if (system("CLS")) system("clear");
		cout << "Search User" << endl;

		cout << "Give the username : ";		
		cin >> username;
	}
	else {
		username = user;
	}

	if (system("CLS")) system("clear");
	ifstream database("users.csv");
	bool found = false;
	string line;
	string cell;
	getline(database, line);
	while (true) {
		getline(database, line);
		istringstream is(line);
		getline(is, cell, '|');
		getline(is, cell, '|');

		for (int i = 0; i <= cell.size(); i++) {
			if (!username.compare(cell.substr(i, username.size()))){
				cout << line << endl;
				found = true;
				getline(is, cell, '|');
				getline(is, cell, '|');
				getline(is, cell, '|');
				type = atoi((cell.c_str()));
			}
		}
		if (database.eof()) break;
	}

	if (!found)
		cout << "Nothing Found !" << endl;

	string pause;
	getchar();
	getchar();

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << "Director " << this->getUsername() << " searched the name " << username << endl;

	return type;
}

int Director::recogniseUser(User *user) {return user->identity_of_user(this); }

bool Director::recogniseDirector(User *user){ return user->identity_of_director(this); }

bool Director::identity_of_director(Director *){ return true; }

int Director::identity_of_user(Director *player){ return 3; }

Director::~Director() {
	// TODO Auto-generated destructor stub
}

void Director::showLog() {
	if (system("CLS")) system("clear");
	ifstream logs("audit.log");

	string line;
	int i=0;
	while (i<25 && (!logs.eof())){
		getline(logs, line);
		cout << line << endl;
		i++;
	}
	getchar();
	getchar();
}

void Director::giveFreebet(){
	if (system("CLS")) system("clear");
	string username, freebet;
	bool found = false;
	ifstream database("users.csv");
	ofstream newdatabase("new.csv");
	while(found == false){
		cout << "Please Give the name of the player you wish to give a freebet" << endl;
		cin >> username;
		
		string line, cell, cell2, line2;
		getline(database, line);
		newdatabase << line << endl;
		while(true){
			getline(database, line);
			if(line.size() > 0){
				line2 = line.substr(0, line.size() - 1);
				if(line.substr(line.size() - 1, line.size()) == "\r")
					newdatabase << line2;
				else
					newdatabase << line;
			}
			else
				newdatabase << line;
			newdatabase.flush();
			istringstream is(line);
			getline(is, cell, '|');
	        getline(is, cell, '|');
	        if(username == cell){
	        	found = true;
	        	cout << "Please Give the amount of money you wish place:" << endl;
	        	cin >> freebet;
	        	for (int i = 0; i < 5; ++i){
	        		getline(is, cell, '|');
	        	}
	        	if(cell.substr(cell.size() - 1, cell.size()) == "\r")
	        		newdatabase << '|' << freebet << endl;
	        	else 
	        		newdatabase << ',' << freebet << endl;
	        }
	        else
	        	newdatabase << endl;
	        if ( database.eof() ) break;
		}
	}
	database.close();
	newdatabase.close();
	remove("users.csv");
	rename("new.csv", "users.csv");

	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << this->getUsername() << " " << "Freebets " << "Booker gave a freebet to " << username << " with amount " << freebet << endl;

}

void Director::showBets(){
	if (system("CLS")) system("clear");
	ifstream database("bets.csv");
	string line;
    string cell;
    int i = 0;
    while(true || i<20){
    	getline(database, line);
    	istringstream is(line);
    	for(int j = 0; j < 5; j++){
	    	getline(is, cell, '|');
	    	cout << setw (10) << cell << " | ";
	    }
    	cout << endl;
    	if ( database.eof() ) break;
    }
    getchar();
    getchar();

    ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << "Director " << this->getUsername() << " viewed the list of bets" << endl;
}