#include<stdio.h>
#include<stdlib.h>
#define MAX 10			//�������֧�ֵĽ���
void shuchu(float m[MAX][MAX], int hang, int lie)
//������������β�Ϊ��ά���飬����������
{
	int i, j, k,t;
	for (i = 0, k = 0; i < hang; i++)	//ѭ��
		for (j = 0,printf("    | "); j < lie; j++)
		{
			if (k == 0)
			{
				for (t = 0; t < lie; t++)
					printf("       ");
				printf(" |\n    | ");
			}
			printf("%6.2f ", m[i][j]);	//�����Ӧ��ֵ
			k++;
			if (k % lie == 0)
			{
					printf(" |\n    | ");
					for (t = 0; t < lie; t++)
						printf("       ");
					printf(" |\n");
			}
			
			//�����б����kΪ�����ı���������
		}
	printf("\n");
}
float value(float a[MAX][MAX], int n)
//����ʽֵ���㺯�����β�Ϊ��ά����ͽ�������������ʽ��ֵ
{
	float sum = 0;
	int i, j, k, m;
	float temp[MAX][MAX];		//��ʱ�������ڴ�ž��������ʽ
	switch (n)	//ѡ�����
	{
	case 1:
		return a[0][0];		//һ�׾���ֱ�ӷ����䱾��
	case 2:
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
		//���׾��󷵻ضԽ���Ԫ�س˻��Ĳ�
	default:	//�������
		for (i = 0; i<n; i++)
			//ѭ���������󰴵�һ�е�Ԫ��չ����ȡ����ʽ
		{
			for (j = 1; j<n; j++)
			{
				m = 0;	//��m���ж���������ʽǰ�����������
				for (k = 0; k<n; k++)
				{
					if (k != i)		//k������iʱ
						temp[j - 1][k - m] = a[j][k];
					//����ӦԪ�ظ����µĶ�ά���飬��Ϊ����ʽ
					else m = 1;
				}
			}
			if (i % 2) m = -1;
			sum += m*a[0][i] * value(temp, n - 1);
			//�õݹ��������ʽֵ��ѭ���Ӻ͵õ�����ʽֵ
		}
		return sum;		//��������ʽֵ
	}
}
void swap_line(float m[MAX][MAX], float x[MAX], int n, int n1)
//���к�������n�׾���m�еĵ�n1����x����
{
	int i;
	float t[MAX];
	for (i = 0; i < n; i++)		//������
	{
		t[i] = x[i];
		x[i] = m[i][n1];
		m[i][n1] = t[i];
	}
}
float inner_product(float a[MAX], float b[MAX], int n)
//�ڻ����㺯��
{
	float ans = 0;
	int i;
	for (i = 0; i < n; i++)
		ans += a[i] * b[i];		//ѭ���Ӻ�����˻��õ��ڻ�
	return ans;	//�����ڻ�
}
void zhuanzhi(void)		//ת�ò���
{
	int i, j, x, y;
	float a[MAX][MAX], b[MAX][MAX];	//aΪԭ����bΪת�ú����
	printf("��������������������\n");
	scanf_s("%d%d", &x, &y);
	printf("�������\n");
	for (i = 0; i < x; i++)		//ѭ���������
		for (j = 0; j < y; j++)
			scanf_s("%f", &a[i][j]);
	for (i = 0; i < x; i++)
		//ѭ��������A��i��j��Ԫ�ظ���B��j��i��
		for (j = 0; j < y; j++)
			b[j][i] = a[i][j];
	printf("\nԭ����Ϊ��\n");
	shuchu(a, x, y);	//���ԭ����
	printf("\nת�þ���Ϊ��\n");
	shuchu(b, y, x);	//���ת�ú����
}
void hanglieshi(void)	//����ʽ����	
{
	int n, i, j;
	float a[MAX][MAX];
	printf("������������\n");
	scanf_s("%d", &n);	//�������
	printf("�������\n");
	for (i = 0; i < n; i++)		//ѭ���������Ԫ��
		for (j = 0; j < n; j++)
			scanf_s("%f", &a[i][j]);
	printf("\nԭ����Ϊ��\n");
	shuchu(a, n, n);	//��������ʽ���㺯����������ʽ
	printf("����ʽ��ֵΪ��%5.2f", value(a, n));
}
void jiafa(void)
{
	int x, y, i, j, n1, n2;
	float a[MAX][MAX], b[MAX][MAX], ans[MAX][MAX];
	//����A��BΪԭ����ansΪ�������
	printf("��������������������\n");
	scanf_s("%d%d", &x, &y);
	printf("����A����\n");
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			scanf_s("%f", &a[i][j]);	//����A����
	printf("����A�ı�����\n");
	scanf_s("%d", &n1);
	printf("����B����\n");
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			scanf_s("%f", &b[i][j]);	//����B����
	printf("����B�ı�����\n");
	scanf_s("%d", &n2);
	for (i = 0; i < x; i++)
		for (j = 0; j < y; j++)
			ans[i][j] = n1*a[i][j] + n2*b[i][j];	//���мӷ�����
	printf("%3dA+%3dB = \n", n1, n2);
	shuchu(ans, x, y);
}
void multiply(void)		//����˷�����
{
	int x1, x2, y1, y2, i, j, k;
	float a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
	//����A��BΪԭ����CΪ�������
	do
	{		//ѭ��������޷����г˷������½���
		printf("����A�����������������\n");
		scanf_s("%d%d", &x1, &y1);
		printf("����B�����������������\n");
		scanf_s("%d%d", &x2, &y2);
		if (y1 != x2) printf("A����������B����������������\n");
	} while (y1 != x2);
	//��������������޷����о���˷�����Ҫ��������
	printf("����A����\n");
	for (i = 0; i < x1; i++)
		for (j = 0; j < y1; j++)
			scanf_s("%f", &a[i][j]);	//����A����
	printf("����B����\n");
	for (i = 0; i < x2; i++)
		for (j = 0; j < y2; j++)
			scanf_s("%f", &b[i][j]);	//����B����
	for (i = 0; i < x1; i++)
		for (j = 0; j < y2; j++)
			c[i][j] = 0;	//��C��ȫ��Ԫ��תΪ0
	for (i = 0; i < x1; i++)
		for (j = 0; j < y2; j++)
			for (k = 0; k < y1; k++)
				c[i][j] += a[i][k] * b[k][j];	//����������C
	printf("\nA����Ϊ��\n");
	shuchu(a, x1, y1);	//���A����
	printf("\nB����Ϊ��\n");
	shuchu(b, x2, y2);		//���B����
	printf("\n����ABΪ��\n");
	shuchu(c, x1, y2);	//���C����
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
	int n, i, j;
	float a[MAX][MAX], b[MAX], d[MAX], x;	//dΪ������������
	for (i = 0; i < MAX; i++)
		b[i] = 0;
	printf("����δ֪���ĸ�����\n");
	scanf_s("%d", &n);
	printf("����ϵ������\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf_s("%f", &a[i][j]);	//�������
	printf("���볣�����У�\n");
	for (i = 0; i < n; i++)
		scanf_s("%f", &b[i]);
	x = value(a, n);	//����ϵ�������ֵx
	if (x)	//�ж�ϵ�������ֵ�����ڲ�Ϊ��ʱ��Ψһ��
	{
		for (i = 0; i < n; i++)		//ѭ���������δ֪���Ľ�
		{
			swap_line(a, b, n, i);	//���������к�ϵ�������еĵ�i�н���
			d[i] = value(a, n) / x;		//����δ֪��x�Ľ�
			swap_line(a, b, n, i);	//���������лָ�ԭ״
		}
		printf("�⣺\n");
		for (i = 0; i < n; i++)
			printf("x%d=%7.2f\n", i + 1, d[i]);		//������
	}
	else printf("�÷�����Ψһ�⡣\n");	//�޽����
}
int jud(void)	//���н����жϲ���
{
	int input;		//�����жϲ���
	do
	{
		printf("-------------\n");
		printf(" ���������\n");
		printf("1����������\n");
		printf("0���˳�\n");
		printf("-------------\n");
		scanf_s("%d", &input);
		switch (input)	//�ж������ֵ�����ز�ͬ��ֵ
		{
		case 1:
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
		switch (input)		//�ж����������벻ͬ����
		{
		case 0:		//ֱ���˳�
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
			printf("������������������\n");
		}
	} while (j);			//ѭ���жϣ����j==1������������
	system("pause");
	return 0;
}