/*
Megoldas lenyege:
Egy nyelv akkor jo, ha minden olyan diak sportcsoportja, aki ezt a nyelvet valasztotta,
csak az adott nyelv diakjaibol all. Ez a feltetel bitsetekkel gyorsan ellenorizheto:
mindegyik nyelvhez eltesszuk a hozza tartozo diakok halmazat, minden sporthoz pedig a sportot
valasztok halmazat. Egy nyelv akkor szamit jonak, ha a sajat diakjaihoz tartozo sporthalmazok
mindegyike benne van a nyelv halmazaban.
*/
/*
Hint 1: || A feltétel egy zártsági feltétel: minden bent lévő diák sportcsoportja is bent kell legyen. ||
Hint 2: || Egy sporthalmaz akkor van benne egy nyelvhalmazban, ha bitsetként a sport és a nyelv metszete megegyezik a sporthalmazzal. ||
Hint 3: || N és S csak 100, ezért a teljes ellenőrzés minden nyelvre simán belefér. ||
*/
#include <bits/stdc++.h>
using namespace std;

static constexpr int MAXD = 1005;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d, n, s;
    cin >> d >> n >> s;

    vector<bitset<MAXD>> lang(n), sport(s);
    vector<int> langOfStudent(d + 1), sportOfStudent(d + 1);

    for (int i = 0; i < n; ++i) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            int x;
            cin >> x;
            lang[i].set(x);
            langOfStudent[x] = i;
        }
    }

    for (int i = 0; i < s; ++i) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            int x;
            cin >> x;
            sport[i].set(x);
            sportOfStudent[x] = i;
        }
    }

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int student = 1; student <= d; ++student) {
            if (!lang[i].test(student)) continue;
            int sp = sportOfStudent[student];
            if ((sport[sp] & lang[i]) != sport[sp]) {
                ok = false;
                break;
            }
        }
        if (ok) ++answer;
    }

    cout << answer << '\n';
    return 0;
}
