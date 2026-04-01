#include <bits/stdc++.h>
using namespace std;

/*
    Minden embernél eltároljuk a kedvenc színek halmazát, majd megszámoljuk,
    mely színek jelennek meg legalább két embernél. Egy ember jó, ha minden
    kedvenc színe ilyen.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<set<string>> kedvencek(n);
    map<string, int> darab;

    for (int i = 0; i < n; ++i) {
        int d;
        cin >> d;
        for (int j = 0; j < d; ++j) {
            string s;
            cin >> s;
            kedvencek[i].insert(s);
        }
        for (const string& s : kedvencek[i]) ++darab[s];
    }

    int valasz = 0;
    for (int i = 0; i < n; ++i) {
        bool jo = true;
        for (const string& s : kedvencek[i]) {
            if (darab[s] < 2) {
                jo = false;
                break;
            }
        }
        if (jo) ++valasz;
    }

    cout << valasz << '\n';
    return 0;
}
