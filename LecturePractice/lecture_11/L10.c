#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constant folding.
 	 Most values in this function can be pre-computed by compiler. */
int CF(int param)
{
				char arr[0x55];

				int a = 0x107;
				int b = a * sizeof(arr);
				int c = sqrt(2.0);
				return a * param + (a + 0x15/c + strlen("hello") * b - 0x37)/4;
}

/* Commen subexpression elimination
 	 param2 + 0x107 is repeated many times */
int CSE(int param1, int param2)
{
				int a = param2 + 0x107;
				int b = param1 * (param2 + 0x107) + a;
				return a * (param2 + 0x107) + b * (param2 + 0x107);
}

/* Strength reduction.
   Multiply and divide are expensive. */
int SR(int param1[], size_t param2)
{
				int b = param2 * 7;
				int c = (b + param2) / 3;

				for (int i = 0; i <= param2; i++) {
								c += param1[i] + 0x107 * i;
				}
				return c;
}

/* Dead code */
int DC(int param1, int param2)
{
				if (param1 < param2 && param1 > param2)
								printf("The end of the world is near!\n");

				for (int i = 0; i < 1000; i++)
								;

				if (param1 == param2)
								param1++;
				else
								param1++;

				return 0;
}

int main()
{
	return 0;
}
