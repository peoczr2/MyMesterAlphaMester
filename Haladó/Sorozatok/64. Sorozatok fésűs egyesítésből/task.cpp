/*
Megoldas lenyege:
A bemeneti sorozatot ket monoton novekvo reszsorozatba kell szetosztani ugy, hogy az elemek
eredeti sorrendje mindket reszsorozatban megmaradjon. Ez pontosan ket nemcsokkeno reszsorozatra
valo felbontas.

Balrol jobbra haladva ket utolso erteket tartunk fenn. Az aktualis x elemet arra a sorozatra
erdemes tenni, amelyikbe beteheto es amelynek az utolso eleme a leheto legnagyobb, de nem
nagyobb x-nel. Ha egyik sorozatba sem fer, akkor nincs megoldas. A greedy azert jo, mert a
masik sorozatnak a kisebb farok nagyobb mozgasteret hagy.
*/
/*
Hint 1: || Itt az a lenyeg, hogy az eredeti sorrend mindket sorozatban megmaradjon. ||
Hint 2: || Egy elemet csak olyan sorozat vegere tehetsz, amelynek utolso eleme legfeljebb o. ||
Hint 3: || Ha mindket hely jo, a nagyobb farokhoz erdemes illeszteni az uj elemet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> first, second;
    int tail1 = INT_MIN, tail2 = INT_MIN;

    for (int x : a) {
        bool can1 = tail1 <= x;
        bool can2 = tail2 <= x;
        if (!can1 && !can2) {
            cout << "0 0\n";
            return 0;
        }

        if (can1 && can2) {
            if (tail1 >= tail2) {
                first.push_back(x);
                tail1 = x;
            } else {
                second.push_back(x);
                tail2 = x;
            }
        } else if (can1) {
            first.push_back(x);
            tail1 = x;
        } else {
            second.push_back(x);
            tail2 = x;
        }
    }

    cout << first.size() << '\n';
    for (int i = 0; i < (int)first.size(); ++i) {
        if (i) cout << ' ';
        cout << first[i];
    }
    cout << '\n';

    cout << second.size() << '\n';
    for (int i = 0; i < (int)second.size(); ++i) {
        if (i) cout << ' ';
        cout << second[i];
    }
    cout << '\n';
    return 0;
}