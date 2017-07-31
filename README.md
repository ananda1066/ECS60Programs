# BTreeImplementation
## Description 

This repo implements a version of the **insert** function of the B+ Tree structure in *C++*, an efficient data structure used to store data on a hard drive. 

## How To Use This Repo

1) Place all the files in a single directory and run **make** to compile the executable BTree. 
2) Run **BTree <data file> <maximum number of internal nodes (M)> <maximum number of leaf nodes (L)>**.
    Ex. **BTree BTree12.dat 3 2**
3) A few data files (.dat) have been provided as examples to test.
4) There is also a file called *BTreeDriverDebug.cpp* provided that can be used in place of BTreeDriver.cpp. This file runs the program one insertion at a time, rather than inserting all numbers at once; pressing enter proceeds to the next insertion. To replace BTreeDriver with BTreeDriverDebug, simply change the Makefile as to find and replace every **BTreeDriver** with **BTreeDriverDebug**.

###### This program was created for a class. 










