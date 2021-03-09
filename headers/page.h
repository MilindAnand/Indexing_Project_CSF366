#include<bits/stdc++.h>
using namespace std;

//Each page has maximum 5 records for now

class Page {
private:
	vector<Record> r;
	int startAddr;
	int numRec;
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
		numRec = inp.size();
	}

	void showPageInfo() {
		cout<<"Starting address : "<<startAddr<<endl;
		cout<<"Records : "<<endl;
		for(int i=0; i<numRec; i++) {
			cout<<r[i].showRecord()<<endl;
		}
	}

	int topInd(){
		return r[0].retKey();
	}

	Record searchPage(int key){
		Record res = Record();
		for (int i = 0; i < pageLength; ++i)
		{
			if(r[i].chkKey(key))
			{
				return r[i];
			}
		}
		return res;
	}

	void setPageInfo() {

	}
};