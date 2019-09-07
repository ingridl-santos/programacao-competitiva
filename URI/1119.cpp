#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n,k,m;
    cin >> n >> k >> m;
    while(n!=0 or k!=0 or m!=0){
        vector<int> v(n,1);
        int tirak,tiram,contador=n,auxk,auxm,gamb;
        tirak = -1;
        tiram = n;


        while(contador>0){


            auxk = auxm = 0;
            gamb = tirak;
            while(auxk < k and k>0){

                if(gamb+1<n) gamb++;
                else gamb = 0;
                if(v[gamb]==1) auxk++;
            }
            tirak = gamb;


            gamb = tiram;
            while(auxm < m and m > 0){
                if(gamb-1>=0) gamb--;
                else gamb = n-1;
                if(v[gamb]==1) auxm++;
            }
            tiram = gamb;
            if(k==0) tirak = tiram;
            if(m==0) tiram = tirak;

            if(tirak!=tiram){
                    if(tirak+1<10) cout << "  "  <<  tirak+1;
                    else if(tirak+1<100) cout << " "  <<  tirak+1;
                    else if(tirak+1<1000) cout  <<  tirak+1;

                    if(tiram+1<10) cout  << "  "  <<  tiram+1;
                    else if(tiram+1<100) cout  << " "  <<  tiram+1;
                    else if(tiram+1<1000) cout   <<  tirak+1;


                    if(contador > 2) cout << ",";
                    v[tirak] = v[tiram] = 0;
                    contador -=2;
            } else {
                if(tirak+1<10) cout << "  "  <<  tirak+1;
                else if(tirak+1<100) cout << " "  <<  tirak+1;
                else if(tirak+1<1000) cout  <<  tirak+1;
           
                if(contador > 1) cout << ",";
                v[tirak] = 0;
                contador --;
            }

        }
        cout << endl;
        cin >> n >> k >> m;
    }
    return 0;
}
