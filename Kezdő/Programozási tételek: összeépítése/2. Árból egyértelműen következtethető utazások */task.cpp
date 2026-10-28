/*
Megoldás lényege:
Egy ár akkor vezet egyértelműen egy városhoz, ha a teljes listában pontosan egyszer szerepel. Ezért minden ár előfordulását megszámoljuk egy map-ben (ár -> darabszám), majd megszámoljuk azokat az árakat, amelyek darabszáma pontosan 1. Mivel a map minden árat egyszer tárol, a végén a darabszám-1 árak száma adja a választ. Az időigény O(N log N), N ≤ 100 mellett ez messze belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Nem a városok számát kell nézni, hanem azt, hogy egy ár a teljes listában hányszor fordul elő. Az egyértelmű ár pontosan egyszer szerepel. ||
Hint 2: || Számold meg az árak előfordulását egy map-ben (ár -> darabszám), majd számold meg azokat a kulcsokat, amelyek értéke pontosan 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    map<int, int> count;
    for (int i = 0; i < n; i++) {
        int distance, price;
        cin >> distance >> price;
        count[price]++;
    }

    int answer = 0;
    for (const auto& [price, times] : count) {
        if (times == 1) {
            answer++;
        }
    }

    cout << answer << "\n";
    return 0;
}
