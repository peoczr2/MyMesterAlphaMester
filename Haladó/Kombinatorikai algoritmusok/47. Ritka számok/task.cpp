/*
   Ritka számok: olyan bináris számok, amelyekben nincs két egymás melletti 1-es. A számjegyeket egy vezető
   nullával egészítjük ki, így a következő szám egy jeggyel hosszabb is lehet. A következő szám: a jobbról első
   olyan 0-t 1-re állítjuk, amelynek bal szomszédja 0, a mögötte álló biteket nullázzuk. Az előző szám: a jobbról
   első 1-est 0-ra állítjuk, a mögötte álló részt a váltakozó 1-0-1… mintával töltjük ki, ez a legnagyobb
   ritka kitöltés. A kiíráskor a vezető nullákat elhagyjuk. Az időigény O(N).
*/
/*
Hint 1: || A ritka számok sorrendje megegyezik a bitsorozatok számértékének sorrendjével. Gondold végig, melyik helyiértéken lehet 0-ról 1-re lépni úgy, hogy a bal szomszéd 0 maradjon. ||
Hint 2: || A következő szám: jobbról az első 0, amelynek bal szomszédja 0, 1-re állítandó, utána minden bit 0. Az előző szám: jobbról az első 1-es 0-ra állítandó, utána váltakozó 1-0-1… minta jön. Mivel a következő szám hosszabb is lehet, érdemes a bemenetet vezető 0-val bővíteni. ||
*/
#include <bits/stdc++.h>
using namespace std;

static string trimLeadingZeros(const vector<int>& bits) {
    int i = 0;
    while (i < (int)bits.size() && bits[i] == 0) ++i;
    if (i == (int)bits.size()) return "";
    string s;
    for (; i < (int)bits.size(); ++i) s.push_back(char('0' + bits[i]));
    return s;
}

static vector<int> nextSparse(vector<int> bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 0 && (i == 0 || bits[i - 1] == 0)) {
            bits[i] = 1;
            for (int j = i + 1; j < L; ++j) bits[j] = 0;
            return bits;
        }
    }
    return bits;
}

static bool prevSparse(vector<int>& bits) {
    int L = (int)bits.size();
    for (int i = L - 1; i >= 0; --i) {
        if (bits[i] == 1) {
            bits[i] = 0;
            for (int j = i + 1; j < L; ++j) bits[j] = ((j - i) % 2 == 1 ? 1 : 0);
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string s;
    cin >> N >> s;

    vector<int> bits(N + 1, 0);
    for (int i = 0; i < N; ++i) bits[i + 1] = s[i] - '0';

    auto nxt = nextSparse(bits);
    string nextAns = trimLeadingZeros(nxt);
    if (nextAns.empty()) nextAns = "-1";

    auto prv = bits;
    bool ok = prevSparse(prv);
    string prevAns = ok ? trimLeadingZeros(prv) : "";
    if (prevAns.empty()) prevAns = "-1";

    cout << nextAns << '\n' << prevAns << '\n';
    return 0;
}