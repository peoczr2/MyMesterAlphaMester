/*
Megoldás lényege:
Egy tanuló annyi versenyen indult, ahányszor a sorszáma a versenyek indulóinak felsorolásában előfordul. A pontszámok és a minimumok ehhez nem kellenek, egy versenyen indulás már akkor is egy bejegyzés, ha a minimumot nem érte el. Ezért minden tanulóra egy számlálót tartunk nyilván, és minden bejegyzésnél növeljük a megfelelő számlálót. Végül azokat a tanulókat írjuk ki sorszám szerint növekvő sorrendben, akiknek a számlálója pontosan 1, az elején a darabszámmal. Az időigény az összes bejegyzés számával arányos, ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy tanuló annyi versenyen indult, ahányszor a sorszáma a versenyek indulói között szerepel. A pontszámok és a minimumok ehhez nem kellenek. ||
Hint 2: || Egy tömbben számold minden tanulóra a bejegyzéseket, majd válogasd ki azokat, ahol a szám pontosan 1. A kimenet elején a darabszám álljon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int minimum;  // ebben a feladatban nem kell
        cin >> minimum;
    }

    vector<int> count(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            count[s]++;
        }
    }

    vector<int> answer;
    for (int s = 1; s <= n; s++) {
        if (count[s] == 1) {
            answer.push_back(s);
        }
    }

    cout << answer.size();
    for (int s : answer) {
        cout << ' ' << s;
    }
    cout << '\n';
    return 0;
}
