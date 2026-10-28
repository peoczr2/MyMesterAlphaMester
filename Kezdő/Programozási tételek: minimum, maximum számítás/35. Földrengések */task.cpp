/*
Megoldás lényege:
Az időpontokat átalakítjuk az eltelt másodpercek számává (nap·86400 + óra·3600 + perc·60 + másodperc), így két időpont különbsége egyszerű kivonással adódik. A két kérdés a szomszédos földrengések közötti különbségekre vonatkozik: a leghosszabb földrengésmentes időszak ezeknek a maximuma, a két földrengés közötti minimális időtartam pedig a minimuma. Az eredményt a bemenettel azonos formában írjuk ki: napok száma, majd óra, perc, másodperc, a napok száma tehát a teljes különbség napos része. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Az időpontot érdemes egyetlen számmá alakítani: az eltelt másodperceket kell kivonni, nem a négy mezőt külön. ||
Hint 2: || A kérdések csak a szomszédos időpontok különbségeire vonatkoznak; ezekből tartsd a maximumot és a minimumot, az eredményt pedig visszaalakítsd nap, óra, perc, másodperc formába. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Az időpont eltelt másodpercei a hónap első napjának 0 órájától.
long long toSeconds(int day, int hour, int minute, int second) {
    return (long long)day * 86400 + hour * 3600LL + minute * 60LL + second;
}

// Időtartam kiírása "napok óra perc másodperc" formában.
void printDuration(long long sec) {
    long long days = sec / 86400;
    sec %= 86400;
    long long hours = sec / 3600;
    sec %= 3600;
    long long minutes = sec / 60;
    long long seconds = sec % 60;
    cout << days << " " << hours << " " << minutes << " " << seconds << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> t(n);
    for (int i = 0; i < n; i++) {
        int day, hour, minute, second;
        cin >> day >> hour >> minute >> second;
        t[i] = toSeconds(day, hour, minute, second);
    }

    long long maxGap = t[1] - t[0];
    long long minGap = maxGap;
    for (int i = 2; i < n; i++) {
        long long gap = t[i] - t[i - 1];
        maxGap = max(maxGap, gap);
        minGap = min(minGap, gap);
    }

    printDuration(maxGap);
    printDuration(minGap);

    return 0;
}
