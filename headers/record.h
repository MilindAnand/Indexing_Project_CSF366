#define recordSize 150

#include<bits/stdc++.h>
using namespace std;

//Each record is a string of 150 characters 
//The values in record are stored separated by comma 

class Record {
private: 
	string rec;
public:	
	Record() {
		rec = "";
	}

	Record(string input) {
		rec = input;
	}

	string getRecord() {
		return rec;
	}

	void setRecord(string input) {
		rec = input;
	}
};