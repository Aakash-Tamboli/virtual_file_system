#	DOCUMENTATION

## Overview
here you get to know about `library` of GENERIC data structures and alogrithms, which is built in `c` programming language.

## Why The Generic Data Structure and algorithms In C ?
we have `STL in C++`, `Collection classes in Java` but when we talk about `C` so there is no such facilites to handle some huge data and In this project I Implemeted data stuctures and some sorting algorithms for data.

***
* [OperationDetail](#error)
  * [Error-Codes](#error-codes)
* [Compile Code](#how-to-compile-code)
  * [Error-Codes](#error-codes)
                          
   
## OperationDetail

The struct type OperationDetail have two properties,

                                              typedef struct __$__operation_detail
                                              {
                                              int code,succ;
                                              }OperationDetail;

1. succ:-
      it aknowlegde your operation is successfull or not.

2. code:-
      it aknowlegde why your operation failed see error codes.

    ### Error-Codes
          Error-Codes   | description of Code
          ------------- | --------------------
                0       | Operation Successfull Executed
                1       | Problem in LowerBound,UpperBound Or may be you are passing same values
                2       | Unable To Allocate Memory For Internal Use
                3       | Problem in your Data_ Structure Address may be you passed NULL Or AVL Tree is Empty
                4       | Problem in data address which you want to store in Data_Structure or retrieve from Data_Structure may be you
                        | passed NULL;
                        | void pushOnStack(&yourStack,NULL,&YourstructtypeErrorCode)
                        | popFromStack(&yourStack,NULL,&YourstructtypeErrorCode)
                5       | Please Initialized Your Data_Structure First
                        |  Note:If you are trying to pass value of sizeofOneElement is 0(zero) in 
                        |       initData_Structure(&yourData_Structure,0);
                        |       Then Your Data_Structure will not initialized because it make no sense.
                6       | Problem in Your Comparator predicate may be you passed NULL
                7       | Your Size of One Element is 0 or may be negative.
                8       | Your Collection is Not int data_type.this Algo only for int data_type
	            9       | Element not found inside AVLTree Or Invalid index related to Singly and Doubly LinkedList
    	        10      | Data already exists inside AVLTree Duplicate Not allowed Or append operation fails because differnet sizeofOneElment in Singly and Doubly



## How to compile code
1. When you compile code inside data-Structure-Algorithm-Library/testCases/
``` c
gcc filename.c -o filename.exe -I ..\include -L ..\lib -l dsAlgo
```

## Algorithm information
My dsAlgo library offers only 12 sorting algorithm this are
                        
           Algorithm    | supported data type   | recursive approach available |         collection type
         -------------- | -------------------   | ---------------------------  | -------------------------------
         Bubble Sort    | Generic data_type     |           YES                |         array type collection
         linear sort    | Generic data_type     |           YES                |         array type collection
         selection sort | Generic data_type     |           YES                |         array type collection
         insertion sort | Generic data_type     |           YES                |         array type collection
         quick sort     | Generic data_type     |           YES                |         array type collection
         merge sort     | Generic data_type     |           YES                |         array type collection
         heap sort      | Generic data_type     |           YES                |         array type collection
         radix sort     | Only int data type    |           NO                 |         array type collection
         count sort     | Only int data type    |           NO                 |         array type collection
         shell sort     | Generic data_type     |           YES                |         array type collection
         pancake sort   | Generic data_type     |           YES                |         array type collection
      addresscalculation| Only int data type    |           NO                 |         array type collection   
            sort        |                       |                              |                              

[More Information about each Alorigthm](https://github.com/Immanuel-Beena/Data-Structure-Algorithm-Library/blob/master/ALGO_README.md)

## DataStructure information
My dsAlgo library offers only 5 Data structure this are

                                 DataStructure      |      supported data type   
                           ------------------------ | ---------------------------   
                                       Stack        |     Generic data_type     
                                       Queue        |     Generic data_type     
                                  SinglyLinkedList  |     Generic data_type     
                                  DoublyLinkedList  |     Generic data_type    
				           AVL Tree     |     Generic data_type



[More Information about each Data Structure](https://github.com/Immanuel-Beena/Data-Structure-Algorithm-Library/blob/master/DS_README.md)

## Future enhancement
I will Implement:
1) sorting algos. for doublyLinkedList
