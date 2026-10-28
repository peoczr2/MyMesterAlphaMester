/*
Megoldás lényege:
Egy napszámos munkanapjainak száma V−K+1, így keresete ennek és a napi bérnek a szorzata. A teljes költség ezeknek az összege, ami akár 10^10 nagyságú is lehet, ezért 64 bites egészeket használunk. A legtöbbet kereső napszámost egy menetben határozzuk meg: az eddigi legnagyobb keresetet tartjuk nyilván, holtverseny esetén pedig azt, aki több munkanapot dolgozott. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy napszámos keresete a munkanapjainak számából (V−K+1) és a napi bérből adódik, így minden sorra közvetlenül kiszámítható. ||
Hint 2: || A teljes költség a keresetek összege; a legtöbbet kereső napszámost egy menetben határozd meg, és holtverseny esetén a több napot dolgozó nyer. Az összeg nem fér be 32 bites egészbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    long long total = 0;
    long long bestEarn = -1;
    long long bestDays = -1;
    int bestIdx = 0;

    for (int i = 1; i <= n; i++) {
        long long k, v, b;
        cin >> k >> v >> b;
        long long days = v - k + 1;
        long long earn = days * b;
        total += earn;
        if (earn > bestEarn || (earn == bestEarn && days > bestDays)) {
            bestEarn = earn;
            bestDays = days;
            bestIdx = i;
        }
    }

    cout << total << "\n" << bestIdx << "\n";
    return 0;
}
