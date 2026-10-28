/*
Megoldás lényege:
Minden feliratot egy IdozitettFelirat objektumban tárolunk, amelynek két szöveges adattagja van: az időzítés és a felirat szövege. A szavak számát úgy kapjuk, hogy a szöveget szóközök mentén egyesével kiolvassuk; a legtöbb szavas feliratot szigorúan nagyobb összehasonlítással keressük, így egyenlőség esetén a bemenetben előbb szereplő marad. Az időzítésből a négy számot úgy nyerjük ki, hogy a nem számjegy karakterek elválasztóként működnek; a kezdő és záró időpontot másodpercre váltjuk (perc * 60 + másodperc), majd óó:pp:mm alakban, vezető nullákkal írjuk ki. Az időigény a bemenet méretével arányos, a memóriaigény is.
*/
/*
Hint 1: || A szavak száma megegyezik a szóközökkel elválasztott részek számával, ezt istringstream-mel egyszerűen megszámolhatod. A legtöbb szavas felirat keresésénél csak szigorúan nagyobb értéknél frissíts, így egyenlőség esetén a korábbi marad. ||
Hint 2: || Az időzítésben az első szám a perc, a második a másodperc: a teljes másodperc-érték perc * 60 + másodperc; ebből az óra érték / 3600, a perc (érték % 3600) / 60, a másodperc érték % 60. ||
Hint 3: || A számokat úgy szedd ki, hogy a nem számjegy karaktereket (kettőspont, kötőjel, szóköz) szóközre cseréled, majd egész számokat olvasol be; a kiíráshoz a setw(2) és setfill('0') manipulátorok adják a vezető nullákat. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy felirat időzítése és szövege, mindkettő szövegként tárolva
class IdozitettFelirat {
public:
    IdozitettFelirat(const string &idozites, const string &szoveg)
        : idozites_(idozites), szoveg_(szoveg) {}

    // a szavak: a szóközökkel elválasztott, nem üres részek
    int SzavakSzama() const {
        istringstream be(szoveg_);
        string szo;
        int db = 0;
        while (be >> szo) {
            db++;
        }
        return db;
    }

    // "kp:kmp - vp:vmp" alakból "óó:pp:mm --> óó:pp:mm" alakot készít
    string SrtIdozites() const {
        vector<int> szamok = Szamok(idozites_);
        int kezdet = szamok[0] * 60 + szamok[1];
        int vege = szamok[2] * 60 + szamok[3];
        return Formaz(kezdet) + " --> " + Formaz(vege);
    }

    const string &Szoveg() const {
        return szoveg_;
    }

private:
    string idozites_;
    string szoveg_;

    // a nem számjegy karakterek elválasztóként működnek
    static vector<int> Szamok(string s) {
        for (char &ch : s) {
            if (!isdigit((unsigned char)ch)) {
                ch = ' ';
            }
        }
        istringstream be(s);
        vector<int> v;
        int x;
        while (be >> x) {
            v.push_back(x);
        }
        return v;
    }

    // másodpercből óó:pp:mm alak
    static string Formaz(int masodperc) {
        ostringstream ki;
        ki << setw(2) << setfill('0') << masodperc / 3600 << ":"
           << setw(2) << setfill('0') << (masodperc % 3600) / 60 << ":"
           << setw(2) << setfill('0') << masodperc % 60;
        return ki.str();
    }
};

// levágja a sor végi kocsi-vissza és szóköz karaktereket
static void LeVag(string &s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) {
        s.pop_back();
    }
}

int main() {
    int n;
    cin >> n;
    string maradek;
    getline(cin, maradek);  // az első sor hátralévő része

    vector<IdozitettFelirat> feliratok;
    for (int i = 0; i < n; i++) {
        string idozites;
        // az időzítés sora nem üres, az üres sorokat átugorjuk
        while (getline(cin, idozites)) {
            LeVag(idozites);
            if (!idozites.empty()) {
                break;
            }
        }
        string szoveg;
        getline(cin, szoveg);
        LeVag(szoveg);
        feliratok.emplace_back(idozites, szoveg);
    }

    // 1. részfeladat: a legtöbb szavas felirat szövege, egyenlőségnél az első
    int legtobb = -1;
    size_t legjobb = 0;
    for (size_t i = 0; i < feliratok.size(); i++) {
        int db = feliratok[i].SzavakSzama();
        if (db > legtobb) {
            legtobb = db;
            legjobb = i;
        }
    }
    cout << "#\n" << feliratok[legjobb].Szoveg() << "\n";

    // 2. részfeladat: a feliratok SRT formátumban
    cout << "#\n";
    for (size_t i = 0; i < feliratok.size(); i++) {
        cout << i + 1 << "\n"
             << feliratok[i].SrtIdozites() << "\n"
             << feliratok[i].Szoveg() << "\n\n";
    }
    return 0;
}
