/*
Felfelé haladva minden táborban a hátizsákba férő legtöbbet vesszük fel, de annyit hagyunk ott, amennyi a visszaútra még hiányzik: az igényből levonjuk az alatta már hagyott mennyiséget. A csúcsra menetnél a csúcs oda-vissza igénye is a visszaúthoz tartozik, az első táborban nincs visszaút-igény. Ha valahol nem lehet elég élelmiszert hagyni, az előző táborból fordulunk vissza, ha pedig a hátizsák nem elég a továbbinduláshoz, az aktuális tábor a legtávolabbi elérhető. A csúcsra jutást a lefelé úton ellenőrizzük, a futásidő O(N).
*/
/*
Hint 1: || Felfelé menet táborról táborra számold, mennyi élelmiszert kell ott hagyni a visszaútra: a tábor alatti szakaszok igényéből vond le az alatta már hagyott mennyiséget. ||
Hint 2: || A csúcsra menetnél a csúcs oda-vissza igénye a második tábortól kezdve minden tábor visszaútjához hozzátartozik, az elsőben nincs visszaút-igény. ||
Hint 3: || Egy tábor elérhetőségéhez a lefelé úton is ellenőrizni kell, hogy a hátizsák nem fogy ki, és a kapacitás korlátja mindkét irányban számít. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Felfelé menet: a táborok felvehető mennyiségei. summit = true esetén a csúcsig megyünk.
// reach: a legtávolabbi elérhető tábor (1-indexelt).
vector<long long> climb(int n, long long h, const vector<long long> &food, const vector<long long> &need,
                        bool summit, int &reach) {
    vector<long long> take;
    long long carry = 0, prefix = 0, leftSum = 0;
    reach = 1;
    for (int i = 0; i < n - 1; ++i) {
        long long extra = (summit && i >= 1) ? need[n - 2] : 0;
        long long keep = max(0LL, prefix + extra - leftSum);
        if (keep > food[i]) {
            reach = i;
            return take;
        }
        long long t = min(food[i] - keep, h - carry);
        take.push_back(t);
        leftSum += food[i] - t;
        carry += t;
        if (carry < need[i]) {
            reach = i + 1;
            return take;
        }
        carry -= need[i];
        prefix += need[i];
        reach = i + 2;
    }
    return take;
}

// Lefelé út ellenőrzése r-ből (1-indexelt). r == n esetén a csúcs oda-vissza már le van vonva.
bool descentOk(int n, long long h, const vector<long long> &food, const vector<long long> &need,
               const vector<long long> &take, int r) {
    if (r < n) {
        long long carry = 0;
        for (int j = 0; j < r - 1; ++j) carry += take[j] - need[j];
        long long c = min(h, carry + food[r - 1]);
        for (int j = r - 2; j >= 0; --j) {
            c -= need[j];
            if (c < 0) return false;
            if (j == 0) return true;
            c = min(h, c + food[j] - take[j]);
        }
        return true;
    }
    long long carry = 0;
    for (int j = 0; j < n - 1; ++j) carry += take[j] - need[j];
    if (carry < 0) return false;
    long long c = min(h, carry + food[n - 2] - take[n - 2]);
    for (int j = n - 3; j >= 0; --j) {
        c -= need[j];
        if (c < 0) return false;
        if (j == 0) return true;
        c = min(h, c + food[j] - take[j]);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long h;
    cin >> n >> h;
    vector<long long> food(n - 1), need(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> food[i] >> need[i];

    int reach = 0;
    vector<long long> take = climb(n, h, food, need, true, reach);
    if (reach == n && descentOk(n, h, food, need, take, n)) {
        cout << n << '\n';
        for (int i = 0; i < n - 1; ++i) cout << take[i] << (i + 1 < n - 1 ? ' ' : '\n');
        return 0;
    }

    take = climb(n, h, food, need, false, reach);
    for (int r = min(reach, n - 1); r >= 2; --r) {
        if (descentOk(n, h, food, need, take, r)) {
            cout << r << '\n';
            for (int i = 0; i < r - 1; ++i) cout << take[i] << (i + 1 < r - 1 ? ' ' : '\n');
            return 0;
        }
    }
    cout << 1 << '\n' << '\n';
    return 0;
}
