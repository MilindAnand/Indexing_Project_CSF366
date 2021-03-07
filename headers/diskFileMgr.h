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
	//fprintf(file_obj, "%d,%d\n", t.retSA(), t.retNR());
	file_obj << t.retSA() << " " << t.retNR() << "\n";
	for (int i = 0; i < t.retNR(); ++i)
	{
		Record r = t.retRec(i);
		file_obj << r.showRecord() << "\n";
	}

	file_obj.close();
/*
	FILE *fp = NULL;
	fp = fopen("./database/dataFile.txt", "a");
	fprintf(fp, "%d,%d\n", t.retSA(), t.retNR());
	if(fp==NULL)
		cout<<"ggwp";
	fclose(fp);*/
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
	vector<Record> rec;
	bool empty = true;
	file_obj.open("./database/dataFile.txt", ios::in);
	int SA=-1, NR=-1;	
	file_obj >> SA;
	file_obj >> NR;
	char buf;
	file_obj >> buf;
	if(SA==-1 && NR==-1) 
	{
		cout<<"Empty database\n";
	}
	else
	{
		cout<<"SA: "<<SA<<"\nNR: "<<NR<<endl;
		
		for (int i = 0; i < NR; ++i)
		{
			char tmp[recordSize];
			file_obj.getline(tmp, recordSize);
			Record r = Record(tmp);
			rec.push_back(r);
		}
		ptr = Table(rec, SA);
		ptr.showTable();
		//if(empty) cout<<"Empty database\n";
	}
	file_obj.close();
}