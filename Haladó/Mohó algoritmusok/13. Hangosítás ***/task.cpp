/*
Feladat: Naponként külön-külön kiválasztjuk a maximális számú, egymást nem átfedő rendezvényt (mindegyik ugyanannyit fizet), majd eldöntjük, meddig és milyen előrefizetési blokkokkal érdemes folyamatosan dolgozni az 1. naptól.
Ötlet: Minden nap profitja: (max kompatibilis rendezvényszám) * L, ezt klasszikus befejezési idő szerinti mohóval kapjuk. Utána DP-t futtatunk nap-határokon: egy előrefizetés egy [i+1..j] blokkra ugrás, költsége K+(j-i)*R, bevétele a blokk napi profitösszege. Ahol a pénz elég az előrefizetésre, ott átmenet engedett.
*/
/*
Hint 1: || Először szedd szét a problémát napi profitokra: egy napot hogyan lehet maximálisan kitölteni átfedés nélküli munkákkal? ||
Hint 2: || Az előrefizetés több napra egyszerre is történhet, ezért érdemes „blokkugrásokban” gondolkodni. ||
Hint 3: || Állapot lehet: egy nap végén mennyi pénzed lehet legfeljebb; innen próbálj minden lehetséges következő fizetési blokkot. ||
*/

#include <bits/stdc++.h>
using namespace std;

static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

static int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

static int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

int main() {
    int N = readInt(), K = readInt(), R = readInt(), L = readInt();

    vector<long long> profit(N + 1, 0);
    for (int day = 1; day <= N; ++day) {
        int m = readInt();
        int cnt = 0;
        int lastEnd = -1;
        for (int i = 0; i < m; ++i) {
            int s = readInt();
            int e = readInt();
            if (s >= lastEnd) {
                ++cnt;
                lastEnd = e;
            }
        }
        profit[day] = 1LL * cnt * L;
    }

    vector<long long> pref(N + 1, 0);
    for (int i = 1; i <= N; ++i) pref[i] = pref[i - 1] + profit[i];

    const long long NEG = -(1LL << 60);
    vector<long long> bestCash(N + 1, NEG);
    vector<int> bestPay(N + 1, INT_MAX);

    bestCash[1] = profit[1];
    bestPay[1] = 0;

    for (int i = 1; i <= N; ++i) {
        if (bestCash[i] == NEG) continue;

        for (int j = i + 1; j <= N; ++j) {
            int days = j - i;
            long long cost = 1LL * K + 1LL * days * R;
            if (bestCash[i] < cost) continue;

            long long blockIncome = pref[j] - pref[i];
            long long newCash = bestCash[i] - cost + blockIncome;
            int newPay = bestPay[i] + 1;

            if (newCash > bestCash[j] || (newCash == bestCash[j] && newPay < bestPay[j])) {
                bestCash[j] = newCash;
                bestPay[j] = newPay;
            }
        }
    }

    int farthest = 1;
    for (int i = N; i >= 1; --i) {
        if (bestCash[i] != NEG) {
            farthest = i;
            break;
        }
    }

    long long ansCash = bestCash[farthest];
    int ansPay = bestPay[farthest];

    cout << ansCash << '\n' << ansPay << '\n';
    return 0;
}
