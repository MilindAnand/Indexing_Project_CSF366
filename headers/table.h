#include<bits/stdc++.h>
using namespace std;

class Table {
private: 
	vector<Record> rows;
	int numOfRows, startAddr;
	Page startPage, endPage;
public:
	Table(vector<Record> r, int addr) {
		rows = r;
		startAddr = addr;
		numOfRows = r.size();
	}

	void getTable() {
		cout<<"Number of rows : "<<numOfRows<<endl;
		cout<<"Starting address : "<<startAddr<<endl;	
		cout<<"Data : "<<endl;
		for(int i=0; i<numOfRows; i++) {
			cout<<rows[i].getRecord()<<endl;
		}
	}
};