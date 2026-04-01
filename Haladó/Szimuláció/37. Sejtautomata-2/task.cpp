/*
Itt a szabályt érdemes mintázat-transzformációként kezelni: a cellák új állapota mindig egy kis helyi környezetből olvasható ki. Ezért a megoldás a lokális minták gyors felismerésére épül.
*/
/*
Hint 1: || A gyorsabb megoldáshoz a szabályt mint mintázat-transzformációt érdemes kezelni, nem egyesével élő cellákat számolni. ||
Hint 2: || A cellák új állapota mindig a helyi szomszédságból olvasható ki. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;
    string a;
    cin >> a;
    int m;
    cin >> m;
    int rule_size = 2 * l + 1;
    vector<int> rule(1 << rule_size, 0);
    for (int i = 0; i < m; ++i) {
        string p;
        cin >> p;
        int mask = 0;
        for (char c : p) mask = (mask << 1) | (c == 'Z');
        rule[mask] = 1;
    }

    for (int step = 0; step < k; ++step) {
        string b(n, 'F');
        for (int i = l; i < n - l; ++i) {
            int mask = 0;
            for (int j = i - l; j <= i + l; ++j) mask = (mask << 1) | (a[j] == 'Z');
            if (rule[mask]) b[i] = 'Z';
        }
        a.swap(b);
    }

    cout << count(a.begin(), a.end(), 'Z') << '\n';
    return 0;
}