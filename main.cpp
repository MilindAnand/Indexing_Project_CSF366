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
	int resp=1;
	do{
		cout<<"1. Show Database\n2. Linear Search\n3. Indexed Search\n4. Modify Record\n5. Delete Record\n6. Add Record\n7. Add Table\n0. Exit\n\nEnter Choice: ";
		cin>>resp;
		switch(resp){
			case 1: {
				DiskFileMgr::showDB();
				break;
			}
			case 2: {
				cout<<"Enter key: ";
				int k, tno;
				cin>>k;
				cout<<"Enter Table number: ";
				cin>>tno;
				Record nlr = DiskFileMgr::linearSearch(k, tno);
				if(!nlr.chkEmp())
					cout<<nlr.showRecord()<<endl;
				else
					cout<<"\nNot found"<<endl;
				break;
			}
			case 3: {
				cout<<"Enter key: ";
				int k, tno;
				cin>>k;
				cout<<"Enter Table number: ";
				cin>>tno;
				Record r2 = DiskFileMgr::indexedSearch(k, tno);
				if(!r2.chkEmp())
					cout<<r2.showRecord()<<endl;
				else
					cout<<"\nNot found"<<endl;
				break;
			}
			case 4: {
				int k, tno;
				cout<<"Enter key: ";
				cin>>k;
				cout<<"Enter Table number: ";
				cin>>tno;
				string s;
				cout<<"Enter record: ";
				cin.ignore();
				getline(cin, s);
				// char buf;
				// cin>>buf;
				// if(s.length()!=0)
				// 	k=1;
				//cout<<"lala"<<s;
				Record rec(s);
				DiskFileMgr::modifyRecord(k, tno, rec);
				break;
			}
			case 5: {
				int k, tno;
				cout<<"Enter key: ";
				cin>>k;
				cout<<"Enter Table number: ";
				cin>>tno;
				DiskFileMgr::deleteRecord(k, tno);
				break;
			}
			case 6: {
				int tno;
				cout<<"Enter Table number: ";
				cin>>tno;
				cout<<"Enter record: ";
				string s;
				cin.ignore();
				getline(cin, s);
				Record rec(s);
				DiskFileMgr::addRecord(tno, rec);
				break;
			}
			case 7: {
				vector<Record> r;
				int NR;
				cout<<"Enter number of rows: ";
				cin>>NR;
				cout<<"Enter rows:\n";
				cin.ignore();
				for (int i = 0; i < NR; ++i)
				{
					string s;
					getline(cin, s);
					//cout<<s<<endl;
					r.push_back(Record(s));
				}
				Table T = Table(r);
				DiskFileMgr::writeTable(T);
				break;
			}
			case 0: 
			default: return 0;
		}
	}while(resp!=0);
	// vector<Record> r, rec;
	// for(int i=0; i<10; i++) {
	// 	string s;
	// 	getline(cin, s);
	// 	//cin.getline(s, recordSize);
	// 	r.push_back(Record(s));
	// 	cout<<i<<"\n";
	// }
	// cout<<"Building table";
	// Table t = Table(r);
	// cout<<"Table built";
	// DiskFileMgr::writeTable(t);
	// cout<<"End of write table";
	// //t.showTable();
	// /*
	// */
	// // cout<<t.compareTable(k)<<endl;
	// // cout<<s.compareTable(t)<<endl;

	// //cout<<endl<<endl;

	// DiskFileMgr::showDB();

	// /*cout<<"Page part:\n\n";
	// Page p = Page(r, 13);
	// p.showPageInfo();*/

	// //cout<<"\n\nTrial for pages:\n\n";
	// //DiskFileMgr::retrievePage(3, 3);

	// //DiskFileMgr::buildPageFile();

	// //reading thru pageinfo file
	// ifstream pgf;
	// pgf.open("./database/Pageinfo.txt", ios::in);
	// while(!pgf.eof())
	// {
	// 	int pAddr, pId, pSize;
	// 	pgf>>pAddr>>pId>>pSize;
	// 	//cout<<pAddr<<" "<<pId<<" "<<pSize<<"\n";
	// 	if (pSize==0)
	// 	{
	// 		break;
	// 	}
	// 	cout<<pId<<endl;
	// 	DiskFileMgr::retrievePage(pAddr, pSize);
	// 	cout<<endl<<endl;	
	// }
	// pgf.close();
	
	// cout<<"Enter pagebuild";
	// DiskFileMgr::buildPageFile();
	// cout<<"PageFile BUilt";
	// DiskFileMgr::buildIndexFile();

	// cout<<"linearSearch\n";
	// Record nlr = DiskFileMgr::linearSearch(193819, 0);
	// if(!nlr.chkEmp())
	// 	cout<<nlr.showRecord()<<endl;
	// else
	// 	cout<<"\nNot found"<<endl;



	// cout<<"Indexed Search:\n\n";
	// Record r2 = DiskFileMgr::indexedSearch(193819, 0);
	// if(!r2.chkEmp())
	// 	cout<<r2.showRecord()<<endl;
	// else
	// 	cout<<"\nNot found"<<endl;

	// Record nrec("193819,New Record put here, NOTICE!!!");
	// DiskFileMgr::deleteRecord(193819, 0);
	// Record newrec("201882,Debra,Wood,F,10/30/1969,54,1991,84318,Blair,68009,dgwood");
	// DiskFileMgr::addRecord(0, newrec);
	return 0;
}