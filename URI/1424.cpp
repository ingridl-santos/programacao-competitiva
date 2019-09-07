#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	
	int a,n,m;
	while(cin >> n >> m){
		vector< vector<int> > v(1000000, vector<int>(0));
		for (int i = 0; i < n; ++i)
		{
			cin >> a;
			v[a-1].push_back(i+1);
		}

		while(m){
			int k, q;
			cin >> k >> q;
			if(v[q-1].size()< k) cout << "0" << endl;
			else cout << v[q-1][k-1] << endl;
			m--;
		}

	
	}
	return 0;
}