/*
Megoldás lényege:
A bemenet minden sora egy sportágat ír le: a pontosvessző előtti rész a sportág neve, utána 16 darab napi szám áll, amelyek július 28. és augusztus 12. között a döntők számát adják. A sort pontosvesszőnként daraboljuk, és a napokat 0-tól 15-ig indexeljük. Az atlétikai döntőket tartalmazó napok száma azoknak a napoknak a darabszáma, ahol az atlétika értéke pozitív; az úszás döntőinek száma az úszás sorának összege. A napi összesítőt egy 16 elemű tömbben gyűjtjük, így a legtöbb döntős nap és a július 29-i szám onnan olvasható ki. A legtöbb döntőt tartalmazó nap keresésekor csak a szigorúan nagyobb értéket fogadjuk el, így azonos számnál a korábbi nap marad. A nap értékét a hónap napjából kapjuk: a 0. indextől a 3. indexig 28 + index, utána index - 3. Az időigény és a memóriaigény is kicsi, lineáris a bemenet méretében.
*/
/*
Hint 1: || A sorok pontosvesszővel vannak elválasztva, a sportág neve a első mező. Darabold a sort pontosvesszőnként, és a számokat tárold egy tömbben a napok szerinti sorrendben. ||
Hint 2: || Térképezd fel az indexeket a napokra: a 0. index július 28., a 3. index július 31., a 4. index augusztus 1., a 15. index augusztus 12. Így a július 29. az 1. indexen van. ||
Hint 3: || Két külön összeg kell az atlétikának és az úszásnak, a többi sportág csak a napi összesítőbe és a teljes összegbe számít. A legtöbb döntős napot egy ciklussal keresd meg, és a 4. részfeladatnál az összes döntő a napi összesítők összege. ||
*/
#include <bits/stdc++.h>
using namespace std;

string sorVeg(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int NAP = 16; // 0: július 28., 3: július 31., 4: augusztus 1., 15: augusztus 12.
    vector<long long> napiOsszeg(NAP, 0);
    vector<long long> atletikaNapi(NAP, 0);
    long long uszasDontok = 0;
    long long osszes = 0;

    string sor;
    while (getline(cin, sor)) {
        sor = sorVeg(sor);
        if (sor.empty()) continue;

        size_t pos = sor.find(';');
        string sportag = sor.substr(0, pos);

        vector<long long> ertek;
        stringstream ss(sor.substr(pos + 1));
        string elem;
        while (getline(ss, elem, ';')) {
            if (!elem.empty()) ertek.push_back(stoll(elem));
        }

        for (int j = 0; j < NAP && j < (int)ertek.size(); j++) {
            napiOsszeg[j] += ertek[j];
            osszes += ertek[j];
            if (sportag == "atletika") atletikaNapi[j] += ertek[j];
            if (sportag == "uszas") uszasDontok += ertek[j];
        }
    }

    // 1. részfeladat: az atlétikai döntőt tartalmazó napok száma
    long long atletikaNapok = 0;
    for (int j = 0; j < NAP; j++) {
        if (atletikaNapi[j] > 0) atletikaNapok++;
    }
    cout << "#\n" << atletikaNapok << "\n";

    // 2. részfeladat: az úszás döntőinek száma
    cout << "#\n" << uszasDontok << "\n";

    // 3. részfeladat: a legtöbb döntőt tartalmazó nap értéke (a legkorábbi, ha több is van)
    int legjobbNap = 0;
    for (int j = 1; j < NAP; j++) {
        if (napiOsszeg[j] > napiOsszeg[legjobbNap]) legjobbNap = j;
    }
    int nap = (legjobbNap <= 3) ? 28 + legjobbNap : legjobbNap - 3;
    cout << "#\n" << nap << "\n";

    // 4. részfeladat: az összes döntő száma
    cout << "#\n" << osszes << "\n";

    // 5. részfeladat: a július 29-i döntők száma
    cout << "#\n" << napiOsszeg[1] << "\n";

    return 0;
}
