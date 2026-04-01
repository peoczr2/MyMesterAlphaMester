#include <bits/stdc++.h>
using namespace std;

/*
    A két naptár ugyanazt a 18980 napos ciklust írja le, csak más hosszúságú
    év- és hónapszerkezettel. Ezért mindkét dátumot egy abszolút sorszámmá
    alakítjuk, majd a másik naptár szerkezetével bontjuk vissza.
*/

static pair<int, pair<int, int>> to_haab(long long sorszam) {
    int ev = sorszam / 365 + 1;
    int maradek = sorszam % 365;
    int honap, nap;
    if (maradek < 360) {
        honap = maradek / 20 + 1;
        nap = maradek % 20 + 1;
    } else {
        honap = 0;
        nap = maradek - 360 + 1;
    }
    return {ev, {honap, nap}};
}

static pair<int, pair<int, int>> to_tzolkin(long long sorszam) {
    int ev = sorszam / 260 + 1;
    int maradek = sorszam % 260;
    int honap = maradek / 20 + 1;
    int nap = maradek % 20 + 1;
    return {ev, {honap, nap}};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tev, tho, tnap;
    int hev, hho, hnap;
    cin >> tev >> tho >> tnap;
    cin >> hev >> hho >> hnap;

    long long t_sorszam = 1LL * (tev - 1) * 260 + 1LL * (tho - 1) * 20 + (tnap - 1);
    long long h_sorszam = 1LL * (hev - 1) * 365 + (hho == 0 ? 360 : 1LL * (hho - 1) * 20) + (hnap - 1);

    auto [hev2, hn] = to_haab(t_sorszam);
    auto [tev2, tn] = to_tzolkin(h_sorszam);

    cout << hev2 << ' ' << hn.first << ' ' << hn.second << '\n';
    cout << tev2 << ' ' << tn.first << ' ' << tn.second << '\n';
    return 0;
}