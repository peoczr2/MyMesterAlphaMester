/*
Megoldás lényege:
Két különböző tolvajt kell összehasonlítani, ezért minden (i, j) párt megvizsgálunk úgy, hogy i < j, így minden pár pontosan egyszer kerül elő. Egy párnál megszámoljuk, hány adat egyezik a négy közül (magasság, szemszín, hajszín, büntetés). Ha legalább kettő egyezik, a válasz IGEN. A párok száma N(N-1)/2, ami N legfeljebb 100 esetén néhány ezer összehasonlítás, így az időigény O(N²), és bőven belefér a korlátba.
*/
/*
Hint 1: || Két különböző zsebtolvajt kell összehasonlítani, ezért minden (i, j) párt meg kell vizsgálni úgy, hogy i < j. Így minden pár pontosan egyszer kerül elő, és N legfeljebb 100, ezért a párok száma bőven belefér az időkorlátba. ||
Hint 2: || Egy párnál számold meg, hány adat egyezik a négyből: a magasságot, a szemszínt, a hajszínt és a büntetést külön-külön hasonlítsd össze. Ha az egyezések száma legalább 2, a válasz IGEN. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Tolvaj {
    int magassag;
    string szemszin;
    string hajszin;
    int buntetes;
};

int main() {
    int n;
    cin >> n;

    vector<Tolvaj> tolvajok(n);
    for (int i = 0; i < n; i++) {
        cin >> tolvajok[i].magassag >> tolvajok[i].szemszin
            >> tolvajok[i].hajszin >> tolvajok[i].buntetes;
    }

    bool van = false;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int egyezes = 0;
            if (tolvajok[i].magassag == tolvajok[j].magassag) {
                egyezes++;
            }
            if (tolvajok[i].szemszin == tolvajok[j].szemszin) {
                egyezes++;
            }
            if (tolvajok[i].hajszin == tolvajok[j].hajszin) {
                egyezes++;
            }
            if (tolvajok[i].buntetes == tolvajok[j].buntetes) {
                egyezes++;
            }
            if (egyezes >= 2) {
                van = true;
            }
        }
    }

    cout << (van ? "IGEN" : "NEM") << '\n';
    return 0;
}
