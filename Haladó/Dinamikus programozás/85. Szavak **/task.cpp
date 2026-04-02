/*
Megoldási ötlet:
Legyen `x_B` annak a nem üres szónak a hossza, amelyre a `B` betűt helyettesítjük.
Ha a két bemeneti szó képe megegyezik, akkor a közös kép teljes hossza mindkét oldalról ugyanaz:

    sum(cnt1[B] * x_B) = sum(cnt2[B] * x_B).

Itt `cnt1[B]` és `cnt2[B]` a betű előfordulásszáma az első, illetve a második szóban.

A konkrét helyettesítő szavak betűi valójában nem fontosak: ha találtunk pozitív egész hosszakat,
akkor minden betűt helyettesíthetünk egyszerűen `x_B` darab `A` betűből álló szóval. Ekkor mindkét
kép csak `A` betűkből áll, tehát pontosan akkor egyeznek meg, ha a teljes hossz megegyezik. Emiatt
a feladat egzaktul egy pozitív egész megoldás keresése az előbbi lineáris egyenletre, minimális
közös hossz mellett.

Legyen `d_B = cnt1[B] - cnt2[B]`. Azok a betűk, amelyekre `d_B = 0`, optimálisan 1 hosszúak.
A pozitív és negatív különbségű betűkön a feltétel így írható át:

    sum(d_B * x_B) = T      a pozitív oldalon,
    sum((-d_B) * x_B) = T   a negatív oldalon.

Ugyanazt a `T` értéket kell mindkét oldalon előállítani. Mindkét oldalra külön unbounded knapsack
DP-t futtatunk: `dp[t]` a legkisebb bal oldali képhossz, amellyel pontosan `t` hozzájárulás érhető
el úgy, hogy minden ottani betű legalább egyszer szerepel. A súlyok legfeljebb 200-asak, ezért az
elérhető maradékosztályok 40000 körül már periodikusan viselkednek; `40200`-ig számolni elegendő az
optimum lefedéséhez.

Az optimum az a közös `T`, amelynél a két oldal összköltsége minimális. A konkrét hosszakat a két
DP elődmutatóiból visszafejtjük, és minden betűhöz `A` ismétlésével kiírjuk a helyettesítő szót.
*/
/*
Hint 1: || Először ne a helyettesítő szavak konkrét betűit keresd, hanem csak azt, milyen hosszúak legyenek. ||
Hint 2: || Ha minden kép csak `A...A`, akkor az egyezéshez kizárólag a két oldali teljes hossz egyezése kell. ||
Hint 3: || A pozitív és negatív `cnt1-cnt2` különbségű betűk két oldalát szét lehet választani, és ugyanazt a `T` összeget kell mindkét oldalon előállítani. ||
Hint 4: || Egy oldal önmagában egy korlátlan hátizsák: pontosan adott súlyt kell elérni minimális hossz-költséggel. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int INF = 1'000'000'000;
constexpr int LIMIT = 40200;

struct SideItem {
    int letter;
    int weight;
    int cost;
};

struct SideResult {
    vector<int> best_cost;
    vector<int> parent_sum;
    vector<int> parent_item;
    int base_weight = 0;
    int base_cost = 0;
};

SideResult solve_side(const vector<SideItem>& items) {
    SideResult result;
    result.best_cost.assign(LIMIT + 1, INF);
    result.parent_sum.assign(LIMIT + 1, -1);
    result.parent_item.assign(LIMIT + 1, -1);

    for (const SideItem& item : items) {
        result.base_weight += item.weight;
        result.base_cost += item.cost;
    }

    if (result.base_weight > LIMIT) {
        return result;
    }

    result.best_cost[result.base_weight] = result.base_cost;

    for (int sum = result.base_weight; sum <= LIMIT; ++sum) {
        if (result.best_cost[sum] == INF) {
            continue;
        }
        for (int index = 0; index < static_cast<int>(items.size()); ++index) {
            int next_sum = sum + items[index].weight;
            if (next_sum > LIMIT) {
                continue;
            }
            int next_cost = result.best_cost[sum] + items[index].cost;
            if (next_cost < result.best_cost[next_sum]) {
                result.best_cost[next_sum] = next_cost;
                result.parent_sum[next_sum] = sum;
                result.parent_item[next_sum] = index;
            }
        }
    }

    return result;
}

}  // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string first_word;
    string second_word;
    cin >> first_word >> second_word;

    vector<int> count_first(26, 0);
    vector<int> count_second(26, 0);
    vector<int> present_letters;

    for (char ch : first_word) {
        ++count_first[ch - 'A'];
    }
    for (char ch : second_word) {
        ++count_second[ch - 'A'];
    }

    for (int letter = 0; letter < 26; ++letter) {
        if (count_first[letter] > 0 || count_second[letter] > 0) {
            present_letters.push_back(letter);
        }
    }

    vector<int> lengths(26, 0);
    vector<SideItem> positive_items;
    vector<SideItem> negative_items;
    int zero_cost = 0;

    for (int letter : present_letters) {
        int diff = count_first[letter] - count_second[letter];
        lengths[letter] = 1;
        if (diff > 0) {
            positive_items.push_back({letter, diff, count_first[letter]});
        } else if (diff < 0) {
            negative_items.push_back({letter, -diff, count_first[letter]});
        } else {
            zero_cost += count_first[letter];
        }
    }

    if (positive_items.empty() && negative_items.empty()) {
        cout << first_word.size() << '\n';
        for (int letter : present_letters) {
            cout << static_cast<char>('A' + letter) << ' ' << 'A' << '\n';
        }
        return 0;
    }

    if (positive_items.empty() || negative_items.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    SideResult positive = solve_side(positive_items);
    SideResult negative = solve_side(negative_items);

    int best_total = INF;
    int best_sum = -1;
    int start_sum = max(positive.base_weight, negative.base_weight);
    for (int sum = start_sum; sum <= LIMIT; ++sum) {
        if (positive.best_cost[sum] == INF || negative.best_cost[sum] == INF) {
            continue;
        }
        int total = positive.best_cost[sum] + negative.best_cost[sum] + zero_cost;
        if (total < best_total) {
            best_total = total;
            best_sum = sum;
        }
    }

    if (best_sum < 0) {
        cout << 0 << '\n';
        return 0;
    }

    int current = best_sum;
    while (current > positive.base_weight) {
        int item_index = positive.parent_item[current];
        ++lengths[positive_items[item_index].letter];
        current = positive.parent_sum[current];
    }

    current = best_sum;
    while (current > negative.base_weight) {
        int item_index = negative.parent_item[current];
        ++lengths[negative_items[item_index].letter];
        current = negative.parent_sum[current];
    }

    cout << best_total << '\n';
    for (int letter : present_letters) {
        cout << static_cast<char>('A' + letter) << ' ' << string(lengths[letter], 'A') << '\n';
    }

    return 0;
}