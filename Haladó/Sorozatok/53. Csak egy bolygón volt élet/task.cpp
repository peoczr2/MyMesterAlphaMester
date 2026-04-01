/*
Megoldas lenyege:
Az eletszakaszokat felig nyitott [kezdet, veg+1) intervallumkent kezeljuk. Ha azonos
allapotban ket szomszedos evszakasz osszeer, akkor a felig nyitott alak ezt automatikusan
egybefuzi.

Kulonbsegterkepet epitunk: minden intervallum elejen +1, a vege utani pontban -1.
A rendezett esemenypontok kozott az aktiv bolygok szama allando. Azokbol a szakaszokbol,
ahol ez az ertek pontosan 1, visszaallitjuk a zart evintervallumokat, es az osszeero
darabokat osszefuzzuk.
*/
/*
Hint 1: || Az [l,r] intervallumot erdemes [l,r+1) alakban kezelni, mert igy konnyu sweeppel dolgozni. ||
Hint 2: || Ket szomszedos esemenypont kozott az aktiv bolygok szama nem valtozik. ||
Hint 3: || A vegso zart intervallum az [x, kovetkezo_pont-1] alakbol adodik. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void addInterval(map<long long, long long>& diff, long long left, long long right) {
    ++diff[left];
    --diff[right + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int aCount, bCount;
    cin >> aCount >> bCount;

    map<long long, long long> diff;
    for (int i = 0; i < aCount; ++i) {
        long long left, right;
        cin >> left >> right;
        addInterval(diff, left, right);
    }
    for (int i = 0; i < bCount; ++i) {
        long long left, right;
        cin >> left >> right;
        addInterval(diff, left, right);
    }

    vector<pair<long long, long long>> answer;
    long long active = 0;
    bool first = true;
    long long previousPoint = 0;

    for (auto [point, delta] : diff) {
        if (!first && active == 1 && previousPoint <= point - 1) {
            if (!answer.empty() && answer.back().second + 1 >= previousPoint) {
                answer.back().second = point - 1;
            } else {
                answer.push_back({previousPoint, point - 1});
            }
        }
        active += delta;
        previousPoint = point;
        first = false;
    }

    cout << answer.size() << '\n';
    for (auto [left, right] : answer) {
        cout << left << ' ' << right << '\n';
    }
    return 0;
}