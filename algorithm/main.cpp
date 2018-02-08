#include "ArrayFuctions.h"
#include "SortTools.h"
#include <iostream>
#include <ctime>

int main()
{
	// 图的测试
	/*int vertexNum = 13;

	SparseGraph sg(vertexNum, false);
	DenseGraph dg(vertexNum, false);

	readGraphFromFile(sg, "g1.graph");
	readGraphFromFile(dg, "g1.graph");

	sg.print();
	std::cout << std::endl;
	dg.print();*/

	int num = 100000;
	int* arr = ArrayFuctions::generateRandomArray(num, 0, num);
	//int* arr1 = ArrayFuctions::copyArray(arr, num);
	//int* arr2 = ArrayFuctions::copyArray(arr, num);
	//int* arr3 = ArrayFuctions::copyArray(arr, num);
	//int* arr4 = ArrayFuctions::copyArray(arr, num);
	//int* arr5 = ArrayFuctions::copyArray(arr, num);

	//ArrayFuctions::printArray(arr, num);

	//ArrayFuctions::testSort("希尔排序(交换) ： ", ArrayFuctions::shell_Sort, arr, num);
	//ArrayFuctions::testSort("希尔排序（插入） ： ", ArrayFuctions::shellSort, arr1, num);
	//ArrayFuctions::testSort("三路快速排序 ： ", ArrayFuctions::quickSort3ways, arr1, num);
	//ArrayFuctions::testSort("堆排序（我的） ： ", ArrayFuctions::loopMergeSort, arr2, num);
	//ArrayFuctions::testSort("归并排序（我的） ： ", SortTools::mergeSort, arr3, num);
	//ArrayFuctions::testSort("基数排序（第一版） ： ", SortTools::radixSort2, arr4, num);
	//ArrayFuctions::testSort("基数排序（第二版） ： ", SortTools::radixSort, arr5, num);

	//ArrayFuctions::printArray(arr, num);
	//ArrayFuctions::printArray(arr1, num);

	return 0;
}
