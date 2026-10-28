/*
Megoldás lényege:
Az országneveket egy vektorban tároljuk, a rendezvényeket a beolvasás sorrendjében dolgozzuk fel. Egy menetes minimumkiválasztással megkeressük a legkisebb évszámot, és közben megjegyezzük a hozzá tartozó ország sorszámát. A mottó sort csak kiolvassuk és eldobjuk, különben a következő esemény adatai elcsúsznának. Ha a sorszám 0, az ország ismeretlen, ezért kérdőjelet írunk. Mivel minden év legfeljebb egyszer szerepel, nincs döntetlen. A bemenet harmadik része (évintervallum) nem befolyásolja az eredményt, ezért nem is olvassuk be. Az időigény O(N + R), a memóriaigény O(N).
*/
/*
Hint 1: || Csak a legkisebb évszámú rendezvényt kell megtalálni, ehhez elég egy minimumkiválasztás és az ország sorszámának megtartása. ||
Hint 2: || A nevek szóközt is tartalmazhatnak, ezért getline-nal olvasd őket. A rendezvények mottó sora üres is lehet, ezért azt is getline-nal olvasd ki, különben a következő évszám beolvasása elcsúszik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto readLine = []() {
        string s;
        getline(cin, s);
        while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) {
            s.pop_back();
        }
        return s;
    };

    int n;
    cin >> n;
    readLine();

    vector<string> countries(n);
    for (int i = 0; i < n; i++) {
        countries[i] = readLine();
    }

    int r;
    cin >> r;
    readLine();

    int bestYear = INT_MAX;
    int bestPlace = 0;
    for (int i = 0; i < r; i++) {
        int year, place;
        cin >> year >> place;
        readLine();
        readLine();

        if (year < bestYear) {
            bestYear = year;
            bestPlace = place;
        }
    }

    cout << bestYear << " ";
    if (bestPlace == 0) {
        cout << "?";
    } else {
        cout << countries[bestPlace - 1];
    }
    cout << "\n";

    return 0;
}
