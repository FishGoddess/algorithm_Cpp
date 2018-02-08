#pragma once
#include <iostream>

// 测试一个并查集的效率
template<typename T>
void testUnionFind(T uf, char* name, int n)
{
	// 测试用例
	srand((unsigned int)time(NULL));
	double begin = clock();

	// 任意合并一些元素，测试耗时
	for (int i = 0; i < n; i++)
	{
		int a = rand() % n;
		int b = rand() % n;
		uf.unionElement(a, b);
	}

	for (int i = 0; i < n; i++)
	{
		int a = rand() % n;
		int b = rand() % n;
		uf.isConnected(a, b);
	}

	double end = clock();

	std::cout << name << "所用时间 : " << (end - begin) / 1000.0 << " 秒" << std::endl;
}


// 简化的并查集，为了学习原理写的
class easyUnionFind
{
public:
	easyUnionFind(int number)
	{
		ID = NULL;
		ID = new int[number];
		if (ID == NULL)
		{
			exit(1);
		}

		// 其实这里的并查集数据就是 ID 数组的下标，而数组的元素是表示数据所属的集合编号，如果编号相同，则是同一个集合的元素
		count = number;
		for (int i = 0; i < count; i++)
		{
			ID[i] = i;
		}
	}

	easyUnionFind(const easyUnionFind& temp)
	{
		ID = new int[temp.count];
		if (ID == NULL)
		{
			exit(1);
		}

		count = temp.count;
		memcpy(ID, temp.ID, sizeof(int) * count);
	}

	~easyUnionFind()
	{
		delete[] ID;
		ID = NULL;
	}

	// 查找某一个数据所属的集合编号
	int find(int element)
	{
		// 由于数组的下标就是这个并查集的元素，所以被查找的元素要符合数组下标的规范
		if (element < 0 || element >= count)
		{
			exit(1);
		}
		return ID[element];
	}

	// 将两个元素合并到同一个集合
	void unionElement(int p, int q)
	{
		int pID = find(p);
		int qID = find(q);

		if (pID == qID)
		{
			return;
		}

		// 将这两个元素的集合编号设为一样，和这两个元素一个集合的都是同样的编号
		for (int i = 0; i < count; i++)
		{
			if (ID[i] == pID)
			{
				ID[i] = qID;
			}
		}
	}

	// 判断两个元素是否相连（属于同一个集合）
	bool isConnected(int p, int q)
	{
		// 看看这两个元素的集合编号是否相同即可
		return (find(p) == find(q));
	}

private:
	int* ID;
	int count;
};


class UnionFind
{
public:
	UnionFind(int number)
	{
		parent = NULL;
		size = NULL;
		parent = new int[number];
		size = new int[number];
		if (parent == NULL || size == NULL)
		{
			exit(1);
		}

		// parent 数组下标就是这个并查集的元素，而数组数据存放着这个元素的根节点（准确的说是上一级的节点）
		count = number;
		for (int i = 0; i < count; i++)
		{
			parent[i] = i;
			size[i] = 1;
		}
	}

	UnionFind(const UnionFind& temp)
	{
		parent = new int[temp.count];
		size = new int[temp.count];
		if (parent == NULL || size == NULL)
		{
			exit(1);
		}
		
		count = temp.count;
		memcpy(parent, temp.parent, sizeof(int) * count);
		memcpy(size, temp.size, sizeof(int) * count);
	}

	~UnionFind()
	{
		delete[] parent;
		delete[] size;
		parent = NULL;
		size = NULL;
	}

	// 查找某一个数据所属的根节点编号
	int find(int element)
	{
		// 由于数组的下标就是这个并查集的元素，所以被查找的元素要符合数组下标的规范
		if (element < 0 || element >= count)
		{
			exit(1);
		}
		
		// 这是第一种路径压缩的方式：（实际效率高）
		while (parent[element] != element)
		{
			// 路径压缩：
			parent[element] = parent[parent[element]];
			element = parent[element];
		}

		return element;

		// 这是第二种路径压缩的方式：（理论效率高）
		/*if (parent[element] != element)
		{
			parent[element] = find(parent[element]);
		}

		return parent[element];*/
	}

	// 将两个元素连接到一起
	void unionElement(int p, int q)
	{
		int pRoot = find(p);
		int qRoot = find(q);

		if (pRoot == qRoot)
		{
			return;
		}
		// 将其中一个元素的根节点连接到另一个元素的根节点即可
		// 优化前：（随意指向根节点）
		//parent[pRoot] = qRoot;

		// 优化后：（根据 size 数组来判断指向哪个根节点）
		if (size[pRoot] < size[qRoot])
		{
			parent[pRoot] = qRoot;
		}
		else if (size[pRoot] > size[qRoot])
		{
			parent[qRoot] = pRoot;
		}
		else // size[pRoot] == size[qRoot]
		{
			parent[pRoot] = qRoot;
			size[qRoot] += 1;
		}
	}

	// 判断两个元素是否相连（属于同一个集合）
	bool isConnected(int p, int q)
	{
		// 看看这两个元素的根编号是否相同即可
		return (find(p) == find(q));
	}

private:
	int* parent;
	int* size; // 为了在合并根节点时可以降低树高，这个数组用来记录层数
	int count;
};