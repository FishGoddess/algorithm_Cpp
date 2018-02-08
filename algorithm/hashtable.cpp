#include <stdio.h>

// 简易哈希表类
class Hashtable
{
private:
	int* keys; // 存放 key 的顺序存储空间
	int opacity; // 哈希表的总空间
	int overflowElementCount; // 公共溢出区的元素个数
	static const int HASH_OPACITY = 13; // 前面一部分散列空间

	// 哈希表的 key 散列函数
	int H(int key)
	{
		return (key % HASH_OPACITY);
	}

public:
	// 用 opacity 来初始化空间
	Hashtable(int opacity)
	{
		if (opacity <= HASH_OPACITY)
		{
			opacity = HASH_OPACITY * 2; // 防止传入空间小于正常工作的数值
		}

		this->opacity = opacity;
		keys = new int[opacity];
		for (int i = 0; i < opacity; i++)
		{
			keys[i] = -1; // 初始化空间，-1 表示没有元素
		}

		overflowElementCount = 0;
	}

	~Hashtable()
	{
		delete[] keys;
		opacity = 0;
		overflowElementCount = 0;
	}

	// 插入一个新键值
	void insert(int key)
	{
		int address = H(key);
		if (keys[address] == -1)
		{
			keys[address] = key;
		}
		else
		{
			keys[HASH_OPACITY + overflowElementCount] = key;
			overflowElementCount++;
		}
	}

	int getAddressByKey(int key)
	{
		int address = H(key);
		if (keys[address] == key)
		{
			return address; // 先在散列区域找
		}

		for (int i = HASH_OPACITY; i < HASH_OPACITY + overflowElementCount; i++)
		{
			if (keys[i] == key)
			{
				return i; // 然后再在公共溢出区找
			}
		}

		insert(key); // 没找到就插入新键值，返回 -1
		return -1;
	}

	// 测试用的打印数组
	/*void printTable()
	{
		for (int i = 0; i < opacity; i++)
		{
			printf("%d : %d\n", i, keys[i]);
		}
	}*/
};

int main()
{
	int keys[] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
	Hashtable table(22);

	for (int i = 0; i < 12; i++)
	{
		table.insert(keys[i]);
	}

	for (int i = 0; i < 12; i++)
	{
		int a = table.getAddressByKey(keys[i]);
		printf("%d : %d\n", a, keys[i]);
	}


	return 0;
}

