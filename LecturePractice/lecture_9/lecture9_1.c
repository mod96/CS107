int arith(int param1, int param2, int *ptr)
{
				int local = param1 + *ptr;
				int local2 = (local - param2) * param1;
				return local2;
}

int main(int argc, char *argv[])
{
				int a = 1, b = 2, c = 3;
				return arith(a, b, &c);
}

