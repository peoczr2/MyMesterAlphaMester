/*
Megoldás lényege:
A mérési pontokhoz kiszámoljuk a készültségi fokot (0 = árvízmentes, 1, 2, 3 = az árvízvédelmi fokozat), majd a sorozatot maximális, azonos fokú folyószakaszokra bontjuk. A harmadfokú (K) és az árvízmentes (M) szakaszokat egyszerűen összegyűjtjük és kiírjuk. Az apadás helyei a szakaszsorozatból az 1–2 fokú szakaszok elhagyásával kapott sorozat egymás utáni (harmadfokú, árvízmentes) párjai: ezek száma P, és a párok adják a P-s sort. A legközelebbi pár a legkisebb távolságú ilyen pár (a harmadfokú szakasz vége és az árvízmentes szakasz kezdete között); egyenlőség esetén az első, legkisebb sorszámú marad. Az egész egy bejárással, O(N) időben megoldható.
*/
/*
Hint 1: || Bontsd a mérési sort maximális, azonos készültségű szakaszokra, és gondold át, melyek kellenek a kérdésekhez: a harmadfokúak és az árvízmentesek. ||
Hint 2: || Az apadáshoz csak az egymás után álló (harmadfokú, árvízmentes) párok kellenek. Ha a szakaszsorozatból kihagyod az 1–2 fokú szakaszokat, a maradékban az egymás utáni párok adják az apadási helyeket. ||
Hint 3: || Egy pár távolsága az árvízmentes szakasz kezdete mínusz a harmadfokú szakasz vége. Ezt számold minden párra, és tartsd meg a legkisebbet úgy, hogy egyenlőségnél az elsőt hagyod meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// készültség: 0 = árvízmentes, 1, 2, 3 = az árvízvédelmi fokozat
int keszultseg(int a) {
    if (a <= 800) return 0;
    if (a <= 900) return 1;
    if (a <= 1000) return 2;
    return 3;
}

struct Szakasz {
    int fok, bal, jobb;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> fok(n + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        fok[i] = keszultseg(a);
    }

    // folyószakaszok: maximális, egymás melletti azonos fokú sorozatok
    vector<Szakasz> szakaszok;
    for (int i = 1; i <= n;) {
        int j = i;
        while (j < n && fok[j + 1] == fok[i]) j++;
        szakaszok.push_back({fok[i], i, j});
        i = j + 1;
    }

    // a szakaszok kezdetét és végét egy sorba írja
    auto kiir_szakaszok = [](const vector<Szakasz> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i) cout << ' ';
            cout << v[i].bal << ' ' << v[i].jobb;
        }
        cout << '\n';
    };

    // 1-2. sor: harmadfokú (K) és árvízmentes (M) szakaszok
    vector<Szakasz> harmad, mentes;
    for (const Szakasz &s : szakaszok) {
        if (s.fok == 3) harmad.push_back(s);
        if (s.fok == 0) mentes.push_back(s);
    }
    cout << harmad.size() << '\n';
    if (!harmad.empty()) kiir_szakaszok(harmad);
    cout << mentes.size() << '\n';
    if (!mentes.empty()) kiir_szakaszok(mentes);

    // 3-6. sor: apadás, vagyis harmadfokú szakasz utáni árvízmentes szakasz,
    // közbülső harmadfokú nélkül. A 0 és 3 fokú szakaszok szűrt sorozatában
    // ezek a szomszédos (3, 0) párok.
    vector<pair<Szakasz, Szakasz>> apadas;
    Szakasz elozo{-1, 0, 0};  // fok -1: még nincs előző szakasz
    for (const Szakasz &s : szakaszok) {
        if (s.fok != 0 && s.fok != 3) continue;
        if (elozo.fok == 3 && s.fok == 0) apadas.push_back({elozo, s});
        elozo = s;
    }
    cout << apadas.size() << '\n';
    if (!apadas.empty()) {
        for (size_t i = 0; i < apadas.size(); i++) {
            if (i) cout << ' ';
            cout << apadas[i].first.jobb << ' ' << apadas[i].second.bal;
        }
        cout << '\n';
    }

    // 7. sor: legközelebbi (harmadfokú, árvízmentes) pár, egyenlőségnél az első
    int legjobb = -1;
    for (size_t i = 0; i < apadas.size(); i++) {
        int tav = apadas[i].second.bal - apadas[i].first.jobb;
        if (legjobb < 0 || tav < apadas[legjobb].second.bal - apadas[legjobb].first.jobb) legjobb = i;
    }
    if (legjobb >= 0) {
        const auto &p = apadas[legjobb];
        cout << p.first.bal << ' ' << p.first.jobb << ' ' << p.second.bal << ' ' << p.second.jobb << '\n';
    }
    return 0;
}
