#pragma once
#include <iostream>

// ����һ�����鼯��Ч��
template<typename T>
void testUnionFind(T uf, char* name, int n)
{
	// ��������
	srand((unsigned int)time(NULL));
	double begin = clock();

	// ����ϲ�һЩԪ�أ����Ժ�ʱ
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

	std::cout << name << "����ʱ�� : " << (end - begin) / 1000.0 << " ��" << std::endl;
}


// �򻯵Ĳ��鼯��Ϊ��ѧϰԭ��д��
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

		// ��ʵ����Ĳ��鼯���ݾ��� ID ������±꣬�������Ԫ���Ǳ�ʾ���������ļ��ϱ�ţ���������ͬ������ͬһ�����ϵ�Ԫ��
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

	// ����ĳһ�����������ļ��ϱ��
	int find(int element)
	{
		// ����������±����������鼯��Ԫ�أ����Ա����ҵ�Ԫ��Ҫ���������±�Ĺ淶
		if (element < 0 || element >= count)
		{
			exit(1);
		}
		return ID[element];
	}

	// ������Ԫ�غϲ���ͬһ������
	void unionElement(int p, int q)
	{
		int pID = find(p);
		int qID = find(q);

		if (pID == qID)
		{
			return;
		}

		// ��������Ԫ�صļ��ϱ����Ϊһ������������Ԫ��һ�����ϵĶ���ͬ���ı��
		for (int i = 0; i < count; i++)
		{
			if (ID[i] == pID)
			{
				ID[i] = qID;
			}
		}
	}

	// �ж�����Ԫ���Ƿ�����������ͬһ�����ϣ�
	bool isConnected(int p, int q)
	{
		// ����������Ԫ�صļ��ϱ���Ƿ���ͬ����
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

		// parent �����±����������鼯��Ԫ�أ����������ݴ�������Ԫ�صĸ��ڵ㣨׼ȷ��˵����һ���Ľڵ㣩
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

	// ����ĳһ�����������ĸ��ڵ���
	int find(int element)
	{
		// ����������±����������鼯��Ԫ�أ����Ա����ҵ�Ԫ��Ҫ���������±�Ĺ淶
		if (element < 0 || element >= count)
		{
			exit(1);
		}
		
		// ���ǵ�һ��·��ѹ���ķ�ʽ����ʵ��Ч�ʸߣ�
		while (parent[element] != element)
		{
			// ·��ѹ����
			parent[element] = parent[parent[element]];
			element = parent[element];
		}

		return element;

		// ���ǵڶ���·��ѹ���ķ�ʽ��������Ч�ʸߣ�
		/*if (parent[element] != element)
		{
			parent[element] = find(parent[element]);
		}

		return parent[element];*/
	}

	// ������Ԫ�����ӵ�һ��
	void unionElement(int p, int q)
	{
		int pRoot = find(p);
		int qRoot = find(q);

		if (pRoot == qRoot)
		{
			return;
		}
		// ������һ��Ԫ�صĸ��ڵ����ӵ���һ��Ԫ�صĸ��ڵ㼴��
		// �Ż�ǰ��������ָ����ڵ㣩
		//parent[pRoot] = qRoot;

		// �Ż��󣺣����� size �������ж�ָ���ĸ����ڵ㣩
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

	// �ж�����Ԫ���Ƿ�����������ͬһ�����ϣ�
	bool isConnected(int p, int q)
	{
		// ����������Ԫ�صĸ�����Ƿ���ͬ����
		return (find(p) == find(q));
	}

private:
	int* parent;
	int* size; // Ϊ���ںϲ����ڵ�ʱ���Խ������ߣ��������������¼����
	int count;
};