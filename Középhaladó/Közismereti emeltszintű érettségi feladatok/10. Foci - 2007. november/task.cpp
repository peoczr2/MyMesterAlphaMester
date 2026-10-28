/*
Megoldás lényege:
A bemenő mérkőzéseket egyszer beolvassuk, és minden kérdést egy végigmenéssel tudunk megválaszolni.
Az adott forduló meccseit a forduló száma alapján szűrjük, a fordítást pedig úgy azonosítjuk, hogy a csapat a félidőben vesztett állásban volt, de a végén nyert.
A CS csapat lőtt és kapott góljait, valamint a hazai vereségeit (a legkisebb fordulószámút) a mérkőzések közül a csapat nevének egyezése alapján gyűjtjük.
A végeredmények előfordulását a két gólszám rendezett párjával számoljuk, így a 4-2 és a 2-4 azonos eredménynek számít, az első előfordulás sorrendjét egy vektor őrzi.
Az időigény O(N), N ≤ 800 mellett ez bőven elég.
*/
/*
Hint 1: || Minden részfeladat egyetlen beolvasás után, a mérkőzéseken egyszer végigmenve megoldható. A félidei és a végeredményt is külön kell figyelni. ||
Hint 2: || Egy csapat akkor fordított, ha a félidőben kevesebb gólja volt, mint az ellenfelének, a végén mégis több gólt szerzett. A végeredményt tárold a gólszámok rendezett párjaként, így a 4-2 és a 2-4 egyezik. ||
Hint 3: || A CS csapat gólösszegeit a hazai és a vendég szerepek szerint külön kell összegezni. Az első hazai vereség a CS hazai mérkőzései közül a legkisebb fordulószámú, amelyen több gólt kapott, mint szerzett. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Meccs {
    int ford, gh, gv, fh, fv;
    string hazai, vendeg;
};

int main() {
    int f, n;
    string cs;
    cin >> f >> cs >> n;
    vector<Meccs> mk(n);
    for (auto& m : mk) {
        cin >> m.ford >> m.gh >> m.gv >> m.fh >> m.fv >> m.hazai >> m.vendeg;
    }

    // 1. és 2. részfeladat: az F. forduló végeredményei
    vector<Meccs> fordulo;
    for (auto& m : mk) {
        if (m.ford == f) fordulo.push_back(m);
    }
    cout << "#\n";
    cout << fordulo.size() << "\n";
    cout << "#\n";
    for (auto& m : fordulo) {
        cout << m.hazai << " " << m.vendeg << " " << m.gh << " " << m.gv << " " << m.fh << " " << m.fv << "\n";
    }

    // 3. és 4. részfeladat: a fordítást véghez vivő csapatok (csapatonként egyszer, bemenet szerinti sorrendben)
    vector<string> forditok;
    set<string> latott;
    for (auto& m : mk) {
        string t;
        if (m.gh > m.gv && m.fh < m.fv) t = m.hazai;
        else if (m.gv > m.gh && m.fv < m.fh) t = m.vendeg;
        else continue;
        if (!latott.count(t)) {
            latott.insert(t);
            forditok.push_back(t);
        }
    }
    cout << "#\n";
    cout << forditok.size() << "\n";
    cout << "#\n";
    for (auto& t : forditok) {
        cout << t << "\n";
    }

    // 5. részfeladat: a CS csapat lőtt és kapott góljai
    int lott = 0, kapott = 0;
    for (auto& m : mk) {
        if (m.hazai == cs) {
            lott += m.gh;
            kapott += m.gv;
        } else if (m.vendeg == cs) {
            lott += m.gv;
            kapott += m.gh;
        }
    }
    cout << "#\n";
    cout << lott << " " << kapott << "\n";

    // 6. részfeladat: a CS csapat első hazai pályás vereségének fordulója és ellenfele
    bool van = false;
    int elsoFord = 0;
    string ellenfel;
    for (auto& m : mk) {
        if (m.hazai == cs && m.gh < m.gv) {
            if (!van || m.ford < elsoFord) {
                van = true;
                elsoFord = m.ford;
                ellenfel = m.vendeg;
            }
        }
    }
    cout << "#\n";
    if (van) {
        cout << elsoFord << " " << ellenfel << "\n";
    } else {
        cout << "0\n";
    }

    // 7. és 8. részfeladat: a végeredmények fajtái és előfordulásuk
    // A pár mindig nagyobb gólszám előre áll, így a 4-2 és a 2-4 azonos kulcsot ad.
    vector<pair<int, int>> fajtak;
    map<pair<int, int>, int> db;
    for (auto& m : mk) {
        pair<int, int> kulcs = make_pair(max(m.gh, m.gv), min(m.gh, m.gv));
        if (db[kulcs] == 0) fajtak.push_back(kulcs);
        db[kulcs]++;
    }
    cout << "#\n";
    cout << fajtak.size() << "\n";
    cout << "#\n";
    for (auto& k : fajtak) {
        cout << k.first << " " << k.second << " " << db[k] << "\n";
    }
    return 0;
}
