#include<bits/stdc++.h>
using namespace std;

//Each page has maximum 5 records for now

class Page {
private:
	vector<Record> r;
	int startAddr;
public:
	Page() {
		for(int i=0; i<pageLength; i++) {
			r.push_back(Record("empty"));
		}
		startAddr = 0;
	}

	Page(vector<Record> inp, int addr) {
		r = inp;
		startAddr = addr;
	}

	void getPageInfo() {
		cout<<"Starting address : "<<startAddr<<endl;
		cout<<"Records : "<<endl;
		for(int i=0; i<pageLength; i++) {
			cout<<r[i].getRecord()<<endl;
		}
	}

	void setPageInfo() {

	}
};