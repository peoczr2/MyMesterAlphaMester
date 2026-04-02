/*
Az [A, B] intervallum akkor metszi a [l, r] bemeneti intervallumot, ha A <= r es B >= l.
Ha kivalasztunk K darab intervallumot, akkor a legkisebb, oket mind metsző [A, B] szelessege
csak a legnagyobb bal vegponttol es a legkisebb jobb vegponttol fugg: max(1, L - R), ahol
L a kivalasztott bal vegpontok maximuma, R pedig a jobb vegpontok minimuma.

Ezert a bemeneti intervallumokat bal vegpont szerint rendezzuk. Egy adott L ertekhez a legjobb
K-es valasztas az aktualis prefixbol a K legnagyobb jobb vegpontot hasznalja, mert azok kozul a
legkisebb jobb vegpont lesz a lehető legnagyobb. Ezt egy K meretu minimumkupaccal tudjuk kovetni.
Minden azonos bal vegpontu csoport utan ellenorizzuk a jelolt megoldast, es holtversenyben a
legkisebb A-t valasztjuk.
*/
/*
Hint 1: || Ha fix a K kivalasztott intervallum, akkor a legkisebb jo [A, B] csak a legnagyobb bal es a legkisebb jobb vegponttol fugg. ||
Hint 2: || Bal vegpont szerint haladva az aktualis L-hez csak az addig latott intervallumok johetnek szoba. ||
Hint 3: || Az aktualis prefixbol a K legnagyobb jobb vegpont tartasa eleg: kozuluk a legkisebb adja az R-t. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int left;
    int right;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Interval> intervals(n);
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].left >> intervals[i].right;
    }

    sort(intervals.begin(), intervals.end(), [](const Interval& first, const Interval& second) {
        if (first.left != second.left) return first.left < second.left;
        return first.right > second.right;
    });

    priority_queue<int, vector<int>, greater<int>> smallestOfLargestRights;
    long long bestWidth = (1LL << 60);
    int bestA = -1;
    int bestB = -1;

    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && intervals[j].left == intervals[i].left) {
            smallestOfLargestRights.push(intervals[j].right);
            if ((int)smallestOfLargestRights.size() > k) {
                smallestOfLargestRights.pop();
            }
            ++j;
        }

        if ((int)smallestOfLargestRights.size() == k) {
            int leftMax = intervals[i].left;
            int rightMin = smallestOfLargestRights.top();

            long long width;
            int candidateA;
            int candidateB;
            if (leftMax - rightMin >= 1) {
                candidateA = rightMin;
                candidateB = leftMax;
                width = (long long)candidateB - candidateA;
            } else {
                candidateA = max(1, leftMax - 1);
                candidateB = candidateA + 1;
                width = 1;
            }

            if (width < bestWidth || (width == bestWidth && candidateA < bestA)) {
                bestWidth = width;
                bestA = candidateA;
                bestB = candidateB;
            }
        }

        i = j;
    }

    cout << bestA << ' ' << bestB << '\n';
    return 0;
}