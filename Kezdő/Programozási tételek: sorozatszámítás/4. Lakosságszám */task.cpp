/*
Megoldás lényege:
A települések adatait egyesével olvassuk be. A megye nevét kulcsként használva egy map tárolja a megyénkénti lakosságot, az ország összlakossága pedig külön összegben gyűlik. A megyék nevét egy vektorban tároljuk abban a sorrendben, ahogy először előfordulnak, így a kiírás a bemenet megjelenési sorrendjét követi.
Az időigény O(N log N), ami N ≤ 1000 esetén bőven elég.
*/
/*
Hint 1: || Minden megyéhez egy összeget kell tartani: a település nevéből nem kell semmit kiolvasni, a megye neve dönti el, melyik összeghez adod a lakosságot. Melyik adatszerkezet adja gyorsan a megye nevéhez tartozó összeget? ||
Hint 2: || Egy map<string, long long> a megye nevéhez rendelje a lakosságot. A kiírás sorrendjéhez egy vektorban tárold a megyék neveit abban a sorrendben, ahogy először előfordulnak, és az ország összlakosságát külön változóban számold. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> megyek;
    map<string, long long> lakossag;
    long long osszes = 0;

    for (int i = 0; i < n; i++) {
        string megye, telepules;
        long long lakos;
        cin >> megye >> telepules >> lakos;
        if (lakossag.find(megye) == lakossag.end()) {
            megyek.push_back(megye);
            lakossag[megye] = 0;
        }
        lakossag[megye] += lakos;
        osszes += lakos;
    }

    cout << megyek.size() << "\n";
    for (const string &megye : megyek) {
        cout << megye << " " << lakossag[megye] << "\n";
    }
    cout << osszes << "\n";
    return 0;
}
