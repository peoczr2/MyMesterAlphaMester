/*
   Azonosító kód: a megadott betűmultihalmaz következő lexikografikus
   permutációját keressük. Ez pontosan a next_permutation feladat.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    if (next_permutation(s.begin(), s.end())) cout << s << '\n';
    else cout << "NINCS\n";
    return 0;
}