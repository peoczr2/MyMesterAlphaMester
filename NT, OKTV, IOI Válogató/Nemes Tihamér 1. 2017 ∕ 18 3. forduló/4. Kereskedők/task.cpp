#include <bits/stdc++.h>
using namespace std;

/*
    Mindkét kereskedő gyümölcseiből halmazt készítünk, majd a szimmetrikus
    különbséget írjuk ki ábécérendben.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    set<string> elso, masodik, eredmeny;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        elso.insert(s);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        masodik.insert(s);
    }

    for (const string& s : elso) {
        if (!masodik.count(s)) eredmeny.insert(s);
    }
    for (const string& s : masodik) {
        if (!elso.count(s)) eredmeny.insert(s);
    }

    cout << eredmeny.size() << '\n';
    for (const string& s : eredmeny) cout << s << '\n';
    return 0;
}