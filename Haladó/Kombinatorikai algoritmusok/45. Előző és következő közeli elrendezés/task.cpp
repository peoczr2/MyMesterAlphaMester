/*
   Előző és következő közeli elrendezés: a közeli permutációk egymást nem fedő szomszédos cserék
   sorozatai, vagyis olyan 0/1 sorozatok, amelyekben nincs két egymás melletti 1-es. A lexikografikus
   sorrend a sorozatok számértékének sorrendje. A következő: a jobbról első olyan 0-t 1-re állítjuk, amelynek
   bal szomszédja 0, a mögötte lévő biteket nullázzuk. Az előző: a jobbról első 1-est 0-ra állítjuk, a mögötte
   álló részt pedig a lehető legnagyobb, váltakozó 1-0-1… mintával töltjük ki. Ha a sorozat csupa 0
   (identitás), az előző a legnagyobb közeli permutáció, vagyis ugyanez a minta az elsőtől kezdve.
   Az időigény O(N).
*/
/*
Hint 1: || Használd ugyanazt a 0/1 kódolást, mint a közeli permutációknál: két szomszédos 1-es nem állhat, és a lexikografikus sorrend a bitsorozat számértékének sorrendje. Az előző és a következő is így keresendő. ||
Hint 2: || A következő keresésénél jobbról az első olyan 0 kell, amelynek bal szomszédja 0, ezt 1-re állítva a mögötte lévő biteket nullázd. Az előző keresésénél jobbról az első 1-est nullázd, a mögötte álló részt viszont a lehető legnagyobb értékkel tölts ki: két 1-es nem állhat egymás mellett, így ez a váltakozó 1-0-1… minta. ||
Hint 3: || Az identitás előzőjét és az utolsó közeli permutáció utáni ugrást külön határesetként kezeld: a csupa 0 sorozat előzője a legnagyobb, váltakozó mintájú sorozat, a legnagyobb sorozat következője pedig az identitás. ||
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> buildPermutation(int n, const vector<int>& bits) {
    vector<int> ans;
    for (int i = 0; i < n - 1; ) {
        if (bits[i]) {
            ans.push_back(i + 2);
            ans.push_back(i + 1);
            i += 2;
        } else {
            ans.push_back(i + 1);
            ++i;
        }
    }
    if ((int)ans.size() < n) ans.push_back(n);
    return ans;
}

static vector<int> nextBits(vector<int> bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 0 && (i == 0 || bits[i - 1] == 0)) {
            bits[i] = 1;
            for (int j = i + 1; j < L; ++j) bits[j] = 0;
            return bits;
        }
    }
    fill(bits.begin(), bits.end(), 0);
    return bits;
}

static vector<int> prevBits(vector<int> bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 1) {
            bits[i] = 0;
            for (int j = i + 1; j < L; ++j) bits[j] = ((j - i) % 2 == 1 ? 1 : 0);
            return bits;
        }
    }
    for (int i = 0; i < L; ++i) bits[i] = (i % 2 == 0 ? 1 : 0);
    return bits;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> bits(max(0, n - 1), 0);
    for (int i = 0; i + 1 < n; ) {
        if (p[i] == i + 1) {
            bits[i] = 0;
            ++i;
        } else {
            bits[i] = 1;
            i += 2;
        }
    }

    auto prevP = buildPermutation(n, prevBits(bits));
    auto nextP = buildPermutation(n, nextBits(bits));

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << prevP[i];
    }
    cout << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << nextP[i];
    }
    cout << '\n';
    return 0;
}