#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct container {
	int pAdd, pSiz;
};
typedef struct container cont;

class DiskFileMgr {
public:
	static void writeTable(Table t); //function to add table to dataFile

	static Page retrievePage(int pgID, int pgSize);

	static void buildPageFile();

	static void buildIndexFile();

	static void showDB();
	
	static cont indexHelper(int key, int TableNo);

	static Record linearSearch(int key, int TableNo);

	static Record indexedSearch(int key, int TableNo);

	static void modifyRecord(int key, int TableNo, Record nrec);

	static void deleteRecord(int key, int TableNo);

	static void addRecord(int TableNo, Record nrec);
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

void DiskFileMgr::showDB() {
	ifstream file_obj;
	bool empty = true;
    int ctr = 0;
	file_obj.open("./database/dataFile.txt", ios::in);
    string str;
	while(getline(file_obj, str)) {
		empty = false;
		cout<<"RECORD "<<ctr<<" : "<<str<<endl;
        ctr++;
	}
	if(empty) {
		cout<<"EMPTY DATABASE\n";	
	}
    cout<<"TOTAL "<<ctr<<" ROW(S) FETCHED\n";
	file_obj.close();
}

Page DiskFileMgr::retrievePage(int pgAddr, int pgSize = pageLength)	//for now pgID is used, once I figure out how to store address of page and use it, probably from index file, this will need an edit// edit made
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
	//pg.showPageInfo();
	//cout<<"Post call";
	fp.close();
	return pg;
}

void DiskFileMgr::buildPageFile() {
    cout<<"BUILDING PAGE INFO...\n";
	ifstream dbf;
	ofstream pgf;
	dbf.open("./database/dataFile.txt", ios::in);
	pgf.open("./database/Pageinfo.txt", ios::out);
	int pos=0, pid=0, psize=0;
	pgf << pos << " " << pid << " ";
    string r;
	while(getline(dbf, r)) {
		psize++;
		pos+=(r.length()+1);
		if(psize == pageLength && !dbf.eof()) {
			pid++;
			pgf << psize << "\n" << pos << " " << pid << " ";
			psize=0;
		}
	}
	//if(psize != 0)		//note this writes extra page of size zero at the end if exactly 5 records in last page, shouldnt be an issue ig
	pgf << (psize-1) << "\n";
	dbf.close();
	pgf.close();
    cout<<"PAGE INFO BUILT SUCCESSFULLY\n";
}

Record DiskFileMgr::linearSearch(int key, int TableNo) {
	ifstream tabf, dbf;
	int SA=-1, NR=-1, spg, epg;
	string rec;
	tabf.open("./database/Tableinfo.txt", ios::in);
	dbf.open("./database/dataFile.txt", ios::in);
    time_point<system_clock> start, end; 
    start = system_clock::now();
    while(TableNo-- && !tabf.eof()) {
		string s;
		getline(tabf, s);
		if(s.length()==0)
			break;
	}
	tabf >> SA >> NR >> spg >> epg;
	if(TableNo != -1 || NR == -1) {
		cout<<"LINEAR SEARCH : INVALID TABLE NUMBER\n";
		return Record("");
	}
	while(NR--) {
		getline(dbf, rec);
		Record res = Record(rec);
		if(res.chkKey(key)) {
            cout<<"LINEAR SEARCH : RECORD "<<key<<" FOUND SUCCESSFULLY\n";
            end = system_clock::now(); 
            duration<double> elapsed_seconds = end - start;
            cout<<"LINEAR TIME TAKEN : "<<elapsed_seconds.count()<<endl;
            tabf.close();
            dbf.close();
			return res;
		}
	}
    cout<<"LINEAR SEARCH : RECORD "<<key<<" NOT FOUND\n";
    end = system_clock::now();
    duration<double> elapsed_seconds = end - start;
    cout<<"LINEAR TIME TAKEN : "<<elapsed_seconds.count()<<endl;
    tabf.close();
    dbf.close();
	return Record("");
}

void DiskFileMgr::buildIndexFile() {
	//idea here is to store the index entries for each table on one line, with page number and id number separated by , as delimiter
	cout<<"BUILDING INDEX FILE...\n";
    ifstream tabf, pgf;
	ofstream indf;
	tabf.open("./database/Tableinfo.txt", ios::in);
	pgf.open("./database/Pageinfo.txt", ios::in);
	indf.open("./database/indexFile.txt", ios::out);
	while(!tabf.eof()) {
		int SA=-1, NR, spg, epg;
		tabf >> SA >> NR >> spg >> epg;
		if(SA == -1) break;
		int bck = spg;
		while(bck--) {
			string s;
			getline(pgf, s);		//skipping lines till appropriate line is reached
		}
		int pAddr, pId, pSize;
		do {
			pgf >> pAddr >> pId >> pSize;
			Page pg = DiskFileMgr::retrievePage(pAddr, pSize);
			int k = pg.topInd();
			indf << pId << "," << pAddr << "," << pSize << "," << k << " ";
		}while(pId != epg);
		indf << "\n";
	}
	tabf.close();
	pgf.close();
	indf.close();
    cout<<"INDEX FILE BUILT SUCCESSFULLY\n";
}

cont DiskFileMgr::indexHelper(int key, int TableNo) {
	ifstream tabf, indf, dbf;
	tabf.open("./database/Tableinfo.txt", ios::in);
	indf.open("./database/indexFile.txt", ios::in);
	cont result;
	result.pAdd = -1;
	result.pSiz = -1;
	while(TableNo-- && !tabf.eof()) {
		string s, t;
		getline(tabf, s);
		getline(indf, t);
		if(s.length()==0)
			break;
	}
	int SA=-1, NR=-1, spg, epg;
	tabf >> SA >> NR >> spg >> epg;
	if(TableNo != -1 || NR == -1) {
		cout<<"INVALID TABLE NUMBER\n";
        tabf.close();
        indf.close();
		return result;
	}

	int pgno=spg, pAddr=-1, pSize=-1;
	do {
		string s;
		indf >> s;
		size_t p1 = s.find(',');
		size_t p2 = s.find(',', p1+1);
		size_t p3 = s.find(',', p2+1);
	
		int addr = stoi(s.substr(p1+1, p2)), size = stoi(s.substr(p2+1, p3)), k = stoi(s.substr(p3+1, s.length()));
	
		if(k > key) {
			pgno--;
			break;
		}
		pAddr = addr;
		pSize = size;
		pgno++;
		
		if (k==key)
			break;
	}while(pgno != epg+1);
	result.pAdd = pAddr;
	result.pSiz = pSize;
	cout<<result.pAdd<<" "<<result.pSiz<<"\n";
	tabf.close();
    indf.close();
    return result;
}

Record DiskFileMgr::indexedSearch(int key, int TableNo) {
	//auto index_start = high_resolution_clock::now();
    time_point<system_clock> start, end;
    start = system_clock::now();
    cont ct = DiskFileMgr::indexHelper(key, TableNo);
	int pAddr = ct.pAdd, pSize = ct.pSiz;
	if(pAddr==-1) {
		cout<<"INDEXED SEARCH : RECORD "<<key<<" NOT FOUND\n";
		return Record("");	
	}
	Page pg = DiskFileMgr::retrievePage(pAddr, pSize);
	Record res = pg.searchPage(key);
    //auto index_end = high_resolution_clock::now();
    end = system_clock::now();
    duration<double> elapsed_seconds = end - start; 
    if(res.chkEmp() == false)
        cout<<"INDEXED SEARCH : RECORD "<<key<<" FOUND SUCCESSFULLY\n";
    else cout<<"INDEXED SEARCH : RECORD "<<key<<" NOT FOUND\n";
    //auto duration = duration_cast<microseconds>(index_end - index_start);
    cout<<"INDEXED TIME TAKEN : "<<elapsed_seconds.count()<<endl;
    return res;
}

void DiskFileMgr::modifyRecord(int key, int TableNo, Record nrec) {
	cont ct = DiskFileMgr::indexHelper(key, TableNo);
	int pAddr = ct.pAdd, pSize = ct.pSiz;
	if(pAddr==-1) {
		cout<<"MODIFY RECORD : RECORD "<<key<<" NOT FOUND\n";
		return;
	}
	fstream dbf;
	dbf.open("./database/dataFile.txt", ios::in | ios::out);
	dbf.seekg(pAddr, ios::beg);
	int offset=0, flag=0;
	while(pSize--){
		string ts;
		getline(dbf, ts);
		Record tr(ts);
		if(key == tr.retKey()) {	
			flag=1;
			break;
		}
		/*else
		{
			cout<<tr.retKey()<<endl;
		}*/
		offset += (tr.retLen()+1);
	}
	if(!flag) {
		cout<<"MODIFY RECORD : RECORD "<<key<<" NOT FOUND\n";
        dbf.close();
		return;
	}
	/*if(pAddr == 0 && offset==1)
		offset=0;*/
	dbf.seekp(pAddr+offset, ios::beg);
	dbf<<nrec.showRecord()<<"\n";
    dbf.close();
}

void DiskFileMgr::deleteRecord(int key, int TableNo) {
	Record drec = DiskFileMgr::indexedSearch(key, TableNo);
	if(drec.chkEmp()) {
		cout<<"DELETE RECORD : RECORD "<<key<<" NOT FOUND"<<endl;
		return;
	}
	ifstream dbf;
	ofstream tmpf;
	dbf.open("./database/dataFile.txt", ios::in);
	tmpf.open("./database/temp.txt", ios::out);
	string tmp;
	while(getline(dbf, tmp)) {
		Record t(tmp);
		if(drec.compareRecord(t))
			continue;
		else
			tmpf<<tmp<<"\n";
	}
	tmpf.close();
	dbf.close();
	remove("./database/dataFile.txt");
	rename("./database/temp.txt", "./database/dataFile.txt");
	DiskFileMgr::buildPageFile();
	DiskFileMgr::buildIndexFile();
    	fstream tabf;
	tabf.open("./database/Tableinfo.txt", ios::in | ios::out);
	int SA, NR, spg, epg, offset=0;
	while(TableNo--){
		getline(tabf, tmp);
		offset+=tmp.length()+1;
	}
	tabf >> SA >> NR >> spg >> epg;
	NR--;
	if(NR%pageLength == 0)
		epg--;
	tabf.seekp(offset, ios::beg);
	tabf << SA <<" " << NR << " " <<spg<<" "<<epg<<"\n";
	tabf.close();
    	cout<<"RECORD "<<key<<" DELETED SUCCESSFULLY\n";
}

void DiskFileMgr::addRecord(int TableNo, Record nrec) {
	ifstream dbf;
	ofstream tmpf;
	dbf.open("./database/dataFile.txt", ios::in);
	tmpf.open("./database/temp.txt", ios::out);
	int newkey = nrec.retKey();
	string tmp;
	bool flag=true;
	while(getline(dbf, tmp)) {
		Record t(tmp);
		if(flag && newkey < t.retKey()) {
			tmpf<<nrec.showRecord()<<"\n";
			flag = false;
		}
		tmpf<<tmp<<"\n";
	}
	tmpf.close();
	dbf.close();
	remove("./database/dataFile.txt");
	rename("./database/temp.txt", "./database/dataFile.txt");
	DiskFileMgr::buildPageFile();
	DiskFileMgr::buildIndexFile();
	fstream tabf;
	tabf.open("./database/Tableinfo.txt", ios::in | ios::out);
	int SA, NR, spg, epg, offset=0;
	while(TableNo--){
		getline(tabf, tmp);
		offset+=tmp.length()+1;
	}
	tabf >> SA >> NR >> spg >> epg;
	NR++;
	if(NR%pageLength == 1)
		epg++;
	tabf.seekp(offset, ios::beg);
	tabf<<SA<<" "<<NR<<" "<<spg<<" "<<epg<<"\n";
	tabf.close();
}
