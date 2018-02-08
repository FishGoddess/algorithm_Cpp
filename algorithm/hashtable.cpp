#include <stdio.h>

// ���׹�ϣ����
class Hashtable
{
private:
	int* keys; // ��� key ��˳��洢�ռ�
	int opacity; // ��ϣ����ܿռ�
	int overflowElementCount; // �����������Ԫ�ظ���
	static const int HASH_OPACITY = 13; // ǰ��һ����ɢ�пռ�

	// ��ϣ��� key ɢ�к���
	int H(int key)
	{
		return (key % HASH_OPACITY);
	}

public:
	// �� opacity ����ʼ���ռ�
	Hashtable(int opacity)
	{
		if (opacity <= HASH_OPACITY)
		{
			opacity = HASH_OPACITY * 2; // ��ֹ����ռ�С��������������ֵ
		}

		this->opacity = opacity;
		keys = new int[opacity];
		for (int i = 0; i < opacity; i++)
		{
			keys[i] = -1; // ��ʼ���ռ䣬-1 ��ʾû��Ԫ��
		}

		overflowElementCount = 0;
	}

	~Hashtable()
	{
		delete[] keys;
		opacity = 0;
		overflowElementCount = 0;
	}

	// ����һ���¼�ֵ
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
			return address; // ����ɢ��������
		}

		for (int i = HASH_OPACITY; i < HASH_OPACITY + overflowElementCount; i++)
		{
			if (keys[i] == key)
			{
				return i; // Ȼ�����ڹ����������
			}
		}

		insert(key); // û�ҵ��Ͳ����¼�ֵ������ -1
		return -1;
	}

	// �����õĴ�ӡ����
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

