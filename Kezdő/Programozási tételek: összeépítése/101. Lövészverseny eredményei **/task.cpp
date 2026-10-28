/*
Megoldás lényege:
A négy kérdést a versenyzők sorrendjében, egy-egy bejárással oldjuk meg. Az A részhez minden versenyzőnél végignézzük az előtte állókat, és megszámoljuk azokat, akiknek az eredménye szigorúan nagyobb; az azonos eredmény nem számít jobbnak. A B és C részhez futó maximumot, illetve futó minimumot tartunk nyilván: egy versenyző akkor állt az első helyen, ha az eredménye legalább akkora, mint az addigi legjobb, és az utolsó helyen, ha legfeljebb akkora, mint az addigi legrosszabb. A holtversenyeket mindhárom helyen figyelembe vesszük, a minta is így várja. A D részhez a végső maximummal egyező eredményű versenyzők sorszámait írjuk ki. Mivel N legfeljebb 1000, az A rész O(N^2) lépése, vagyis kb. félmillió összehasonlítás, az időlimitbe belefér.
*/
/*
Hint 1: || A B, C és D rész egyetlen bejárásból is megkapható, ha közben az addigi legjobb és legrosszabb eredményt követed. Az A részhez viszont minden versenyzőnél az előtte állókat kell megnézni. ||
Hint 2: || Egy versenyző az első helyen állt, ha az eredménye nem kisebb az addigi maximumnál, és az utolsó helyen állt, ha nem nagyobb az addigi minimumnál. Holtverseny esetén mindkét versenyző megkapja a helyezést. ||
Hint 3: || Az A részhez minden i-edik versenyzőnél számold meg a 0..i-1 indexű versenyzők közül a nála szigorúan jobb eredményűeket. Az N ≤ 1000 miatt ez mintegy 500 000 összehasonlítás, ami belefér az időlimitbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy sort kiír: a számokat szóközzel választja el, a sor végén újsor áll.
void kiir(const vector<int> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<int> eredmeny(n);
    for (int &x : eredmeny) cin >> x;

    // A. minden versenyzőre: az előtte állók közül hányan értek el nála jobbat
    vector<int> jobb(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (eredmeny[j] > eredmeny[i]) jobb[i]++;
        }
    }

    // B. és C. futó maximum és minimum alapján, D. a végső maximum
    vector<int> elso, utolso, gyoztes;
    int legjobb = eredmeny[0], legrosszabb = eredmeny[0];
    for (int i = 0; i < n; i++) {
        if (eredmeny[i] >= legjobb) elso.push_back(i + 1);
        if (eredmeny[i] <= legrosszabb) utolso.push_back(i + 1);
        legjobb = max(legjobb, eredmeny[i]);
        legrosszabb = min(legrosszabb, eredmeny[i]);
    }
    for (int i = 0; i < n; i++) {
        if (eredmeny[i] == legjobb) gyoztes.push_back(i + 1);
    }

    kiir(jobb);
    kiir(elso);
    kiir(utolso);
    kiir(gyoztes);
    return 0;
}
