#include<bits/stdc++.h>
using namespace std;

class Table {
private: 
	vector<Record> rows;
	int numOfRows, startAddr;
	int startPageID, endPageID;
public:
	Table() {

	}

	Table(vector<Record> r) {
		rows = r;
		numOfRows = r.size();
	}

	int retSA(){
		return startAddr;
	}

	int retNR(){
		return numOfRows;
	}

	Record retRec(int i){
		return rows[i];
	}

	void setAddr(int addr){
		startAddr = addr;
	}

	void setPgNo(int sp, int ep){
		startPageID = sp;
		endPageID = ep;
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
