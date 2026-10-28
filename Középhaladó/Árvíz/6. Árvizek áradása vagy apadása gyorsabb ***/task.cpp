/*
Megoldás lényege:
Minden mérést készültségi szintre alakítunk: 800 cm-ig a szint 0 (nincs árvíz), különben legalább 1.
Az árvizek a legfeljebb 0-nál nagyobb szintű mérések maximális, egymás utáni sorozatai, ezeket egyetlen balról jobbra haladó bejárással gyűjtjük ki.
Egy árvíz áradása a kezdetén álló szigorúan növekvő szakasz hossza, apadása a végén álló szigorúan csökkenő szakasz hossza; mindkettőt a két szélről indulva, egyesével bővítve kapjuk meg.
Az a gyorsabb, amelyiknek a hossza kisebb: ha az áradás, akkor 1, ha az apadás, akkor -1, egyenlőség esetén 0 a kiírt érték.
Minden árvízre egy-egy lineáris bejárás fut, így az összes munka O(N).
*/
/*
Hint 1: || Az árvíz kezdetén a szigorúan növekvő szakasz a bal szélről indul: amíg a következő mérés nagyobb az előzőnél, növeld a hosszt. ||
Hint 2: || Az apadás ugyanígy, de a jobb szélről visszafelé haladva: amíg az előző mérés nagyobb a következőnél, növeld a hosszt. Mindkét hosszt az árvíz határain belül számold. ||
Hint 3: || Hasonlítsd össze a két hosszt: ha az áradás hossza kisebb, írj 1-et, ha az apadásé kisebb, írj -1-et, különben 0-t. Az árvizek sorrendje a bemenet szerinti marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs árvíz, 1 = elsőfokú, 2 = másodfokú, 3 = harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

// Egy árvíz [bal, jobb] sorszámokkal (1-től indexelve)
struct Arviz {
    int bal, jobb;
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = szint(a[i]);
    }

    vector<Arviz> arvizek;
    int i = 1;
    while (i <= n) {
        if (s[i] == 0) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && s[j + 1] >= 1) j++;
        arvizek.push_back({i, j});
        i = j + 1;
    }

    int k = arvizek.size();
    cout << k << '\n';
    if (k == 0) return 0;

    for (int t = 0; t < k; t++) {
        if (t > 0) cout << ' ';
        cout << arvizek[t].bal << ' ' << arvizek[t].jobb;
    }
    cout << '\n';

    for (int t = 0; t < k; t++) {
        int bal = arvizek[t].bal, jobb = arvizek[t].jobb;

        // Áradás: a kezdő szigorúan növekvő szakasz hossza
        int aradas = 1;
        while (bal + aradas <= jobb && a[bal + aradas] > a[bal + aradas - 1]) aradas++;

        // Apadás: a záró szigorúan csökkenő szakasz hossza
        int apadas = 1;
        while (jobb - apadas >= bal && a[jobb - apadas] > a[jobb - apadas + 1]) apadas++;

        int eredmeny = 0;
        if (aradas < apadas) eredmeny = 1;
        else if (apadas < aradas) eredmeny = -1;

        if (t > 0) cout << ' ';
        cout << eredmeny;
    }
    cout << '\n';
    return 0;
}
