# Indexing_Project_CSF366
Datbase Systems project related to indexing and disk management 

# How to run the program
1) Open terminal in root folder
2) Type the following line in terminal
   "g++ -o main.o main.cpp"
   
# Progress made till now
1) Simulation of DiskFileManager created
2) Implementation of classes: Record, Page, Table, and DiskFileMgr
3) Indexfile, Pageinfo, Tableinfo files built and populated using appropriate functions
4) Linear Search for records on key value Implemented
5) Indexed search on key Implemented (Sparse Primary Indexing followed)

# Things left to do
1) Testing current functions, especially for multiple tables as that has not been extensively tested
2) Organising main function for better UX
3) Figure out how to modify records in the datafile, might be impossible to do without reading the datafile
   into another file and then modifying and copying the rest back, as, at the moment at least, C++ seems incapable to insert in between
   existing text without overwriting.
