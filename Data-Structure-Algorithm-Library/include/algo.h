#ifndef ALGO_H
#define ALGO_H 123
#include<common.h>
void bubbleSort(void *,int ,int,int,OperationDetail *,int (*)(void *,void *));
void bubbleSortRecursive(void *,int ,int,int,OperationDetail *,int (*)(void *,void *));
void linearSort(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void linearSortRecursive(void *,int ,int ,int ,OperationDetail *,int (*)(void *,void *));
void selectionSort(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void selectionSortRecursive(void *,int ,int ,int ,OperationDetail *,int (*)(void *,void *));
void insertionSort(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void insertionSortRecursive(void *,int ,int ,int ,OperationDetail *,int (*)(void *,void *));
void quickSort(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void quickSortRecursive(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void mergeSort(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void mergeSortRecursive(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void heapSort(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void heapSortRecursive(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void shellSort(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void shellSortRecursive(void *,int,int,int,OperationDetail *,int (*)(void *,void *));
void pancakeSort(void *,int,int,int,OperationDetail *,int (*) (void *,void *));
void pancakeSortRecursive(void *,int,int,int,OperationDetail *,int (*) (void *,void *));
void radixSort(void *,int,int,int,OperationDetail *,int);
void countSort(void *,int,int,int,OperationDetail *,int);
void addressCalculationSort(void *,int,int,int,OperationDetail *,int);
#endif