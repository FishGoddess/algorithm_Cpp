#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;

void sort_selection(int L[], int n, int &cn, int &sn)   // 简单选择排序
{ //************************************************
	int i = 0,j=0,minIndex = 0,temp = 0;
	for (i = 0; i < n; i++) 
	{
		minIndex = i;
		for (j = i + 1; j < n; j++) 
		{
			if (L[j] < L[minIndex]) 
			{
				minIndex = j;
			}
			cn++;
		}
		if (i != minIndex) 
		{
			temp = L[i];
			L[i] = L[minIndex];
			L[minIndex] = temp;
			sn += 3;
		}
	}
  //================================================
}

void sort_Shell(int L[], int n, int &cn, int &sn)   // 希尔排序 
{ //************************************************
	int gap, i, j;
	for (gap = n / 2; gap > 0; gap = gap / 2)//取希尔排序的增量，每次循环都变成原来的1/2；
	{
		for (i = gap; i < n; i++)
		{
			for (j = i - gap; j >= 0 && L[j] > L[j + gap]; j = j - gap)//让间隔为gap的元素互换，例如：v[1]与v[1+n],v[2]与v[2+n].....;
			{
				swap(L[j], L[j + gap]);
				sn+=3;
				cn++;
			}cn++;
		}
	}
  //================================================
}

int partition(int L[], int p1, int p2, int &cn, int &sn)   // 快速排序一趟分割, 返回分割点
{ //************************************************
	int temp = L[p1];
	sn++;
	//cn++;
	while (p1 < p2) 
	{
		while (p1 < p2&&L[p2]>temp)
		{
			p2--;cn++;
		}
		L[p1] = L[p2];
		sn ++;
		while (p1 < p2&&L[p1] <= temp)
		{
			p1++;cn++;
		}
		sn++;
		L[p2] = L[p1];
	}
	L[p1] = temp;
	sn++;
	return p1;


  //================================================
}

void sort_quick(int L[], int n, int &cn, int &sn)	// 快速排序（非递归）
{
	int stack[256], top = -1;
	int low, up, mid;
	stack[++top] = 0; stack[++top] = n - 1;
	while (top != -1)
	{
		up = stack[top--]; low = stack[top--];
		mid = partition(L, low, up, cn, sn);
		if (low<mid - 1)
		{
			stack[++top] = low; stack[++top] = mid - 1;
		}
		if (mid + 1<up)
		{
			stack[++top] = mid + 1; stack[++top] = up;
		}
	}
}

/*
void sort_quick(int L[],int s,int t,int &cn, int &sn)   // 快速排序（递归）
{ int m;
if(s<t)
{ m=partition(L,s,t,cn,sn);
sort_quick(L,s,m-1,cn,sn);
sort_quick(L,m+1,t,cn,sn);
}
}
*/

void heap_sift(int L[], int s, int t, int &cn, int &sn)   // 堆排序中的一次筛选 
{
	int i, j;
	int temp = L[s];
	sn++;
	i = s;
	j = 2 * i + 1;
	while (j <= t)
	{
		if ((j<t) && (L[j]<L[j + 1])) j++;
		if (j<t) cn++;
		cn++;
		if (temp >= L[j]) break;
		L[i] = L[j];
		sn++;
		i = j; j = 2 * i + 1;
	}
	L[i] = temp; sn++;
}

void sort_heap(int L[], int n, int &cn, int &sn)   // 堆排序
{
	int i;
	int temp;
	for (i = n / 2 - 1; i >= 0; i--) heap_sift(L, i, n - 1, cn, sn);
	for (i = n - 1; i>0; i--)
	{
		temp = L[0]; L[0] = L[i]; L[i] = temp;
		sn = sn + 3;
		heap_sift(L, 0, i - 1, cn, sn);
	}
}

void merge(int *L, int *LL, int s, int m, int t, int &cn, int &sn)  // 两个相邻有序子序列的合并 
{  // 将有序表L[s..m]与有序表L[m+1..t]合并到LL[s..t]
	int i, j, k;
	i = s; j = m + 1;
	k = s;
	while ((i <= m) && (j <= t))
	{
		if (L[i] <= L[j]) LL[k++] = L[i++];
		else LL[k++] = L[j++];
		cn++;
		sn++;
	}
	while (i <= m)
	{
		LL[k++] = L[i++];
		sn++;
	}
	while (j <= t)
	{
		LL[k++] = L[j++];
		sn++;
	}
}

void mpass(int *R, int *RR, int h, int n, int &cn, int &sn)   // 整个记录区间上相邻有序子序列的合并 
{
	int i = 0;
	while (i <= n - 2 * h)
	{
		merge(R, RR, i, i + h - 1, i + 2 * h - 1, cn, sn);
		i = i + 2 * h;
	}
	if (i + h<n) merge(R, RR, i, i + h - 1, n - 1, cn, sn);
	else
		while (i<n)
		{
			RR[i] = R[i];
			i++;
			sn++;
		}
}

void sort_merge(int *R, int *RR, int n, int &cn, int &sn)   // 二路归并排序 
{
	int h = 1;
	while (h<n)
	{
		mpass(R, RR, h, n, cn, sn);
		h = 2 * h;
		mpass(RR, R, h, n, cn, sn);
		h = 2 * h;
	}
}

void output(char *s, int L[], int n, int cn, int sn)   // 输出函数
{
	int i;
	cout << "------ " << s << " ------\n";
	for (i = 0; i<n; i++)
	{
		cout << setw(5) << L[i];
		if ((i + 1) % 16 == 0) cout << endl;    // 按每行10个输出
	}
	cout << "comparison: " << cn << ", shift: " << sn << endl;
}

int main()
{
	int a[256];   		// 存储原始记录
	int b[256];   		// 存储用于排序的记录和结果
	int i, n;     		// n为记录总数 
	int cmp_num, sft_num;	// 分别存储排序中的记录比较和移动次数

	freopen("exp09.in", "r", stdin);
	//freopen("exp09.out", "w", stdout);

	cin >> n;
	for (i = 0; i<n; i++) cin >> a[i];

	// 简单选择排序 //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_selection(b, n, cmp_num, sft_num);
	output("selection sorting", b, n, cmp_num, sft_num);

	// 希尔排序 //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_Shell(b, n, cmp_num, sft_num);
	output("Shell sorting", b, n, cmp_num, sft_num);

	// 快速排序 //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_quick(b, n, cmp_num, sft_num);
	//  sort_quick(b,0,n-1,cmp_num,sft_num);
	output("quick sorting", b, n, cmp_num, sft_num);

	// 堆排序 //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_heap(b, n, cmp_num, sft_num);
	output("heap sorting", b, n, cmp_num, sft_num);

	// 二路归并排序 //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_merge(b, a, n, cmp_num, sft_num);
	output("merging sorting", b, n, cmp_num, sft_num);

	return 0;
}

