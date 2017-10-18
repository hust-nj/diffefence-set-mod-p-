#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int set(int *index, int cur, int k, int all);
int deal(int *index, int max, int all);
void main1(int prime);

int main(void)
{
	int prime;
	printf("输入你想进行测试的数：");
	scanf("%d", &prime);
	printf("下面将输出满足λ(p-1)=k(k-1)的λ及k(<=p)以及对应的所有满足要求的集合\n");
	printf("=========================================================================\n");
	main1(prime);
	return 0;
}

void main1(int prime)
{
	int lamuta = 1;
	int k;
	while (lamuta <= prime)
	{
		k = (int)(sqrt(lamuta*(prime-1)) + 1);
		if (lamuta*(prime-1) == k*(k - 1))
		{
			printf("每个剩余类重复出现出现λ=%d次，集合元素个数k=%d\n", lamuta, k);
			printf("以下输出满足要求的集合:\n");
			int *index = (int *)malloc(sizeof(int)*k);
			int flag=set(index, 0, k, prime);
			if (flag == 0)printf("此时无满足要求的集合！！！\n");
			printf("-------------------------------------------------------------------------\n");
			free(index);
		}
		lamuta++;
	}
}

int set(int *index, int cur, int k, int all)//k>1
{
	int flag = 0;
	if (cur == 0)
		for (index[0] = 0; index[0] < all - (k - 1 - cur); index[0]++)
			flag |= set(index, cur + 1, k, all);
	else if (cur == k - 1)
	{
		for (index[cur] = index[cur - 1] + 1; index[cur] < all - (k - 1 - cur); index[cur]++)
		{
			flag |= deal(index, k, all);
		}
	}
	else
		for (index[cur] = index[cur - 1] + 1; index[cur] < all - (k - 1 - cur); index[cur]++)
			flag |= set(index, cur + 1, k, all);
	return flag;
}

int deal(int *index,int max,int all)
{
	int p = all;
	int *count=(int *)malloc(sizeof(int)*(p-1));
	for (int i = 0; i < all-1; i++)
	{
		count[i] = 0;
	}
	for (int i = 0; i < max-1; i++)
	{
		for (int j = i + 1; j < max; j++)
		{
			int t = index[i] - index[j];
			t = t > 0 ? t : t + p;
			count[t-1]++;
			count[p - t - 1]++;
		}
	}
	int flag = 1;
	for (int i = 0; i < p - 2; i++)
	{
		flag &= count[i] == count[i + 1] ? 1 : 0;
	}
	if (flag == 1)
	{
		for (int i = 0; i < max; i++)
			printf("%-4d", index[i]);
		printf("\n");
	}
	free(count);
	return flag;
}
