#pragma once
#include <iostream>
#include <string>

// 使用数组实现最大堆（完全二叉树）
template<typename T>
class MaxHeap
{
public:

	MaxHeap(int number = 1)
	{
		data = new T[number + 1];
		count = 0;
		size = number;
	}

	MaxHeap(T arr[], int n)
	{
		data = new T[n + 1];

		for (int i = 0; i < n; i++)
		{
			data[i + 1] = arr[i];
		}
		count = n;
		size = n;

		for (int i = count / 2; i >= 1; i--)
		{
			shiftDown(i);
		}
	}

	~MaxHeap()
	{
		delete[] data;
		data = NULL;
	}

	int getSize() const
	{
		return count;
	}

	bool isEmpty() const
	{
		return (count == 0);
	}

	// 将一个元素插入堆中
	void insert(T element)
	{
		if (size == count)
		{
			T* temp = new T[size * 2 + 1];
			size *= 2;
			if (temp == NULL)
			{
				std::cout << "堆空间已经存满！无法再插入数据！" << std::endl;
				exit(1);
			}
			memcpy(temp, data, sizeof(T) * (count + 1));

			delete[] data;
			data = temp;
		}

		count++;
		data[count] = element;

		// 让这个新加的元素满足最大堆的规则
		shiftUp(count);
	}

	// 将堆中最大值取出
	T pickMax()
	{
		if (count == 0)
		{
			cout << "这个堆很穷，啥也没有！" << endl;
			exit(1);
		}

		T max = data[1];
		data[1] = data[count--];

		shiftDown(1);

		return max;
	}

	void print()
	{
		testPrint();
		//printArray(data, count + 1);

		/*
		int i = 0;
		int floor = 0;
		while (count - (int)pow(2, i) > 0)
		{
		floor++;
		i++;
		}

		int index = 1;
		for (i = 1; i <= floor; i++)
		{
		int j = 0, k = 0;
		int spaceNumber = (int)pow(2, floor - i);
		int elementNumber = (int)pow(2, i - 1);

		for (j = 0; j < elementNumber; j++)
		{
		for (k = 0; k < spaceNumber; k++)
		{
		std::cout << ' ';
		}
		std::cout << data[index++];

		if (index > count)
		{
		break;
		}
		}

		std::cout << std::endl;
		std::cout << std::endl;
		}
		*/
	}



private:

	T* data;
	int count;
	int size;

	void shiftUp(int index)
	{
		int parentIndex = index / 2;
		while (index > 1 && data[index] > data[parentIndex])
		{
			T temp = data[index];
			data[index] = data[parentIndex];
			data[parentIndex] = temp;

			index /= 2;
			parentIndex /= 2;
		}
	}

	void shiftDown(int index)
	{
		int leftChildIndex = index * 2;

		// 有左边的孩子才进行交换
		while (leftChildIndex <= count)
		{
			int childMaxIndex = leftChildIndex;

			// 检查有没有右边的儿子，以及看看两个儿子谁大
			if (leftChildIndex + 1 <= count)
			{
				if (data[leftChildIndex] < data[leftChildIndex + 1])
				{
					childMaxIndex += 1;
				}
			}

			if (data[childMaxIndex] > data[index])
			{
				T temp = data[childMaxIndex];
				data[childMaxIndex] = data[index];
				data[index] = temp;

				index = childMaxIndex;
				leftChildIndex = index * 2;
			}
			else
			{
				break;
			}

		}
	}

	// 刘宇波大佬写的树的打印函数
	void testPrint()
	{
		if (getSize() >= 100) {
			std::cout << "Fancy print can only work for less than 100 int";
			return;
		}

		if (typeid(T) != typeid(int)) {
			std::cout << "Fancy print can only work for int item";
			return;
		}

		std::cout << "The Heap size is: " << getSize() << std::endl;
		std::cout << "data in heap: ";
		for (int i = 1; i <= getSize(); i++)
			std::cout << data[i] << " ";
		std::cout << std::endl;
		std::cout << std::endl;

		int n = getSize();
		int max_level = 0;
		int number_per_level = 1;
		while (n > 0) {
			max_level += 1;
			n -= number_per_level;
			number_per_level *= 2;
		}

		int max_level_number = int(pow(2, max_level - 1));
		int cur_tree_max_level_number = max_level_number;
		int index = 1;
		for (int level = 0; level < max_level; level++) {
			std::string line1 = std::string(max_level_number * 3 - 1, ' ');

			int cur_level_number = (count - int(pow(2, level)) + 1 <= int(pow(2, level))) ? count - int(pow(2, level)) + 1 : int(pow(2, level));
			bool isLeft = true;
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
				putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
				isLeft = !isLeft;
			}
			std::cout << line1 << std::endl;

			if (level == max_level - 1)
				break;

			std::string line2 = std::string(max_level_number * 3 - 1, ' ');
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
				putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
			std::cout << line2 << std::endl;

			cur_tree_max_level_number /= 2;
		}
	}

	// 刘宇波大佬写的树的打印
	void putNumberInLine(int num, std::string &line, int index_cur_level, int cur_tree_width, bool isLeft)
	{
		int sub_tree_width = (cur_tree_width - 1) / 2;
		int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
		if (offset + 1 >= line.size())
		{
			exit(1);
		}
		if (num >= 10) {
			line[offset + 0] = '0' + num / 10;
			line[offset + 1] = '0' + num % 10;
		}
		else {
			if (isLeft)
				line[offset + 0] = '0' + num;
			else
				line[offset + 1] = '0' + num;
		}
	}

	// 刘宇波大佬写的树的打印
	void putBranchInLine(std::string &line, int index_cur_level, int cur_tree_width)
	{
		int sub_tree_width = (cur_tree_width - 1) / 2;
		int sub_sub_tree_width = (sub_tree_width - 1) / 2;
		int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
		if (offset_left + 1 >= line.size())
		{
			exit(1);
		}
		int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
		if (offset_right >= line.size())
		{
			exit(1);
		}

		line[offset_left + 1] = '/';
		line[offset_right + 0] = '\\';
	}
};


// 使用数组实现索引最大堆（还未进行过测试）
template<typename T>
class IndexMaxHeap
{
public:

	IndexMaxHeap(int number = 1)
	{
		data = new T[number + 1];
		indexes = new int[number + 1];
		rev = new int[number + ];
		memset(rev, 0, sizeof(int)*(number + 1));
		
		count = 0;
		size = number;
	}

	~IndexMaxHeap()
	{
		delete[] data;
		data = NULL;

		delete[] indexes;
		indexes = NULL;

		delete[] rev;
		rev = NULL;
	}

	int getSize() const
	{
		return count;
	}

	bool isEmpty() const
	{
		return (count == 0);
	}

	// 将一个元素插入堆中
	void insert(int index, T element)
	{
		if (index < 0)
		{
			cout << "索引必须大于 0 ！！！" << endl;
			exit(1);
		}

		if (size == count)
		{
			T* temp = new T[size * 2 + 1];
			int* indexTemp = new int[size * 2 + 1];
			int* revTemp = new int[size * 2 + 1];

			size *= 2;
			if (temp == NULL || indexTemp == NULL || revTemp == NULL)
			{
				std::cout << "堆空间已经存满！无法再插入数据！" << std::endl;
				exit(1);
			}
			memcpy(temp, data, sizeof(T) * (count + 1));
			memcpy(indexTemp, indexes, sizeof(int) * (count + 1));
			memcpy(revTemp, rev, sizeof(int) * (count + 1));

			delete[] data;
			data = temp;

			delete[] indexes;
			indexes = indexTemp;

			delete[] rev;
			rev = revTemp;
		}

		count++;
		index += 1;
		indexes[count] = index;
		rev[index] = count;
		data[index] = element;

		// 让这个新加的元素满足最大堆的规则
		shiftUp(count);
	}

	// 将堆中最大值取出
	T pickMax()
	{
		if (count == 0)
		{
			cout << "这个堆很穷，啥也没有！" << endl;
			exit(1);
		}

		T max = data[indexes[1]];
		data[indexes[1]] = data[indexes[count--]];

		shiftDown(1);

		return max;
	}

	// 取得这个堆中最大值的索引
	int pickMaxIndex()
	{
		if (rev[index] == 0)
		{
			exit(1);
		}

		if (count == 0)
		{
			cout << "这个堆很穷，啥也没有！" << endl;
			exit(1);
		}

		int max = indexes[1] - 1;
		rev[indexes[1]] = 1;
		rev[indexes[count]] = 0;

		data[indexes[1]] = data[indexes[count--]];
		rev[indexes[1]] = 1;
		rev[indexes[count]] = 0;

		shiftDown(1);

		return max;
	}

	T getItem(int index) const
	{
		return data[index + 1];
	}

	// 更改某一个元素
	void updateItem(int index, T newItem)
	{
		if (rev[index] == 0)
		{
			exit(1);
		}

		data[index + 1] = newItem;

		/*for (int i = 1; i <= count; i++)
		{
			if (indexes[i] == index)
			{
				shiftUp(i);
				shiftDown(i);

				break;
			}
		}*/

		int j = rev[index];
		shiftUp(j);
		shiftDown(j);
	}

private:

	T* data;
	int* indexes; // 储存元素索引
	int* rev; // 储存索引在堆中的位置
	int count;
	int size;

	void shiftUp(int index)
	{
		int parentIndex = index / 2;
		while (index > 1 && data[indexes[index]] > data[indexes[parentIndex]])
		{
			int temp = indexes[index];
			indexes[index] = indexes[parentIndex];
			indexes[parentIndex] = temp;

			rev[indexes[index]] = index;
			rev[indexes[pareIndex]] = parentIndex;

			index /= 2;
			parentIndex /= 2;
		}
	}

	void shiftDown(int index)
	{
		int leftChildIndex = index * 2;

		// 有左边的孩子才进行交换
		while (leftChildIndex <= count)
		{
			int childMaxIndex = leftChildIndex;

			// 检查有没有右边的儿子，以及看看两个儿子谁大
			if (leftChildIndex + 1 <= count)
			{
				if (data[indexes[leftChildIndex]] < data[indexes[leftChildIndex + 1]])
				{
					childMaxIndex += 1;
				}
			}

			if (data[indexes[childMaxIndex]] > data[indexes[index]])
			{
				int temp = indexes[childMaxIndex];
				indexes[childMaxIndex] = indexes[index];
				indexes[index] = temp;

				rev[indexes[childMaxIndex]] = childMaxIndex;
				rev[indexes[index]] = index;

				index = childMaxIndex;
				leftChildIndex = index * 2;
			}
			else
			{
				break;
			}
		}
	}
};