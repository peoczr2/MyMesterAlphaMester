/*
Megoldás lényege:
Az A=(a,b) szigetből 1 lépésben pontosan az északnyugati és a délkeleti negyed szigetei érhetők el; az elérhetetlenek egy jobb felső sarok (sor <= a, oszlop >= b) és egy bal alsó sarok (sor >= a, oszlop <= b) szigetei.
Ha a jobb felső elérhetetlen sarok éppen a T(P,Q) = {sor <= P, oszlop >= Q} téglalap, akkor egy y sziget ebből a következő lépésben akkor érhető el, ha van (már elért) sziget, amelynek oszlopa < Q és sora < y sora, vagy amelynek sora > P és oszlopa > y oszlopa.
Így az új elérhetetlen rész ismét ilyen sarok: T(min(P, a Q-nál kisebb oszlopú szigetek legkisebb sora), max(Q, a P-nél nagyobb sorú szigetek legnagyobb oszlopa)), és ez csak (P,Q)-tól függ, a kiinduló szigettől nem.
A távolságösszeg az egyes lépések után még el nem ért szigetek számának összege, ezért F(P,Q) = (szigetek száma T(P,Q)-ban) + F(következő sarok) a teljes 2500x2500-as rácson kiszámolható (sor szerint növekvő, oszlop szerint csökkenő sorrendben, mert a következő sarok sora nem nagyobb, oszlopa nem kisebb).
A bal alsó sarok ugyanez a sor és oszlop felcserélésével, ezért ugyanazt a függvényt hívjuk a felcserélt koordinátákra.
Az A szigetre a válasz (N-1) + (F(a,b)-1) + (F'(b,a)-1), ahol a -1 azért kell, mert A maga mindkét kezdő sarokban benne van.
Időigény: O(N + K^2), ahol K = 2500 a koordináták korlátja; memória kb. 75 MB.
*/
/*
Hint 1: || Egy lépés után mely szigetek maradnak elérhetetlenek? Rajzold le: a jobb felső és a bal alsó "sarok" szigetei. Nézd meg, hogy a következő lépés után is sarok alakú marad-e az elérhetetlen rész. ||
Hint 2: || A jobb felső {sor <= P, oszlop >= Q} sarokból a következő lépés után a {sor <= min(P, X), oszlop >= max(Q, Y)} sarok marad, ahol X a Q-nál kisebb oszlopú szigetek legkisebb sora, Y a P-nél nagyobb sorú szigetek legnagyobb oszlopa. Ez két egydimenziós tömbből adódik. ||
Hint 3: || A távolságok összege = sum_k (k lépés után még el nem ért szigetek száma). Ezért F(P,Q) = darab(P,Q) + F(következő sarok) dinamikus programozással kiszámolható az egész rácsra; a bal alsó sarokhoz cseréld fel a sorokat és az oszlopokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int K = 2500;  // a koordináták felső korlátja

// Minden szigetre visszaadja F(r, c)-t: lépésenként összeadva, hány sziget van még
// az elérhetetlen jobb felső sarokban (az első sarokban a kiinduló sziget is benne van).
vector<long long> cornerSums(const vector<int>& r, const vector<int>& c) {
    int n = r.size();
    // minRowLeft[q]: a q-nál kisebb oszlopú szigetek legkisebb sora (ha nincs: K+1)
    // maxColBelow[p]: a p-nél nagyobb sorú szigetek legnagyobb oszlopa (ha nincs: 0)
    vector<int> minRowLeft(K + 2, K + 1), maxColBelow(K + 2, 0);
    vector<vector<int>> cnt(K + 2, vector<int>(K + 2, 0));
    for (int i = 0; i < n; ++i) {
        minRowLeft[c[i] + 1] = min(minRowLeft[c[i] + 1], r[i]);
        maxColBelow[r[i] - 1] = max(maxColBelow[r[i] - 1], c[i]);
        cnt[r[i]][c[i]]++;
    }
    for (int q = 2; q <= K + 1; ++q) minRowLeft[q] = min(minRowLeft[q], minRowLeft[q - 1]);
    for (int p = K - 1; p >= 0; --p) maxColBelow[p] = max(maxColBelow[p], maxColBelow[p + 1]);

    // cnt[p][q]: szigetek száma a {sor <= p, oszlop >= q} sarokban
    // F[p][q] = cnt[p][q] + F[következő sarok]
    vector<vector<long long>> F(K + 2, vector<long long>(K + 2, 0));
    for (int p = 1; p <= K; ++p) {
        for (int q = K; q >= 1; --q) {
            cnt[p][q] += cnt[p - 1][q] + cnt[p][q + 1] - cnt[p - 1][q + 1];
            int np = min(p, minRowLeft[q]);
            int nq = max(q, maxColBelow[p]);
            F[p][q] = cnt[p][q];
            if (np != p || nq != q) F[p][q] += F[np][nq];
        }
    }

    vector<long long> res(n);
    for (int i = 0; i < n; ++i) res[i] = F[r[i]][c[i]];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) cin >> r[i] >> c[i];

    vector<long long> upRight = cornerSums(r, c);   // jobb felső sarok
    vector<long long> downLeft = cornerSums(c, r);  // bal alsó sarok (felcserélt koordinátákkal)

    for (int i = 0; i < n; ++i) cout << (n - 1) + (upRight[i] - 1) + (downLeft[i] - 1) << '\n';
    return 0;
}
