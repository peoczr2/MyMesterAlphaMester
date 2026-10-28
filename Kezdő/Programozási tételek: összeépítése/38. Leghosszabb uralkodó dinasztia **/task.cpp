/*
Megoldás lényege:
A királyokat a bemenet sorrendjében (időrendben) dolgozzuk fel, és az egymás utáni uralkodókat hasonlítjuk össze.
Egy király akkor követte az apját, ha az apja közvetlenül előtte uralkodott, és az uralkodásuk folytonosan csatlakozik
(az előző király záró éve egyezik a következő király kezdő évével). Így az uralkodók sorozata szakaszokra bomlik: minden
szakasz egy olyan királlyal indul, aki nem az apját követte, a további tagjai pedig mind az apjukat követik.
Egy szakasz időszaka az első király kezdő éve és az utolsó király záró éve. A szakaszokat időrendben bejárva a leghosszabbat
tartjuk meg, egyenlőségnél a korábbit, mert a strict összehasonlítás az első találatot hagyja meg. A szülő-gyerek párokat
halmazban tároljuk, így minden ellenőrzés logaritmikus. Az időigény O(N log N + M log M).
*/
/*
Hint 1: || Az uralkodók időrendben vannak, így elég az egymás utáni párokat vizsgálni: egy király akkor folytatja az előző szakaszt, ha az előző király az apja és a trónöröklés folytonos. ||
Hint 2: || Tárold a szülő-gyerek kapcsolatokat egy halmazban (szülő, gyerek) párokként, a folytonosságot pedig a két uralkodás éveinek egyezésével ellenőrizd. ||
Hint 3: || Minden szakasz egy kezdő királytól indul, és addig tart, amíg a következő király nem az apját követi; a hossza az első kezdő év és az utolsó záró év különbsége. A szakaszokat végigjárva a leghosszabbat tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Levágja a szóközöket és a sorvégi '\r' karaktert (a nevek szóközt is tartalmazhatnak).
string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// A következő nem üres sor tartalmát adja vissza.
string readName() {
    string line;
    while (getline(cin, line)) {
        line = trim(line);
        if (!line.empty()) return line;
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> from(n), to(n); // uralkodás kezdő és záró éve
    vector<string> name(n);
    for (int i = 0; i < n; i++) {
        cin >> from[i] >> to[i];
        name[i] = readName(); // a név a sor maradékában van
    }

    int m;
    cin >> m;
    set<pair<string, string>> parentOf; // (szülő, gyerek)
    for (int i = 0; i < m; i++) {
        string parent = readName();
        string child = readName();
        parentOf.insert({parent, child});
    }

    // Az i-edik király az apját követte: az előző király az apja, és a trónöröklés folytonos.
    auto followsFather = [&](int i) {
        return to[i - 1] == from[i] && parentOf.count({name[i - 1], name[i]}) > 0;
    };

    int bestFrom = 0, bestTo = 0;
    int bestLen = -1;
    int segStart = 0; // az aktuális szakasz első királyának indexe
    for (int i = 1; i <= n; i++) {
        if (i < n && followsFather(i)) continue; // a szakasz folytatódik
        // a [segStart, i-1] szakasz véget ért
        int len = to[i - 1] - from[segStart];
        if (len > bestLen) {
            bestLen = len;
            bestFrom = from[segStart];
            bestTo = to[i - 1];
        }
        segStart = i;
    }

    cout << bestFrom << ' ' << bestTo << '\n';
    return 0;
}
