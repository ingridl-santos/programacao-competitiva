#include <iostream>
#include <string>
using namespace std;
int main(){
	string a = "3",b;
	int n,aux,cont;
	char letra;
	while(cin >> n){
		 a = "3";
		if(n==1) cout << "3" << endl;
		else {
			while(n-1){
				b="";
				cont =0;
				for (int i = 0; i < a.length(); ++i)
				{

					aux = a[i] + '0';
					letra = a[i];
					cont =1;
					while(a[i+1]==letra){				
						cont ++;
						i++;
					}
					//cout << (char) cont+'0' << " " << (char) letra << endl;
					b.push_back((char) cont+'0');
					b.push_back((char) letra);
				}
				a = b;
				
				n--;
			}
			cout << a << endl;
		}
	}
	return 0;
}