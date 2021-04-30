#define pageLength 5 //The page length is currently fixed to 5 records 

#include<bits/stdc++.h>

#include "./headers/record.h"
#include "./headers/page.h"
#include "./headers/table.h"
#include "./headers/diskFileMgr.h"

using namespace std;

int main() {
	int mode=1, resp=1;
	cout<<"1. Indexing on key attribute\n2. Indexing on non-key attribute (Clustered Indexing)\n0. Exit\n\nEnter Choice: ";
	cin>>mode;
	switch(mode){
		case 1: {
			do{
				cout<<"1. Show Database\n2. Linear Search\n3. Indexed Search\n4. Multilevel Indexed Search (BPTree)\n5. Modify Record\n6. Delete Record\n7. Add Record\n8. Add Table\n9. Naive Linear Search\n0. Exit\n\nEnter Choice: ";
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
						cout<<"Enter key: ";
						int k, tno;
						cin>>k;
						cout<<"Enter Table number: ";
						cin>>tno;
						DiskFileMgr::buildBPTree();
						Record r3 = DiskFileMgr::BPTreeSearch(k, tno);
						if(!r3.chkEmp())
							cout<<r3.showRecord()<<endl;
						else
							cout<<"\nNot found"<<endl;
						break;
					}
					case 5: {
						int k, tno;
						cout<<"Enter key: ";
						cin>>k;
						cout<<"Enter Table number: ";
						cin>>tno;
						string s;
						cout<<"Enter record: ";
						cin.ignore();
						getline(cin, s);
						Record rec(s);
						DiskFileMgr::modifyRecord(k, tno, rec);
						break;
					}
					case 6: {
						int k, tno;
						cout<<"Enter key: ";
						cin>>k;
						cout<<"Enter Table number: ";
						cin>>tno;
						DiskFileMgr::deleteRecord(k, tno);
						break;
					}
					case 7: {
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
					case 8: {
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
							r.push_back(Record(s));
						}
						Table T = Table(r);
						DiskFileMgr::writeTable(T);
						break;

						///////////////
						// only for very large number of records (~1 million)
						// vector<Record> r;
						// /*int NR;
						// cout<<"Enter number of rows: ";
						// cin>>NR;
						// cout<<"Enter rows:\n";
						// cin.ignore();*/
						// ifstream inp;
						// inp.open("./database/Hr1m.csv");
						// for (long long i = 0; i < 1000000; ++i)
						// {
						// 	string s;
						// 	getline(inp, s);
						// 	//cout<<s<<endl;
						// 	r.push_back(Record(s));
						// }
						// Table T = Table(r);
						// DiskFileMgr::writeTable(T);
						// break;
					}
					case 9: {
						cout<<"Enter key: ";
						int k, tno;
						cin>>k;
						cout<<"Enter Table number: ";
						cin>>tno;
						Record nlr = DiskFileMgr::naivelinearSearch(k, tno);
						if(!nlr.chkEmp())
							cout<<nlr.showRecord()<<endl;
						else
							cout<<"\nNot found"<<endl;
						break;
					}
					case 0: 
					default: return 0;
				}
			}while(resp!=0);
		}
		case 2: {
			do{
				cout<<"1. Show Database\n2. Linear Search\n3. Clustered Indexing Search\n4. Add table\n0. Exit\n\nEnter Choice: ";
				cin>>resp;
				switch(resp){
					case 1: {
						DiskFileMgr::showClustDB();
						break;
					}
					case 2: {
						cout<<"Enter val: ";
						int k, tno;
						cin>>k;
						cout<<"Enter Table number: ";
						cin>>tno;
						vector<Record> nlr = DiskFileMgr::clustLinearSearch(k, tno);
						if(nlr.size() != 0)
						{	
							cout<<"\nRECORDS HAVING CARD NUMBER TYPE = "<<k<<"\n\n";
							for(Record i : nlr)
							{
								cout<<i.showRecord()<<"\n";
							}
							cout<<"\n";
						}	
						else
							cout<<"\nNot found\n";
						break;
					}
					case 3: {
						cout<<"Enter val: ";
						int k, tno;
						cin>>k;
						cout<<"Enter Table number: ";
						cin>>tno;
						vector<Record> nlr = DiskFileMgr::clustIndexedSearch(k, tno);
						if(nlr.size() != 0)
						{	
							cout<<"\nRECORDS HAVING CARD NUMBER TYPE = "<<k<<"\n\n";
							for(Record i : nlr)
							{
								cout<<i.showRecord()<<"\n";
							}
							cout<<"\n";
						}	
						else
							cout<<"\nNot found\n";
						break;
					}
					case 4: {
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
							r.push_back(Record(s));
						}
						Table T = Table(r);
						DiskFileMgr::writeClustTable(T);
						break;
					}
					default: break;
				}
			}while(resp!=0);
		}
	}
	return 0;
}