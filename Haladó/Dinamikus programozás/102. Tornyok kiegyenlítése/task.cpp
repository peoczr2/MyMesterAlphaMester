/*
Megoldási ötlet:
Egy rögzített K hosszú szakaszon akkor minimális a teljes műveletszám, ha minden torony magasságát
ugyanarra az értékre állítjuk, és ez az érték valamelyik medián. Ekkor az ár pontosan az abszolút
eltérések összege.

Ezért csúszóablakban végigvizsgáljuk az összes K hosszú szakaszt. Az aktuális ablak elemeit két multihalmazban
tartjuk: az alsó felében vannak a kisebb elemek, a felső felében a nagyobbak. Így a medián mindig az alsó halmaz
legnagyobb eleme, és a költség a két rész összegeiből O(1)-ben kiszámítható. Az ablak csúsztatása O(log K).
*/
/*
Hint 1: || Egy adott szakaszon az azonos célmagasságra állítás költsége az abszolút eltérések összege. ||
Hint 2: || Az abszolút eltérések összegét medián választása minimalizálja. ||
Hint 3: || Csúszóablakhoz érdemes két rendezett multihalmazt és a bennük levő elemek összegét fenntartani. ||
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class SlidingMedianCost {
public:
    void add(long long value) {
        if (low.empty() || value <= *low.rbegin()) {
            low.insert(value);
            sumLow += value;
        } else {
            high.insert(value);
            sumHigh += value;
        }
        rebalance();
    }

    void remove(long long value) {
        auto itLow = low.find(value);
        if (itLow != low.end()) {
            sumLow -= value;
            low.erase(itLow);
        } else {
            auto itHigh = high.find(value);
            sumHigh -= value;
            high.erase(itHigh);
        }
        rebalance();
    }

    long long cost() const {
        long long median = *low.rbegin();
        long long leftCost = median * static_cast<long long>(low.size()) - sumLow;
        long long rightCost = sumHigh - median * static_cast<long long>(high.size());
        return leftCost + rightCost;
    }

private:
    multiset<long long> low, high;
    long long sumLow = 0;
    long long sumHigh = 0;

    void rebalance() {
        while (low.size() < high.size()) {
            auto it = high.begin();
            long long value = *it;
            high.erase(it);
            sumHigh -= value;
            low.insert(value);
            sumLow += value;
        }
        while (low.size() > high.size() + 1) {
            auto it = prev(low.end());
            long long value = *it;
            low.erase(it);
            sumLow -= value;
            high.insert(value);
            sumHigh += value;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> height(n);
    for (int i = 0; i < n; ++i) cin >> height[i];

    SlidingMedianCost window;
    for (int i = 0; i < k; ++i) window.add(height[i]);

    long long answer = window.cost();
    for (int i = k; i < n; ++i) {
        window.remove(height[i - k]);
        window.add(height[i]);
        answer = min(answer, window.cost());
    }

    cout << answer << '\n';
    return 0;
}