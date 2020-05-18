# Linked list + PThread with Mutex & Read Write Lock

* Compile serial link list program using the following terminal command
```
gcc -o linkList linkList.c
```
* Run the compiled program as show below under three types of cases. If you give any other arguments other than 1,2,3 it will run case 1 as default.
```
./linkList 1
```
* Compile the mutex(`linkListMutex.c`) and read-write lock(`linkListRWLock.c`) programs using the following command
```
gcc -g -Wall -o linkListMutex linkListMutex.c -lpthread
```
* Run the compiled program as shown below under three tupes of cases.
* Argument 1 - case(1 or 2 or 3)
* Argument 2 - no of threads used to execute the pogram
```
./linkListMutex 1 4
```
