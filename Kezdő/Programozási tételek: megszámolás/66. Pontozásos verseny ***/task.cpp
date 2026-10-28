/*
Megoldás lényege:
Sorban haladva minden versenyzőnél azt kell megszámolni, hány korábbi versenyző pontszáma volt kisebb az övénél. Mivel a pontszámok 1 és 100 közötti egész számok, egy 101 elemű gyakorisági tömbben nyilvántartjuk, hány versenyző kapott eddig az egyes pontszámokat. Egy új versenyzőnél a tömbben az övénél kisebb pontszámok darabszámait összegezzük, majd a saját pontszámát beírjuk a tömbbe. Az időigény O(N·100), a memóriaigény O(100).
*/
/*
Hint 1: || Minden versenyzőnél a korábbi versenyzők közül azokat kell megszámolni, akiknek kisebb pontszámuk volt, mint neki. Ezért a sorozatot balról jobbra haladva dolgozd fel, és közben tartsd nyilván, ki mennyit kapott. ||
Hint 2: || A pontszámok 1 és 100 közötti egészek, ezért tárolj egy gyakorisági tömböt: cnt[p] megmutatja, hány korábbi versenyző kapott p pontot. Egy új P pontszámnál a válasz cnt[1] + cnt[2] + … + cnt[P − 1]. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> gyakori(101, 0);  // gyakori[p]: hány korábbi versenyző kapott p pontot
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        int kisebb = 0;
        for (int q = 1; q < p; q++)
            kisebb += gyakori[q];
        cout << kisebb << "\n";
        gyakori[p]++;
    }
    return 0;
}
