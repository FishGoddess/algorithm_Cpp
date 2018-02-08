#include <iostream>
#include <iomanip>
#include <stdio.h>
using namespace std;

void sort_selection(int L[], int n, int &cn, int &sn)   // ��ѡ������
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

void sort_Shell(int L[], int n, int &cn, int &sn)   // ϣ������ 
{ //************************************************
	int gap, i, j;
	for (gap = n / 2; gap > 0; gap = gap / 2)//ȡϣ�������������ÿ��ѭ�������ԭ����1/2��
	{
		for (i = gap; i < n; i++)
		{
			for (j = i - gap; j >= 0 && L[j] > L[j + gap]; j = j - gap)//�ü��Ϊgap��Ԫ�ػ��������磺v[1]��v[1+n],v[2]��v[2+n].....;
			{
				swap(L[j], L[j + gap]);
				sn+=3;
				cn++;
			}cn++;
		}
	}
  //================================================
}

int partition(int L[], int p1, int p2, int &cn, int &sn)   // ��������һ�˷ָ�, ���طָ��
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

void sort_quick(int L[], int n, int &cn, int &sn)	// �������򣨷ǵݹ飩
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
void sort_quick(int L[],int s,int t,int &cn, int &sn)   // �������򣨵ݹ飩
{ int m;
if(s<t)
{ m=partition(L,s,t,cn,sn);
sort_quick(L,s,m-1,cn,sn);
sort_quick(L,m+1,t,cn,sn);
}
}
*/

void heap_sift(int L[], int s, int t, int &cn, int &sn)   // �������е�һ��ɸѡ 
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

void sort_heap(int L[], int n, int &cn, int &sn)   // ������
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

void merge(int *L, int *LL, int s, int m, int t, int &cn, int &sn)  // �����������������еĺϲ� 
{  // �������L[s..m]�������L[m+1..t]�ϲ���LL[s..t]
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

void mpass(int *R, int *RR, int h, int n, int &cn, int &sn)   // ������¼�������������������еĺϲ� 
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

void sort_merge(int *R, int *RR, int n, int &cn, int &sn)   // ��·�鲢���� 
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

void output(char *s, int L[], int n, int cn, int sn)   // �������
{
	int i;
	cout << "------ " << s << " ------\n";
	for (i = 0; i<n; i++)
	{
		cout << setw(5) << L[i];
		if ((i + 1) % 16 == 0) cout << endl;    // ��ÿ��10�����
	}
	cout << "comparison: " << cn << ", shift: " << sn << endl;
}

int main()
{
	int a[256];   		// �洢ԭʼ��¼
	int b[256];   		// �洢��������ļ�¼�ͽ��
	int i, n;     		// nΪ��¼���� 
	int cmp_num, sft_num;	// �ֱ�洢�����еļ�¼�ȽϺ��ƶ�����

	freopen("exp09.in", "r", stdin);
	//freopen("exp09.out", "w", stdout);

	cin >> n;
	for (i = 0; i<n; i++) cin >> a[i];

	// ��ѡ������ //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_selection(b, n, cmp_num, sft_num);
	output("selection sorting", b, n, cmp_num, sft_num);

	// ϣ������ //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_Shell(b, n, cmp_num, sft_num);
	output("Shell sorting", b, n, cmp_num, sft_num);

	// �������� //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_quick(b, n, cmp_num, sft_num);
	//  sort_quick(b,0,n-1,cmp_num,sft_num);
	output("quick sorting", b, n, cmp_num, sft_num);

	// ������ //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_heap(b, n, cmp_num, sft_num);
	output("heap sorting", b, n, cmp_num, sft_num);

	// ��·�鲢���� //
	for (i = 0; i<n; i++) b[i] = a[i];
	cmp_num = 0; sft_num = 0;
	sort_merge(b, a, n, cmp_num, sft_num);
	output("merging sorting", b, n, cmp_num, sft_num);

	return 0;
}

