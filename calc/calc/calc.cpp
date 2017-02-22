#include<stdio.h>
#include<stdlib.h>
#define MAX 10			//定义最大支持的阶数
int choice = 0;
struct Matrix	//矩阵结构体
{
	int row;
	int column;
	float m[MAX][MAX];
};
void shuchu(struct Matrix *p)
{
	int i, j, k, t;
	for (i = 0, k = 0; i < p->row; i++)	//循环
		for (j = 0,printf("    | "); j < p->column; j++)
		{
			if (k == 0)
			{
				for (t = 0; t < p->column; t++)
					printf("       ");
				printf(" |\n    | ");
			}
			printf("%6.2f ", p->m[i][j]);	//输出对应的值
			k++;
			if (k % p->column == 0)
			{
				printf(" |\n    | ");
				for (t = 0; t < p->column; t++)
					printf("       ");
				printf(" |\n");
			}
		}
	printf("\n");
}
float value(struct Matrix *p)
{
	float sum = 0;
	int i, j, k, m;
	struct Matrix temp;
	struct Matrix *s;
	s = &temp;
	temp.column = p->column-1;
	temp.row = p->row-1;
	switch (p->column)
	{
	case 1:
		return p->m[0][0];
	case 2:
		return p->m[0][0] * p->m[1][1] - p->m[0][1] * p->m[1][0];
	default:
		for (i = 0; i < p->column; i++)
		{
			for (j = 1; j < p->column; j++)
			{
				m = 0;
				for (k = 0; k < p->column; k++)
				{
					if (k != i)	
						s->m[j - 1][k - m] = p->m[j][k];
					else m = 1;
				}
			}
			if (i % 2) m = -1;
			sum += m*p->m[0][i] * value(s);
		}
		return sum;	
	}
}
void swap_line(struct Matrix *p, float x[MAX], int n1)
{
	int i;
	float temp[MAX];
	for (i = 0; i < p->column; i++)		//交换列
	{
		temp[i] = x[i];
		x[i] = p->m[i][n1];
		p->m[i][n1] = temp[i];
	}
}
float inner_product(float a[MAX], float b[MAX], int n)	//内积计算函数
{
	float ans = 0;
	int i;
	for (i = 0; i < n; i++)
		ans += a[i] * b[i];		//循环加和两项乘积得到内积
	return ans;	//返回内积
}
void zhuanzhi(void)		//转置部分
{
	int i, j;
	struct Matrix a[2];
	struct Matrix *p;
	p = &a[0];
	printf("输入矩阵的行数、列数：\n");
	scanf_s("%d%d", &p->row, &p->column);
	a[1].column = p->row;
	a[1].row = p->column;
	printf("输入矩阵：\n");
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			a[1].m[j][i] = a[0].m[i][j];
	printf("\n原矩阵为：\n");
	shuchu(p);
	printf("\n转置矩阵为：\n");
	shuchu(p+1);
}
void hanglieshi(void)	//行列式部分	
{
	struct Matrix a;
	struct Matrix *p;
	p = &a;
	int i, j;
	printf("输入矩阵阶数：\n");
	scanf_s("%d", &p->column);	//输入阶数
	p->row = p->column;
	printf("输入矩阵：\n");
	for (i = 0; i < p->column; i++)		//循环输入矩阵元素
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);
	printf("\n原矩阵为：\n");
	shuchu(p);	//调用行列式计算函数计算行列式
	printf("行列式的值为：%5.2f\n", value(p));
}
void jiafa(void)
{
	int i, j, n1, n2;
	struct Matrix a[3];
	struct Matrix *p;
	p = &a[0];
	printf("输入矩阵的行数、列数：\n");
	scanf_s("%d%d", &p->row, &p->column);
	for (p = p + 1, i = 0; i < 2; i++, p++)
	{
		p->row = a[0].row;
		p->column = a[0].column;
	}
	p = &a[0];
	printf("输入A矩阵：\n");
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);	//输入A矩阵
	printf("输入A的倍数：\n");
	scanf_s("%d", &n1);
	p++;
	printf("输入B矩阵：\n");
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);	//输入B矩阵
	printf("输入B的倍数：\n");
	scanf_s("%d", &n2);
	p++;
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			p->m[i][j] = n1*(p - 2)->m[i][j] + n2*(p - 1)->m[i][j];	//进行加法运算
	printf("%3dA+%3dB = \n", n1, n2);
	shuchu(&a[2]);
}
void multiply(void)		//矩阵乘法部分
{
	int i, j, k, t;
	char ch;
	struct Matrix a[3];
	struct Matrix *p;
	do
	{
		for (i = 0, p = &a[0],ch = 'A'; i < 2; i++,p++, ch++)
		{
			printf("输入%c矩阵的行数、列数：\n", ch);
			scanf_s("%d%d", &p->row, &p->column);
		}
		if (a[0].column != a[1].row) printf("A列数不等于B行数，请重新输入\n");
	} while (a[0].column != a[1].row);
	for (t = 0, p = &a[0], ch = 'A'; t < 2; t++,p++, ch++)
	{
		printf("输入%c矩阵：\n", ch);
		for (i = 0; i < p->row; i++)
			for (j = 0; j < p->column; j++)
				scanf_s("%f", &p->m[i][j]);
	}
	p = &a[2];
	p->row = a[0].row;
	p->column = a[1].column;
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			p->m[i][j] = 0;
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			for (k = 0; k < (p - 2)->column; k++)
				p->m[i][j] += a[0].m[i][k] * a[1].m[k][j];
	printf("A*B=C\n");
	for (i = 0, p = &a[0], ch = 'A'; i < 3; i++, p++, ch++)
	{
		printf("\n%c矩阵为：\n", ch);
		shuchu(p);
	}
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
	int i, j;
	struct Matrix a;
	struct Matrix *p;
	p = &a;
	float b[MAX], d[MAX], x;	//d为储存结果的数组
	for (i = 0; i < MAX; i++)
		b[i] = 0;
	printf("输入未知数的个数：\n");
	scanf_s("%d", &p->column);
	p->row = p->column;
	printf("输入系数矩阵：\n");
	for (i = 0; i < p->column; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);	//输入矩阵
	printf("输入常数项列：\n");
	for (i = 0; i < p->column; i++)
		scanf_s("%f", &b[i]);
	x = value(p);	//计算系数矩阵的值x
	if (x)	//判断系数矩阵的值，仅在不为零时有唯一解
	{
		for (i = 0; i < p->column; i++)		//循环计算各个未知数的解
		{
			swap_line(p, b, i);	//将常数项列和系数矩阵中的第i列交换
			d[i] = value(p) / x;		//计算未知数x的解
			swap_line(p, b, i);	//将常数项列恢复原状
		}
		printf("解：\n");
		for (i = 0; i < p->column; i++)
			printf("x%d=%7.2f\n", i + 1, d[i]);		//输出结果
	}
	else printf("该方程无唯一解。\n");	//无解输出
}
int jud(void)	//运行结束判断部分
{
	int input;		//定义判断参数
	do
	{
		printf("    ----------------\n");
		printf("     已运行完毕\n");
		printf("     1、重新运行\n");
		printf("     2、返回主菜单\n");
		printf("     0、退出\n");
		printf("    ----------------\n");
		scanf_s("%d", &input);
		switch (input)	//判断输入的值来返回不同的值
		{
		case 1:
			return 2;
		case 2:
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
		if (input == 0)break;
		do {
			switch (input)		//判断输入来进入不同区块
			{
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
				jiafa(); break;
			default: break;
			}
			if (input >= 0 && input <= 6)
				j = jud();
			else
			{
				j = 0;
				printf("输入有误，请重新输入\n");
			}
		} while (j == 2);
	} while (j == 1);			//循环判断，如果j==1，即重新运行
	system("pause");
	return 0;
}