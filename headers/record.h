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

	string showRecord() {
		return rec;
	}

	void setRecord(string input) {
		rec = input;
	}

	int retLen(){
		return rec.length();
	}

	bool chkKey(int key);

	bool compareRecord(Record r);

	int retKey(){
		size_t pos = rec.find(',');
		if(pos != string::npos)			//string::npos is -1 defined by std library
		{
			string id = rec.substr(0, pos);
			int k = stoi(id);
			return k;
		}
		return -1;
	}
};

bool Record::compareRecord(Record r) {
	if(rec != r.rec) return false;
	return true;
}

bool Record::chkKey(int key)
{
	if(this->retKey() == key)
			return true;
	return false;
}