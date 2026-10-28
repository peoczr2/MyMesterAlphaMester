/*
Megoldás lényege:
A rendezett sorban a célszínek blokkokban állnak: az első cnt[1] pozíción 1-es, a következő cnt[2] pozíción 2-es, és így tovább.
Egy pozíciót akkor tekintünk rossznak, ha a benne lévő szín nem egyezik a célszínnel; minden rossz konténert pontosan egyszer kell átpakolni.
A rossz pozíciókból színek közötti élek adódnak (cél szín → konténer szín), és minden összefüggő komponens egy zárt bejárással oldható meg, amelyhez a szabad hely egyszeri bevonása kell, azaz komponensenként +1 lépés.
A válasz tehát a rossz pozíciók száma plusz az élekkel rendelkező komponensek száma, amit DSU-val határozunk meg; az idő O(N).
*/
/*
Hint 1: || Először állapítsd meg, melyik pozíción melyik színnek kellene állnia a rendezett sorban, és számold meg, hány pozíción tér el a tényleges szín. ||
Hint 2: || Egy rossz pozíciójú konténert közvetlenül a céljába csak akkor tudsz tenni, ha a cél pozíció szabad; a zárt körforgásokhoz a szabad hely kell, ami körönként egy plusz lépést jelent. ||
Hint 3: || Tekintsd a színeket csúcsoknak, és minden rossz pozíciót egy élnek a cél színből a konténer színébe; az összefüggő komponensek száma adja az extra lépések számát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int parent_[5];

int findRoot(int x) {
    while (parent_[x] != x) {
        parent_[x] = parent_[parent_[x]];
        x = parent_[x];
    }
    return x;
}

int main() {
    int n;
    cin >> n;
    vector<int> c(n);
    int cnt[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        cnt[c[i]]++;
    }

    vector<int> target;
    for (int col = 1; col <= 4; col++)
        for (int k = 0; k < cnt[col]; k++) target.push_back(col);

    for (int i = 0; i < 5; i++) parent_[i] = i;
    bool used[5] = {false, false, false, false, false};
    long long moves = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] != target[i]) {
            moves++;
            used[target[i]] = used[c[i]] = true;
            parent_[findRoot(target[i])] = findRoot(c[i]);
        }
    }

    int comps = 0;
    for (int col = 1; col <= 4; col++)
        if (used[col] && findRoot(col) == col) comps++;

    cout << moves + comps << '\n';
    return 0;
}
