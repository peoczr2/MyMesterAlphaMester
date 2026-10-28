/*
Megoldás lényege:
Minden résztvevőt egyszer olvasunk be, és a pontszámát a maximális pontszámhoz képest hasonlítjuk össze a 90%, 80% és 70% küszöbökkel. A pontszám és a küszöb összevetését egész számokkal végezzük (100 * pont >= k * P), így nincs kerekítési hiba. A résztvevőket négy listába (I., II., III., nem díjazott) gyűjtjük a bemeneti sorrendben, majd minden listát a kért formában írunk ki: előbb az elemek száma, utána minden név pontosvesszővel lezárva. Üres lista esetén is a 0; sor kerül a kimenetbe. Az idő O(N).
*/
/*
Hint 1: || Egyszerre egy résztvevőt vizsgálj: a pontszámot a maximális pontszámhoz kell viszonyítani, és a 90%, 80%, 70% határokat a törtek helyett szorzással érdemes összehasonlítani. ||
Hint 2: || Négy külön listában gyűjtsd az eredményeket (I., II., III., nem díjazott), a bemeneti sorrendet megtartva, a sorokat pedig a pontosvessző mentén bontsd szét a névre és a pontszámra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    string line;
    getline(cin, line);  // az első sor maradéka

    vector<string> csoport[4];  // 0: I., 1: II., 2: III., 3: nem díjazott
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        size_t pos = line.find(';');
        string nev = line.substr(0, pos);
        int pont = stoi(line.substr(pos + 1));

        // pont >= k% * P  <=>  100 * pont >= k * P
        long long a = 100LL * pont;
        int idx;
        if (a >= 90LL * p) idx = 0;
        else if (a >= 80LL * p) idx = 1;
        else if (a >= 70LL * p) idx = 2;
        else idx = 3;
        csoport[idx].push_back(nev);
    }

    for (int c = 0; c < 4; c++) {
        cout << csoport[c].size() << ';';
        for (const string &nev : csoport[c]) cout << nev << ';';
        cout << '\n';
    }
    return 0;
}
