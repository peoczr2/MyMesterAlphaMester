/*
Megoldás lényege:
Az egyenlegeket egy tömbben tartjuk nyilván (1-től N-ig), és a változásokat sorban, egyenként dolgozzuk fel. Ha a sorszám nem nulla, akkor az adott tanuló egyenlegét módosítjuk. Ha a sorszám 0, akkor az osztályra vonatkozó kiadást úgy osztjuk el, hogy minden tanuló a saját, egészre felfelé kerekített részét fizeti: ezt a részt (|x| + N - 1) / N adja, és minden tanulótól levonjuk. Az egyenlegek negatívba is mehetnek, ezért long long típust használunk. Az időigény O(K + N), a memóriaigény O(N).
*/
/*
Hint 1: || A változásokat nem kell eltárolni: a bemenet sorai sorrendben feldolgozhatók, elég az N darab egyenleget nyilván tartani. ||
Hint 2: || Osztályszintű kiadásnál az egy főre eső rész felfelé kerekített egész osztás: (|x| + N - 1) / N, és ezt kell minden tanulóra alkalmazni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> balance(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> balance[i];
    }

    for (int j = 0; j < k; j++) {
        int student;
        long long change;
        cin >> student >> change;

        if (student == 0) {
            long long share = (llabs(change) + n - 1) / n;
            if (change < 0) {
                share = -share;
            }
            for (int i = 1; i <= n; i++) {
                balance[i] += share;
            }
        } else {
            balance[student] += change;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << balance[i] << "\n";
    }
    return 0;
}
