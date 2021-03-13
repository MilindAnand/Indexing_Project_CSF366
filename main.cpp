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
	for(int i=0; i<10; i++) {
		string s;
		getline(cin, s);
		//cin.getline(s, recordSize);
		r.push_back(Record(s));
		cout<<i<<"\n";
	}
	cout<<"Building table";
	Table t = Table(r);
	cout<<"Table built";
	DiskFileMgr::writeTable(t);
	cout<<"End of write table";
	//t.showTable();
	/*
	*/
	// cout<<t.compareTable(k)<<endl;
	// cout<<s.compareTable(t)<<endl;

	//cout<<endl<<endl;

	DiskFileMgr::showDB();

	/*cout<<"Page part:\n\n";
	Page p = Page(r, 13);
	p.showPageInfo();*/

	//cout<<"\n\nTrial for pages:\n\n";
	//DiskFileMgr::retrievePage(3, 3);

	//DiskFileMgr::buildPageFile();

	//reading thru pageinfo file
	/*ifstream pgf;
	pgf.open("./database/Pageinfo.txt", ios::in);
	while(!pgf.eof())
	{
		int pAddr, pId, pSize;
		pgf>>pAddr>>pId>>pSize;
		//cout<<pAddr<<" "<<pId<<" "<<pSize<<"\n";
		if (pSize==0)
		{
			break;
		}
		cout<<pId<<endl;
		DiskFileMgr::retrievePage(pAddr, pSize);
		cout<<endl<<endl;	
	}
	pgf.close();
	*/
	cout<<"Enter pagebuild";
	DiskFileMgr::buildPageFile();
	cout<<"PageFile BUilt";
	DiskFileMgr::buildIndexFile();

	cout<<"linearSearch\n";
	Record nlr = DiskFileMgr::linearSearch(193819, 0);
	if(!nlr.chkEmp())
		cout<<nlr.showRecord()<<endl;
	else
		cout<<"\nNot found"<<endl;



	cout<<"Indexed Search:\n\n";
	Record r2 = DiskFileMgr::indexedSearch(193819, 0);
	if(!r2.chkEmp())
		cout<<r2.showRecord()<<endl;
	else
		cout<<"\nNot found"<<endl;

	Record nrec("193819,New Record put here, NOTICE!!!");
	DiskFileMgr::deleteRecord(193819, 0);
	Record newrec("201882,Debra,Wood,F,10/30/1969,54,1991,84318,Blair,68009,dgwood");
	DiskFileMgr::addRecord(0, newrec);
	return 0;
}