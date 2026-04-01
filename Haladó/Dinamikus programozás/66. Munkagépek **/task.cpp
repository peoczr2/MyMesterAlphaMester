/*
Ket azonos gepnel a befejezesi ido a ket geptol kapott idok maximuma. Ez akkor minimalis, ha az
egyik gepre jutott osszido a teljes ido felehez a lehetseges legkozelebb van. Tehat ujra egy
reszosszeg-feladatot kapunk: mely idok allithatok elo a munkak egy reszhalmazabol. Dinamikus
programozassal taroljuk az elerheto osszegeket es azt is, melyik munka hozott letre egy allapotot,
igy vissza tudjuk epiteni az egyik optimalis ketreszes felosztast.
*/
/*
Hint 1: || Ha az egyik gep terhelese x, akkor a masike osszeg-x. ||
Hint 2: || A jo felosztas az, ahol x a teljes osszeg felehez van a legkozelebb. ||
Hint 3: || A reszosszeg-DP-bol ugyanugy visszaepitheto az egyik geplistaja, mint egy hatizsakfeladatnal. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> time_needed(n + 1);
    int total = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> time_needed[i];
        total += time_needed[i];
    }

    vector<char> reachable(total + 1, false);
    vector<int> parent_item(total + 1, -1);
    vector<int> parent_sum(total + 1, -1);
    reachable[0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int sum = total; sum >= time_needed[i]; --sum) {
            if (!reachable[sum] && reachable[sum - time_needed[i]]) {
                reachable[sum] = true;
                parent_item[sum] = i;
                parent_sum[sum] = sum - time_needed[i];
            }
        }
    }

    int best_sum = 0;
    int best_time = total;
    for (int sum = 0; sum <= total; ++sum) {
        if (!reachable[sum]) {
            continue;
        }
        int finish = max(sum, total - sum);
        if (finish < best_time) {
            best_time = finish;
            best_sum = sum;
        }
    }

    vector<char> on_first(n + 1, false);
    for (int sum = best_sum; sum > 0; sum = parent_sum[sum]) {
        on_first[parent_item[sum]] = true;
    }

    cout << best_time << '\n';
    bool first_printed = false;
    for (int i = 1; i <= n; ++i) {
        if (on_first[i]) {
            if (first_printed) {
                cout << ' ';
            }
            cout << i;
            first_printed = true;
        }
    }
    cout << '\n';
    bool second_printed = false;
    for (int i = 1; i <= n; ++i) {
        if (!on_first[i]) {
            if (second_printed) {
                cout << ' ';
            }
            cout << i;
            second_printed = true;
        }
    }
    cout << '\n';
    return 0;
}