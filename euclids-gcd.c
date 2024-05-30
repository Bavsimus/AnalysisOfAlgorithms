#include <stdio.h>

int gcd(int a, int b){
	while (b != 0){
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

int main(){
	int num1, num2;

	printf("enter first integer: ");
	scanf("%d", &num1);
	printf("second integer: ");
	scanf("%d", &num2);
	
	int result = gcd(num1, num2);

	printf("GCD of %d and %d is %d\n", num1, num2, result);

	return 0;
}
