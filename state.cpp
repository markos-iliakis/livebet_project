//#include "stdafx.h"
#include "state.h"

//guest = 0
//player = 1
//booker = 2
//director = 3

ifstream hierarchy("hierarchy.dat");

using namespace std;

//check if string is abortion of current operation
bool isAbort(string s) {
	if (!strcasecmp(s.c_str(), "cancel") || !strcasecmp(s.c_str(), "abort") || !strcasecmp(s.c_str(), "c") || !strcasecmp(s.c_str(), "a"))
		return true;
	else
		return false;
}

//insert hierarchy from hierarchy.dat
Hierarchy& create_hierarchy() {
	Hierarchy* h = new Hierarchy();
	string line;
	string name;
	string id;
	string subId;
	string subId2;
	string id2;
	double price = 0;
	vector<int> arr;

	while (true) {

		arr.clear();
		id2 = "";
		int i = 0;

		getline(hierarchy, line);
		istringstream line1(line);
		getline(line1, id, ' ');	//seperate id from name
		getline(line1, name, '\n');
		istringstream id2(id);

		while (getline(id2, subId, '.')) { //count depth of tree and find the final subId

			arr.push_back(atoi(subId.c_str()));
			subId2 = subId;
			i++;
		}

		switch (i) {

		case 1:
			h->addCategory(subId2, name);
			break;

		case 2:
			h->addSubcategory(arr[0] - 1, subId2, name);
			break;

		case 3:
			h->addEvent(arr[0] - 1, arr[1] - 1, subId2, name);
			break;

		case 4:
			h->addMarket(arr[0] - 1, arr[1] - 1, arr[2] - 1, subId2, name);
			break;

		case 5:
			//seperate name from price
			string tmp = name;
			string tmp2;
			string tmp3;
			istringstream name2(tmp);
			getline(name2, name, '#');
			getline(name2, tmp2, '\n');

			//create classes
			h->addSelection(arr[0] - 1, arr[1] - 1, arr[2] - 1, arr[3] - 1, subId2, name);
			h->addPrice(arr[0] - 1, arr[1] - 1, arr[2] - 1, arr[3] - 1, arr[4] - 1, tmp2);
			break;
		}

		if (hierarchy.eof()) break;
	}
	return *h;
}

Currentstate::Currentstate(vector<string>& user_details) : level("."), h(create_hierarchy()), toggle(false), name("BetYourHome"), location("/" + name + "/"), TotalMoney(500000) {
	//Select what user to create
	if (atoi((user_details[4].c_str())) == 1) {
		if (user_details.size() == 8) {
			user = new Player(user_details[5], user_details[1], user_details[2], user_details[3], atoi(user_details[0].c_str()), atof(user_details[6].c_str()), user_details[7]);	//autos edw  exei freebets
		}
		else
			user = new Player(user_details[5], user_details[1], user_details[2], user_details[3], atoi(user_details[0].c_str()), atof(user_details[6].c_str()));
	}

	else if (atoi(user_details[4].c_str()) == 2) {
		user = new Booker(user_details[1], user_details[2], user_details[3], atoi(user_details[0].c_str()));
	}
	else if (atoi((user_details[4].c_str())) == 3) {
		user = new Director(user_details[1], user_details[2], user_details[3], atoi(user_details[0].c_str()));
	}
}

Currentstate::Currentstate() : level("."), h(create_hierarchy()), toggle(false), name("BetYourHome"), location("/" + name + "/"), TotalMoney(500000) {
	user = new Guest("guest", "guest");
}

void Currentstate::levelChange(string l, string mode) {		//mode : app for append , rw for rewrite
	ofstream log;
	log.open("audit.log", ios::app);

	if (mode == "app") {
		if (level.size() >= 9)	//if the last nodes are displayed dont go anywhere
			return;
		level += l + ".";
		h.updateLocation(level, l, location);
		if(user->recogniseUser(user) == 1)
			log << user->getUsername() << " Navigate to " << location << endl;
	}
	else if (mode == "rw") { // for home function
		level = l;
		location = name + "/";
		if (user->recogniseUser(user) == 1)
			log << user->getUsername() << "Navigate to Home" << endl;
	}
}

//show the operations of the current user and the available nodes to go
void Currentstate::showOperations() {
	cout << "\n\n" << location << endl;
	if(user->recogniseUser(user) == 3)
		cout << "System Money : " << TotalMoney << endl;
	if (toggle)
		cout << "Price Type : decimal" << endl;
	else
		cout << "Price Type : fractional" << endl;

	user->showOperations(level);
	h.nextNodes(level, toggle, isDirector());

	cout << endl;
}

//receive the choice(operation) of the user
void Currentstate::receiveOperation(string operation) {
	if (operation == "H" || operation == "Home")
		Home();
	else if (operation == "T" || operation == "Toggle")
		Toggle();
	else if (operation == "X" || operation == "Exit")
		Exit();
	else if ((operation == "R" || operation == "Rename") && user->recogniseDirector(user) == true)
		Rename();
	else if ((operation == "N" || operation == "New") && user->recogniseDirector(user) == true)
		New();
	else if ((operation == "C" || operation == "Copy") && user->recogniseDirector(user) == true)
		Copy();
	else if ((operation == "D" || operation == "Delete") && user->recogniseDirector(user) == true)
		Delete();
	else if ((operation == "V" || operation == "Visibility") && user->recogniseDirector(user) == true)
		Visibility();
	else if ((operation == "V" || operation == "Void") && user->recogniseUser(user) == 2 && level.size() > 8){
		
		if (system("CLS")) system("clear");
		h.nextNodes(level, toggle, isDirector());
		cout << "\n\n";
		string lvl = level;
		user->getOperation(user, operation, lvl);
		Voiding(lvl);
	}
	else if ((operation == "P" || operation == "Place") && user->recogniseUser(user) == 1 && level.size() > 8){
		
		if (system("CLS")) system("clear");
		h.nextNodes(level, toggle, isDirector());
		
		string eventchoice;
		cout << "\n\nPlease choose the event you want to bet or 'cancel' to cancel the bet" << endl;
		cin >> eventchoice;
		string lvl = level + eventchoice + ".";
		
		if(checkVoid(lvl))
			user->getOperation(user, operation, level);
	}
	else if((operation == "S" || operation == "Settle") && user->recogniseUser(user) == 2 && level.size() > 8){
		
		if (system("CLS")) system("clear");
		h.nextNodes(level, toggle, isDirector());
		
		string eventchoice;
		cout << "Please choose the event you want to settle" << endl;
		cin >> eventchoice;
		string lvl =  level + eventchoice + ".";
		string pr = h.retPrice(lvl);
		user->getOperation(user, operation, lvl, pr);   //h price na einai to teleutaio orisma
		//to pr twra exei to poso pou kerdisan oi paiktes apo ta stoixhmata
		
		TotalMoney+= atof(pr.c_str());
	}
	else if ((operation == "S" || operation == "Save") && user->recogniseUser(user) == 3) {
		h.save();
	}
	else {
		istringstream tmp(level);
		string temp1;
		int counter = 0;

		while (getline(tmp, temp1, '.'))			//example of s: .1.1.2
			counter++;
		user->getOperation(user, operation, level);
	}
}

void Currentstate::Home() {
	levelChange(".", "rw");
}

void Currentstate::Toggle() {
	if (toggle)
		toggle = false;
	else
		toggle = true;
}

void Currentstate::Exit() {
	ofstream logfile;
	logfile.open("audit.log", ios::app);
	logfile << user->getUsername() << " Signed out " << endl;
	exit(0);
}

void Currentstate::Rename() {

	string id;
	string tmp;
	string lvl;

	if (system("CLS")) system("clear");
	h.nextNodes(level, toggle, isDirector());

	cout << "\n\nSelect a Node : ";
	cin >> id;
	if (isAbort(id))
		return;
	cout << "\nGive a new name : ";
	getchar();
	getline(cin, tmp);
	if (isAbort(tmp))
		return;

	lvl = level + id + ".";
	h.changeName(lvl, tmp);
}

void Currentstate::New() {

	string id;
	string tmp;
	string lvl;

	if (system("CLS")) system("clear");
	h.nextNodes(level, toggle, isDirector());

	cout << "\n\nSelect new Node's id : ";
	cin >> id;
	if (isAbort(id))
		return;
	cout << "\nGive a name : ";
	getchar();
	getline(cin, tmp);
	if (isAbort(tmp))
		return;

	lvl = level + id + ".";

	h.newNode(lvl, id, tmp);
}

void Currentstate::Copy() {

	string id;
	string newid;
	string tmp;
	string lvl;

	if (system("CLS")) system("clear");
	h.nextNodes(level, toggle, isDirector());

	cout << "\n\nSelect a Node to copy : ";
	cin >> id;
	if (isAbort(id))
		return;
	cout << "\nSelect new Node's id : ";
	cin >> newid;
	if (isAbort(newid))
		return;
	lvl = level + id + ".";

	h.copyNode(lvl, id, newid);
}

void Currentstate::Delete() {

	string id;
	string tmp;
	string lvl;
	char c;

	if (system("CLS")) system("clear");

	cout << "Are you sure you want to DELETE a node and it's sub-nodes ? (Y/N) : ";
	getchar();
	c = getchar();

	if (c == 'Y' || c == 'y') {
		h.nextNodes(level, toggle, isDirector());

		cout << "\n\nSelect a Node to delete : ";
		cin >> id;

		if (isAbort(id))
			return;

		lvl = level + id + ".";

		h.deleteNode(lvl, id);
	}
}

void Currentstate::Visibility() {
	string id;
	string newid;
	string tmp;
	string lvl;

	if (system("CLS")) system("clear");
	h.nextNodes(level, toggle, isDirector());

	cout << "\n\nSelect a Node to toggle it's Visibility : ";
	cin >> id;

	lvl = level + id + ".";
	h.toggleVisibility(lvl, id);
}

void Currentstate::Voiding(string flevel) {
	h.toggleAvailable(flevel);
}

bool Currentstate::checkVoid(string flevel) {
	return h.checkVoid(flevel);
}

bool Currentstate::isDirector(){
	return user->recogniseDirector(user);
}