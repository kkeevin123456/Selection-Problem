#include<bits/stdc++.h>

using namespace std;

int main() {
    int n = 3000000;
    int min_k = 1;
    int max_k = n;
    int min = 1;
    int max = 20000;
    ofstream output("input.txt");

    srand(time(NULL));

    int k = rand() % (max_k - min_k + 1) + min_k;
    output << n << " " << k << endl;

    for (int i=0; i<n; i++) {
        int x = rand() % (max - min + 1) + min;
        output << x << " ";
    }
}