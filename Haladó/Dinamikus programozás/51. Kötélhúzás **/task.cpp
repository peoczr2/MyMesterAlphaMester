/*
Az N tanuló közül pontosan N/2 fő kerül az egyik csapatba, ezért elég azt megkeresni, hogy
az N/2 kiválasztott tanuló súlyai milyen összeget adhatnak ki. Dinamikus programozással
nyilvántartjuk, hogy az első i tanulóból pontosan c darabot választva előáll-e egy adott s
összeg. A végső cél az a csapat, amelynek összsúlya a teljes összeg felének legközelebb esik,
mert ekkor a két csapat különbsége minimális. A szülőket is eltároljuk, így vissza tudjuk
építeni az egyik optimális csapat összetételét.
*/
/*
Hint 1: || Csak az egyik csapatot kell kiválasztani, a másik automatikusan adódik. ||
Hint 2: || A kiválasztott emberek száma is legyen állapot, nem elég csak az összsúly. ||
Hint 3: || Ha eltároljuk, melyik tanuló hozott létre egy állapotot, visszaállítható a csapat. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    vector<int> weight(n + 1);
    int total = 0;
    for (int index = 1; index <= n; ++index) {
        cin >> weight[index];
        total += weight[index];
    }

    int half = n / 2;
    vector<vector<char>> possible(half + 1, vector<char>(total + 1, false));
    vector<vector<int>> parent_item(half + 1, vector<int>(total + 1, -1));
    vector<vector<int>> parent_sum(half + 1, vector<int>(total + 1, -1));
    possible[0][0] = true;

    for (int index = 1; index <= n; ++index) {
        int current = weight[index];
        for (int count = min(index, half); count >= 1; --count) {
            for (int sum = total; sum >= current; --sum) {
                if (!possible[count][sum] && possible[count - 1][sum - current]) {
                    possible[count][sum] = true;
                    parent_item[count][sum] = index;
                    parent_sum[count][sum] = sum - current;
                }
            }
        }
    }

    int best_sum = 0;
    int best_diff = total;
    for (int sum = 0; sum <= total; ++sum) {
        if (!possible[half][sum]) {
            continue;
        }
        int diff = abs(total - 2 * sum);
        if (diff < best_diff) {
            best_diff = diff;
            best_sum = sum;
        }
    }

    vector<int> first_team;
    vector<char> chosen(n + 1, false);
    int count = half;
    int sum = best_sum;
    while (count > 0) {
        int index = parent_item[count][sum];
        first_team.push_back(index);
        chosen[index] = true;
        sum = parent_sum[count][sum];
        --count;
    }

    vector<int> second_team;
    for (int index = 1; index <= n; ++index) {
        if (!chosen[index]) {
            second_team.push_back(index);
        }
    }

    sort(first_team.begin(), first_team.end());
    sort(second_team.begin(), second_team.end());

    cout << best_diff << '\n';
    for (int index = 0; index < half; ++index) {
        if (index > 0) {
            cout << ' ';
        }
        cout << first_team[index];
    }
    cout << '\n';
    for (int index = 0; index < half; ++index) {
        if (index > 0) {
            cout << ' ';
        }
        cout << second_team[index];
    }
    cout << '\n';

    return 0;
}