#include <bits/stdc++.h>

using namespace std;

//funcao para a subsequencia de palindromo mais longa
int palindromo(string &s, int tamS, vector<int> &vetPos){
	//pd (palindromo) guarda a maximizacao de posicoes marcadas
	//a tabela tam e usada para o desempate
	int tam[tamS][tamS], pd[tamS][tamS];

	for(int i = 0; i < tamS; i++){
		pd[i][i] = vetPos[i];
		tam[i][i] = 1;
	}

	int contTam = 2;

	while(contTam <= tamS){
		for(int i = 0, j = contTam - 1 + i; j < tamS; i++, j++){
			if(s[i] == s[j] && contTam == 2){
				pd[i][j] = vetPos[i] + vetPos[j];
				tam[i][j] = 2;
			}else{
				//perde o valor, quero maximizar
				tam[i][j] = pd[i][j] = 0;

				//testa para o pd[i + 1][j]
				if(pd[i + 1][j] > pd[i][j]){
					pd[i][j] = pd[i + 1][j];
					tam[i][j] = tam[i + 1][j];
				}else if(pd[i + 1][j] == pd[i][j]){
					if(tam[i + 1][j] > tam[i][j]){
						pd[i][j] = pd[i + 1][j];
						tam[i][j] = tam[i + 1][j];
					}
				}

				//testa para o pd[i][j - 1]
				if(pd[i][j - 1] > pd[i][j]){
					pd[i][j] = pd[i][j - 1];
					tam[i][j] = tam[i][j - 1];
				}else if(pd[i][j - 1] == pd[i][j]){
					if(tam[i][j - 1] > tam[i][j]){
						pd[i][j] = pd[i][j - 1];
						tam[i][j] = tam[i][j - 1];
					}
				}

				//testa pra pd[i+1][j-1],mas apenas se s[i]==s[j]
				if (s[i] == s[j]){
					if (pd[i + 1][j - 1] + vetPos[i] + vetPos[j] > pd[i][j]){
						pd[i][j] = pd[i + 1][j - 1] + vetPos[i] + vetPos[j];
						tam[i][j] = tam[i + 1][j - 1] + 2;
					}else if (pd[i + 1][j - 1] + vetPos[i] + vetPos[j] == pd[i][j]){
						if (tam[i + 1][j - 1] + 2 > tam[i][j]){
							pd[i][j] = pd[i + 1][j - 1] + vetPos[i] + vetPos[j];
							tam[i][j] = tam[i + 1][j - 1] + 2;
						}
					}
				}
			}
		}
		contTam++;
	}

		//ao final retorna o maior tam da subsequencia
		//palindrome que pega mais posicoes especiais

	return tam[0][tamS - 1];
}

int main(int argc, char const *argv[]){
	string s;
	int n, tamS;

	cin >> s;
	cin >> n;

	tamS = s.size();

	vector<int> vetPos(tamS);

	for(int i = 0; i < n; i++){
		int pos;
		cin >> pos;
		vetPos[pos - 1] = 1;
	}

	cout << palindromo(s, tamS, vetPos) << endl;

	return 0;
}
