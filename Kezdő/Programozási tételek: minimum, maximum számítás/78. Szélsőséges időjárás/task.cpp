/*
Megoldás lényege: minden K hosszú, egymás utáni napokból álló szakasz esetén a legnagyobb és a legkisebb hőmérséklet különbségét kell megkeresni.
A szakaszokat csúszóablakkal járjuk be: a jobb végpontot egyesével léptetjük, és két monoton deque-ben tartjuk az ablak maximumának és minimumának indexeit, így minden lépés átlagosan konstans idejű.
A szigorú > összehasonlítás miatt döntetlen esetén a legkisebb kezdőindexű szakasz marad meg.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Minden K hosszú szakaszra tudnod kell a legnagyobb és a legkisebb értéket. Ne számold ezt minden szakaszra újra a nulláról, hanem csúsztasd a szakaszt végig a sorozaton. ||
Hint 2: || Az ablak maximumát és minimumát egy-egy deque-ben tartsd: a maximumhoz olyan indexeket, amelyek értékei csökkenő sorrendben vannak, a minimumhoz növekvő sorrendben. Új elem érkezésekor a végükről dobd ki azokat, amelyek már nem lehetnek szélsők. ||
Hint 3: || Az ablakon kívülre került indexeket a deque elejéről dobd ki. A kész ablakok különbségét számold ki, és csak akkor frissítsd a legjobbat, ha szigorúan nagyobb, így a legkisebb kezdőindexű szakasz marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (auto &x : h) cin >> x;

    deque<int> mxq, mnq;
    int best = -1, bestStart = 0, bestMin = 0, bestMax = 0;
    for (int i = 0; i < n; i++) {
        while (!mxq.empty() && h[mxq.back()] <= h[i]) mxq.pop_back();
        mxq.push_back(i);
        while (!mnq.empty() && h[mnq.back()] >= h[i]) mnq.pop_back();
        mnq.push_back(i);

        int start = i - k + 1;
        while (mxq.front() < start) mxq.pop_front();
        while (mnq.front() < start) mnq.pop_front();

        if (start >= 0) {
            int mx = h[mxq.front()], mn = h[mnq.front()];
            if (mx - mn > best) {
                best = mx - mn;
                bestStart = start;
                bestMin = mn;
                bestMax = mx;
            }
        }
    }
    cout << bestStart + 1 << "\n";
    cout << bestMin << " " << bestMax << "\n";
    return 0;
}
