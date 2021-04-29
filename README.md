# Indexing_Project_CSF366
Datbase Systems project related to indexing and disk management 

# How to run the program
## Ubuntu 20.04
In root directory:
```
   $ g++ main.cpp - main.o -fno-stack-protector
   $ ./main.o
```
   
# Progress made till now
1) Simulation of DiskFileManager created
2) Implementation of classes: Record, Page, Table, and DiskFileMgr
3) Indexfile, Pageinfo, Tableinfo files built and populated using appropriate functions
4) Linear Search for records on key value Implemented
5) Indexed search on key Implemented (Sparse Primary Indexing followed)
6) Organising main function for better UX
7) Addition, Deletion and Modification of records
8) Apply time functions to measure performance improvements.
9) Apply number of block(file) accesses as a measure of performance improvements.
10) BPTree class created for multilevel indexing
11) Insertion into BPTree 
12) Search in BPTree integrated with the rest of the program
13) Clustered indexing added

# Things left to do
1) Testing current functions, especially for multiple tables as that has not been extensively tested
2) Add time and block access measurements to multilevel indexed search to measure performance
3) Add further functionalities to BPTree
4) Serialise BPTree to avoid building it each time.
