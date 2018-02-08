#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#define UNORDERED_ARRAY -1

namespace ArrayFuctions
{
	// ��ӡ����ĺ�����֧�ֶ������͵�����
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

	// ����һ��ӵ�� n ��int����Ԫ�ص����飬Ĭ��������ģ����ҳ̶���swapTimes����Χ�� rangeL �� rangeR
	//==========================================================================
	int* generateRandomArray(int n, int rangeL, int rangeR, int swapTimes = UNORDERED_ARRAY)
	{
		int* arr = new int[n];
		srand((int)time(NULL));

		if (arr == NULL || rangeL > rangeR)
		{
			std::cout << "��������ʧ�ܣ�" << std::endl;
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
			// ��������������飬Ȼ���ٽ��н�����ʹ���ɼ�������
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
			std::cout << "[ " << n << "��Ԫ�ص��������ɺ�ʱ : " << makeTime << " �� ";
		}
		else if (n >= 10000 && n < 100000000)
		{
			std::cout << "[ " << (n / 10000) << "���Ԫ�ص��������ɺ�ʱ : " << makeTime << " �� ";
		}
		else // n >= 100000000
		{
			std::cout << "[ " << (n / 100000000) << "�ڸ�Ԫ�ص��������ɺ�ʱ : " << makeTime << " �� ";
		}

		if (swapTimes == -1)
		{
			std::cout << "(��ȫ����) ]" << std::endl << std::endl;
		}
		else
		{
			std::cout << "(��������) ]" << std::endl << std::endl;
		}
		
		return arr;
	}
	//==========================================================================

	// �ж��Ƿ�����ɹ�������Խ�����Ԫ���̲�������� bug
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

	// ����һ�����鸴�Ƴ���һ��һģһ��������
	//==========================================================================
	template<typename T>
	T* copyArray(T arr[], int n)
	{
		T* arr2 = new T[n];
		memcpy(arr2, arr, n * sizeof(T));

		return arr2;
	}
	//==========================================================================

	// ����һ�������㷨ִ�е�ʱ��
	//==========================================================================
	template<typename T>
	void testSort(std::string sortName, void(*sortFuction)(T[], int), T arr[], int n)
	{
		clock_t begin = clock();
		sortFuction(arr, n);
		clock_t end = clock();

		if (isSorted(arr, n) == false)
		{
			std::cout << "==> " << sortName << " : ��������ʧ�ܣ�" << std::endl;
		}
		else
		{
			double sortTime = (end - begin) / 1000.0; // ת��Ϊ��
			std::cout << "==> " << sortName << " : " << sortTime << " ��" << std::endl;
		}
	}
	//==========================================================================

	// ð������o(n^2)ʱ�临�Ӷȣ�
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

			// �����Ż��������һ��ѭ����һ�ν�����û�������������Ѿ��ź��򣬿���break
			if (ifBreak)
			{
				break;
			}
		}
	}
	//==========================================================================

	// ѡ������o(n^2)ʱ�临�Ӷȣ�
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

	// ��������С�ڵ���o(n^2)ʱ�临�Ӷȣ����ڼ������������Ч�ʼ��ߣ�
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
					//arr[j] = temp; // �����︳ֵЧ�ʲ��ȶ������ή�ͣ�Ϊʲô��
					break;
				}
			}
			arr[j] = temp;
		}
	}

	// ϣ�������ڲ��ǽ�������o(n^1.5)ʱ�临�Ӷ����ң��ܽӽ�o(nlogn)��
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

	// ϣ�������ڲ��ǲ�������o(n^1.5)ʱ�临�Ӷ����ң��ܽӽ�o(nlogn)��
	//==========================================================================
	template<typename T>
	void shellSort(T arr[], int n)
	{
		for (int gap = n / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < n; i++)
			{
				// ÿ��Ԫ�����Լ����ڵ����ݽ���ֱ�Ӳ�������
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


	// �Զ����µݹ�Ĺ鲢����o(nlogn)ʱ�临�Ӷȣ�
	//==========================================================================
	template<typename T>
	void recursiveMergeSort(T arr[], int n)
	{
		// �ȴ���һ����ʱ�ռ䣬��������ݹ�ʱ�ظ�����
		T* temp = new T[n];
		subdivison(arr, temp, 0, n-1);
		delete[] temp;
	}

	// �鲢������ϸ������ĺ���
	template<typename T>
	void subdivison(T arr[], T temp[], int L, int R)
	{
		// �� L == R ��û��Ҫϸ���ˣ���Ϊ��ʱ��ֻ��һ��Ԫ��
		if (L >= R)
		{
			return;
		}

		// L + R �п����������, ������ int m = (l & r) + ((l ^ r) >> 1); 
		//int middle = (L + R) / 2;
		int middle = L + (R-L) / 2; // �����������

		// �ֱ���������߽�������
		subdivison(arr, temp, L, middle);
		subdivison(arr, temp, middle+1, R);

		if (arr[middle] > arr[middle+1])
		{
			merge(arr, temp, L, middle, R);
		}
	}

	// �鲢�����кϲ�����ĺ���
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

		// ���ִ�����ϲ�ѭ���� i ��û�е� middle ��λ�ã�˵����Щ���Ƚϴ��û�з������飬Ҫ���в���
		while (i <= middle)
		{
			arr[index] = temp[i-L];
			i++;
			index++;
		}

		// ���ִ�����ϲ�ѭ���� j ��û�е� R ��λ�ã�˵����Щ���Ƚϴ��û�з������飬Ҫ���в���
		while (j <= R)
		{
			arr[index] = temp[j-L];
			j++;
			index++;
		}
	}
	//==========================================================================

	// �Ե����ϵĹ鲢����o(nlogn)ʱ�临�Ӷȣ�
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

	// ˫·�������򣨴��ڵ��� o(nlogn) ʱ�临�Ӷȣ�
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

	// ˫·��������ϸ��Ԫ�صĺ���
	template<typename T>
	int partition(T arr[], int L, int R)
	{
		T temp = 0;

		// Ϊ�˽��Ϳ��������˻��� o(n^2) ʱ�临�Ӷȵĸ���
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

			// ���һ�ֹ�ȥ�����������������˵���Ѿ����ֺ��ˣ�����break
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

	// ��·�������򣨴��ڵ��� o(nlogn) ʱ�临�Ӷȣ����д���Ԫ���ظ���ʱ��Ч�ʼ��ߣ�
	//==========================================================================
	template<typename T>
	void quickSort3ways(T arr[], int n)
	{
		srand((unsigned int)time(NULL));
		quick3ways(arr, 0, n - 1);
	}

	// ��·���������partitionд��������ϸ�ֵĺ����У���ΪpartitionҪ��������ֵ
	template<typename T>
	void quick3ways(T arr[], int L, int R)
	{
		if (L >= R)
		{
			return;
		}

		// Ϊ�˽��Ϳ��������˻�Ϊ��o(n^2)��ʱ�临�Ӷȵĸ���
		int index = rand() % (R - L + 1) + L;
		T temp = arr[index];
		arr[index] = arr[L];
		arr[L] = temp;

		index = L + 1;
		// С��������յ�
		int Lindex = L;

		// ������������
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

		// ���������
		temp = arr[L];
		arr[L] = arr[Lindex];
		arr[Lindex] = temp;

		Lindex--;

		quick3ways(arr, L, Lindex);
		quick3ways(arr, Rindex, R);
	}
	//==========================================================================

	// ������o(nlogn)ʱ�临�Ӷȣ�
	//==========================================================================
	template<typename T>
	void heapSort(T arr[], int n)
	{
		int i = 0;
		T temp = 0;

		// ����������Ϊ����
		for (i = (n - 1 - 1) / 2; i >= 0; i--)
		{
			shiftDown(arr, n, i);
		}

		// �����ֵ�ƶ���δ���������β��
		for (i = n - 1; i > 0; i--)
		{
			temp = arr[i];
			arr[i] = arr[0];
			arr[0] = temp;

			shiftDown(arr, i, 0);
		}
	}

	// ������Ҫ�õ��� shiftDown ����
	template<typename T>
	void shiftDown(T arr[], int count, int index)
	{
		int leftChildIndex = index * 2 + 1;

		// ����ߵĺ��ӲŽ��н���
		while (leftChildIndex < count)
		{
			int childMaxIndex = leftChildIndex;

			// �����û���ұߵĶ��ӣ��Լ�������������˭��
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

