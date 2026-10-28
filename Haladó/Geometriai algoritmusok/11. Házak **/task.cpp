/*
Megoldás lényege:
A napfény balról-fentről, párhuzamos sugarakkal érkezik (DX,DY > 0), ezért minden sugár egyenese azonos
meredekségű: y + (DY/DX)*x értéke egy sugáron állandó (ez a sugár tengelymetszete). Egy ház akkor kap napot,
ha valamely pontján átmenő sugár nem metszi a tőle balra lévő házakat. Egy ház pontjai közül a legnagyobb
tengelymetszetet a jobb felső sarka adja, ezért elég ezt vizsgálni: a ház akkor napos, ha jobb felső sarkának
tengelymetszete nagyobb, mint az eddigi házak legnagyobb tengelymetszete. Az egyenlőség csak érintés, ezért
szigorú > kell. Az összehasonlítást DX-szel szorozva egész számokkal végezzük, így nincs lebegőpontos hiba.

Idő: O(N).
*/
/*
Hint 1: || Minden sugár párhuzamos, ezért egy sugarat egyetlen szám jellemez: az a magasság, ahol az
y-tengelyt metszi (a sugár egyenesének tengelymetszete). Egy ház napos, ha van olyan pontja, amelyen átmenő
sugár nem akad el a balra lévő házakon. ||
Hint 2: || Melyik pontja a legkitettebb? Az y + (DY/DX)*x tengelymetszet a jobb felső sarokban a legnagyobb.
Haladj balról jobbra, tartsd nyilván az eddigi legnagyobb tengelymetszetet, és csak a szigorúan nagyobb
értékű házak lesznek naposak. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long DX, DY;
    if (!(cin >> N >> DX >> DY)) return 0;

    // h + (DY/DX)*r > best  <=>  h*DX + DY*r > best*DX  (DX > 0), ezért a tárolt érték már DX-szeresen szerepel.
    long long bestScaled = LLONG_MIN;
    vector<int> sunny;
    sunny.reserve(N);

    for (int i = 1; i <= N; ++i) {
        long long x, w, h;
        cin >> x >> w >> h;
        long long r = x + w;  // a jobb felső sarok x-koordinátája
        long long val = h * DX + DY * r;
        if (val > bestScaled) {
            sunny.push_back(i);
            bestScaled = val;
        }
    }

    cout << sunny.size() << '\n';
    for (int i = 0; i < (int)sunny.size(); ++i) {
        if (i) cout << ' ';
        cout << sunny[i];
    }
    cout << '\n';

    return 0;
}
