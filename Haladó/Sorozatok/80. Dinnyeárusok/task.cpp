/*
Megoldás lényege:
A lakhelyek és az árusítóhelyek is rendezettek. Ha a legbaloldalibb még fel nem használt ember és
a legbaloldalibb még fel nem használt hely túl messze vannak egymástól, akkor biztosan azt a baloldali
elemet kell eldobni, amelyik már a másik számára sem lehet jó később.

Ezért két mutatóval greedyn végigmehetünk a két rendezett sorozaton. Ha az aktuális ember és hely
illeszthető, akkor párosítjuk őket; különben a balabbra fekvő, reménytelen elemet tovább léptetjük.
*/
/*
Hint 1: || A bemenet mindkét oldalon rendezett. ||
Hint 2: || Ha egy hely még a legkorábbi szóba jövő embernek is túl balra van, akkor később sem lesz jó senkinek. ||
Hint 3: || Illeszkedés esetén érdemes az aktuális legbaloldalibb párt rögtön összepárosítani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> people(n);
    for (int &x : people) cin >> x;

    int m;
    cin >> m;
    vector<int> places(m);
    for (int &x : places) cin >> x;

    int k;
    cin >> k;

    int i = 0, j = 0, answer = 0;
    while (i < n && j < m) {
        if (places[j] < people[i] - k) {
            ++j;
        } else if (places[j] > people[i] + k) {
            ++i;
        } else {
            ++answer;
            ++i;
            ++j;
        }
    }

    cout << answer << '\n';
    return 0;
}