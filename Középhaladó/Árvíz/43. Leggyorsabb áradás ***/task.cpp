/*
Megoldás lényege:
A mérési pontokhoz kiszámoljuk a készültségi fokot (0 = árvízmentes, 1, 2, 3 = az árvízvédelmi fokozat), majd a sorozatot maximális, azonos fokú folyószakaszokra bontjuk. Az árvízmentes (K) és a harmadfokú (M) szakaszokat egyszerűen összegyűjtjük és kiírjuk. Az áradás helyei a szakaszsorozatból az 1–2 fokú szakaszok elhagyásával kapott sorozat egymás utáni (árvízmentes, harmadfokú) párjai: ezek száma P, és a párok adják a P-s sort. A legközelebbi pár a legkisebb távolságú ilyen pár (az árvízmentes szakasz vége és a harmadfokú szakasz kezdete között); egyenlőség esetén a legkisebb sorszámú marad. Az egész egy bejárással, O(N) időben megoldható.
*/
/*
Hint 1: || Bontsd a mérési sort maximális, azonos készültségű szakaszokra, és ezekből számold meg az árvízmentes és a harmadfokú szakaszokat. ||
Hint 2: || Áradásnál az árvízmentes szakasz után a harmadfokú következik. Ha a szakaszsorozatból kihagyod az 1–2 fokú szakaszokat, a maradékban az egymás utáni (árvízmentes, harmadfokú) párok adják a keresett helyeket. ||
Hint 3: || Egy pár távolsága a harmadfokú szakasz kezdete mínusz az árvízmentes szakasz vége. Keresd ezek közül a legkisebbet, és egyenlőségnél az elsőt hagyd meg. ||
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

    // 1-2. sor: árvízmentes (K) és harmadfokú (M) szakaszok
    vector<Szakasz> mentes, harmad;
    for (const Szakasz &s : szakaszok) {
        if (s.fok == 0) mentes.push_back(s);
        if (s.fok == 3) harmad.push_back(s);
    }
    cout << mentes.size() << '\n';
    if (!mentes.empty()) kiir_szakaszok(mentes);
    cout << harmad.size() << '\n';
    if (!harmad.empty()) kiir_szakaszok(harmad);

    // 5-6. sor: áradás, vagyis árvízmentes szakasz utáni harmadfokú szakasz,
    // közbülső árvízmentes nélkül. A 0 és 3 fokú szakaszok szűrt sorozatában
    // ezek a szomszédos (0, 3) párok.
    vector<pair<Szakasz, Szakasz>> aradas;
    Szakasz elozo{-1, 0, 0};  // fok -1: még nincs előző szakasz
    for (const Szakasz &s : szakaszok) {
        if (s.fok != 0 && s.fok != 3) continue;
        if (elozo.fok == 0 && s.fok == 3) aradas.push_back({elozo, s});
        elozo = s;
    }
    cout << aradas.size() << '\n';
    if (!aradas.empty()) {
        for (size_t i = 0; i < aradas.size(); i++) {
            if (i) cout << ' ';
            cout << aradas[i].first.jobb << ' ' << aradas[i].second.bal;
        }
        cout << '\n';
    }

    // 7. sor: legközelebbi (árvízmentes, harmadfokú) pár, egyenlőségnél a legkisebb sorszámú
    int legjobb = -1;
    for (size_t i = 0; i < aradas.size(); i++) {
        int tav = aradas[i].second.bal - aradas[i].first.jobb;
        if (legjobb < 0 || tav < aradas[legjobb].second.bal - aradas[legjobb].first.jobb) legjobb = i;
    }
    if (legjobb >= 0) {
        const auto &p = aradas[legjobb];
        cout << p.first.bal << ' ' << p.first.jobb << ' ' << p.second.bal << ' ' << p.second.jobb << '\n';
    }
    return 0;
}
