/*
Megoldás lényege:
A feladat kétoldalú párosítás: az egyik oldalon a tanulók, a másikon az ülőhelyek állnak, és minden tanulót a két kért székkel kötünk össze. A legtöbb teljesülő kérés a legnagyobb párosítás mérete, amelyet Kuhn-algoritmussal (augmentáló utak keresésével) kapunk; ez adja T-t és egy legjobb kiosztást. Az összefüggő tartomány kérdésében minden [l, l+T-1] ülőhely-intervallumra megnézzük, van-e T méretű párosítás, amely csak ezeket a székeket használja; ha igen, a kiosztott helyek összefüggő tartományt alkotnak. A korlátok (N legfeljebb 200, M legfeljebb 250) miatt az N intervallumonkénti újrafuttatás bőven belefér az időkorlátba. Az időigény O(N * M * (M + N)).
*/
/*
Hint 1: || Rajzolj kétoldalú gráfot: az egyik oldalon a tanulók, a másikon az ülőhelyek állnak, és minden tanulóhoz húzz élt a két kért székhez. ||
Hint 2: || A legtöbb kielégített kérés a legnagyobb párosítás mérete. Augmentáló utakat keresve (Kuhn-algoritmus) egyesével bővítsd a párosítást. ||
Hint 3: || Az összefüggő kérdéshez próbáld ki az összes [l, l+T-1] ülőhely-intervallumot: csak ezeken a székeken engedd a párosítást, és nézd meg, eléred-e a T méretet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<array<int, 2>> want;  // tanuló két kért széke (0-tól M-1-ig a tanulók)
int lo, hi;                  // az engedélyezett székek tartománya
vector<int> seatOwner;       // seatOwner[szék] = tanuló, vagy -1
vector<int> studentSeat;     // studentSeat[tanuló] = szék, vagy -1
vector<char> vis;

bool tryKuhn(int st) {
    for (int c : want[st]) {
        if (c < lo || c > hi || vis[c]) continue;
        vis[c] = 1;
        if (seatOwner[c] == -1 || tryKuhn(seatOwner[c])) {
            seatOwner[c] = st;
            studentSeat[st] = c;
            return true;
        }
    }
    return false;
}

// Legnagyobb párosítás, csak a [l, h] tartományba eső székeket használva.
int maxMatching(int l, int h) {
    lo = l;
    hi = h;
    seatOwner.assign(N + 1, -1);
    studentSeat.assign(M, -1);
    int cnt = 0;
    for (int st = 0; st < M; st++) {
        vis.assign(N + 1, 0);
        if (tryKuhn(st)) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    want.resize(M);
    for (int i = 0; i < M; i++) cin >> want[i][0] >> want[i][1];

    int T = maxMatching(1, N);

    // A legjobb kiosztás elmentése, mielőtt az intervallumokon újra párosítunk.
    vector<pair<int, int>> pairs;  // (szék, tanuló)
    for (int c = 1; c <= N; c++)
        if (seatOwner[c] != -1) pairs.push_back({c, seatOwner[c]});

    cout << T << '\n';
    for (size_t i = 0; i < pairs.size(); i++) {
        if (i) cout << ' ';
        cout << pairs[i].second + 1 << ' ' << pairs[i].first;
    }
    cout << '\n';

    // Összefüggő tartomány: van-e T méretű párosítás egy T hosszú intervallumon belül.
    bool contiguous = (T == 0);
    for (int l = 1; !contiguous && l + T - 1 <= N; l++) {
        if (maxMatching(l, l + T - 1) == T) contiguous = true;
    }
    cout << (contiguous ? "IGEN" : "NEM") << '\n';
    return 0;
}
