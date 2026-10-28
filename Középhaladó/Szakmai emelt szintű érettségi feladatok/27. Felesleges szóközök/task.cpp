/*
Megoldás lényege:
Soronként haladunk balról jobbra, és egy szóközt csak akkor írunk ki, ha az előtte álló
karakter nem szóköz, így egy szóközsorozatból az első marad meg. A sor eleji szóközök nem
feleslegesek, ezért ezeket változatlanul megtartjuk; a sorvégi szóközöket levágjuk. A csak
szóközökből álló sor üres lesz. Az időigény a bemenet méretével arányos, O(N·K).
*/
/*
Hint 1: || Egy sort elég egyszer balról jobbra végigjárni: egy szóközt akkor hagyj meg, ha az előtte lévő karakter nem szóköz (a sor eleji szóközöket külön kezeld). ||
Hint 2: || A sor elején álló szóközök maradnak, a sor végén maradt szóközöket a kiírás előtt vágd le; a getline-nal beolvasott sorból a Windows-os \r karaktert távolítsd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy sor feldolgozása: a felesleges szóközök eltávolítása
string tisztit(const string& sor) {
    size_t elso = sor.find_first_not_of(' ');
    if (elso == string::npos)
        return ""; // csak szóközökből áll: üres sor lesz

    string eredmeny = sor.substr(0, elso); // a sor eleji szóközök megmaradnak
    for (size_t i = elso; i < sor.size(); i++) {
        if (sor[i] == ' ' && sor[i - 1] == ' ')
            continue; // ismétlődő szóköz: kihagyjuk
        eredmeny += sor[i];
    }

    while (!eredmeny.empty() && eredmeny.back() == ' ')
        eredmeny.pop_back(); // sorvégi szóközök
    return eredmeny;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string sor;
    getline(cin, sor); // az első sor maradékának eldobása

    for (int i = 0; i < n; i++) {
        getline(cin, sor);
        if (!sor.empty() && sor.back() == '\r')
            sor.pop_back();
        cout << tisztit(sor) << "\n";
    }
    return 0;
}
