/* 济勤09班 2150265 王加炜 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

//取系统时间

int main()
{
	LARGE_INTEGER tick, begin, end;

	QueryPerformanceFrequency(&tick);	//获得计数器频率
	QueryPerformanceCounter(&begin);	//获得初始硬件计数器计数

	/* 此处是你的程序开始 */
	int num = 0;
	int a = 0;
	for (a = 123; a < 999; a++)
	{
		int d, e, f;
		d = a % 10;
		e = (a / 10) % 10;
		f = (a / 100);
		int b = 0;
		for (b = 124; ((b < 999)); b++)
		{
			int g, h, i;
			g = b % 10;
			h = (b / 10) % 10;
			i = (b / 100);
			int c = 0;
			for (c = 125; ((c < 999)); c++)
			{
				int  j, k, l;
				j = c % 10;
				k = (c / 10) % 10;
				l = (c / 100);
				if ((c > b) && (b > a))
				{
					if ((a + b + c == 1953) && (d != e) && (d != f) && (d != g) && (d != h) && (d != i) && (d != j) && (d != k) && (d != l) && (e != f) && (e != g) && (e != h) && (e != i) && (e != j) && (e != k) && (e != l) && (f != g) && (f != h) && (f != i) && (f != j) && (f != k) && (f != l) && (g != h) && (g != i) && (g != j) && (g != k) && (g != l) && (h != i) && (h != j) && (h != k) && (h != l) && (i != j) && (i != k) && (i != l) && (j != k) && (j != l) && (k != l) && (d != 0) && (e != 0) && (g != 0) && (h != 0) && (j != 0) && (k != 0))
					{
						num = num + 1;
						printf("No.%3d : %d+%d+%d=1953\n", num, a, b, c);
					}
				}
			}
		}
	}
	printf("total=%d\n", num);

	/* 此处是你的程序结束 */

	QueryPerformanceCounter(&end);		//获得终止硬件计数器计数

	printf("计数器频率 : %lldHz\n", tick.QuadPart);
	printf("计数器计数 : %lld\n", end.QuadPart - begin.QuadPart);
	printf("%.6f秒\n", (double)(end.QuadPart - begin.QuadPart) / tick.QuadPart);

	return 0;
}
