#include "ArrayFuctions.h"
#include "SortTools.h"
#include <iostream>
#include <ctime>

int main()
{
	// ͼ�Ĳ���
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

	//ArrayFuctions::testSort("ϣ������(����) �� ", ArrayFuctions::shell_Sort, arr, num);
	//ArrayFuctions::testSort("ϣ�����򣨲��룩 �� ", ArrayFuctions::shellSort, arr1, num);
	//ArrayFuctions::testSort("��·�������� �� ", ArrayFuctions::quickSort3ways, arr1, num);
	//ArrayFuctions::testSort("�������ҵģ� �� ", ArrayFuctions::loopMergeSort, arr2, num);
	//ArrayFuctions::testSort("�鲢�����ҵģ� �� ", SortTools::mergeSort, arr3, num);
	//ArrayFuctions::testSort("�������򣨵�һ�棩 �� ", SortTools::radixSort2, arr4, num);
	//ArrayFuctions::testSort("�������򣨵ڶ��棩 �� ", SortTools::radixSort, arr5, num);

	//ArrayFuctions::printArray(arr, num);
	//ArrayFuctions::printArray(arr1, num);

	return 0;
}
