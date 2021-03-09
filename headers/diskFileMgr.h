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

	//static void searchTable(Table t);

	static void retrievePage(int pgID, int pgSize);

	static void buildPageFile();

	static void showDB();

	static Record linearSearch(int key, int TableNo);
};

void DiskFileMgr::writeTable(Table t) {
	ofstream file_obj, tabf;
	file_obj.open("./database/dataFile.txt", ios::app);
	tabf.open("./database/Tableinfo.txt", ios::app);
	file_obj.seekp(0, ios::end);
	//fprintf(file_obj, "%d,%d\n", t.retSA(), t.retNR());
	t.setAddr(file_obj.tellp());
	int SA = t.retSA(), NR = t.retNR();
	for (int i = 0; i < NR; ++i)
	{
		Record r = t.retRec(i);
		file_obj << r.showRecord() << "\n";
	}

	file_obj.close();
	DiskFileMgr::buildPageFile();
	ifstream pgf;
	pgf.open("./database/Pageinfo.txt", ios::in);
	int pAddr, pId, pSize, stpg=-1, endpg=-1;
	while(!pgf.eof())
	{
		pgf>>pAddr>>pId>>pSize;
		if(pAddr == SA)
		{
			stpg = pId;
			endpg = pId + NR/pageLength;
			if(NR%5 == 0)
				endpg--;
		}
	}
	tabf << SA << " " << NR << " " << stpg << " " << endpg << "\n";
	pgf.close();
	tabf.close();
	//suggestion for future, maybe build a table info file as well, like page info, might be useful for multiple tables in database
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
	//Table ptr;
	//vector<Record> rec;
	bool empty = true;
	file_obj.open("./database/dataFile.txt", ios::in);
	/*int SA=-1, NR=-1;	
	file_obj >> SA;
	file_obj >> NR;
	char buf[2];
	file_obj.getline(buf, 1);
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
		ptr = Table(rec);
		ptr.showTable();
	}*/
	while(!file_obj.eof())
	{
		empty = false;
		string str;
		getline(file_obj, str);
		cout<<str<<endl;
	}
	if(empty){
		cout<<"Empty database\n";	
	}
	//add something for number of rows as well
	file_obj.close();
}

void DiskFileMgr::retrievePage(int pgAddr, int pgSize = pageLength)	//for now pgID is used, once I figure out how to store address of page and use it, probably from index file, this will need an edit// edit made
{
	ifstream fp;
	fp.open("./database/dataFile.txt", ios::in);
	/*string toignore;
	getline(fp, toignore);
	*/
	vector<Record> rec;
	//fp.seekg(recordSize*pageLength*pgID, ios::cur);			//NOTE: This assumes pgID starts from 0, if it starts from 1, then replace pgID with (pgID-1)
	//another assumption used here is the fixed size of each record, if that isnt met then the address will be calculated wrongly
	//if address is known, use fp.seekg(pgAddr, ios::cur) instead

	fp.seekg(pgAddr, ios::cur);
	//cout<<"Pre loop";
	for (int i = 0; i < pgSize; ++i)						//Need to change this from pageLength to length of 
	{
		char tmp[recordSize];
		fp.getline(tmp, recordSize);
		//cout<<tmp<<endl;
		Record r = Record(tmp);
		rec.push_back(r);
	}
	Page pg = Page(rec, pgAddr);
	pg.showPageInfo();
	//cout<<"Post call";
	fp.close();
}

void DiskFileMgr::buildPageFile()
{
	ifstream dbf;
	ofstream pgf;
	dbf.open("./database/dataFile.txt", ios::in);
	pgf.open("./database/Pageinfo.txt", ios::out);
	/*string toignore;
	getline(dbf, toignore);*/
	int pos=0, pid=0, psize=0;
	pgf << pos << " " << pid << " ";
	while(!dbf.eof()){
		string r;
		getline(dbf, r);
		psize++;
		pos+=(r.length()+1);
		if(psize == pageLength && !dbf.eof())
		{
			pid++;
			pgf << psize << "\n" << pos << " " << pid << " ";
			psize=0;
		}
	}
	//if(psize != 0)		//note this writes extra page of size zero at the end if exactly 5 records in last page, shouldnt be an issue ig
	pgf << (psize-1) << "\n";
	dbf.close();
	pgf.close();
}

Record DiskFileMgr::linearSearch(int key, int TableNo)
{
	ifstream tabf, dbf;
	tabf.open("./database/Tableinfo.txt", ios::in);
	while(TableNo--){
		string s;
		getline(tabf, s);
	}
	int SA, NR, spg, epg;
	tabf >> SA >> NR >> spg >> epg;
	dbf.open("./database/dataFile.txt", ios::in);
	string rec;
	while(NR--){
		getline(dbf, rec);
		Record res = Record(rec);
		if(res.chkKey(key))
		{
			return res;
		}
		/*else
		{
			cout<<NR<<" "<<key<<" "<<rec<<endl;
		}*/
	}
	return Record("");
}