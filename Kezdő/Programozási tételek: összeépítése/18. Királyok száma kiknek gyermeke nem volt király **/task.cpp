/*
Megoldás lényege:
A királyok nevét halmazba tesszük, a szülő-gyerek párokból pedig két halmazt építünk: azokat a szülőket, akiknek van gyereke, és azokat, akiknek van olyan gyereke, aki király. Az uralkodási évek a kérdéshez nem kellenek. A válasz azoknak a királyoknak a száma, akik az első halmazban benne vannak, de a másodikban nincsenek. A nevek szóközt tartalmazhatnak, ezért soronként olvasunk, és az évszámok utáni maradékot tekintjük névnek. Az időigény O((N + M) log(N + M)), ami bőven elég.
*/
/*
Hint 1: || Két halmazt érdemes építeni: a szülőknek van-e egyáltalán gyereke, illetve van-e olyan gyerekük, aki királyként szerepel. A kérdés e két halmaz különbsége. ||
Hint 2: || A királyok nevét külön halmazban tartsd, így egy gyerekről egy keresés alatt eldönthető, hogy király-e. Az uralkodási évek a kérdéshez nem kellenek. ||
Hint 3: || A nevek szóközt is tartalmazhatnak (például „I. András”), ezért soronként olvass be, és az évszámok utáni teljes maradékot tekintsd névnek. ||
*/
#include <bits/stdc++.h>
using namespace std;

static string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static string kovetkezoSor() {
    string sor;
    while (getline(cin, sor)) {
        sor = trim(sor);
        if (!sor.empty()) return sor;
    }
    return "";
}

int main() {
    int n = stoi(kovetkezoSor());
    set<string> kiralyok;
    for (int i = 0; i < n; i++) {
        istringstream ss(kovetkezoSor());
        int kezdo, vege;
        ss >> kezdo >> vege;
        string nev;
        getline(ss, nev);
        kiralyok.insert(trim(nev));
    }

    int m = stoi(kovetkezoSor());
    set<string> vanGyereke, vanKiralyGyereke;
    for (int i = 0; i < m; i++) {
        string szulo = kovetkezoSor();
        string gyerek = kovetkezoSor();
        vanGyereke.insert(szulo);
        if (kiralyok.count(gyerek)) vanKiralyGyereke.insert(szulo);
    }

    int valasz = 0;
    for (const string &k : kiralyok)
        if (vanGyereke.count(k) && !vanKiralyGyereke.count(k)) valasz++;
    cout << valasz << "\n";
    return 0;
}
