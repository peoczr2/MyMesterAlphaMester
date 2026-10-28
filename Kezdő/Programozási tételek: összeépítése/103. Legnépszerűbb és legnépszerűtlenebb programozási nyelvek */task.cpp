/*
Megoldás lényege:
A két évi listát egy-egy map-ban tároljuk: a kulcs a nyelv neve, az érték a tanulók száma abban az évben. A nyelveket teljes sorként olvassuk be, mert a nevek több szavasak is lehetnek, és a sor végi kocsivisszát (\r) levágjuk. Az első év minden nyelvére megnézzük, szerepel-e a második évben; ha igen, a két évi létszám összegét számoljuk, és ezek közül keressük a legkisebbet és a legnagyobbat. Ha nincs közös nyelv, mindkét sorba NINCS kerül. A map miatt a keresés O((N+M) log(N+M)) időben fut, ami a korlátok mellett bőven elég.
*/
/*
Hint 1: || Egy nyelv csak akkor számít, ha mindkét évben szerepel. Az összesítéshez a két évi létszámot kell összeadni, és az ilyen nyelvek közül kell a legkisebbet és a legnagyobbat megtalálni. ||
Hint 2: || A nyelveket érdemes név szerint tárolni, például map-ban, így a másik évben való szereplés gyorsan ellenőrizhető. A nyelv neve szóközt is tartalmazhat, ezért a számot követő teljes sort olvasd be. ||
*/
#include <bits/stdc++.h>
using namespace std;

string tisztit(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ' || s.back() == '\t')) s.pop_back();
    return s;
}

map<string, long long> beolvas(int darab) {
    map<string, long long> ev;
    for (int i = 0; i < darab; ++i) {
        long long db;
        cin >> db >> ws;
        string nyelv;
        getline(cin, nyelv);
        ev[tisztit(nyelv)] = db;
    }
    return ev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    map<string, long long> elsoEv = beolvas(n);
    map<string, long long> masodikEv = beolvas(m);

    bool van = false;
    string legkevesebb, legtobb;
    long long minOssz = 0, maxOssz = 0;

    for (const auto& [nyelv, db] : elsoEv) {
        auto it = masodikEv.find(nyelv);
        if (it == masodikEv.end()) continue;
        long long ossz = db + it->second;
        if (!van || ossz < minOssz) {
            minOssz = ossz;
            legkevesebb = nyelv;
        }
        if (!van || ossz > maxOssz) {
            maxOssz = ossz;
            legtobb = nyelv;
        }
        van = true;
    }

    if (!van) {
        cout << "NINCS\nNINCS\n";
    } else {
        cout << legkevesebb << '\n' << legtobb << '\n';
    }
    return 0;
}
