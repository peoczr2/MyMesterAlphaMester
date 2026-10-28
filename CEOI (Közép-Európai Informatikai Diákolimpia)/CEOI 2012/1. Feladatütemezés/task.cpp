/*
Megoldás lényege:
Minden feladat a beküldés napjától számított D nap múlva (S+D-dik napig) készülhet el, így a határidők
egyenlő hosszúak: a korábban beküldött feladatnak korábbi a határideje. Ezért a legsürgősebb feladat
elvégzése mindig megfelelő, a várakozó feladatok sorrendje egyszerű FIFO sor.
A gépek K minimumát bináris kereséssel keressük: egy adott K-ra napról napra haladva ellenőrizzük, hogy
egyik feladat határideje sem telik le. Egy ellenőrzés O(N), mert a sorban napi darabszámok állnak.
A minimális K-val az ütemezést ugyanígy építjük fel: egy napon belül a korábbi beküldésű, azon belül a
nagyobb sorszámú feladatok mennek előbb. Az időigény O(N log M + M), a memóriaigény O(N + M).
*/
/*
Hint 1: || Minden feladat S-től S+D-ig készülhet el, és a határidők egyenlő hosszúak. Ezért a korábban beküldött feladat határideje is korábbi, tehát mindig a legsürgősebbet érdemes előre venni. ||
Hint 2: || Egy adott K gépszámra napról napra haladva ellenőrizd, hogy van-e lejárt határidő. Ez a feltétel K-ra monoton, így a minimális K bináris kereséssel megtalálható. ||
Hint 3: || A feladatokat napok szerinti darabszámban tárold, így egy ellenőrzés O(N) lehet. A kiíráshoz egy napon belül a nagyobb sorszámú feladatot add ki előbb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, d, m;
vector<int> cnt;  // cnt[s]: hány feladat érkezik az s. napon

// K gépszámmal betartható-e minden határidő (EDF = FIFO a napok sorrendjében)
bool feasible(int k) {
    vector<int> rem(cnt);
    int head = 1;  // a legrégebbi napon, ahol még van várakozó feladat
    for (int t = 1; t <= n; t++) {
        int cap = k;
        while (cap > 0 && head <= t) {
            if (rem[head] == 0) {
                head++;
                continue;
            }
            int take = min(cap, rem[head]);
            rem[head] -= take;
            cap -= take;
        }
        while (head <= t && rem[head] == 0) head++;
        if (head <= t && head + d <= t) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d >> m;
    cnt.assign(n + 2, 0);
    vector<int> s(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> s[i];
        cnt[s[i]]++;
    }

    int lo = 1, hi = m;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }
    int k = lo;

    // a napra érkező feladatok sorszámai növekvő sorrendben, egy közös tömbben
    vector<int> startOf(n + 2, 0);
    for (int day = 1; day <= n; day++) startOf[day + 1] = startOf[day] + cnt[day];
    vector<int> pos(startOf);
    vector<int> order(m);
    for (int i = 1; i <= m; i++) order[pos[s[i]]++] = i;

    vector<int> left(cnt);  // még ki nem adott feladatok naponként
    deque<int> q;           // azok a napok, ahol van még várakozó feladat

    cout << k << '\n';
    for (int t = 1; t <= n; t++) {
        if (cnt[t] > 0) q.push_back(t);
        int cap = k;
        while (cap > 0 && !q.empty()) {
            int day = q.front();
            while (cap > 0 && left[day] > 0) {
                cout << order[startOf[day] + left[day] - 1] << ' ';
                left[day]--;
                cap--;
            }
            if (left[day] == 0) q.pop_front();
        }
        cout << "0\n";
    }
    return 0;
}
