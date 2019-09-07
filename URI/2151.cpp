#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
	int caso,matriz[100][100],aux;
	cin >> caso;
	for (int h = 1; h <= caso; ++h)
	{
		cout << "Parede " << h << ":" << endl;
		int m,n,x,y;
		cin >> m >> n >> x >> y;
		x--; y--;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cin >> matriz[i][j];
			}
		}

		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if(abs(i-x) > abs(j-y)) aux = abs(i-x);
				else aux = abs(j-y);
				aux = 10 - aux;
				if(aux<1) aux = 1;
				matriz[i][j] +=aux;
			}
		}

		for (int i = 0; i < m; ++i)
		{
			cout << matriz[i][0] ;
			for (int j = 1; j < n; ++j)
			{
				cout <<" " <<matriz[i][j] ;
			}
			cout << endl;
		}

	}
}