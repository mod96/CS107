#include <stdio.h>

int isTMax(int x){
	return !(x ^ (x + 1) + 1);
}

int main(void) {
	int var = 1 << 31;
	int vars[6] = {var, 0, 1, 5, -5, var - 1};
	for (int i = 0; i < 6; i++) {
		printf("%d", isTMax(vars[i]));
	}
	return 0;
}


