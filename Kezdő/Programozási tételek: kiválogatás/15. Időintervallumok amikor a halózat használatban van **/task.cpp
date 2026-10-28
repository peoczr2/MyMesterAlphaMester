/*
Megoldás lényege:
Minden felhasználóhoz nyilvántartjuk, hogy éppen be van-e jelentkezve, és ha igen, mikor jelentkezett be. A figyelmen kívül hagyott műveletek (már bent lévő felhasználó újabb BE-je, már kint lévő KI-ja) nem változtatják az állapotot. Ha valakinek az első művelete KI, akkor az előző napról még bent volt, ezért a szakasza 0:00-tól a kijelentkezésig tart; a nap végéig bent maradó felhasználó a nap végéig aktív. Egy bejelentkezés–kijelentkezés szakaszt a [BE perce, KI perce) félnyílt intervallumként kezelünk, így az egymáshoz pontosan csatlakozó szakaszok összeolvadnak. A szakaszokat egy különbségi tömbbel (a kezdő percnél +1, a záró percnél -1) és prefixösszeggel rögzítjük percenként, majd a legalább 1 aktív felhasználót tartalmazó összefüggő percblokkok adják az intervallumokat. Az időigény O(N + 1440), ami bőven elég.
*/
/*
Hint 1: || Minden felhasználónál elég az állapotot követni: bent van-e, és ha igen, mióta. A figyelmen kívül hagyott műveletek nem változtatnak az állapoton. ||
Hint 2: || Ha egy felhasználó első művelete KI, akkor a szakasza a nap 0:00 órájától a kijelentkezésig tart. A szakaszokat percekre bontva (0-tól 1439-ig) tudjuk, melyik percben hány felhasználó van bent. ||
Hint 3: || Egy 1441 elemű különbségi tömb segít: egy szakasz kezdő percénél növeld 1-gyel, a záró percénél csökkentsd 1-gyel, majd a prefixösszeg adja az aktív felhasználók számát percenként. A nullánál nagyobb percek összefüggő blokkjai az intervallumok. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int NAP = 24 * 60;

int main() {
    int n;
    cin >> n;

    // felhasználónként: bent van-e, és ha igen, mikortól (perc)
    map<string, pair<bool, int>> allapot;
    // különbségi tömb: a szakaszok kezdő percénél +1, záró percénél -1
    vector<int> kulonbseg(NAP + 1, 0);

    auto szakasz = [&](int kezdet, int vege) {
        if (kezdet < vege) {
            kulonbseg[kezdet]++;
            kulonbseg[vege]--;
        }
    };

    for (int i = 0; i < n; i++) {
        string muvelet, azonosito;
        int ora, perc;
        cin >> muvelet >> azonosito >> ora >> perc;
        int ido = ora * 60 + perc;
        bool be = (muvelet == "BE");

        auto it = allapot.find(azonosito);
        if (it == allapot.end()) {
            if (be) {
                allapot[azonosito] = {true, ido};
            } else {
                // az előző napról még bent volt
                szakasz(0, ido);
                allapot[azonosito] = {false, 0};
            }
            continue;
        }

        bool bent = it->second.first;
        int kezdet = it->second.second;
        if (be && !bent) {
            it->second = {true, ido};
        } else if (!be && bent) {
            szakasz(kezdet, ido);
            it->second = {false, 0};
        }
    }

    // a nap végéig bent maradók
    for (const auto &p : allapot) {
        if (p.second.first) {
            szakasz(p.second.second, NAP);
        }
    }

    // összefüggő blokkok keresése a percek mentén
    vector<pair<int, int>> intervallumok; // [kezdet, vég) percek
    int aktiv = 0;
    int kezdet = -1;
    for (int p = 0; p < NAP; p++) {
        aktiv += kulonbseg[p];
        if (aktiv > 0 && kezdet < 0) {
            kezdet = p;
        } else if (aktiv == 0 && kezdet >= 0) {
            intervallumok.push_back({kezdet, p});
            kezdet = -1;
        }
    }
    if (kezdet >= 0) {
        intervallumok.push_back({kezdet, NAP});
    }

    cout << intervallumok.size();
    for (auto [a, b] : intervallumok) {
        int vege = min(b, NAP - 1); // a nap utolsó perce 23:59
        cout << " " << a / 60 << " " << a % 60 << " " << vege / 60 << " " << vege % 60;
    }
    cout << "\n";
    return 0;
}
