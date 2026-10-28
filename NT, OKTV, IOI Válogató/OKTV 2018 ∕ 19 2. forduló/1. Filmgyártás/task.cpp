/*
Megoldás lényege:
Egy rendezvényen legfeljebb egy film készül, ezért a maximális filmszám azoknak a rendezvényeknek a száma, amelyekre legalább egy filmes munkaideje rámutat. Minden felfogadott filmesért egyszer A forint jár, a munkanapokért pedig filmenként B forint, így a költség A·(felfogadott filmesek száma) + B·(filmek száma) alakú, a B-s tag a filmszámtól függ, az A-s tag a felfogadott filmesek számától, ezért a filmesek számát kell minimalizálni.
A felfogadott filmesek minimális száma intervallumokkal való pontlefedés, amelyet mohón oldunk meg: a rendezvényeket növekvő sorrendben nézzük, és az első még nem lefedett rendezvényhez a rá eső filmesek közül azt választjuk, akinek a munkaideje a legkésőbb ér véget. Ez a választás optimális, mert a lehető legtovább fedi a későbbi rendezvényeket is.
Az időigény O(K·F), ami K ≤ 1000 és F ≤ 10 000 mellett bőven belefér az időkorlátba.
*/
/*
Hint 1: || Két szempontot külön kezelj: a maximális filmszám csak azoktól a rendezvényektől függ, amelyekre van szabad filmes, a minimális költségben pedig az A forint a felfogadott filmesek számával, a B forint a készült filmek számával arányos. ||
Hint 2: || Ez pontok lefedése szakaszokkal: a rendezvények a pontok, a filmesek munkaideje a szakaszok. Minden lefedhető rendezvényt olyan filmessel kell lefedni, akinek a szakasza tartalmazza a rendezvény napját. ||
Hint 3: || Rendezd a rendezvényeket növekvő sorrendbe, és az első lefedetlen rendezvénynél válaszd azt a rá eső filmest, akinek a munkaideje a legkésőbb ér véget. Az eddig lefedett szakasz végét egyetlen változóban tárold, és az ezen belül eső rendezvényeket ne számold újra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, k, f, a, b;
    cin >> n >> k >> f >> a >> b;

    vector<long long> r(k);
    for (auto &x : r) cin >> x;

    vector<pair<long long, long long>> iv(f);
    for (auto &p : iv) cin >> p.first >> p.second;

    // Azok a rendezvények, amelyekre van legalább egy szabad filmes.
    vector<long long> pts;
    for (long long d : r) {
        for (auto &p : iv) {
            if (p.first <= d && d <= p.second) {
                pts.push_back(d);
                break;
            }
        }
    }

    // Mohó pontlefedés: a legkésőbb záródó, rá eső intervallumot választjuk.
    long long hired = 0;
    long long coveredUntil = -1;
    for (long long d : pts) {
        if (d <= coveredUntil) continue;
        long long best = -1;
        for (auto &p : iv) {
            if (p.first <= d && d <= p.second) best = max(best, p.second);
        }
        hired++;
        coveredUntil = best;
    }

    long long films = pts.size();
    long long cost = a * hired + b * films;
    cout << films << "\n" << cost << "\n";
    return 0;
}
