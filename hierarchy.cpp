//#include "stdafx.h"
#include "hierarchy.h"

using namespace std;

string to_str(double a) {
	stringstream ss;
	ss << a;
	return ss.str();
}

Hierarchy::Hierarchy() {
	//cout << "\nCategory list constructed" << endl;
}

void Hierarchy::addCategory(string id1, string name) {
	cat.push_back(new Category(id1, name));
}

Category::Category(string id1, string n) : name(n), id(id1), vis(true) {
	//cout << "Category constructed with id : " << id1 << " and name : " << name << endl;
}

Category::Category(Category& x, string s) {

	id = x.id;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Subcategory*>::const_iterator it = x.sub.begin(); it < x.sub.end(); ++it) {
		sub.push_back(new Subcategory(*(*it), s));
	}
}

Category::Category(Category& x, string s, string newid) {

	id = newid;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Subcategory*>::const_iterator it = x.sub.begin(); it < x.sub.end(); ++it) {
		sub.push_back(new Subcategory(*(*it), s));
	}
}

void Hierarchy::addSubcategory(int index, string id1, string name) {
	cat[index]->sub.push_back(new Subcategory(id1, name));
}

Subcategory::Subcategory(string id1, string nam) : name(nam), id(id1), vis(true) {
	//cout << "Subcategory constructed with id : " << id1 << " and name : " << name << endl;
}

Subcategory::Subcategory(Subcategory& x, string s) {

	id = x.id;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Event*>::const_iterator it = x.ev.begin(); it < x.ev.end(); ++it) {
		ev.push_back(new Event(*(*it), s));
	}

}

Subcategory::Subcategory(Subcategory& x, string s, string newid) {

	id = newid;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Event*>::const_iterator it = x.ev.begin(); it < x.ev.end(); ++it) {
		ev.push_back(new Event(*(*it), s));
	}

}

void Hierarchy::addEvent(int index, int index2, string id1, string name) {
	cat[index]->sub[index2]->ev.push_back(new Event(id1, name));
}

Event::Event(string id1, string nam) : name(nam), id(id1), vis(true) {
	//cout << "Event Constructed with id : " << id1 << " and name : " << name << endl;
}

Event::Event(Event& x, string s) {

	id = x.id;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Market*>::const_iterator it = x.mark.begin(); it < x.mark.end(); ++it) {
		mark.push_back(new Market(*(*it), s));
	}
}

Event::Event(Event& x, string s, string newid) {

	id = newid;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Market*>::const_iterator it = x.mark.begin(); it < x.mark.end(); ++it) {
		mark.push_back(new Market(*(*it), s));
	}
}

void Hierarchy::addMarket(int index, int index2, int index3, string id1, string name) {
	cat[index]->sub[index2]->ev[index3]->mark.push_back(new Market(id1, name));
}

Market::Market(string id1, string nam) : name(nam), id(id1), vis(true) {
	//cout << "Market Constructed with id : " << id1 << " and name : " << name << endl;
}

Market::Market(Market& x, string s) {

	id = x.id;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Selection*>::const_iterator it = x.sel.begin(); it < x.sel.end(); ++it) {
		sel.push_back(new Selection(*(*it), s));
	}
}

Market::Market(Market& x, string s, string newid) {

	id = newid;
	name = x.name + s;
	vis = x.vis;

	for (std::vector<Selection*>::const_iterator it = x.sel.begin(); it < x.sel.end(); ++it) {
		sel.push_back(new Selection(*(*it), s));
	}
}

void Hierarchy::addSelection(int index, int index2, int index3, int index4, string id1, string name) {
	cat[index]->sub[index2]->ev[index3]->mark[index4]->sel.push_back(new Selection(id1, name));
}

Selection::Selection(string id1, string nam) : name(nam), id(id1), vis(true), isavailable(true) {
	//cout << "Selection Constructed with id : " << id1 << " and name : " << name << endl;
}

Selection::Selection(Selection& x, string s) {

	pr = new Price(*x.pr);
	id = x.id;
	name = x.name + s;
	vis = x.vis;
	isavailable = x.isavailable;
}

Selection::Selection(Selection& x, string s, string newid) {

	pr = new Price(*x.pr);
	id = newid;
	name = x.name + s;
	vis = x.vis;
	isavailable = x.isavailable;
}

void Hierarchy::addPrice(int index, int index2, int index3, int index4, int index5, string price) {
	cat[index]->sub[index2]->ev[index3]->mark[index4]->sel[index5]->pr = new Price(price);
}

Price::Price(string pr) : price(pr) {
	//cout << "Price Constructed with price : " << pr << endl;
}

void Price::changePrice(string n) {
	price = n;
}

double Price::priceToInt() {

	string tmp2;
	double pr;
	istringstream tmp(price);
	getline(tmp, tmp2, '/');
	pr = atoi(tmp2.c_str());
	getline(tmp, tmp2, '\n');
	return (pr / atoi(tmp2.c_str()));
}

void Hierarchy::showCategories(bool isDirector) {
	for (std::vector<Category*>::iterator it = cat.begin(); it != cat.end(); ++it) {
		if (isDirector) {
			if (!(*it)->vis)
				cout << "[HIDDEN] ";

			cout << (*it)->id << " " << (*it)->name << endl;
		}
		else {
			if ((*it)->vis)
				cout << (*it)->id << " " << (*it)->name << endl;
		}
	}
}

void Hierarchy::showSubcategories(int index, bool isDirector) {
	for (std::vector<Subcategory*>::iterator it = cat[index]->sub.begin(); it != cat[index]->sub.end(); ++it) {
		if (isDirector) {
			if (!(*it)->vis)
				cout << "[HIDDEN] ";

			cout << (*it)->id << " " << (*it)->name << endl;
		}
		else {
			if ((*it)->vis)
				cout << (*it)->id << " " << (*it)->name << endl;
		}
	}
}

void Hierarchy::showEvents(int index, int index2, bool isDirector) {
	for (std::vector<Event*>::iterator it = cat[index]->sub[index2]->ev.begin(); it != cat[index]->sub[index2]->ev.end(); ++it) {
		if (isDirector) {
			if (!(*it)->vis)
				cout << "[HIDDEN] ";

			cout << (*it)->id << " " << (*it)->name << endl;
		}
		else {
			if ((*it)->vis)
				cout << (*it)->id << " " << (*it)->name << endl;
		}
	}
}

void Hierarchy::showMarkets(int index, int index2, int index3, bool isDirector) {
	for (std::vector<Market*>::iterator it = cat[index]->sub[index2]->ev[index3]->mark.begin(); it != cat[index]->sub[index2]->ev[index3]->mark.end(); ++it) {
		if (isDirector) {
			if (!(*it)->vis)
				cout << "[HIDDEN] ";

			cout << (*it)->id << " " << (*it)->name << endl;
		}
		else {
			if ((*it)->vis)
				cout << (*it)->id << " " << (*it)->name << endl;
		}
	}
}

void Hierarchy::showSelections(int index, int index2, int index3, int index4, bool toggle, bool isDirector) {
	for (std::vector<Selection*>::iterator it = cat[index]->sub[index2]->ev[index3]->mark[index4]->sel.begin(); it != cat[index]->sub[index2]->ev[index3]->mark[index4]->sel.end(); ++it) {

		if (isDirector) {
			if (!(*it)->vis)
				cout << "[HIDDEN] ";

			cout << (*it)->id << " " << (*it)->name << " ";

			if (toggle)
				cout << (*it)->pr->priceToInt();
			else
				cout << (*it)->pr->price;

			if(!(*it)->isavailable)
				cout << "  Not Available!";
				
			cout << endl;
		}
		else {
			if ((*it)->vis) {
				cout << (*it)->id << " " << (*it)->name << " ";

				if (toggle)
					cout << (*it)->pr->priceToInt();
				else
					cout << (*it)->pr->price;

				if(!(*it)->isavailable)
				cout << "  Not Available!";
				
				cout << endl;
			}
		}
	}
}

void Hierarchy::nextNodes(string s, bool toggle, bool isDirector) {
	istringstream tmp(s);
	string temp1;
	int counter = 0;
	vector<int> arr;

	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));		//the arr[0] is nothing
		counter++;
	}

	cout << "\n\n";

	switch (counter) {
	case 1:
		showCategories(isDirector);
		break;
	case 2:
		showSubcategories(arr[1] - 1, isDirector);
		break;
	case 3:
		showEvents(arr[1] - 1, arr[2] - 1, isDirector);
		break;
	case 4:
		showMarkets(arr[1] - 1, arr[2] - 1, arr[3] - 1, isDirector);
		break;
	case 5:
		showSelections(arr[1] - 1, arr[2] - 1, arr[3] - 1, arr[4] - 1, toggle, isDirector);
		break;
	}
}

void Hierarchy::changeName(string level, string newName) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;
	ofstream logfile;
	logfile.open("audit.log", ios::app);
	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}

	switch (counter) {
	case 2:
		logfile << "Director changed name of node " << cat[arr[1] - 1]->name << " to " << newName << endl;
		cat[arr[1] - 1]->name = newName;
		break;
	case 3:
		logfile << "Director changed name of node " << cat[arr[1] - 1]->sub[arr[2] - 1]->name << " to " << newName << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->name = newName;
		break;
	case 4:
		logfile << "Director changed name of node " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->name << " to " << newName << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->name = newName;
		break;
	case 5:
		logfile << "Director changed name of node " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->name << " to " << newName << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->name = newName;
		break;
	case 6:
		logfile << "Director changed name of node " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->name << " to " << newName << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->name = newName;
	}
}

void Hierarchy::newNode(string level, string pos, string newName) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;
	ofstream logfile;
	logfile.open("audit.log", ios::app);
	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}

	switch (counter) {
	case 2:
		addCategory(pos, newName);
		logfile << "Director added a Category with name " << newName << endl;
		break;
	case 3:
		addSubcategory(arr[1] - 1, pos, newName);
		logfile << "Director added a Subcategory with name " << newName << endl;
		break;
	case 4:
		addEvent(arr[1] - 1, arr[2] - 1, pos, newName);
		logfile << "Director added an Event with name " << newName << endl;
		break;
	case 5:
		addMarket(arr[1] - 1, arr[2] - 1, arr[3] - 1, pos, newName);
		logfile << "Director added a Market with name " << newName << endl;
		break;
	case 6:
		string price;
		cout << "\nGive a price : ";
		cin >> price;
		addSelection(arr[1] - 1, arr[2] - 1, arr[3] - 1, arr[4] - 1, pos, newName);
		addPrice(arr[1] - 1, arr[2] - 1, arr[3] - 1, arr[4] - 1, arr[5] - 1, price);
		logfile << "Director added a Selection with name " << newName << " and price " << price << endl;
		break;
	}
}

void Hierarchy::deleteNode(string level, string pos) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;
	ofstream logfile;
	logfile.open("audit.log", ios::app);
	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}

	cout << "\n\n";
	int id;
	id = atoi(pos.c_str());

	switch (counter) {
	case 2:
		logfile << "Director deleted a Category with name " << cat[ id - 1]->name << endl;
		cat.erase(cat.begin() + id - 1);
		break;
	case 3:
		logfile << "Director deleted a Subcategory with name " << cat[arr[1] - 1]->sub[id - 1]->name << endl;
		cat[arr[1] - 1]->sub.erase(cat[arr[1] - 1]->sub.begin() + id - 1);
		break;
	case 4:
		logfile << "Director deleted a nEvent with name " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[ id - 1]->name << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev.erase(cat[arr[1] - 1]->sub[arr[2] - 1]->ev.begin() + id - 1);
		break;
	case 5:
		logfile << "Director deleted a Market with name " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[ id - 1]->name << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark.erase(cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark.begin() + id - 1);
		break;
	case 6:
		logfile << "Director deleted a Selecton with name " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[id - 1]->name << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel.erase(cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel.begin() + id - 1);
		break;
	}
}

void Hierarchy::copyNode(string level, string pos, string newid) {
	istringstream tmp(level);
	string temp1;
	string s = "-Copied";
	int counter = 0;
	vector<int> arr;
	ofstream logfile;
	logfile.open("audit.log", ios::app);

	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}

	cout << "\n\n";
	int id;
	id = atoi(pos.c_str());

	switch (counter) {
	case 2:
		logfile << "Director copied a Category with name " << cat[arr[1] - 1]->name << endl;
		cat.push_back(new Category(*cat[arr[1] - 1], s, newid));
		break;
	case 3:
		logfile << "Director copied a Subcategeory with name " << cat[arr[1] - 1]->sub[arr[2] - 1]->name << endl;
		cat[arr[1] - 1]->sub.push_back(new Subcategory(*cat[arr[1] - 1]->sub[arr[2] - 1], s, newid));
		break;
	case 4:
		logfile << "Director copied an Event with name " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->name << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev.push_back(new Event(*cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1], s, newid));
		break;
	case 5:
		logfile << "Director copied a Market with name " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->name << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark.push_back(new Market(*cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1], s, newid));
		break;
	case 6:
		logfile << "Director copied a Selection with name " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->name << endl;
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel.push_back(new Selection(*cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1], s, newid));
		break;
	}
}

void Hierarchy::toggleVisibility(string level, string pos) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;
	ofstream logfile;
	logfile.open("audit.log", ios::app);


	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}

	cout << "\n\n";
	int id;
	id = atoi(pos.c_str());

	switch (counter) {
	case 2:
		if (cat[arr[1] - 1]->vis)

			cat[arr[1] - 1]->vis = false;
		else
			cat[arr[1] - 1]->vis = true;
			logfile << "Director changed the visibility of " << cat[arr[1] - 1]->name << " to " << cat[arr[1] - 1]->vis << endl;
		
		for (int i = 1; i <= cat[arr[1] - 1]->sub.size(); i++ ) {
			string s;
			s = level + to_str(i) + ".";
			toggleVisibility(s, to_str(i));
		}
		break;
	case 3:
		if (cat[arr[1] - 1]->sub[arr[2] - 1]->vis)
			cat[arr[1] - 1]->sub[arr[2] - 1]->vis = false;
		else
			cat[arr[1] - 1]->sub[arr[2] - 1]->vis = true;
			logfile << "Director changed the visibility of " << cat[arr[1] - 1]->sub[arr[2] - 1]->name << " to " << cat[arr[1] - 1]->sub[arr[2] - 1]->vis << endl;
		
		for (int i = 1; i <= cat[arr[1] - 1]->sub[arr[2] - 1]->ev.size(); i++) {
			string s;
			s = level + to_str(i) + ".";
			toggleVisibility(s, to_str(i));
		}
		break;
	case 4:
		if (cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->vis)
			cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->vis = false;
		else
			cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->vis = true;
			logfile << "Director changed the visibility of " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->name << " to " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->vis << endl;
		
		for (int i = 1; i <= cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark.size(); i++) {
			string s;
			s = level + to_str(i) + ".";
			toggleVisibility(s, to_str(i));
		}
		break;
	case 5:
		if (cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->vis)
			cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->vis = false;
		else
			cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->vis = true;
			logfile << "Director changed the visibility of " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->name << " to " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->vis << endl;
		
		for (int i = 1; i <= cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel.size(); i++) {
			string s;
			s = level + to_str(i) + ".";
			toggleVisibility(s, to_str(i));
		}
		break;
	case 6:
		if (cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->vis)
			cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->vis = false;
		else
			cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->vis = true;
			logfile << "Director changed the visibility of " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->name << " to " << cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->vis << endl;
		break;
	}
}

void Hierarchy::updateLocation(string level, string pos, string& location) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;

	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}

	cout << "\n\n";
	int id;
	id = atoi(pos.c_str());

	switch (counter) {
	case 2:
		location += cat[arr[1] - 1]->name + "/";
		break;
	case 3:
		location += cat[arr[1] - 1]->sub[arr[2] - 1]->name + "/";
		break;
	case 4:
		location += cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->name + "/";
		break;
	case 5:
		location += cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->name + "/";
		break;
	case 6:
		location += cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->name + "/";
		break;
	}
}

void Hierarchy::toggleAvailable(string level) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;

	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}
	//cout << counter << " " << arr[4] << endl;
	if (cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->isavailable)
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->isavailable = false;
	else
		cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->isavailable = true;
}

bool Hierarchy::checkVoid(string level) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;

	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}

	return cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->isavailable;
}

string Hierarchy::retPrice(string level) {
	istringstream tmp(level);
	string temp1;
	int counter = 0;
	vector<int> arr;

	while (getline(tmp, temp1, '.')) {			//example of s: .1.1.2
		arr.push_back(atoi(temp1.c_str()));	//the arr[0] is nothing
		counter++;
	}
		
	return cat[arr[1] - 1]->sub[arr[2] - 1]->ev[arr[3] - 1]->mark[arr[4] - 1]->sel[arr[5] - 1]->pr->price;
}

void Hierarchy::save() {
	remove("hierarchy.dat");
	ofstream newh("hierarchy.dat");
	ofstream logfile;
	logfile.open("audit.log", ios::app);

	for (vector <Category*>::iterator it1 = cat.begin(); it1 != cat.end(); it1++){
		newh << (*it1)->id + ". " << (*it1)->name << endl;

		for (vector<Subcategory*>::iterator it2 = (*it1)->sub.begin(); it2 != (*it1)->sub.end(); ++it2){
			newh << (*it1)->id + "." + (*it2)->id + " " << (*it2)->name << endl;

			for (vector<Event*>::iterator it3 = (*it2)->ev.begin(); it3 != (*it2)->ev.end(); ++it3){
				newh << (*it1)->id + "." + (*it2)->id + "." + (*it3)->id + " " << (*it3)->name << endl;

				for (vector<Market*>::iterator it4 = (*it3)->mark.begin(); it4 != (*it3)->mark.end(); ++it4) {
					newh << (*it1)->id + "." + (*it2)->id + "." + (*it3)->id + "." + (*it4)->id + " " << (*it4)->name << endl;

					for (vector<Selection*>::iterator it5 = (*it4)->sel.begin(); it5 != (*it4)->sel.end(); ++it5) {
						newh << (*it1)->id + "." + (*it2)->id + "." + (*it3)->id + "." + (*it4)->id + "." + (*it5)->id + " " << (*it5)->name + "#" << (*it5)->pr->price << endl;
					}
				}
			}
		}
	}
	
	if (system("CLS")) system("clear");
	cout << "\nSave Done!" << endl;
	logfile << "Director saved the changes" << endl;
	getchar();
	getchar();
}