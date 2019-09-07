#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  int k, n;

  cin >> k;

  //caso top1
  if(k == 1){
    cout << "Top 1\n";
  }else if(k <= 3){ //caso top3
    cout << "Top 3\n";
  }else if(k <=5){ //caso top5
    cout << "Top 5\n";
  }else if(k <= 10){ //caso top10
    cout << "Top 10\n";
  }else if(k <= 25){ //caso top25
    cout << "Top 25\n";
  }else if(k <= 50){ //caso top50
    cout << "Top 50\n";
  }else{
    cout << "Top 100\n";
  }
}
