/*
Не очень оптимальный код для крестиков ноликов с произвольной постановкой символа на поле -- 
неумные игроки -- то есть, если будет возможна победа
то игрок поставит всё равно в произвольное место, не обязательно выигрышное.
10 тысяч сыгранных партий максимальный показатель количества различных игр 960
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CROSS 1
#define ZERO 2
#define horisontal (((arr[0] == arr[1]) && (arr[0] == arr[2]) && arr[0]) || ((arr[3] == arr[4]) && (arr[3] == arr[5]) && arr[3]) || ((arr[6] == arr[7]) && (arr[6] == arr[8]) && arr[6]))
#define vertical (((arr[0] == arr[3]) && (arr[0] == arr[6]) && arr[0]) || ((arr[1] == arr[4]) && (arr[1] == arr[7]) && arr[1]) || ((arr[2] == arr[5]) && (arr[2] == arr[8]) && arr[2]))
#define diagonal (((arr[0] == arr[4]) && (arr[0] == arr[8]) && arr[0]) || ((arr[2] == arr[4]) && (arr[2] == arr[6]) && arr[2]))

int win(int * arr)
{
	if (horisontal || vertical || diagonal)
	{
		// printf("%d\n", arr[2]);
		return 1;
	}
	else
		return 0;
}

int main()
{
	int ** full;
	int i, j, z_or_c, count, c, k, sum;
	sum = 0;

	full = (int **)malloc(10000 * sizeof(*full));
	for (i = 0; i < 10000; i++)
	{
		full[i] = (int *)calloc(9, sizeof(*full[0]));
		z_or_c = CROSS;
		count = 0;
		while (1)
		{
			srand(time(NULL) + i);
			int t = (i + rand()) % 9;
			while (full[i][t])
			{
				t = (i + rand()) % 9;
			}
			full[i][t] = z_or_c;
			count++;
			if (count >= 5)
			{
				if ((win(full[i])) || (count == 9))
					// printf("arr %d count %d t is %d\n",i, count, t);
					break;
			}
			if (z_or_c == CROSS)
				z_or_c = ZERO;
			else
				z_or_c = CROSS;
		}

		for (j = 0; j < i; j++)
		{
			c = 0;
			for (k = 0; k < 9; k++)
			{
				if(full[i][k] == full[j][k])
					c++;
			}
			if (c == 9)
			{
				for (k = 0; k < 9; k++)
				{
					full[i][k] = 0;
				}
			}
		}
		c = 0;
		printf("arr %d is ", i);
		for(j = 0; j < 9; j++)
		{
			if (full[i][j] == 0)
				c++;
			printf("%d", full[i][j]);
		}
		printf("\n");
		if (c < 9)
		{
			sum++;
		}
	}


	// printf("pointer is %x, value is %d\n", &full, *full);
	for (i = 0; i < 10000; i++)
	{
		free(full[i]);
	}
	free(full);
	printf("%d\n", sum);
	return 0;
}