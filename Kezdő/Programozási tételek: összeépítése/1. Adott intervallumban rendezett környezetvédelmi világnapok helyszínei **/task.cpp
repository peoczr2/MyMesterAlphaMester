/*
Megoldás lényege:
A nevek több szóból is állhatnak, és a mottó sor üres is lehet, ezért a bemenetet soronként olvassuk be: minden rendezvény pontosan három sor. Egy országot akkor jelölünk meg, ha legalább egy olyan rendezvénye van, amelynek évszáma a két adott év közé esik (a határokat is beleértve), és az ország sorszáma nem 0, vagyis nem anonim. A jelölés igaz/hamis értékű, így egy ország több találat esetén is csak egyszer kerül a kimenetbe. A kiíráskor a jelölt országokat a bemeneti sorrendben, vagyis sorszám szerint növekvő sorrendben soroljuk fel. Ha nincs jelölt ország, a válasz „0 NINCS”. Az időigény O(N + R), ami a legfeljebb 20 ország és 40 rendezvény mellett elhanyagolható.
*/
/*
Hint 1: || Nem kell a rendezvényeket külön tárolni: elég minden országhoz eldönteni, hogy volt-e legalább egy rendezvénye a megadott évtartományban. ||
Hint 2: || Tárolj egy igaz/hamis jelölőt minden ország sorszámához (1-től N-ig), és a rendezvényeket egyesével vizsgáld meg: az anonim (0) rendezvények ne jelöljenek senkit. A kiírás a jelölőkön végigmenve a bemeneti sorrendet adja. ||
Hint 3: || A bemenet soronként értelmezhető: a nevek több szóból állhatnak, a mottó üres is lehet, ezért minden rendezvénynél három sort kell beolvasni, a harmadikat (mottót) csak átugrani. A Windows-os sorvégi '\r' karaktert a sorok végéről érdemes levágni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy sort olvas be, a sorvégi '\r' karaktert eltávolítja.
string olvasSor() {
    string s;
    getline(cin, s);
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

int main() {
    int n = stoi(olvasSor());
    vector<string> orszag(n + 1);
    for (int i = 1; i <= n; i++) {
        orszag[i] = olvasSor();
    }

    int r = stoi(olvasSor());
    vector<int> ev(r), sorszam(r);
    for (int i = 0; i < r; i++) {
        ev[i] = stoi(olvasSor());
        sorszam[i] = stoi(olvasSor());
        olvasSor(); // a mottó, lehet üres: nem kell
    }

    stringstream ss(olvasSor());
    int ev1, ev2;
    ss >> ev1 >> ev2;

    vector<bool> volt(n + 1, false);
    for (int i = 0; i < r; i++) {
        if (sorszam[i] >= 1 && ev[i] >= ev1 && ev[i] <= ev2) {
            volt[sorszam[i]] = true;
        }
    }

    vector<string> nevek;
    for (int i = 1; i <= n; i++) {
        if (volt[i]) nevek.push_back(orszag[i]);
    }

    if (nevek.empty()) {
        cout << "0 NINCS" << endl;
        return 0;
    }
    cout << nevek.size();
    for (const string &nev : nevek) cout << " " << nev;
    cout << endl;
    return 0;
}
