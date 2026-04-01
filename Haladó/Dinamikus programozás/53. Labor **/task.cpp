/*
Ha kivalasztunk nehany kemcsovet, es ezek folyadekat egymasba ontjuk, akkor minden tele csove
valas utan ujabb K egysegnyi mennyiseget "levagunk", ezert egy reszhalmazbol eloallithato nem
tele mennyiseget csak a reszhalmaz osszegenek K szerinti maradeka hatarozza meg. Emiatt eleg
dinamikus programozassal nyilvantartani, hogy mely maradekok allithatok elo reszhalmazosszegkent.
Ezen felul a 0 akkor es csak akkor allithato elo, ha az osszes folyadek elfer legfeljebb N-1
kemcsoben, vagyis az osszmennyiseg legfeljebb (N-1)*K. A K mennyiseg pedig akkor allithato elo,
ha legalabb K egysegnyi folyadek van osszesen.
*/
/*
Hint 1: || Egy reszhalmaz tartalmanal a teljes K-k csak megtoltott kemcsoveket adnak, a maradek lesz az erdekes. ||
Hint 2: || Ezert 0..K-1 kozott eleg azt tarolni, milyen maradekok erhetok el reszhalmazosszegkent. ||
Hint 3: || A 0 es a K specialis: ezekre kulon, az osszmennyisegbol kovetkezo feltetel adodik. ||
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