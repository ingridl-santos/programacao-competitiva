#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
	
	int a, b, c, d;
	float e, f, result;
	
	std:: cin >> a >> b >> e;
	std:: cin >> c >> d >> f;
	
	result = (b*e)+(d*f);
	
	printf("VALOR A PAGAR: R$ %.2f\n", result);
	
	return 0;	
	
}
