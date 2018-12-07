#include<stdio.h>

int main()
{
	int d, i1, i2, i3, i4, i5, j1, j2, j3, j4, j5, e;
	int x, y, z;
	
	printf("Enter the first (single) digit: ");
	scanf("%1d", &d);
	
	printf("Enter first group of five digits: ");
	scanf("%1d%1d%1d%1d%1d", &i1, &i2 ,&i3, &i4, &i5);
	
	printf("Enter second group of five digits: ");
	scanf("%1d%1d%1d%1d%1d", &j1, &j2 ,&j3, &j4, &j5);
	
	printf("Enter the last (single) digit: ");
	scanf("%1d", &e);
	x = d + i2 + i4 + j1 + j3 + j5;
	y = i1 + i3 + i5 + j2 + j4;
	z = 3 * x + y;
	z = 9 - (z - 1) % 10;

	if(z == e) printf("VALID\n");
	else printf("NOT VALID\n");
	
	return 0;
	
}