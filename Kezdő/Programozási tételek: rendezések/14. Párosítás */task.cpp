/*
Megoldás lényege:
Mindkét csapat erősségét növekvő sorrendbe rendezzük az eredeti sorszámokkal együtt.
Ezután mohón párosítunk: a saját tagokat a gyengébbtől az erősebbek felé haladva mindig a még ki nem párosított legkisebb ellenféllel kötjük össze, ha a tag le tudja győzni; ha nem, a tag vesztes lesz.
A mohó választás optimális: a legkisebb ellenfelet a legkisebb, még legyőzni képes taggal érdemes legyőzni, így a nagyobb tagok később is meg tudják verni a maradék ellenfeleket.
A vesztes tagokat a maradék ellenfelekkel tetszőleges sorrendben párosítjuk, a kimenetben pedig az eredeti sorszámok szerepelnek.
A rendezés miatt az időigény O(N log N).
*/
/*
Hint 1: || Nem kell minden párosítást végignézni: rendezd mindkét csapatot erősség szerint, és gondold végig, melyik ellenfél a legkönnyebben legyőzhető. ||
Hint 2: || Haladj a gyengébb saját tagtól az erősebbek felé, és mindig a még ki nem párosított legkisebb ellenfelet nézd: ha a tag megveri, párosítsd, különben a tag vesztes lesz. ||
Hint 3: || A kimenet második sorában minden eredeti sorszámhoz a párját írd ki; a vesztes tagok maradék ellenfeleit tetszőleges sorrendben rendeld hozzájuk, így a sor továbbra is permutáció lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int &v : a) cin >> v;
    for (int &v : b) cin >> v;

    vector<int> ordA(n), ordB(n);
    iota(ordA.begin(), ordA.end(), 0);
    iota(ordB.begin(), ordB.end(), 0);
    sort(ordA.begin(), ordA.end(), [&](int x, int y) { return a[x] < a[y]; });
    sort(ordB.begin(), ordB.end(), [&](int x, int y) { return b[x] < b[y]; });

    vector<int> match(n, -1);   // saját tag -> ellenfél indexe
    vector<bool> used(n, false);
    int wins = 0, j = 0;        // j: a legkisebb még ki nem párosított ellenfél a ordB-ben
    for (int i : ordA) {
        if (j < n && a[i] > b[ordB[j]]) {
            match[i] = ordB[j];
            used[ordB[j]] = true;
            j++;
            wins++;
        }
    }

    // a vesztes tagok a maradék ellenfelekkel párosodnak
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (match[i] != -1) continue;
        while (used[ordB[k]]) k++;
        match[i] = ordB[k];
        used[ordB[k]] = true;
    }

    cout << wins << '\n';
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << match[i] + 1;
    }
    cout << '\n';
    return 0;
}
