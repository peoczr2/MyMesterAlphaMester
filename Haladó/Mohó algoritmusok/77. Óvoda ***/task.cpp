/*
Megoldás lényege:
Minden szerepnél a legnagyobb sírású saját jelentkezők maradnak boldogok, legfeljebb a szerep kapacitásáig, mert így a megspórolt sírás a legnagyobb.
Ha ezzel több hely foglalódna el, mint N, vagy egy szerep üresen maradna, a legkisebb sírású boldogok közül kell néhányat átengedni (egy szerep első boldogja mindig marad).
Az így maradt sírók közül az üres szerepekre jut egy-egy gyerek, a többi a szabad helyekre kerül; a sírók sírásainak összege a kiosztástól függetlenül adott.
Időigény: O(N log N).
*/
/*
Hint 1: || Alapállapot: mindenki sír, ezt csökkented a „saját szerepen maradókkal”. ||
Hint 2: || Egy szerepnél a legnagyobb Ti értékű saját jelentkezőket érdemes megtartani. ||
Hint 3: || Ha ezért egy szerep üresen maradna, vagy túl sok hely foglalódna el, a legkisebb sírású boldogok közül kell valakit kiengedni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> cap(K + 1);
    for (int r = 1; r <= K; ++r) cin >> cap[r];

    vector<int> pref(N + 1), cry(N + 1);
    for (int i = 1; i <= N; ++i) cin >> pref[i];
    for (int i = 1; i <= N; ++i) cin >> cry[i];

    // szerepenként a rá jelentkezők, sírás szerint csökkenően
    vector<vector<int>> byRole(K + 1);
    for (int i = 1; i <= N; ++i) byRole[pref[i]].push_back(i);
    for (int r = 1; r <= K; ++r) {
        sort(byRole[r].begin(), byRole[r].end(), [&](int a, int b) {
            if (cry[a] != cry[b]) return cry[a] > cry[b];
            return a < b;
        });
    }

    // 1. szerepenként legfeljebb cap[r] saját jelentkező marad boldog
    vector<char> happy(N + 1, 0);
    vector<int> hap(K + 1, 0);
    int usage = 0; // a boldogok száma + az üres szerepek (ezeknek kell majd egy sírós)
    for (int r = 1; r <= K; ++r) {
        hap[r] = min((int)byRole[r].size(), cap[r]);
        for (int j = 0; j < hap[r]; ++j) happy[byRole[r][j]] = 1;
        usage += hap[r] + (byRole[r].empty() ? 1 : 0);
    }

    // 2. ha több hely foglalódna, mint N, a legkisebb sírású boldogokat átengedjük
    //    (szerepenként az első boldog mindig marad, hogy a szerep ne legyen üres)
    int excess = usage - N;
    if (excess > 0) {
        vector<int> pool;
        for (int r = 1; r <= K; ++r)
            for (int j = 1; j < hap[r]; ++j) pool.push_back(byRole[r][j]);
        sort(pool.begin(), pool.end(), [&](int a, int b) {
            if (cry[a] != cry[b]) return cry[a] < cry[b];
            return a < b;
        });
        for (int j = 0; j < excess; ++j) happy[pool[j]] = 0;
    }

    // 3. a nem boldogok kiosztása: előbb az üres szerepek kapnak egy-egy gyereket,
    //    a maradékot a szabad helyekre tesszük
    vector<int> assigned(N + 1, 0), load(K + 1, 0);
    vector<int> unhappy;
    for (int i = 1; i <= N; ++i) {
        if (happy[i]) {
            assigned[i] = pref[i];
            load[pref[i]]++;
        } else {
            unhappy.push_back(i);
        }
    }

    size_t ptr = 0;
    for (int r = 1; r <= K; ++r) {
        if (load[r] == 0) {
            int id = unhappy[ptr++];
            assigned[id] = r;
            load[r]++;
        }
    }
    int role = 1;
    while (ptr < unhappy.size()) {
        while (load[role] >= cap[role]) ++role;
        int id = unhappy[ptr++];
        assigned[id] = role;
        load[role]++;
    }

    long long totalCry = 0;
    for (int i = 1; i <= N; ++i) {
        if (assigned[i] != pref[i]) totalCry += cry[i];
    }

    cout << totalCry << '\n';
    for (int i = 1; i <= N; ++i) {
        if (i > 1) cout << ' ';
        cout << assigned[i];
    }
    cout << '\n';
    return 0;
}
