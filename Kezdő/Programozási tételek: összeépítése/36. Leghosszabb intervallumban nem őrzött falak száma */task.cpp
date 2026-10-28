/*
Megoldás lényege:
Az N őrhely között N-1 fal van: az i. fal az i. és az (i+1). őrhely között húzódik. Egy fal akkor őrzött, ha legalább az egyik végén van őrség; nem őrzött, ha mindkét végén nincs. Egy bejárásban számolom a folyamatos nem őrzött falakat: őrzött fal után a számláló nullázódik, nem őrzött fal esetén nő, és közben a maximumot tartom, ami a keresett hossz. Időigény O(N), memóriaigény O(N).
*/
/*
Hint 1: || Az őrhelyek szomszédos párjai között vannak a falak. Egy fal akkor nem őrzött, ha a két végén egyaránt nincs őrség. ||
Hint 2: || Egy bejárásban tartsd nyilván az aktuális, folytonos nem őrzött falakból álló szakasz hosszát: őrzött falnál nullázd, különben növeld, és közben a legnagyobb értéket jegyezd meg. ||
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
        if (orseg[i] == 0 && orseg[i + 1] == 0) {
            aktualis++;
            legHosszabb = max(legHosszabb, aktualis);
        } else {
            aktualis = 0;
        }
    }
    cout << legHosszabb << "\n";
    return 0;
}
