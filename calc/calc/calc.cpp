#include<stdio.h>
#include<stdlib.h>
#define MAX 10			//�������֧�ֵĽ���
int choice = 0;
struct Matrix	//����ṹ��
{
	int row;
	int column;
	float m[MAX][MAX];
};
void shuchu(struct Matrix *p)
{
	int i, j, k, t;
	for (i = 0, k = 0; i < p->row; i++)	//ѭ��
		for (j = 0,printf("    | "); j < p->column; j++)
		{
			if (k == 0)
			{
				for (t = 0; t < p->column; t++)
					printf("       ");
				printf(" |\n    | ");
			}
			printf("%6.2f ", p->m[i][j]);	//�����Ӧ��ֵ
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
	for (i = 0; i < p->column; i++)		//������
	{
		temp[i] = x[i];
		x[i] = p->m[i][n1];
		p->m[i][n1] = temp[i];
	}
}
float inner_product(float a[MAX], float b[MAX], int n)	//�ڻ����㺯��
{
	float ans = 0;
	int i;
	for (i = 0; i < n; i++)
		ans += a[i] * b[i];		//ѭ���Ӻ�����˻��õ��ڻ�
	return ans;	//�����ڻ�
}
void zhuanzhi(void)		//ת�ò���
{
	int i, j;
	struct Matrix a[2];
	struct Matrix *p;
	p = &a[0];
	printf("��������������������\n");
	scanf_s("%d%d", &p->row, &p->column);
	a[1].column = p->row;
	a[1].row = p->column;
	printf("�������\n");
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			a[1].m[j][i] = a[0].m[i][j];
	printf("\nԭ����Ϊ��\n");
	shuchu(p);
	printf("\nת�þ���Ϊ��\n");
	shuchu(p+1);
}
void hanglieshi(void)	//����ʽ����	
{
	struct Matrix a;
	struct Matrix *p;
	p = &a;
	int i, j;
	printf("������������\n");
	scanf_s("%d", &p->column);	//�������
	p->row = p->column;
	printf("�������\n");
	for (i = 0; i < p->column; i++)		//ѭ���������Ԫ��
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);
	printf("\nԭ����Ϊ��\n");
	shuchu(p);	//��������ʽ���㺯����������ʽ
	printf("����ʽ��ֵΪ��%5.2f\n", value(p));
}
void jiafa(void)
{
	int i, j, n1, n2;
	struct Matrix a[3];
	struct Matrix *p;
	p = &a[0];
	printf("��������������������\n");
	scanf_s("%d%d", &p->row, &p->column);
	for (p = p + 1, i = 0; i < 2; i++, p++)
	{
		p->row = a[0].row;
		p->column = a[0].column;
	}
	p = &a[0];
	printf("����A����\n");
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);	//����A����
	printf("����A�ı�����\n");
	scanf_s("%d", &n1);
	p++;
	printf("����B����\n");
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);	//����B����
	printf("����B�ı�����\n");
	scanf_s("%d", &n2);
	p++;
	for (i = 0; i < p->row; i++)
		for (j = 0; j < p->column; j++)
			p->m[i][j] = n1*(p - 2)->m[i][j] + n2*(p - 1)->m[i][j];	//���мӷ�����
	printf("%3dA+%3dB = \n", n1, n2);
	shuchu(&a[2]);
}
void multiply(void)		//����˷�����
{
	int i, j, k, t;
	char ch;
	struct Matrix a[3];
	struct Matrix *p;
	do
	{
		for (i = 0, p = &a[0],ch = 'A'; i < 2; i++,p++, ch++)
		{
			printf("����%c�����������������\n", ch);
			scanf_s("%d%d", &p->row, &p->column);
		}
		if (a[0].column != a[1].row) printf("A����������B����������������\n");
	} while (a[0].column != a[1].row);
	for (t = 0, p = &a[0], ch = 'A'; t < 2; t++,p++, ch++)
	{
		printf("����%c����\n", ch);
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
		printf("\n%c����Ϊ��\n", ch);
		shuchu(p);
	}
}
void neiji(void)	//�ڻ�����
{
	int i, n;
	float a[MAX], b[MAX];	//���������������ڴ�������
	printf("����������n��\n");	//����
	scanf_s("%d", &n);
	printf("����������a��\n");
	for (i = 0; i < n; i++)
		scanf_s("%f", &a[i]);
	printf("����������b��\n");
	for (i = 0; i < n; i++)
		scanf_s("%f", &b[i]);
	printf("a��b���ڻ�Ϊ��\n");
	printf("%7.2f\n", inner_product(a, b, n));	//�����ڻ���������ڻ�
}
void cramer(void)	//Carmer����nԪ���Է����鲿��
{
	int i, j;
	struct Matrix a;
	struct Matrix *p;
	p = &a;
	float b[MAX], d[MAX], x;	//dΪ������������
	for (i = 0; i < MAX; i++)
		b[i] = 0;
	printf("����δ֪���ĸ�����\n");
	scanf_s("%d", &p->column);
	p->row = p->column;
	printf("����ϵ������\n");
	for (i = 0; i < p->column; i++)
		for (j = 0; j < p->column; j++)
			scanf_s("%f", &p->m[i][j]);	//�������
	printf("���볣�����У�\n");
	for (i = 0; i < p->column; i++)
		scanf_s("%f", &b[i]);
	x = value(p);	//����ϵ�������ֵx
	if (x)	//�ж�ϵ�������ֵ�����ڲ�Ϊ��ʱ��Ψһ��
	{
		for (i = 0; i < p->column; i++)		//ѭ���������δ֪���Ľ�
		{
			swap_line(p, b, i);	//���������к�ϵ�������еĵ�i�н���
			d[i] = value(p) / x;		//����δ֪��x�Ľ�
			swap_line(p, b, i);	//���������лָ�ԭ״
		}
		printf("�⣺\n");
		for (i = 0; i < p->column; i++)
			printf("x%d=%7.2f\n", i + 1, d[i]);		//������
	}
	else printf("�÷�����Ψһ�⡣\n");	//�޽����
}
int jud(void)	//���н����жϲ���
{
	int input;		//�����жϲ���
	do
	{
		printf("    ----------------\n");
		printf("     ���������\n");
		printf("     1����������\n");
		printf("     2���������˵�\n");
		printf("     0���˳�\n");
		printf("    ----------------\n");
		scanf_s("%d", &input);
		switch (input)	//�ж������ֵ�����ز�ͬ��ֵ
		{
		case 1:
			return 2;
		case 2:
			return 1;
		case 0:
			return 0;
		default:	//�������Ĳ���0��1��ֱ�ӽ���
			break;
		}
	} while (input);	//���input���㣬��������󣬻ص���һ��
}
int main()
{
	int j, input;
	do {
		printf("    ------------------------------------\n\n");
		//ѡ�����
		printf("                ���������\n\n");
		printf("         ��֧��%d�����¾��������\n\n", MAX);
		printf("         1������ת��\n\n");
		printf("         2������ʽ��ֵ\n\n");
		printf("         3������˷�\n\n");
		printf("         4��Carmer����nԪ���Է�����\n\n");
		printf("         5�������ڻ�\n\n");
		printf("         6������ӷ�\n\n");
		printf("         0���˳�\n\n");
		printf("    ------------------------------------\n\n");
		scanf_s("%d", &input);
		if (input == 0)break;
		do {
			switch (input)		//�ж����������벻ͬ����
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
				printf("������������������\n");
			}
		} while (j == 2);
	} while (j == 1);			//ѭ���жϣ����j==1������������
	system("pause");
	return 0;
}