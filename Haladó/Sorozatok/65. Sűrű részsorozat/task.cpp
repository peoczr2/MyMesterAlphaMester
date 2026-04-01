/*
Megoldas lenyege:
A feltetel azt jelenti, hogy minden M hosszu intervallumba kerul legalabb egy kivalasztott
pozicio. Ez pontosan akkor teljesul, ha a kivalasztott indexek kozti tavolsag legfeljebb M,
az elso kivalasztott index legfeljebb M, az utolso pedig legfeljebb M tavolsagra van a vegetol.

Binary search-csel megkeressuk a legkisebb X erteket, amelyre az S[i] <= X poziciokbol lehet
ilyen lefedest epiteni. Egy fix X-re a lehetoseg es a minimalis darabszam is mohó: mindig a
jelenlegi ponttol legfeljebb M tavolsagra eso legjobboldalibb megengedett indexet valasztjuk.
Ez egyszerre biztositja a lefedest es a minimalis elemszamot.
*/
/*
Hint 1: || Fix maximumertekre csak az olyan indexek valaszthatok, ahol S[i] nem nagyobb nala. ||
Hint 2: || Ha egy lefedes letezik, a kovetkezo pontnak mindig a leheto legjobboldalibbnak erdemes lennie. ||
Hint 3: || A minimum maximalis erteket binaris keresessel tudod megtalalni. ||
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> buildSelection(const vector<long long>& s, int m, long long limit) {
    int n = (int)s.size() - 1;
    vector<int> selected;
    int current = 0;
    int nextIndex = 1;

    while (current + m <= n) {
        int best = -1;
        while (nextIndex <= n && nextIndex <= current + m) {
            if (s[nextIndex] <= limit) best = nextIndex;
            ++nextIndex;
        }
        if (best == -1) return {};
        selected.push_back(best);
        current = best;
    }
    return selected;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> s(n + 1);
    vector<long long> values;
    values.reserve(n);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        values.push_back(s[i]);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    int low = 0, high = (int)values.size() - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        if (buildSelection(s, m, values[mid]).empty()) low = mid + 1;
        else high = mid;
    }

    vector<int> answer = buildSelection(s, m, values[low]);
    cout << answer.size() << '\n';
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}