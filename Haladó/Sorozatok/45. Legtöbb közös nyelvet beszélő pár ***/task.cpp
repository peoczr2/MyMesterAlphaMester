/*
Megoldas lenyege:
Minden emberhez csak az általa beszélt nyelvek halmazára van szükségünk. Mivel
legfeljebb 200 nyelv fordul elő, ezt bitsetként tárolhatjuk. Ezután minden emberpár
közös nyelveinek számát a két bitset metszetének elemszámával kapjuk meg, és a
legnagyobb értéket őrizzük meg.
*/
/*
Hint 1: || Egy embernél ugyanaz a nyelv többször is szerepelhet, de halmazként elég egyszer számolni. ||
Hint 2: || A legfeljebb 200 nyelv bitsettel kényelmesen tárolható. ||
Hint 3: || Ezután már csak minden emberpárt végig kell nézni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Bits {
    array<unsigned long long, 4> w{};
};

static int popcountBits(const Bits& b) {
    return __builtin_popcountll(b.w[0]) + __builtin_popcountll(b.w[1]) +
           __builtin_popcountll(b.w[2]) + __builtin_popcountll(b.w[3]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    unordered_map<string, int> langId;
    unordered_map<string, int> personId;
    vector<string> names;
    vector<Bits> people;
    names.reserve(1000);
    people.reserve(1000);

    for (int i = 0; i < m; ++i) {
        string name, lang;
        cin >> name >> lang;
        int &id = langId[lang];
        if (id == 0) id = (int)langId.size();
        int personIdx;
        auto it = personId.find(name);
        if (it == personId.end()) {
            personIdx = (int)names.size();
            personId[name] = personIdx;
            names.push_back(name);
            people.push_back({});
        } else {
            personIdx = it->second;
        }
        int langIdx = id - 1;
        people[personIdx].w[langIdx / 64] |= 1ULL << (langIdx % 64);
    }

    if (names.size() < 2) {
        cout << "NINCS\n";
        return 0;
    }

    int best = 0;
    string bestA, bestB;
    for (int i = 0; i < (int)names.size(); ++i) {
        for (int j = i + 1; j < (int)names.size(); ++j) {
            const Bits &a = people[i];
            const Bits &b = people[j];
            Bits inter;
            for (int k = 0; k < 4; ++k) inter.w[k] = a.w[k] & b.w[k];
            int c = popcountBits(inter);
            if (c > best) {
                best = c;
                bestA = names[i];
                bestB = names[j];
            }
        }
    }

    if (best == 0) {
        cout << "NINCS\n";
    } else {
        cout << bestA << '\n' << bestB << '\n';
    }
    return 0;
}
