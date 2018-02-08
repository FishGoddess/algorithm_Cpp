#pragma once
#include <queue>

/**
数组工具类，主要是常用的排序函数
作者：水不要鱼
*/
class SortTools
{
public:
	// 双路快速排序(未经优化)
	static void quickSort(int num[], int n)
	{
		quickSort(num, 0, n - 1);
	}

	// 从底向上进行合并的归并排序
	static void mergeSort(int num[], int n)
	{
		int* temp = new int[n]; // 归并需要的辅助空间
		int right = 0;

		for (int group = 1; group <= n; group += group)
		{
			for (int i = 0; i + group < n; i += (group * 2))
			{
				// 一次优化，只有当左区间的最后一个数大于右区间的第一个数才需要合并
				if (num[i + group - 1] > num[i + group])
				{
					right = ((i + group * 2 - 1 > n - 1) ? (n - 1) : (i + group * 2 - 1));
					merge(num, temp, i, i + group - 1, right);
				}
			}
		}

		delete[] temp;
	}

	// 堆排序
	static void heapSort(int num[], int n)
	{
		// 从数组尾部的父亲位置开始向前建堆
		for (int i = (n - 1 - 1) / 2; i >= 0; i--)
		{
			buildHeap(num, i, n);
		}

		// 不断从堆顶取最大值放到数组尾部，同时不断维护堆
		for (int i = n - 1; i >= 0; i--)
		{
			int temp = num[i];
			num[i] = num[0];
			num[0] = temp;

			// 由于最大值已经取走，此时数组的开头元素不一定是符合堆顶的值，所以需要重新创堆
			buildHeap(num, 0, i);
		}
	}

	/**
	下面第一版的时间复杂度是 o(r * d * n)，第二版的是 o(d * d * n)，通常情况下 d > r，所以第一版的时间复杂度
	其实是更低的，只是第一版的操作也会比第二版的多，可能起步会慢点，但是数据相对集中的时候对第一版是非常有利的，
	这个时候第一版的效率更高一点，不过平均起来还是第二版的性能会好一点，也就是一点。。。
	*/

	// 基数排序(我自己乱写的第一版，过程很繁琐，效率应该不高)
	static void radixSort2(int num[], int n)
	{
		int* temp = new int[n]; // 临时存放空间

								// 遍历看看数组数据中最高位是多少位，决定下面的执行次数
		int maxBit = 1;
		for (int i = 0, max = 10; i < n; i++)
		{
			while (num[i] >= max)
			{
				maxBit++;
				max *= 10;
			}
		}

		// 根据最高位统计每种位数的个数
		int* bits = new int[maxBit + 1];
		for (int i = 0; i < maxBit + 1; i++)
		{
			bits[i] = 0; // 数组清零
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

	// 基数排序(严格根据定义的第二版)
	static void radixSort(int num[], int n)
	{
		//int* temp = new int[n]; // 临时空间
		std::queue<int>* queues = new std::queue<int>[10]; // 存储每一位的个数

														   // 找到这堆数据最高位是几位
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

		// 根据最高位来执行次数
		for (int i = 1, radix = 1; i <= maxBit; i++, radix *= 10)
		{
			// 根据此时的基数来决定这个元素该去哪
			for (int j = 0; j < n; j++)
			{
				int k = ((num[j] / radix) % 10);
				queues[k].push(num[j]);
			}

			// 放完之后就可以按顺序从队列里取出来
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

			// 将临时空间的数据复制回原数组
			//for (int j = 0; j < n; j++)
			//{
			//	num[j] = temp[j];
			//}
		}

		//delete[] temp;
		delete[] queues;
	}

	// 只可以排非负数，无聊写着玩的。。。
	static void fishSort(int nums[], int n)
	{
		// 找到数组中的最大值
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
	// 快速排序中把一个区间划分为三部分的函数
	static int partition(int num[], int left, int right)
	{
		int mid = num[left];

		// 1 6 2 5
		while (right > left)
		{
			while (right > left && num[right] >= mid)
			{
				right--; // 从右边开始一直找，找到比中点小的数，将它放在左边
			}
			if (right > left)
			{
				num[left++] = num[right];
			}

			while (right > left && num[left] < mid)
			{
				left++; // 从左边开始一直找，找到大于等于中点的数，将它放在右边
			}
			if (right > left)
			{
				num[right--] = num[left];
			}
		}

		num[left] = mid;

		return left;
	}

	// 快速排序递归要用到
	static void quickSort(int num[], int left, int right)
	{
		if (right > left)
		{
			int mid = partition(num, left, right);

			quickSort(num, left, mid - 1);
			quickSort(num, mid + 1, right);
		}
	}

	// 归并排序要用到的合并函数
	static void merge(int num[], int temp[], int left, int mid, int right)
	{
		// 在辅助空间上进行合并
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

		// 合并完将结果写回原数组
		index = 0;
		while (index < (right - left + 1))
		{
			num[left + index] = temp[index];
			index++;
		}
	}

	// 堆排序需要用到的建堆
	static void buildHeap(int num[], int parentIndex, int n)
	{
		// 有左孩子才进行建堆操作
		while (parentIndex * 2 + 1 < n)
		{
			int maxChildIndex = parentIndex * 2 + 1;

			// 判断是否有右孩子，有的话就比较左右孩子谁大
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

				// 将父节点转向最大孩子的节点，因为这个位置的值变了，需要进一步判断堆顶
				parentIndex = maxChildIndex;
			}
			else
			{
				break;
			}
		}
	}

	// 基数排序要用到的子排序(我自己乱写的第一版，过程很繁琐，效率应该不高)
	static void radixSubSort(int num[], int temp[], int n, int maxBit)
	{
		// 从个位开始，一直执行到最高位
		for (int i = 1, currentbit = 1; i <= maxBit; i++)
		{
			int bits[10] = { 0 }; // 记录每位数有多少个

								  // 统计每位数的个数
			for (int j = 0; j < n; j++)
			{
				int k = ((num[j] / currentbit) % 10);
				bits[k]++;
			}

			// 统计每位数有多少个，和前面有几个数
			for (int j = 1; j < 10; j++)
			{
				bits[j] = bits[j] + bits[j - 1];
			}

			// 根据统计结果填充临时空间
			for (int j = n - 1; j >= 0; j--)
			{
				int k = ((num[j] / currentbit) % 10);
				temp[bits[k] - 1] = num[j];
				bits[k]--;
			}

			// 将临时空间复制回原数组
			for (int j = 0; j < n; j++)
			{
				num[j] = temp[j];
			}

			currentbit *= 10;
		}
	}
};