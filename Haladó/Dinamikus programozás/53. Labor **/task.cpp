/*
Ha kiválasztunk néhány kémcsövet, és a folyadékukat egymásba öntjük, akkor minden alkalommal,
amikor egy cső megtelik, K egységnyi mennyiség "kiesik" a folyamatból. Ezért egy részhalmazból
előállítható, nem tele mennyiséget csak a részhalmaz összegének K szerinti maradéka határozza
meg. Emiatt elég dinamikus programozással nyilvántartani, hogy mely maradékok állíthatók elő
részhalmaz-összegként.
Ezen felül a 0 akkor és csak akkor állítható elő, ha az összes folyadék elfér legfeljebb N-1
kémcsőben, vagyis az összmennyiség legfeljebb (N-1)*K. A K mennyiség pedig akkor állítható elő,
ha legalább K egységnyi folyadék van összesen.
*/
/*
Hint 1: || Egy részhalmaz összegének K-val osztható része csak teli kémcsöveket ad, a maradék lesz az érdekes. ||
Hint 2: || Ezért 0 és K-1 között elég azt tárolni, hogy mely maradékok érhetők el részhalmaz-összegként. ||
Hint 3: || A 0 és a K speciális: ezekre külön, az összmennyiségből következő feltétel adódik. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> amount(n);
    long long total = 0;
    for (int index = 0; index < n; ++index) {
        cin >> amount[index];
        total += amount[index];
    }

    vector<char> reachable(k, false);
    reachable[0] = true;

    for (int current : amount) {
        vector<char> next = reachable;
        for (int remainder = 0; remainder < k; ++remainder) {
            if (reachable[remainder]) {
                next[(remainder + current) % k] = true;
            }
        }
        reachable.swap(next);
    }

    vector<int> answer;
    if (total <= 1LL * (n - 1) * k) {
        answer.push_back(0);
    }
    for (int value = 1; value < k; ++value) {
        if (reachable[value]) {
            answer.push_back(value);
        }
    }
    if (total >= k) {
        answer.push_back(k);
    }

    cout << answer.size() << '\n';
    for (int index = 0; index < static_cast<int>(answer.size()); ++index) {
        if (index > 0) {
            cout << ' ';
        }
        cout << answer[index];
    }
    cout << '\n';
    return 0;
}