#include <iostream>
#include <cmath>

using namespace std;

int main(){
	
	float a,b,c;
	float media = 0;
		
	cin >> a >> b >> c;
	
	media = (2*a + 3*b + 5*c)/(2+3+5);
	
	printf("MEDIA = %0.1lf\n",media);	
	
	return 0;
	
}
