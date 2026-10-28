/*
Megoldás lényege:
Az N őrhely között N-1 fal van: az i. fal az i. és az (i+1). őrhely között húzódik. Egy fal akkor védett, ha mindkét végén van őrség, egyébként nem védett. Egy bejárásban számolom a folyamatos nem védett falakat: védett fal után a számláló nullázódik, nem védett fal esetén nő, és közben a maximumot tartom, ami a keresett hossz. Időigény O(N), memóriaigény O(N).
*/
/*
Hint 1: || Az őrhelyek szomszédos párjai között vannak a falak, így N őrhely N-1 falat jelent. Egy fal akkor védett, ha a két végén is van őrség. ||
Hint 2: || Egy bejárásban tartsd nyilván az aktuális, folytonos nem védett falakból álló szakasz hosszát: védett falnál nullázd, különben növeld, és közben a legnagyobb értéket jegyezd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> orseg(n);
    for (int i = 0; i < n; i++) cin >> orseg[i];

    int legHosszabb = 0, aktualis = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (orseg[i] == 1 && orseg[i + 1] == 1) {
            aktualis = 0;
        } else {
            aktualis++;
            legHosszabb = max(legHosszabb, aktualis);
        }
    }
    cout << legHosszabb << "\n";
    return 0;
}
