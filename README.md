# ECS 60 Programs
## BTreeImplementation
### Description 

This program implements a version of the **insert** function of the B+ Tree structure in *C++*, an efficient data structure used to store data on a hard drive. 

### How To Use The BTreeImplementation Folder

1) Place all the files in a single directory and run **make** to compile the executable BTree. 
2) Run **BTree <data file> <maximum number of internal nodes (M)> <maximum number of leaf nodes (L)>**.
    Ex. **BTree BTree12.dat 3 2**
3) A few data files (.dat) have been provided as examples to test.
4) There is also a file called *BTreeDriverDebug.cpp* provided that can be used in place of BTreeDriver.cpp. This file runs the program one insertion at a time, rather than inserting all numbers at once; pressing enter proceeds to the next insertion. To replace BTreeDriver with BTreeDriverDebug, simply change the Makefile as to find and replace every **BTreeDriver** with **BTreeDriverDebug**.

## BidirectionalDijkstra
### Description

This program implements a version of the **bidirectional Dijkstra** algorithm, which can be used to find the shortest path between two specific points. The bidirectional Dijkstra algorithm is a variation of the Dijkstra algorithm that runs Dijkstra's from both the starting point and the destination. This specific program uses cities and roads as the vertices and edges of the graph and returns the roads to provide the shortest distance between given starting and ending cities. It then prints the path and returns the CPU time required to find the path.

### How to Use The BidirectionalDijkstra Folder

1) Place all the files in a single directory and run **make** to compile the executable runner.out.
2) Run **./runner.out *<text file>* 0**.
    Ex. **./runner.out roads100-4S.txt 0**
3) Text files containing the roads and cities are provided for testing. 
4) Use the comments to find what to remove in order to avoid printing the actual path.

###### These programs were created for a class. 










