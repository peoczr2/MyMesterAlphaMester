/*
Megoldás lényege:
Az j. fal (az j. és a j+1. őrhely között) akkor őrzött, ha a j. vagy a j+1. őrhelyen van őrség. Ezt egyetlen balról jobbra haladó bejárásban ellenőrizzük.
Egy őrzött szakasz ott kezdődik, ahol egy nem őrzött fal után őrzött fal következik, illetve az 1. falnál, ha az őrzött. Elég ezeket a kezdeteket megszámolni.
Az időigény O(N), a tároláshoz egy N elemű logikai tömb kell.
*/
/*
Hint 1: || Az őrzött falakat az őrségek helyéből határozd meg: a j. fal őrzött, ha a j. vagy a j+1. őrhelyen van őrség. Az őrségek helyét egy logikai tömbben tárold. ||
Hint 2: || Az őrzött szakaszok száma megegyezik azzal, hányszor vált a fal állapota „nem őrzött” állapotról „őrzött” állapotra. A bejárás közben az előző fal állapotát jegyezd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> orseg(n + 2, false);
    for (int i = 0; i < m; i++) {
        int hely;
        cin >> hely;
        orseg[hely] = true;
    }
    int szakaszok = 0;
    bool elozo_orzott = false;
    for (int j = 1; j < n; j++) {
        bool orzott = orseg[j] || orseg[j + 1];
        if (orzott && !elozo_orzott) {
            szakaszok++;
        }
        elozo_orzott = orzott;
    }
    cout << szakaszok << endl;
    return 0;
}
