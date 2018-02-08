#pragma once
#include <iostream>
#define FROM_BOTTOM true
#define FROM_TOP false

// 栈类
template<typename T>
class Stack
{
public:
	Stack(int size)
	{
		bottom = new T[size];
		top = bottom;
		count = 0;
		this->size = size;
	}

	~Stack()
	{
		delete[] bottom;
	}

	// 得到栈中的元素个数
	int getCount() const
	{
		return count;
	}

	// 栈是否为空
	bool isEmpty() const
	{
		return (getCount() == 0);
	}

	// 清空一个栈
	void clearStack()
	{
		memset(bottom, 0, size * sizeof(T));
		count = 0;
		top = bottom;
	}

	// 入栈
	void push(T e)
	{
		if (count == size)
		{
			T* temp = new T[size + size];
			memcpy(temp, bottom, size * sizeof(T));
			bottom = temp;
			top = &bottom[size];
			size += size;
			//std::cout << "栈空间已满！！" << std::endl;
			//return;
		}

		*top = e;
		top++;
		count++;
	}

	// 出栈
	T pop()
	{
		if (isEmpty())
		{
			std::cout << "这个栈空空如也！！" << std::endl;
			exit(1);
		}

		top--;
		count--;

		return *top;
	}

	// 遍历栈中的元素
	void traversal(bool isFromBottom = true)
	{
		if (isFromBottom)
		{
			for (int i = 0; i < count; i++)
			{
				std::cout << bottom[i] << "  ";
			}
			std::cout << std::endl;
		}
		else
		{
			for (int i = count - 1; i >= 0; i--)
			{
				std::cout << bottom[i] << "  ";
			}
			std::cout << std::endl;
		}
	}

private:
	T* bottom;
	T* top;
	int count;
	int size;

};


// 判断括号是否配对，目前只能判断 [], ()
void isMatching(Stack<char>* pStack, char str[])
{
	char ch = 0;
	bool flag = true;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '[' || str[i] == '(')
		{
			pStack->push(str[i]);
		}
		else if (str[i] == ')')
		{
			if (!pStack->isEmpty())
			{
				ch = pStack->pop();
				if (ch == '(')
				{
					continue;
				}
				else
				{
					flag = false;
					break;
				}
			}
			else
			{
				flag = false;
				break;
			}
		}
		else if (str[i] == ']')
		{
			if (!pStack->isEmpty())
			{
				ch = pStack->pop();
				if (ch == '[')
				{
					continue;
				}
				else
				{
					flag = false;
					break;
				}
			}
			else
			{
				flag = false;
				break;
			}
		}
	}

	if (flag && pStack->isEmpty())
	{
		std::cout << "MATCHING !!!" << std::endl;
	}
	else
	{
		std::cout << "NO MATCHING !!!" << std::endl;
	}

}