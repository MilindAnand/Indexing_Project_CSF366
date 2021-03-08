#define pageLength 5 //The page length is currently fixed to 5 records 

#include<bits/stdc++.h>

#include "./headers/record.h"
#include "./headers/page.h"
#include "./headers/table.h"
#include "./headers/diskFileMgr.h" 

using namespace std;

//This file is added for testing Table, Page and Record classes
//Each table can have multiple pages and each page can have multiple tables

int main() {
	vector<Record> r, rec;
	/*for(int i=0; i<5; i++) {
		string s;
		cin>>s;
		//cin.getline(s, recordSize);
		r.push_back(Record(s));
	}
	Table t = Table(r, 10);
	t.showTable();*/
	// cout<<t.compareTable(k)<<endl;
	// cout<<s.compareTable(t)<<endl;
	//DiskFileMgr::writeTable(t);
	DiskFileMgr::showDB();

	/*cout<<"Page part:\n\n";
	Page p = Page(r, 13);
	p.showPageInfo();*/

	cout<<"\n\nTrial for pages:\n\n";
	//DiskFileMgr::retrievePage(3, 3);

	DiskFileMgr::buildPageFile();

	//reading thru pageinfo file
	ifstream pgf;
	pgf.open("./database/Pageinfo.txt", ios::in);
	for (int i = 0; i < 4; ++i)
	{
		int pAddr, pId, pSize;
		pgf>>pAddr>>pId>>pSize;
		//cout<<pAddr<<" "<<pId<<" "<<pSize<<"\n";
		cout<<pId<<endl;
		DiskFileMgr::retrievePage(pAddr, pSize);
		cout<<endl<<endl;	
	}
	pgf.close();
	return 0;
}