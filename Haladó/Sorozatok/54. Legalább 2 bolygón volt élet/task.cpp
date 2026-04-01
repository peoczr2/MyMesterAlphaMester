/*
Megoldas lenyege:
Ugyanazt a felig nyitott intervallumos sweepet hasznaljuk, mint a ket bolygos valtozatban,
csak most harom bolygo adja az esemenyeket, es azokat a reszeket keressuk, ahol legalabb
ketto aktiv egyszerre.

Minden [l,r] eletszakaszt [l,r+1) alakban veszunk fel egy kulonbsegterkepbe. Ket egymas
utani esemenypont kozott az aktiv bolygok szama allando. Ha ez legalabb 2, akkor a teljes
[pont, kovetkezo_pont-1] zart intervallum bekerul a valaszba, az osszeero darabokat pedig
egybefuzzuk.
*/
/*
Hint 1: || Itt is eleg az aktiv bolygok szamat kovetni egy sweep soran. ||
Hint 2: || A [l,r] intervallum helyett a [l,r+1) alak egyszerusiti a nyitas-zaras kezelest. ||
Hint 3: || Akkor kell kiirni egy reszt, ha a ket esemenypont kozotti allando ertek legalabb 2. ||
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

    int aCount, bCount, cCount;
    cin >> aCount >> bCount >> cCount;

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
    for (int i = 0; i < cCount; ++i) {
        long long left, right;
        cin >> left >> right;
        addInterval(diff, left, right);
    }

    vector<pair<long long, long long>> answer;
    long long active = 0;
    bool first = true;
    long long previousPoint = 0;

    for (auto [point, delta] : diff) {
        if (!first && active >= 2 && previousPoint <= point - 1) {
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