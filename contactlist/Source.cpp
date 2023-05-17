#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iterator>
using namespace std;

class Contactinfo {
private:
	string name;
	map <string, string> numberMap;
public:
	Contactinfo(string n, vector<string> num, vector<string> typ) {
		name = n;
		for (int i = 0; i < num.size(); i++) {
			numberMap.insert(pair<string, string>(num[i], typ[i]));
		}
	}
	void setName(string str) {
		name = str;
	}
	const string getName() const{
		return name;
	}
	const map<string, string>& getNumberMap() const{
		return numberMap;
	}
	void setNumberMap(vector<string> num, vector<string> typ) {
		numberMap.clear();
		for (int i = 0; i < num.size(); i++) {
			numberMap.insert(pair<string, string>(num[i], typ[i]));
		}
	}	
	void copyNumberMap(map<string, string> m) {
		numberMap = m;
	}
};
//insert new contacts into the vector
Contactinfo* insert() {
	string n, tmpnum, tmptyp;
	vector<string> num, typ;
	cout << "Please Enter Contact name: ";
	getline(cin, n);
	cout << endl;
	while (true) {
		cout << "Inorder to Exit please Enter \"done\" infront of Phone Number entery. " << endl;	
		cout << "please Enter Phone Number: ";
		getline(cin, tmpnum);
		if (tmpnum == "done") break;
		num.push_back(tmpnum);
		cout << endl;
		cout << "please Enter Number Type (Home,Mobile,Work,etc): ";
		getline(cin, tmptyp);
		typ.push_back(tmptyp);
		cout << endl;
		cout << "Press Enter to proceed." << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	Contactinfo* c = new Contactinfo(n, num, typ);
	return c;
}
// sort the contact list by name and print it
void SortPrint(vector<Contactinfo*> v) {
	std::sort(v.begin(), v.end(), []( Contactinfo* a,  Contactinfo* b) {
		return a->getName() < b->getName();
		});
	int i = 1;
	for (const auto* contact : v) {
		cout << i<<".Name: " << contact->getName() << endl;
		i++;
		map<string, string> m = contact->getNumberMap();
		map<string, string>::iterator itr;
		for (itr = m.begin(); itr != m.end(); ++itr) {
			cout << itr->second << " Number: " << itr->first << endl;
		}
		cout << endl;
	}
	system("pause");
}
//removes a contact from contactlist vector
void remove(vector<Contactinfo*>& v) {
	string key;
	cout << "Please Enter Contact Name/Number to Delete: ";
	getline(cin, key);
	cout << endl;
	auto removeCondition = [&](Contactinfo* contact) {
		if (contact->getName() == key) 	return true;
		map<string, string> m = contact->getNumberMap();
		map<string, string>::iterator itr;
		for (itr = m.begin(); itr != m.end(); ++itr) {
			if (itr->first == key) 	return true;
		}
		return false;
	};
	auto removeIt = std::remove_if(v.begin(), v.end(), removeCondition);
	if (removeIt != v.end()) {
		v.erase(removeIt, v.end());
		cout << "Deleted successfully" << endl;
	}
	else {
		cout << "No contact found with the given name/number." << endl;
	}
	system("pause");
}
//Edits a contact
void editcontact(vector<Contactinfo*>& v) {
	string key,nm,tp;
	cout << "Please Enter Contact Name/Number to Edit: ";
	getline(cin, key);
	cout << endl;
	int i = 0;
	for (auto* contact : v) {
		if (contact->getName() == key || contact->getNumberMap().find(key) != contact->getNumberMap().end()) {
			i++;
			cout << "Editing Contact " << i << endl << endl;
			cout << "Enter New Name: ";
			getline(cin, key);
			contact->setName(key);
			vector<string> num, typ;
			while (true) {
				cout << "Enter Phone Number (or 'done' to finish): ";
				getline(cin, nm);
				if (nm == "done") break;
				map<string, string> m = contact->getNumberMap();
				map<string, string>::iterator itr;
				for (itr = m.begin(); itr != m.end(); ++itr) {
					if (itr->first == nm) {
						cout << "Editing " << nm << endl;
						cout << "Enter Phone Number Type: ";
						getline(cin, tp);
						itr->second = tp;
						break;
					}
					else {
						num.push_back(nm);
						cout << "Enter Phone Number Type: ";
						getline(cin, tp);
						typ.push_back(tp);
						break;
					}
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			contact->setNumberMap(num, typ);
			cout << "Contact edited successfully!" << endl;
			return;
		}
		}
	system("pause");
}

//seraches the contactlist for a specific contact 
void searchlist(vector<Contactinfo*>& v) {
	string key;
	cout << "Please Enter Contact Name to Seek: ";
	getline(cin, key);
	cout << endl;
	int i = 1;
	for (const auto* contact : v) {
		string str = contact->getName();
		size_t index = str.find(key);
		if (index != string::npos) {
			cout << "Matching Contacts: " << endl;
			cout << i << ".Name: " << contact->getName() << endl;
			i++;
			//map<string, string> m = contact->getNumberMap();
			//map<string, string>::iterator itr;
			//for (itr = m.begin(); itr != m.end(); ++itr) {
			//	cout << itr->second << " Number: " << itr->first << endl;
			//}
			cout << endl;
		}
		else {
			cout << "No Matching Contact Found!" << endl;
		}
	}
	system("pause");
}
//Adds a contact to the favorite list
void addfavorite(vector<Contactinfo*>& v, vector<Contactinfo*>& fav) {
	string key;
	cout << "Please Enter Contact Name to Add to the Favorite list: ";
	getline(cin, key);
	cout << endl;
	for (auto* contact : v) {
		if (contact->getName() == key) {
			fav.push_back(contact);
			cout << "Contact Added to favrite list!" << endl;	
			return;
		}
	}
	cout << "Contact not found!" << endl;
	system("pause");
}
//removes a contact from the favorite list
void removefavorite(vector<Contactinfo*>& v) {
	string key;
	cout << "Please Enter Contact Name remove from the Favorite list: ";
	getline(cin, key);
	cout << endl;
	auto it = find_if(v.begin(), v.end(), [&](Contactinfo* contact) {
		return contact->getName() == key;});
	if (it != v.end()) {
		v.erase(it);
		cout << "Contact removed from favorite list!" << endl;
	}
	else {
		cout << "Contact not found!" << endl;
	}
	system("pause");
}
//print favorite list
void printfavlist(vector<Contactinfo*>& v) {
	int i = 1;
	for (const auto* contact : v) {
		cout << i << ".Name: " << contact->getName() << endl;
		i++;
		map<string, string> m = contact->getNumberMap();
		map<string, string>::iterator itr;
		for (itr = m.begin(); itr != m.end(); ++itr) {
			cout << itr->second << " Number: " << itr->first << endl;
		}
		cout << endl;
	}
	if (i == 1) {
		cout << "Favorite list is empty!" << endl;
	}
	system("pause");
}

//edits favlist order
void editfavlist(vector<Contactinfo*>& fav) {
	printfavlist(fav);
	int key1, key2;
	cout << "Please Enter Contact indexes you want to Swap: "<<endl;
	cout << "First contact: ";
	cin >> key1;
	cout << "Second contact: ";
	cin >> key2;
	cout << endl;
	Contactinfo* temp;
	temp = fav[key1 - 1];
	fav[key1 - 1] = fav[key2 - 1];
	fav[key2 - 1] = temp;
	cout << "Success!" << endl;
	system("pause");
}
//prints favourit menu
void printFavmenu(vector<Contactinfo*>& v, vector<Contactinfo*>& fav) {
	while (true) {
	cout << "1. Add a Contact to Favorite List." << endl;
	cout << "2. Remove a Contact from Favorite List." << endl;
	cout << "3. Change Favorite List Order." << endl;
	cout << "4. Print Favorite List." << endl;
	cout << "5. Main Menu." << endl;
	cout << "Please enter your Choic: ";
	char ch = cin.get();
	cout << endl;
		switch (ch) {
		case('1'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			addfavorite(v,fav);
			system("pause");
			break;
		case('2'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			removefavorite(fav);
			break;
		case('3'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			editfavlist(fav);
			break;
		case('4'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			printfavlist(fav);
			break;
		case('5'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return;
			break;
		default:
			break;
		}
	}
}
//prints a single contact according to user's request
void printcontact(vector<Contactinfo*>& v) {
	string key;
	cout << "Please Enter Contact Name to Show: ";
	getline(cin, key);
	cout << endl;
	int i = 1;
	for (const auto* contact : v) {
		if (contact->getName()== key) {
			cout << "Matching Contacts: " << endl;
			cout << i << ".Name: " << contact->getName() << endl;
			i++;
			map<string, string> m = contact->getNumberMap();
			map<string, string>::iterator itr;
			for (itr = m.begin(); itr != m.end(); ++itr) {
				cout << itr->second << " Number: " << itr->first << endl;
			}
			cout << endl;
		}
		else if (contact == v.back()){
			cout << "Contact not Found!" << endl;
		}
	}
	system("pause");
}
int main() {
	cout << "Welcome" << endl;
	vector<Contactinfo*> contactlist;
	vector<Contactinfo*> favlist;
	while (true) {
		cout << "1. Add New Contact." << endl;
		cout << "2. Remove Contact." << endl;
		cout << "3. Edit Contact." << endl;
		cout << "4. Print All Contacts." << endl;
		cout << "5. Favorite Contacts Menu." << endl;
		cout << "6. Search." << endl;
		cout << "7. Contact info print." << endl;
		cout << "8. Exit." << endl;
		cout << "Please enter your Choic: ";
		char ch = cin.get();
		cout << endl;
		switch (ch) {
		case('1'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	
			contactlist.push_back(insert());
			break;
		case('2'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			remove(contactlist);
			break;
		case('3'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			editcontact(contactlist);
			break;
		case('4'):
			SortPrint(contactlist);
			break;
		case('5'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			printFavmenu(contactlist,favlist);
			break;
		case('6'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			searchlist(contactlist);
			break;
		case('7'):
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			printcontact(contactlist);
			break;
		case('8'):
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}