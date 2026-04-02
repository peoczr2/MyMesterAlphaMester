/*
Megoldás:
Legyen d[i] = i-edik kútnál felvehető benzinből megtehető út mínusz a következő kútig vezető
távolság. Egy kezdőállomás akkor jó, ha a belőle induló N egymást követő prefixösszegek sosem
esnek a kezdőpont prefixe alá. Ezt a duplázott tömb prefixösszegein csúszóablakos minimumkereséssel
O(N) időben megkapjuk.

Ha nincs teljes kör, akkor minden kezdőpontra azt kell tudni, mikor esik először a prefixösszeg a
kiindulási szint alá. Ez a prefixösszeg-sorozat következő kisebb eleme problémává válik, amit szintén
lineárisan megoldhatunk monotonnal veremmel. Innen már kiszámítható, hány kutat érinthetünk.

Az egész algoritmus O(N) idejű és O(N) memóriájú.
*/
/*
Hint 1: || A körbejárhatóságot a nettó nyereség-prefixek nemnegativitására lehet átírni. ||
Hint 2: || A duplázott tömbön minden kezdőponthoz egy hosszú ablak minimumát kell ellenőrizni. ||
Hint 3: || Ha nincs teljes kör, a „meddig jutunk el” kérdés a prefixsorozat első kisebb elemére vezethető vissza. ||
*/

#include <deque>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    cin >> n >> m;

    vector<long long> diff(2 * n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long distance, fuel;
        cin >> distance >> fuel;
        diff[i] = fuel * m - distance;
        diff[i + n] = diff[i];
    }

    vector<long long> prefix(2 * n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i) {
        prefix[i] = prefix[i - 1] + diff[i];
    }

    vector<int> goodStarts;
    deque<int> dq;
    for (int i = 1; i <= n; ++i) {
        while (!dq.empty() && prefix[dq.back()] >= prefix[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    for (int start = 1; start <= n; ++start) {
        while (!dq.empty() && dq.front() < start) {
            dq.pop_front();
        }
        if (!dq.empty() && prefix[dq.front()] >= prefix[start - 1]) {
            goodStarts.push_back(start);
        }
        int nextIndex = start + n;
        if (nextIndex <= 2 * n) {
            while (!dq.empty() && prefix[dq.back()] >= prefix[nextIndex]) {
                dq.pop_back();
            }
            dq.push_back(nextIndex);
        }
    }

    if (!goodStarts.empty()) {
        cout << "IGEN\n";
        for (int i = 0; i < static_cast<int>(goodStarts.size()); ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << goodStarts[i];
        }
        cout << '\n';
        return 0;
    }

    vector<int> nextSmaller(2 * n + 1, 2 * n + 1);
    stack<int> monotone;
    for (int i = 2 * n; i >= 0; --i) {
        while (!monotone.empty() && prefix[monotone.top()] >= prefix[i]) {
            monotone.pop();
        }
        if (!monotone.empty()) {
            nextSmaller[i] = monotone.top();
        }
        monotone.push(i);
    }

    int bestStart = 1;
    int bestCount = 0;
    for (int start = 1; start <= n; ++start) {
        int firstBad = nextSmaller[start - 1];
        int touched;
        if (firstBad > start - 1 + n) {
            touched = n;
        } else {
            touched = firstBad - (start - 1);
        }
        if (touched > bestCount) {
            bestCount = touched;
            bestStart = start;
        }
    }

    cout << "NEM\n" << bestStart << '\n';
    return 0;
}