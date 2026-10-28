/*
Megoldás lényege:
A szabadon választható tárgyakat egy map-be tesszük, amely a tárgy nevéhez a sorszámát rendeli.
A tanulók sorait egyesével, getline-nal olvassuk, és minden sort szavakra bontunk.
Ha egy szó szabadon választható tárgy, a tanuló sorszámát beírjuk ennek a tárgynak a listájába.
Mivel a tanulókat sorszámuk szerint dolgozzuk fel, a listákban a sorszámok már növekvő sorrendben vannak.
A végén tárgyanként, a megadott sorrendben kiírjuk a darabszámot, majd a sorszámokat.
Az időigény a szavak számával és a log T tényezővel arányos, ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Minden tanulónál csak azt kell eldönteni, hogy a sorában mely szavak szabadon választható tárgyak. Ha igen, a tanuló sorszámát a tárgy listájához kell írni. ||
Hint 2: || Tárold a szabadon választható tárgyakat egy map-ben (név → sorszám), így egy szóról gyorsan eldöntheted, hogy tárgy-e, és melyik listába tartozik. ||
Hint 3: || Minden tanuló sorát külön olvasd be (getline), mert a sorok hossza eltérő. A sor szavait egy istringstream-mel bonthatod szét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    vector<string> subjects(t);
    map<string, int> idx;
    for (int i = 0; i < t; ++i) {
        cin >> subjects[i];
        idx[subjects[i]] = i;
    }

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> takers(t);
    string line;
    for (int s = 1; s <= n; ++s) {
        getline(cin, line);
        istringstream in(line);
        string word;
        while (in >> word) {
            auto it = idx.find(word);
            if (it != idx.end()) takers[it->second].push_back(s);
        }
    }

    for (int i = 0; i < t; ++i) {
        cout << takers[i].size();
        for (int s : takers[i]) cout << ' ' << s;
        cout << '\n';
    }
    return 0;
}
