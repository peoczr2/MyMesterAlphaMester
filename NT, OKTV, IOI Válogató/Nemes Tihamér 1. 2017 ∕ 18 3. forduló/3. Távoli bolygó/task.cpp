#include <bits/stdc++.h>
using namespace std;

/*
    K darab egymást követő betűből álló genetikai kódokat kell megszámolni.
    Mivel K legfeljebb 3, a kódok 26-os számrendszerben egyértelműen
    kódolhatók, és a két élőlény akkor tartozik ugyanabba a fajba, ha a kódok
    gyakorisága minden kódra azonos.
*/

static int kod(const string& s, int kezd, int k) {
    int ertek = 0;
    for (int i = 0; i < k; ++i) ertek = ertek * 26 + (s[kezd + i] - 'a');
    return ertek;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, k;
    cin >> m >> k;
    int maxkod = 1;
    for (int i = 0; i < k; ++i) maxkod *= 26;

    while (m--) {
        string a, b;
        cin >> a >> b;
        vector<int> cnta(maxkod), cntb(maxkod);
        for (int i = 0; i < (int)a.size(); i += k) ++cnta[kod(a, i, k)];
        for (int i = 0; i < (int)b.size(); i += k) ++cntb[kod(b, i, k)];
        cout << (cnta == cntb ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}