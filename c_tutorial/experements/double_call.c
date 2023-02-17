#include<stdio.h>

#define MAX(x,y) (((x) > (y)) ? (x) : (y))

int main(int argc, char** argv)
{
	int a = 1;
	int b = 5;
	printf("max result %d,%d : %d\n", ++a, ++b, MAX(a,b));
	return 0;
}	
