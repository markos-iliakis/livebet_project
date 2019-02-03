#ifndef STATE_H
#define STATE_H
#include "users.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include "hierarchy.h"
#include <string.h>

class Currentstate {
	User *user;
	Hierarchy h;
	string level;
	string name;
	string location;
	bool toggle;
	double TotalMoney;
public:
	Currentstate(vector<string>&);
	Currentstate();
	void showOperations();
	void levelChange(string l, string mode);
	void Home();
	void Toggle();
	void Exit();
	void Rename();
	void New();
	void Copy();
	void Delete();
	void Visibility();
	void receiveOperation(string);
	bool isDirector();
	void Voiding(string level);
	bool checkVoid(string level);
};
#endif