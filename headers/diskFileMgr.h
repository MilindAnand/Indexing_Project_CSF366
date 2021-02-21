#include<bits/stdc++.h>
using namespace std;

class DiskFileMgr {
private:
public:
	static void writeTable(Table t); //function to add table to dataFile

	static void deleteTable(Table t) {
		//function to delete table from dataFile
	}

	static void modifyTable() {
		//function to modify records in particular table
	}

	// static void searchTable(Table t);

	static void showDB();
};

void DiskFileMgr::writeTable(Table t) {
	ofstream file_obj;
	file_obj.open("./database/dataFile.txt", ios::app);
	file_obj.write((char*)&t, sizeof(t));
	file_obj.close();
}

// void DiskFileMgr::searchTable(Table t) {
// 	ifstream file_obj;
// 	Table ptr;
// 	file_obj.open("./database/dataFile.txt", ios::in);
// 	file_obj.read((char*)&ptr, sizeof(ptr));
// 	while(!file_obj.eof()) {
// 		if(t.compareTable(ptr)) {
// 			cout<<"Table found successfully\n";
// 			file_obj.close();
// 			return;
// 		}
// 		file_obj.read((char*)&ptr, sizeof(ptr));
// 	}
// 	cout<<"Table not found in database\n";
// 	file_obj.close();
// 	return;
// }

void DiskFileMgr::showDB() {
	ifstream file_obj;
	Table ptr;
	Record rec;
	bool empty = true;
	file_obj.open("./database/dataFile.txt", ios::in);
	while(!file_obj.eof()) {
		file_obj.read((char*)&ptr, sizeof(ptr));
		empty = false;
		ptr.showTable();
	}
	if(empty) cout<<"Empty database\n";
	file_obj.close();
}