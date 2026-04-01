/*
Megoldási ötlet:
Ha egy kiválasztott ingatlancsoport legnagyobb adója T, akkor a vásárlások összára legfeljebb K-T lehet. Ezért az
ingatlanokat adó szerint növekvő sorrendbe rakjuk, és balról jobbra haladva fenntartjuk, hogy az eddig látott ingatlanokból
adott árkeret mellett mekkora maximális érték érhető el.

Ez egy szokásos 0/1 hátizsák DP a vételárra. Amikor az i-edik ingatlant is feldolgoztuk, akkor az összes olyan megoldás,
amelynek maximális adója legfeljebb T[i], már benne van a DP-ben, ezért a K-T[i] keretű legjobb értékkel frissíthetjük a választ.
*/
/*
Hint 1: || A „maximális adó” miatt érdemes az ingatlanokat az adó szerint rendezetten kezelni. ||
Hint 2: || Ha az aktuális legnagyobb adó T, akkor a vételárak összegére K-T a felső korlát. ||
Hint 3: || Minden új ingatlant 0/1 hátizsák-lépésként dolgozz fel a vételár dimenziójában. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Property {
    int price;
    int value;
    int tax;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, budget;
    cin >> n >> budget;
    vector<Property> items(n);
    for (int i = 0; i < n; ++i) cin >> items[i].price >> items[i].value >> items[i].tax;
    sort(items.begin(), items.end(), [](const Property& a, const Property& b) {
        return a.tax < b.tax;
    });

    vector<long long> dp(budget + 1, 0);
    long long answer = 0;
    for (const Property& item : items) {
        for (int cap = budget; cap >= item.price; --cap) {
            dp[cap] = max(dp[cap], dp[cap - item.price] + item.value);
        }
        int limit = budget - item.tax;
        if (limit < 0) continue;
        for (int cap = 0; cap <= limit; ++cap) answer = max(answer, dp[cap]);
    }

    cout << answer << '\n';
    return 0;
}