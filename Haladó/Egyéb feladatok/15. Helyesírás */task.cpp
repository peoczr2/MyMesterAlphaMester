/*
Megoldás lényege:
A szöveg karaktereit négy osztályba soroljuk: írásjel (, . ? ! ; :), nyitó zárójel ( [ {), csukó zárójel ) ] } és minden más karakter.
Minden két szomszédos, nem szóköz karakter között külön eldöntjük, kell-e szóköz. Tilos a szóköz, ha a jobb karakter írásjel
vagy csukó zárójel, vagy ha a bal karakter nyitó zárójel. Kötelező a szóköz, ha a bal karakter írásjel vagy csukó zárójel,
vagy ha a jobb karakter nyitó zárójel. Ha a két szabály ütközik, a tiltó szabály nyer, mert a tiltást előbb ellenőrizzük.
Minden más esetben (két sima karakter között) az eredeti szóköz-viszonyt tartjuk meg, így a szóközsorozat egy szóközre csökken.
A sor elején és végén lévő szóközöket töröljük. A karakterek nem változnak, csak a szóközök. Az időigény O(N).
*/
/*
Hint 1: || Ne próbáld a szöveget több lépésben átalakítani. Elég minden szomszédos karakterpárra eldönteni, kell-e közéjük szóköz. Előbb add meg a karaktereket osztályokba: írásjel, nyitó zárójel, csukó zárójel vagy egyéb. ||
Hint 2: || A tiltó szabályok: írásjel elé, nyitó zárójel után és csukó zárójel elé nem kerül szóköz. A kötelező szabályok: írásjel után, nyitó zárójel elé és csukó zárójel után kell szóköz. Ha egy pár mindkettőbe esik, a tiltó szabály győz. ||
*/
#include <bits/stdc++.h>
using namespace std;

enum Kind { WORD, OPEN, CLOSE, PUNCT };

Kind kind_of(char c) {
    if (c == ',' || c == '.' || c == '?' || c == '!' || c == ';' || c == ':') return PUNCT;
    if (c == '(' || c == '[' || c == '{') return OPEN;
    if (c == ')' || c == ']' || c == '}') return CLOSE;
    return WORD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);

    // A nem szóköz karakterek listája, és hogy előttük volt-e szóköz a bemenetben.
    string chars;
    vector<char> space_before;
    bool pending = false;
    for (char c : line) {
        if (c == '\r' || isspace(static_cast<unsigned char>(c))) {
            if (!chars.empty()) pending = true;
            continue;
        }
        chars.push_back(c);
        space_before.push_back(pending ? 1 : 0);
        pending = false;
    }

    string out;
    out.reserve(chars.size() * 2);
    for (size_t i = 0; i < chars.size(); ++i) {
        if (i > 0) {
            Kind a = kind_of(chars[i - 1]);
            Kind b = kind_of(chars[i]);
            bool need;
            if (b == PUNCT || a == OPEN || b == CLOSE)
                need = false;                       // tiltó szabályok (ezek erősebbek)
            else if (a == PUNCT || a == CLOSE || b == OPEN)
                need = true;                        // kötelező szabályok
            else
                need = space_before[i] != 0;        // két sima karakter: az eredeti marad
            if (need) out.push_back(' ');
        }
        out.push_back(chars[i]);
    }

    cout << out << '\n';
    return 0;
}
