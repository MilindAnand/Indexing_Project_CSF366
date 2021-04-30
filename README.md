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
14) Extensive Testing carried out, with graphs for visualisation

# Possible Further Additions
1) Add further functionalities to BPTree
2) Serialise BPTree to avoid building it each time.
3) Add secondary indexing (Single level indexing on non-key non-ordering attribute).

# Issues
1) There seems to be some issue with the clustered indexing part, which seemed difficult to find/fix; to keep the code from breaking it uses linear search if clustered search fails. Feel free to drop in a PR in case a fix is found.