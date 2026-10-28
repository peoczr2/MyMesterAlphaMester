/*
Megoldás lényege:
Az ugrások száma úgy kapható meg, hogy minden szomszédos elempárt megvizsgálunk: ha a második elem és az első különbsége nagyobb 1-nél, akkor ott ugrás van. Egyetlen bejárással, egy számláló növelésével végezzük, mivel az összehasonlítás csak két szomszédos elemet érint. Az időigény O(N), a memóriaigény O(N), ami N legfeljebb 100 mellett elhanyagolható.
*/
/*
Hint 1: || Elég a szomszédos elemek különbségét vizsgálni: minden i-re nézd meg, hogy A[i+1] − A[i] nagyobb-e 1-nél. ||
Hint 2: || Egy ciklussal i = 1-től N−1-ig fuss végig a sorozaton, és az aktuális elemet mindig az előzővel hasonlítsd össze. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int ugras = 0;
    for (int i = 1; i < n; i++)
        if (a[i] - a[i - 1] > 1) ugras++;
    cout << ugras << "\n";
    return 0;
}
