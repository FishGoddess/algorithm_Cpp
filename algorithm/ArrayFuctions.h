#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#define UNORDERED_ARRAY -1

namespace ArrayFuctions
{
	// 打印数组的函数，支持多种类型的数组
	//==========================================================================
	template<typename T>
	void printArray(T arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << arr[i];

			if (i < n - 1)
			{
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
	//==========================================================================

	// 生成一个拥有 n 个int类型元素的数组，默认是无序的，混乱程度是swapTimes，范围是 rangeL 到 rangeR
	//==========================================================================
	int* generateRandomArray(int n, int rangeL, int rangeR, int swapTimes = UNORDERED_ARRAY)
	{
		int* arr = new int[n];
		srand((int)time(NULL));

		if (arr == NULL || rangeL > rangeR)
		{
			std::cout << "数组生成失败！" << std::endl;
			exit(0);
		}

		clock_t begin = clock();

		if (swapTimes == UNORDERED_ARRAY)
		{
			for (int i = 0; i < n; i++)
			{
				arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
			}
		}
		else
		{
			// 先生成有序的数组，然后再进行交换，使其变成几乎有序
			for (int i = 0; i < n; i++)
			{
				arr[i] = i + 1;
			}
			for (int i = 0; i < swapTimes; i++)
			{
				int x = rand() % n;
				int y = rand() % n;

				int temp = arr[x];
				arr[x] = arr[y];
				arr[y] = temp;
			}
		}

		clock_t end = clock();

		double makeTime = (end - begin) / 1000.0;

		if (n < 10000)
		{
			std::cout << "[ " << n << "个元素的数组生成耗时 : " << makeTime << " 秒 ";
		}
		else if (n >= 10000 && n < 100000000)
		{
			std::cout << "[ " << (n / 10000) << "万个元素的数组生成耗时 : " << makeTime << " 秒 ";
		}
		else // n >= 100000000
		{
			std::cout << "[ " << (n / 100000000) << "亿个元素的数组生成耗时 : " << makeTime << " 秒 ";
		}

		if (swapTimes == -1)
		{
			std::cout << "(完全无序) ]" << std::endl << std::endl;
		}
		else
		{
			std::cout << "(近乎有序) ]" << std::endl << std::endl;
		}
		
		return arr;
	}
	//==========================================================================

	// 判断是否排序成功，对于越界或者元素吞并的情况有 bug
	//==========================================================================
	template<typename T>
	bool isSorted(T arr[], int n)
	{
		for (int i = 1; i < n; i++)
		{
			if (arr[i - 1] > arr[i] || arr[i-1] < -10000 || arr[i] < -10000)
			{
				return false;
			}
		}

		return true;
	}
	//==========================================================================

	// 根据一个数组复制出另一个一模一样的数组
	//==========================================================================
	template<typename T>
	T* copyArray(T arr[], int n)
	{
		T* arr2 = new T[n];
		memcpy(arr2, arr, n * sizeof(T));

		return arr2;
	}
	//==========================================================================

	// 测试一个排序算法执行的时间
	//==========================================================================
	template<typename T>
	void testSort(std::string sortName, void(*sortFuction)(T[], int), T arr[], int n)
	{
		clock_t begin = clock();
		sortFuction(arr, n);
		clock_t end = clock();

		if (isSorted(arr, n) == false)
		{
			std::cout << "==> " << sortName << " : 数组排序失败！" << std::endl;
		}
		else
		{
			double sortTime = (end - begin) / 1000.0; // 转化为秒
			std::cout << "==> " << sortName << " : " << sortTime << " 秒" << std::endl;
		}
	}
	//==========================================================================

	// 冒泡排序（o(n^2)时间复杂度）
	//==========================================================================
	template<typename T>
	void bubbleSort(T arr[], int n)
	{
		for (int i = 0; i < n - 1; i++)
		{
			bool ifBreak = true;
			for (int j = 0; j < n - 1 - i; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					ifBreak = false;
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}

			// 进行优化，如果在一次循环中一次交换都没发生，则数组已经排好序，可以break
			if (ifBreak)
			{
				break;
			}
		}
	}
	//==========================================================================

	// 选择排序（o(n^2)时间复杂度）
	//==========================================================================
	template<typename T>
	void selectionSort(T arr[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < n; j++)
			{
				if (arr[minIndex] > arr[j])
				{
					minIndex = j;
				}
			}

			T temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
	//==========================================================================

	// 插入排序（小于等于o(n^2)时间复杂度，对于几乎有序的数组效率极高）
	template<typename T>
	void insertionSort(T arr[], int n)
	{
		for (int i = 1; i < n; i++)
		{
			T temp = arr[i];
			int j;
			for (j = i; j > 0; j--)
			{
				if (temp < arr[j - 1])
				{
					arr[j] = arr[j - 1];
				}
				else
				{
					//arr[j] = temp; // 在这里赋值效率不稳定甚至会降低，为什么？
					break;
				}
			}
			arr[j] = temp;
		}
	}

	// 希尔排序（内部是交换排序，o(n^1.5)时间复杂度左右，能接近o(nlogn)）
	//==========================================================================
	template<typename T>
	void shell_Sort(T arr[], int n)
	{
		for (int gap = n >> 2; gap >= 1; gap /= 2)
		{
			for (int i = gap; i < n; i++)
			{
				for (int j = i - gap; j >= 0; j -= gap)
				{
					if (arr[j] > arr[j + gap])
					{
						T temp = arr[j];
						arr[j] = arr[j + gap];
						arr[j + gap] = temp;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	//==========================================================================

	// 希尔排序（内部是插入排序，o(n^1.5)时间复杂度左右，能接近o(nlogn)）
	//==========================================================================
	template<typename T>
	void shellSort(T arr[], int n)
	{
		for (int gap = n / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < n; i++)
			{
				// 每个元素与自己组内的数据进行直接插入排序
				if (arr[i] < arr[i - gap])
				{
					T temp = arr[i];
					int k = i - gap;
					do
					{
						arr[k + gap] = arr[k];
						k -= gap;
					} while (k >= 0 && arr[k] > temp);

					arr[k + gap] = temp;
				}
			}
		}
	}
	
	//==========================================================================


	// 自顶向下递归的归并排序（o(nlogn)时间复杂度）
	//==========================================================================
	template<typename T>
	void recursiveMergeSort(T arr[], int n)
	{
		// 先创建一个临时空间，避免下面递归时重复创建
		T* temp = new T[n];
		subdivison(arr, temp, 0, n-1);
		delete[] temp;
	}

	// 归并排序中细分数组的函数
	template<typename T>
	void subdivison(T arr[], T temp[], int L, int R)
	{
		// 当 L == R 就没必要细分了，因为此时就只有一个元素
		if (L >= R)
		{
			return;
		}

		// L + R 有可能数据溢出, 建议用 int m = (l & r) + ((l ^ r) >> 1); 
		//int middle = (L + R) / 2;
		int middle = L + (R-L) / 2; // 避免数据溢出

		// 分别对左右两边进行排序
		subdivison(arr, temp, L, middle);
		subdivison(arr, temp, middle+1, R);

		if (arr[middle] > arr[middle+1])
		{
			merge(arr, temp, L, middle, R);
		}
	}

	// 归并排序中合并数组的函数
	template<typename T>
	void merge(T arr[], T temp[], int L, int middle, int R)
	{
		for (int i = L; i <= R; i++)
		{
			temp[i-L] = arr[i];
		}

		int i = L, j = middle + 1, index = L;
		while (i <= middle && j <= R)
		{
			if (temp[i-L] < temp[j-L])
			{
				arr[index] = temp[i-L];
				i++;
				index++;
			}
			else
			{
				arr[index] = temp[j-L];
				j++;
				index++;
			}
		}

		// 如果执行完上层循环后 i 还没有到 middle 的位置，说明这些数比较大而没有放入数组，要自行操作
		while (i <= middle)
		{
			arr[index] = temp[i-L];
			i++;
			index++;
		}

		// 如果执行完上层循环后 j 还没有到 R 的位置，说明这些数比较大而没有放入数组，要自行操作
		while (j <= R)
		{
			arr[index] = temp[j-L];
			j++;
			index++;
		}
	}
	//==========================================================================

	// 自底向上的归并排序（o(nlogn)时间复杂度）
	//==========================================================================
	template<typename T>
	void loopMergeSort(T arr[], int n)
	{
		T* temp = new T[n];
		int R = 0;
		for (int group = 1; group <= n; group += group)
		{
			for (int i = 0; i + group < n; i += (group * 2))
			{
				if (arr[i + group - 1] > arr[i + group])
				{
					R = ((i + group*2 - 1 > n - 1) ? (n - 1) : (i + group * 2 - 1));
					merge(arr, temp, i, i + group -1, R);
				}
			}
		}

		delete[] temp;
	}
	//==========================================================================

	// 双路快速排序（大于等于 o(nlogn) 时间复杂度）
	//==========================================================================
	template<typename T>
	void quickSort2ways(T arr[], int n)
	{
		srand((unsigned int)time(NULL));
		quick2ways(arr, 0, n - 1);
	}

	template<typename T>
	void quick2ways(T arr[], int L, int R)
	{
		if (L >= R)
		{
			return;
		}

		int division = partition(arr, L, R);

		quick2ways(arr, L, division - 1);
		quick2ways(arr, division + 1, R);
	}

	// 双路快速排序细分元素的函数
	template<typename T>
	int partition(T arr[], int L, int R)
	{
		T temp = 0;

		// 为了降低快速排序退化到 o(n^2) 时间复杂度的概率
		int index = rand() % (R - L + 1) + L;
		temp = arr[index];
		arr[index] = arr[L];
		arr[L] = temp;

		int Lindex = L + 1;
		int Rindex = R;

		while (true)
		{
			while (Lindex <= R && arr[Lindex] < arr[L])
			{
				Lindex++;
			}

			while (Rindex >= L + 1 && arr[Rindex] > arr[L])
			{
				Rindex--;
			}

			// 如果一轮过去满足了这个条件，则说明已经被分好了，可以break
			if (Lindex > Rindex)
			{
				break;
			}

			temp = arr[Rindex];
			arr[Rindex] = arr[Lindex];
			arr[Lindex] = temp;

			Lindex++;
			Rindex--;
		}

		temp = arr[Rindex];
		arr[Rindex] = arr[L];
		arr[L] = temp;

		return Rindex;
	}
	//==========================================================================

	// 三路快速排序（大于等于 o(nlogn) 时间复杂度，对有大量元素重复的时候效率极高）
	//==========================================================================
	template<typename T>
	void quickSort3ways(T arr[], int n)
	{
		srand((unsigned int)time(NULL));
		quick3ways(arr, 0, n - 1);
	}

	// 三路快速排序的partition写进了下面细分的函数中，因为partition要返回两个值
	template<typename T>
	void quick3ways(T arr[], int L, int R)
	{
		if (L >= R)
		{
			return;
		}

		// 为了降低快速排序退化为（o(n^2)）时间复杂度的概率
		int index = rand() % (R - L + 1) + L;
		T temp = arr[index];
		arr[index] = arr[L];
		arr[L] = temp;

		index = L + 1;
		// 小于中轴的终点
		int Lindex = L;

		// 大于中轴的起点
		int Rindex = R + 1;

		while (index < Rindex)
		{
			if (arr[index] < arr[L])
			{
				temp = arr[index];
				arr[index] = arr[Lindex + 1];
				arr[Lindex + 1] = temp;

				Lindex++;
				index++;
			}
			else if (arr[index] > arr[L])
			{
				temp = arr[index];
				arr[index] = arr[Rindex - 1];
				arr[Rindex - 1] = temp;

				Rindex--;
			}
			else // arr[index] == arr[L]
			{	
				index++;		
			}
		}

		// 将中轴归中
		temp = arr[L];
		arr[L] = arr[Lindex];
		arr[Lindex] = temp;

		Lindex--;

		quick3ways(arr, L, Lindex);
		quick3ways(arr, Rindex, R);
	}
	//==========================================================================

	// 堆排序（o(nlogn)时间复杂度）
	//==========================================================================
	template<typename T>
	void heapSort(T arr[], int n)
	{
		int i = 0;
		T temp = 0;

		// 将这个数组变为最大堆
		for (i = (n - 1 - 1) / 2; i >= 0; i--)
		{
			shiftDown(arr, n, i);
		}

		// 将最大值移动到未排序数组的尾部
		for (i = n - 1; i > 0; i--)
		{
			temp = arr[i];
			arr[i] = arr[0];
			arr[0] = temp;

			shiftDown(arr, i, 0);
		}
	}

	// 堆排序要用到的 shiftDown 操作
	template<typename T>
	void shiftDown(T arr[], int count, int index)
	{
		int leftChildIndex = index * 2 + 1;

		// 有左边的孩子才进行交换
		while (leftChildIndex < count)
		{
			int childMaxIndex = leftChildIndex;

			// 检查有没有右边的儿子，以及看看两个儿子谁大
			if (leftChildIndex + 1 < count)
			{
				if (arr[leftChildIndex] < arr[leftChildIndex + 1])
				{
					childMaxIndex += 1;
				}
			}

			if (arr[childMaxIndex] > arr[index])
			{
				T temp = arr[childMaxIndex];
				arr[childMaxIndex] = arr[index];
				arr[index] = temp;

				index = childMaxIndex;
				leftChildIndex = index * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	//==========================================================================
}

