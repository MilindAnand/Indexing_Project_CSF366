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

    //Test code to build PageFile and IndexFile
	DiskFileMgr::buildPageFile();
	DiskFileMgr::buildIndexFile();

    //Test code to search records linearly and by indexing
	Record nlr = DiskFileMgr::linearSearch(193819, 0);
	Record r2 = DiskFileMgr::indexedSearch(193819, 0);
	
    //Test code for adding and deleting records
    //Record nrec("193819,New Record put here, NOTICE!!!");
    //DiskFileMgr::addRecord(0, nrec);
    //DiskFileMgr::deleteRecord(193819, 0);
	//Record newrec("201882,Debra,Wood,F,10/30/1969,54,1991,84318,Blair,68009,dgwood");
	//DiskFileMgr::addRecord(0, newrec);
	
    return 0;
}
