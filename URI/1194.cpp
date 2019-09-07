#include <iostream>

using namespace std;

int p;

void f(string prefixa, string infixa, int a, int b){
	if(a <= b){

		p++;
		int posfixa = infixa.find(prefixa[p]);
		f(prefixa, infixa, a, posfixa-1);
		f(prefixa, infixa, posfixa+1,b);
		cout << infixa[posfixa];
	}
}

int main(int argc, char const *argv[])
{
	int casoTeste;

	cin >> casoTeste;

	for(int i = 1; i <= casoTeste; i++){
		p = -1;
		int n;
		string pre, in;

		cin >> n >> pre >> in;

		f(pre,in,0,n-1);
		cout << endl;
	}
}
