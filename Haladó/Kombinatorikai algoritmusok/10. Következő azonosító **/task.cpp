/*
   Következő azonosító: a szabályos azonosító a benne szereplő különböző
   betűk permutációja, ezért a következő szabályos azonosító a következő
   lexikografikus permutáció.
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