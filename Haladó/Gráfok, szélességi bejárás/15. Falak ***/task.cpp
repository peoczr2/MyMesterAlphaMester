/*
Megoldás lényege:
A négyzet H × H cellából áll (koordinátái 1..H), a falak 1 egység szélesek, ezért a fal a [x, x+dx−1] × [y, y+dy−1] cellákat foglalja el.
Ha a kezdőpont cellája fal, a válasz NEM.
Egyébként a kezdőpontból szélességi bejárást (BFS) futtatunk az élen szomszédos szabad cellákon át.
Ha a bejárás a négyzet szélső sorának vagy oszlopának (1-es vagy H-s koordináta) valamelyik cellájára ér, a válasz IGEN, különben NEM.
Minden kezdőpontra külön bejárást végzünk (legfeljebb 5), így az időigény O(K · H²), a falak jelölése pedig összesen O(L · H).
*/
/*
Hint 1: || A kérdés szélességi bejárással (BFS) dönthető el: a négyzetet cellákra bontva a szabad cellák között kell eljutni a szélső sorba vagy oszlopba. ||
Hint 2: || A falak cellái az [x, x+dx-1] és [y, y+dy-1] tartományok; ha a kezdőpont cellája fal, a válasz NEM. ||
Hint 3: || A bejárás minden kezdőpontra új időbélyeggel fusson (látogatott-jelölés), hogy ne kelljen a tömböt minden alkalommal nullázni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, l, k;
    cin >> h >> l >> k;
    vector<array<int, 4>> walls(l);
    for (auto &w : walls) cin >> w[0] >> w[1] >> w[2] >> w[3];

    // A (i, j) cella koordinátái 1..h; az index i * S + j, S = h + 2 (a keret is elfér).
    const int S = h + 2;
    vector<char> wallCell(S * S, 0);
    for (auto &w : walls) {
        for (int i = w[0]; i < w[0] + w[2]; ++i)
            for (int j = w[1]; j < w[1] + w[3]; ++j)
                wallCell[i * S + j] = 1;
    }

    const int di[4] = {1, -1, 0, 0};
    const int dj[4] = {0, 0, 1, -1};
    vector<int> seenAt(S * S, 0), queueBuf(S * S);
    for (int t = 1; t <= k; ++t) {
        int kx, ky;
        cin >> kx >> ky;

        if (wallCell[kx * S + ky]) {
            cout << "NEM\n";
            continue;
        }

        int head = 0, tail = 0;
        seenAt[kx * S + ky] = t;
        queueBuf[tail++] = kx * S + ky;

        bool ok = false;
        while (head < tail) {
            int id = queueBuf[head++];
            int i = id / S, j = id % S;
            if (i == 1 || j == 1 || i == h || j == h) {
                ok = true;
                break;
            }
            for (int d = 0; d < 4; ++d) {
                int nid = (i + di[d]) * S + (j + dj[d]);
                if (wallCell[nid] || seenAt[nid] == t) continue;
                seenAt[nid] = t;
                queueBuf[tail++] = nid;
            }
        }
        cout << (ok ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
