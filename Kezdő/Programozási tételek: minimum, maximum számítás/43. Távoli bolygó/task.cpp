/*
Megoldás lényege:
Egy ember a születési és a halálozási óráján is élőnek számít, vagyis a [Si, Hi] zárt intervallumban él. Az élők száma csak a születések és halálozások óráin változik, ezért különbségtömböt használunk: a Si órához +1-et, a Hi+1 órához −1-et írunk. A prefix összeggel minden órára megkapjuk az élők számát, egy menetben kiválasztjuk a maximumot és megszámoljuk, hány órában fordul elő. Az időigény O(N + T), ahol T = 1 000 000 az órák száma; a memóriaigény O(T).
*/
/*
Hint 1: || Nem kell minden emberre minden órát végigvizsgálni: az élők száma csak a születések és halálozások óráin változik, ezért elég ezeket az eseményeket rögzíteni. ||
Hint 2: || Használj különbségtömböt: a születés órájánál növeld az értéket eggyel, a halálozás órája utáni órához pedig csökkentsd eggyel. A prefix összeg minden órában megadja az élők számát. ||
Hint 3: || Egy végigfutással a maximumot és az azt elérő órák számát is megkapod. Nagyobb maximumnál a számlálót állítsd 1-re, egyenlő maximumnál növeld eggyel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAX_HOUR = 1000000;

    int n;
    cin >> n;

    vector<int> diff(MAX_HOUR + 2, 0);
    for (int i = 0; i < n; i++) {
        int born, died;
        cin >> born >> died;
        diff[born]++;
        diff[died + 1]--;
    }

    int alive = 0, best = 0, hours = 0;
    for (int t = 0; t <= MAX_HOUR; t++) {
        alive += diff[t];
        if (alive > best) {
            best = alive;
            hours = 1;
        } else if (alive == best) {
            hours++;
        }
    }

    cout << best << "\n" << hours << "\n";
    return 0;
}
