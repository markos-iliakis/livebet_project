//#include "stdafx.h"
#include <string>
#include <vector>

using namespace std;

class Player;
class Guest;
class Booker;
class Director;

class User {
	string username;
	string realname;
	string password;
	int id;
public:
	User(const string, const string, const string, const int);
	User(const string, const string);
	string getUsername();
	string getRealname();
	string getPassword();
	void setUsername(string);
	void setPassword(string);
	int getId();
	virtual ~User();
	virtual void showOperations(string);
	virtual void getOperation(User *, string, string&, string = "");
	virtual void makeOperation(Guest *, string, string&);
	virtual void makeOperation(Player *, string, string&);
	virtual void makeOperation(Booker *, string, string&, string);
	virtual void makeOperation(Director *, string, string&);
	virtual bool recogniseDirector(User *);
	virtual int recogniseUser(User *);
	virtual int identity_of_user(Guest *);
	virtual int identity_of_user(Player *);
	virtual int identity_of_user(Booker *);
	virtual int identity_of_user(Director *);
	virtual bool identity_of_director(Player *);
	virtual bool identity_of_director(Booker *);
	virtual bool identity_of_director(Guest *);
	virtual bool identity_of_director(Director *);
};

class Wallet
{
	float remain;
	vector<float> freebets;

public:
	Wallet(const float);
	Wallet(const float, const string);
	float getRemain();
	vector<float> getFreebets();
	int getSize();
	void increament(const float);
	void showfreebets();
	void decreament(float);
	void eraseFreebet(int);
	float getFreebet(int);
	~Wallet();
};

class Guest: public User {
public:
	Guest(const string, const string);
	void showOperations(string);
	void getOperation(User *, string, string&, string = "");
	void makeOperation(Guest *, string, string&);
	bool recogniseDirector(User *);
	int recogniseUser(User *);
	int identity_of_user(Guest *);
	bool identity_of_director(Guest *);
	~Guest();
};

class Player: public User {
	string status;
	Wallet wallet;
public:
	Player(const string, const string, const string, const string, const int, const float, const string);   //in case the user has freebets
	Player(const string, const string, const string, const string, const int, const float);
	void showOperations(string);
	void getOperation(User *, string, string&, string = "");
	void makeOperation(Player *, string, string&);
	bool recogniseDirector(User *);
	int recogniseUser(User *);
	int identity_of_user(Player *);
	bool identity_of_director(Player *);
	void enterAccount();
	Wallet& getWallet();
	void renamePlayer();
	void changePassword();
	void betsHistory();
	void refillAccount();
	void placeBet(string);
	~Player();
};

class Booker: public User{
public:
	Booker(const string, const string, const string, const int);
	void showOperations(string);
	void getOperation(User *, string, string&, string = "");
	void makeOperation(Booker *, string, string&, string);
	bool recogniseDirector(User *);
	int recogniseUser(User *);
	int identity_of_user(Booker *);
	bool identity_of_director(Booker *);
	void showBets();
	void giveFreebet();
	void cancelBet(string&);
	void settleBet(string&, string);
	~Booker();
};

class Director: public User{
public:
	Director(const string, const string, const string, const int);
	void showOperations(string);
	void getOperation(User *, string, string&, string = "");
	void makeOperation(Director *, string, string&);
	bool recogniseDirector(User *);
	int recogniseUser(User *);
	int identity_of_user(Director *);
	bool identity_of_director(Director *);
	void manageUsers();
	void showUsers();
	void lockUser();
	int searchUser(string = "");
	~Director();
	void showLog();
	void showBets();
	void giveFreebet();
};