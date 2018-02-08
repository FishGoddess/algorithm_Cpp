#pragma once
#include <queue>

/**
���鹤���࣬��Ҫ�ǳ��õ�������
���ߣ�ˮ��Ҫ��
*/
class SortTools
{
public:
	// ˫·��������(δ���Ż�)
	static void quickSort(int num[], int n)
	{
		quickSort(num, 0, n - 1);
	}

	// �ӵ����Ͻ��кϲ��Ĺ鲢����
	static void mergeSort(int num[], int n)
	{
		int* temp = new int[n]; // �鲢��Ҫ�ĸ����ռ�
		int right = 0;

		for (int group = 1; group <= n; group += group)
		{
			for (int i = 0; i + group < n; i += (group * 2))
			{
				// һ���Ż���ֻ�е�����������һ��������������ĵ�һ��������Ҫ�ϲ�
				if (num[i + group - 1] > num[i + group])
				{
					right = ((i + group * 2 - 1 > n - 1) ? (n - 1) : (i + group * 2 - 1));
					merge(num, temp, i, i + group - 1, right);
				}
			}
		}

		delete[] temp;
	}

	// ������
	static void heapSort(int num[], int n)
	{
		// ������β���ĸ���λ�ÿ�ʼ��ǰ����
		for (int i = (n - 1 - 1) / 2; i >= 0; i--)
		{
			buildHeap(num, i, n);
		}

		// ���ϴӶѶ�ȡ���ֵ�ŵ�����β����ͬʱ����ά����
		for (int i = n - 1; i >= 0; i--)
		{
			int temp = num[i];
			num[i] = num[0];
			num[0] = temp;

			// �������ֵ�Ѿ�ȡ�ߣ���ʱ����Ŀ�ͷԪ�ز�һ���Ƿ��϶Ѷ���ֵ��������Ҫ���´���
			buildHeap(num, 0, i);
		}
	}

	/**
	�����һ���ʱ�临�Ӷ��� o(r * d * n)���ڶ������ o(d * d * n)��ͨ������� d > r�����Ե�һ���ʱ�临�Ӷ�
	��ʵ�Ǹ��͵ģ�ֻ�ǵ�һ��Ĳ���Ҳ��ȵڶ���Ķ࣬�����𲽻����㣬����������Լ��е�ʱ��Ե�һ���Ƿǳ������ģ�
	���ʱ���һ���Ч�ʸ���һ�㣬����ƽ���������ǵڶ�������ܻ��һ�㣬Ҳ����һ�㡣����
	*/

	// ��������(���Լ���д�ĵ�һ�棬���̺ܷ�����Ч��Ӧ�ò���)
	static void radixSort2(int num[], int n)
	{
		int* temp = new int[n]; // ��ʱ��ſռ�

								// ���������������������λ�Ƕ���λ�����������ִ�д���
		int maxBit = 1;
		for (int i = 0, max = 10; i < n; i++)
		{
			while (num[i] >= max)
			{
				maxBit++;
				max *= 10;
			}
		}

		// �������λͳ��ÿ��λ���ĸ���
		int* bits = new int[maxBit + 1];
		for (int i = 0; i < maxBit + 1; i++)
		{
			bits[i] = 0; // ��������
		}

		for (int i = 0; i < n; i++)
		{
			int tem = num[i];
			int bit = (tem == 0 ? 1 : 0);
			while (tem != 0)
			{
				tem /= 10;
				bit++;
			}

			bits[bit]++;
		}

		int* temp2 = new int[maxBit + 1];
		for (int i = 0; i < maxBit + 1; i++)
		{
			temp2[i] = bits[i];
		}

		for (int i = 2; i <= maxBit; i++)
		{
			bits[i] = bits[i] + bits[i - 1];
		}

		for (int i = 0; i < n; i++)
		{
			int tem = num[i];
			int bit = (tem == 0 ? 1 : 0);
			while (tem != 0)
			{
				tem /= 10;
				bit++;
			}
			temp[bits[bit - 1]++] = num[i];
		}

		for (int i = 0; i < n; i++)
		{
			num[i] = temp[i];
		}

		for (int i = 1; i <= maxBit; i++)
		{
			if (temp2[i] != 0 && temp2[i] != 1)
			{
				//printf("%d %d %d %d\n", num + temp2[i - 1], temp + temp2[i - 1], temp2[i], i);
				radixSubSort(num + temp2[i - 1], temp + temp2[i - 1], temp2[i], i);
			}
		}

		delete[] bits;
		delete[] temp2;
		delete[] temp;
	}

	// ��������(�ϸ���ݶ���ĵڶ���)
	static void radixSort(int num[], int n)
	{
		//int* temp = new int[n]; // ��ʱ�ռ�
		std::queue<int>* queues = new std::queue<int>[10]; // �洢ÿһλ�ĸ���

														   // �ҵ�����������λ�Ǽ�λ
		int maxBit = 1;
		int max = 10;
		for (int i = 0; i < n; i++)
		{
			while (num[i] >= max)
			{
				maxBit++;
				max *= 10;
			}
		}

		// �������λ��ִ�д���
		for (int i = 1, radix = 1; i <= maxBit; i++, radix *= 10)
		{
			// ���ݴ�ʱ�Ļ������������Ԫ�ظ�ȥ��
			for (int j = 0; j < n; j++)
			{
				int k = ((num[j] / radix) % 10);
				queues[k].push(num[j]);
			}

			// ����֮��Ϳ��԰�˳��Ӷ�����ȡ����
			for (int j = 0, index = 0; j < n; j++)
			{
				while (queues[index].size() == 0)
				{
					index++;
				}

				//temp[j] = queues[index].front();
				num[j] = queues[index].front();
				queues[index].pop();
			}

			// ����ʱ�ռ�����ݸ��ƻ�ԭ����
			//for (int j = 0; j < n; j++)
			//{
			//	num[j] = temp[j];
			//}
		}

		//delete[] temp;
		delete[] queues;
	}

	// ֻ�����ŷǸ���������д����ġ�����
	static void fishSort(int nums[], int n)
	{
		// �ҵ������е����ֵ
		int max = nums[0];
		for (int i = 1; i < n; i++)
		{
			if (max < nums[i])
			{
				max = nums[i];
			}
		}

		max += 1;

		printf("%d\n", max);

		int* temp = new int[max];
		for (int i = 0; i < max; i++)
		{
			temp[i] = 0;
		}

		for (int i = 0; i < n; i++)
		{
			temp[nums[i]]++;
		}

		for (int i = 0, index = 0; i < max; i++)
		{
			while (temp[i])
			{
				nums[index] = i;

				index++;
				temp[i]--;
			}
		}

		delete[] temp;
	}
private:
	// ���������а�һ�����仮��Ϊ�����ֵĺ���
	static int partition(int num[], int left, int right)
	{
		int mid = num[left];

		// 1 6 2 5
		while (right > left)
		{
			while (right > left && num[right] >= mid)
			{
				right--; // ���ұ߿�ʼһֱ�ң��ҵ����е�С�����������������
			}
			if (right > left)
			{
				num[left++] = num[right];
			}

			while (right > left && num[left] < mid)
			{
				left++; // ����߿�ʼһֱ�ң��ҵ����ڵ����е���������������ұ�
			}
			if (right > left)
			{
				num[right--] = num[left];
			}
		}

		num[left] = mid;

		return left;
	}

	// ��������ݹ�Ҫ�õ�
	static void quickSort(int num[], int left, int right)
	{
		if (right > left)
		{
			int mid = partition(num, left, right);

			quickSort(num, left, mid - 1);
			quickSort(num, mid + 1, right);
		}
	}

	// �鲢����Ҫ�õ��ĺϲ�����
	static void merge(int num[], int temp[], int left, int mid, int right)
	{
		// �ڸ����ռ��Ͻ��кϲ�
		int index = 0;
		int i = left;
		int j = mid + 1;

		while (i <= mid && j <= right)
		{
			if (num[i] > num[j])
			{
				temp[index++] = num[j++];
			}
			else // num[i] <= num[j]
			{
				temp[index++] = num[i++];
			}
		}

		while (i <= mid)
		{
			temp[index++] = num[i++];
		}

		while (j <= right)
		{
			temp[index++] = num[j++];
		}

		// �ϲ��꽫���д��ԭ����
		index = 0;
		while (index < (right - left + 1))
		{
			num[left + index] = temp[index];
			index++;
		}
	}

	// ��������Ҫ�õ��Ľ���
	static void buildHeap(int num[], int parentIndex, int n)
	{
		// �����ӲŽ��н��Ѳ���
		while (parentIndex * 2 + 1 < n)
		{
			int maxChildIndex = parentIndex * 2 + 1;

			// �ж��Ƿ����Һ��ӣ��еĻ��ͱȽ����Һ���˭��
			if (maxChildIndex + 1 < n)
			{
				if (num[maxChildIndex] < num[maxChildIndex + 1])
				{
					maxChildIndex += 1;
				}
			}

			if (num[parentIndex] < num[maxChildIndex])
			{
				int temp = num[parentIndex];
				num[parentIndex] = num[maxChildIndex];
				num[maxChildIndex] = temp;

				// �����ڵ�ת������ӵĽڵ㣬��Ϊ���λ�õ�ֵ���ˣ���Ҫ��һ���ж϶Ѷ�
				parentIndex = maxChildIndex;
			}
			else
			{
				break;
			}
		}
	}

	// ��������Ҫ�õ���������(���Լ���д�ĵ�һ�棬���̺ܷ�����Ч��Ӧ�ò���)
	static void radixSubSort(int num[], int temp[], int n, int maxBit)
	{
		// �Ӹ�λ��ʼ��һֱִ�е����λ
		for (int i = 1, currentbit = 1; i <= maxBit; i++)
		{
			int bits[10] = { 0 }; // ��¼ÿλ���ж��ٸ�

								  // ͳ��ÿλ���ĸ���
			for (int j = 0; j < n; j++)
			{
				int k = ((num[j] / currentbit) % 10);
				bits[k]++;
			}

			// ͳ��ÿλ���ж��ٸ�����ǰ���м�����
			for (int j = 1; j < 10; j++)
			{
				bits[j] = bits[j] + bits[j - 1];
			}

			// ����ͳ�ƽ�������ʱ�ռ�
			for (int j = n - 1; j >= 0; j--)
			{
				int k = ((num[j] / currentbit) % 10);
				temp[bits[k] - 1] = num[j];
				bits[k]--;
			}

			// ����ʱ�ռ临�ƻ�ԭ����
			for (int j = 0; j < n; j++)
			{
				num[j] = temp[j];
			}

			currentbit *= 10;
		}
	}
};