#include<bits/stdc++.h>
using namespace std;

class Table {
private: 
	vector<Record> rows;
	int numOfRows, startAddr;
	Page startPage, endPage;
public:
	Table() {

	}

	Table(vector<Record> r, int addr) {
		rows = r;
		startAddr = addr;
		numOfRows = r.size();
	}

	void showTable();

	bool compareTable(Table t);

};

void Table::showTable() {
	cout<<"Number of rows : "<<numOfRows<<endl;
	cout<<"Starting address : "<<startAddr<<endl;	
	cout<<"Data : "<<endl;
	for(int i=0; i<numOfRows; i++) {
		cout<<rows[i].showRecord()<<endl;
	}
}

bool Table::compareTable(Table t) {
	if(startAddr != t.startAddr) return false;
	if(numOfRows != t.numOfRows) return false;
	for(int i=0; i<numOfRows; i++) {
		if(!rows[i].compareRecord(t.rows[i])) return false;
	}
	return true;
}
