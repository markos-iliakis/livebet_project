#ifndef HIERARCHY_H
#define HIERARCHY_H
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>

using namespace std;
class Category;
class Subcategory;
class Event;
class Market;
class Selection;
class Price;

class Hierarchy {
	vector <Category*> cat;

	void showCategories(bool isDirector);
	void showSubcategories(int index, bool isDirector);
	void showEvents(int index, int index2, bool isDirector);
	void showMarkets(int index, int index2, int index3, bool isDirector);
	void showSelections(int index, int index2, int index3, int index4, bool toggle, bool isDirector);

public:
	Hierarchy();

	void addCategory(string id1, string name);
	void addSubcategory(int index, string id1, string name);
	void addEvent(int index, int index2, string id1, string name);
	void addMarket(int index, int index2, int index3, string id1, string name);
	void addSelection(int index, int index2, int index3, int index4, string id1, string name);
	void addPrice(int index, int index2, int index3, int index4, int index5, string price);

	void nextNodes(string s, bool toggle, bool isDirector);
	void changeName(string level, string newName);
	void newNode(string level, string pos, string newName);
	void deleteNode(string level, string pos);
	void copyNode(string level, string pos, string newid);
	void toggleVisibility(string level, string pos);
	void updateLocation(string level, string pos, string& location);
	void toggleAvailable(string level);
	bool checkVoid(string level);
	string retPrice(string level);
	void save();
};

class Category {
	friend class Hierarchy;
	string id;
	string name;
	bool vis;				//true = visible , false = hidden
	vector<Subcategory*> sub;

public:
	Category(string id1, string n);
	Category(Category& x, string s);
	Category(Category& x, string s, string newid);

	//friend void addSubcategory(string id1, string name);
};

class Subcategory {
	friend class Hierarchy;
	string id;
	string name;
	bool vis;
	vector<Event*> ev;

public:
	Subcategory(string id1, string nam);
	Subcategory(Subcategory& x, string s);
	Subcategory(Subcategory& x, string s, string newid);

	//friend void addEvent(string id1, string name);
};

class Event {
	friend class Hierarchy;
	string id;
	string name;
	bool vis;
	vector <Market*> mark;

public:
	Event(string id1, string nam);
	Event(Event& x, string s);
	Event(Event& x, string s, string newid);

	//friend void addMarket(string id1, string name);
};

class Market {
	friend class Hierarchy;
	string id;
	string name;
	bool vis;
	vector <Selection*> sel;

public:
	Market(string id1, string nam);
	Market(Market& x, string s);
	Market(Market& x, string s, string newid);

	//friend void addSelection(string id1, string name);
};

class Selection {
	friend class Hierarchy;
	string id;
	string name;
	bool vis;
	Price* pr;
	bool isavailable;
	string result;
public:
	Selection(string id1, string nam);
	Selection(Selection& x, string s);
	Selection(Selection& x, string s, string newid);

	//friend void addPrice(int price);
};

class Price {
	friend class Hierarchy;
	string price;
public:
	Price(string pr);

	void changePrice(string n);

	double priceToInt();
};
#endif