#include<stdio.h>
#include<stdlib.h>
#define MAX 10			//定义最大支持的阶数
void shuchu(float m[MAX][MAX], int hang, int lie)
//输出矩阵函数，形参为二维数组，行数和列数
{
	int i, j, k,t;
	for (i = 0, k = 0; i < hang; i++)	//循环
		for (j = 0,printf("    | "); j < lie; j++)
		{
			if (k == 0)
			{
				for (t = 0; t < lie; t++)
					printf("       ");
				printf(" |\n    | ");
			}
			printf("%6.2f ", m[i][j]);	//输出对应的值
			k++;
			if (k % lie == 0)
			{
					printf(" |\n    | ");
					for (t = 0; t < lie; t++)
						printf("       ");
					printf(" |\n");
			}
			
			//列数判别，如果k为列数的倍数，则换行
		}
	printf("\n");
}
float value(float a[MAX][MAX], int n)
//行列式值计算函数，形参为二维数组和阶数，返回行列式的值
{
	float sum = 0;
	int i, j, k, m;
	float temp[MAX][MAX];		//临时矩阵，用于存放矩阵的余子式
	switch (n)	//选择阶数
	{
	case 1:
		return a[0][0];		//一阶矩阵直接返回其本身
	case 2:
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
		//二阶矩阵返回对角线元素乘积的差
	default:	//其余情况
		for (i = 0; i<n; i++)
			//循环，将矩阵按第一行的元素展开，取余子式
		{
			for (j = 1; j<n; j++)
			{
				m = 0;	//用m来判定代数余子式前所需的正负号
				for (k = 0; k<n; k++)
				{
					if (k != i)		//k不等于i时
						temp[j - 1][k - m] = a[j][k];
					//将对应元素赋给新的二维数组，即为余子式
					else m = 1;
				}
			}
			if (i % 2) m = -1;
			sum += m*a[0][i] * value(temp, n - 1);
			//用递归计算余子式值并循环加和得到行列式值
		}
		return sum;		//返回行列式值
	}
}
void swap_line(float m[MAX][MAX], float x[MAX], int n, int n1)
//换列函数，将n阶矩阵m中的第n1列与x交换
{
	int i;
	float t[MAX];
	for (i = 0; i < n; i++)		//交换列
	{
		t[i] = x[i];
		x[i] = m[i][n1];
		m[i][n1] = t[i];
	}
}
float inner_product(float a[MAX], float b[MAX], int n)
//内积计算函数
{
	float ans = 0;
	int i;
	for (i = 0; i < n; i++)
		ans += a[i] * b[i];		//循环加和两项乘积得到内积
	return ans;	//返回内积
}
void zhuanzhi(void)		//转置部分
{
	int i, j, x, y;
	float a[MAX][MAX], b[MAX][MAX];	//a为原矩阵，b为转置后矩阵
	printf("输入矩阵的行数、列数：\n");
	scanf_s("%d%d", &x, &y);
	printf("输入矩阵：\n");
	for (i = 0; i < x; i++)		//循环输入矩阵
		for (j = 0; j < y; j++)
			scanf_s("%f", &a[i][j]);
	for (i = 0; i < x; i++)
		//循环，将将A的i行j列元素赋给B的j行i列
		for (j = 0; j < y; j++)
			b[j][i] = a[i][j];
	printf("\n原矩阵为：\n");
	shuchu(a, x, y);	//输出原矩阵
	printf("\n转置矩阵为：\n");
	shuchu(b, y, x);	//输出转置后矩阵
}
void hanglieshi(void)	//行列式部分	
{
	int n, i, j;
	float a[MAX][MAX];
	printf("输入矩阵阶数：\n");
	scanf_s("%d", &n);	//输入阶数
	printf("输入矩阵：\n");
	for (i = 0; i < n; i++)		//循环输入矩阵元素
		for (j = 0; j < n; j++)
			scanf_s("%f", &a[i][j]);
	printf("\n原矩阵为：\n");
	shuchu(a, n, n);	//调用行列式计算函数计算行列式
	printf("行列式的值为：%5.2f", value(a, n));
}
void jiafa(void)
{
	int x, y, i, j, n1, n2;
	float a[MAX][MAX], b[MAX][MAX], ans[MAX][MAX];
	//矩阵A，B为原矩阵，ans为结果矩阵
	printf("输入矩阵的行数、列数：\n");
	scanf_s("%d%d", &x, &y);
	printf("输入A矩阵：\n");
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			scanf_s("%f", &a[i][j]);	//输入A矩阵
	printf("输入A的倍数：\n");
	scanf_s("%d", &n1);
	printf("输入B矩阵：\n");
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			scanf_s("%f", &b[i][j]);	//输入B矩阵
	printf("输入B的倍数：\n");
	scanf_s("%d", &n2);
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			ans[i][j] = n1*a[i][j] + n2*b[i][j];	//进行加法运算
	printf("%3dA+%3dB = \n", n1, n2);
	shuchu(ans, x, y);
}
void multiply(void)		//矩阵乘法部分
{
	int x1, x2, y1, y2, i, j, k;
	float a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
	//矩阵A，B为原矩阵，C为结果矩阵
	do
	{		//循环，如果无法进行乘法则重新进行
		printf("输入A矩阵的行数、列数：\n");
		scanf_s("%d%d", &x1, &y1);
		printf("输入B矩阵的行数、列数：\n");
		scanf_s("%d%d", &x2, &y2);
		if (y1 != x2) printf("A列数不等于B行数，请重新输入\n");
	} while (y1 != x2);
	//若满足该条件，无法进行矩阵乘法，需要重新输入
	printf("输入A矩阵：\n");
	for (i = 0; i < x1; i++)
		for (j = 0; j < y1; j++)
			scanf_s("%f", &a[i][j]);	//输入A矩阵
	printf("输入B矩阵：\n");
	for (i = 0; i < x2; i++)
		for (j = 0; j < y2; j++)
			scanf_s("%f", &b[i][j]);	//输入B矩阵
	for (i = 0; i < x1; i++)
		for (j = 0; j < y2; j++)
			c[i][j] = 0;	//将C中全部元素转为0
	for (i = 0; i < x1; i++)
		for (j = 0; j < y2; j++)
			for (k = 0; k < y1; k++)
				c[i][j] += a[i][k] * b[k][j];	//计算结果赋给C
	printf("\nA矩阵为：\n");
	shuchu(a, x1, y1);	//输出A矩阵
	printf("\nB矩阵为：\n");
	shuchu(b, x2, y2);		//输出B矩阵
	printf("\n矩阵AB为：\n");
	shuchu(c, x1, y2);	//输出C矩阵
}
void neiji(void)	//内积部分
{
	int i, n;
	float a[MAX], b[MAX];	//定义两个数组用于储存向量
	printf("请输入项数n：\n");	//输入
	scanf_s("%d", &n);
	printf("请输入向量a：\n");
	for (i = 0; i < n; i++)
		scanf_s("%f", &a[i]);
	printf("请输入向量b：\n");
	for (i = 0; i < n; i++)
		scanf_s("%f", &b[i]);
	printf("a和b的内积为：\n");
	printf("%7.2f\n", inner_product(a, b, n));	//调用内积函数输出内积
}
void cramer(void)	//Carmer法解n元线性方程组部分
{
	int n, i, j;
	float a[MAX][MAX], b[MAX], d[MAX], x;	//d为储存结果的数组
	for (i = 0; i < MAX; i++)
		b[i] = 0;
	printf("输入未知数的个数：\n");
	scanf_s("%d", &n);
	printf("输入系数矩阵：\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf_s("%f", &a[i][j]);	//输入矩阵
	printf("输入常数项列：\n");
	for (i = 0; i < n; i++)
		scanf_s("%f", &b[i]);
	x = value(a, n);	//计算系数矩阵的值x
	if (x)	//判断系数矩阵的值，仅在不为零时有唯一解
	{
		for (i = 0; i < n; i++)		//循环计算各个未知数的解
		{
			swap_line(a, b, n, i);	//将常数项列和系数矩阵中的第i列交换
			d[i] = value(a, n) / x;		//计算未知数x的解
			swap_line(a, b, n, i);	//将常数项列恢复原状
		}
		printf("解：\n");
		for (i = 0; i < n; i++)
			printf("x%d=%7.2f\n", i + 1, d[i]);		//输出结果
	}
	else printf("该方程无唯一解。\n");	//无解输出
}
int jud(void)	//运行结束判断部分
{
	int input;		//定义判断参数
	do
	{
		printf("-------------\n");
		printf(" 已运行完毕\n");
		printf("1、重新运行\n");
		printf("0、退出\n");
		printf("-------------\n");
		scanf_s("%d", &input);
		switch (input)	//判断输入的值来返回不同的值
		{
		case 1:
			return 1;
		case 0:
			return 0;
		default:	//如果输入的不是0或1，直接结束
			break;
		}
	} while (input);	//如果input非零，即输入错误，回到上一步
}
int main()
{
	int j, input;
	do {
		printf("    ------------------------------------\n\n");
		//选择界面
		printf("                矩阵计算器\n\n");
		printf("         仅支持%d阶以下矩阵或向量\n\n", MAX);
		printf("         1、矩阵转置\n\n");
		printf("         2、行列式求值\n\n");
		printf("         3、矩阵乘法\n\n");
		printf("         4、Carmer法解n元线性方程组\n\n");
		printf("         5、向量内积\n\n");
		printf("         6、矩阵加法\n\n");
		printf("         0、退出\n\n");
		printf("    ------------------------------------\n\n");
		scanf_s("%d", &input);
		switch (input)		//判断输入来进入不同区块
		{
		case 0:		//直接退出
			j = 0; break;
		case 1:
			zhuanzhi();	break;
		case 2:
			hanglieshi(); break;
		case 3:
			multiply();	break;
		case 4:
			cramer(); break;
		case 5:
			neiji(); break;
		case 6:
			jiafa();break;
		default: break;
		}
		if (input >= 0 && input <=6)
			j = jud();
		else
		{
			j = 1;
			printf("输入有误，请重新输入\n");
		}
	} while (j);			//循环判断，如果j==1，即重新运行
	system("pause");
	return 0;
}