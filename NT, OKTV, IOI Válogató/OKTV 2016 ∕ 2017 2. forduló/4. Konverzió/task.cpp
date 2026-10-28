/*
Megoldás lényege: a posztfix kifejezést veremmel dolgozzuk fel. A változók egyedi elemként kerülnek a verembe, a műveleti jel a két felső részkifejezésből új részkifejezést készít. Minden részkifejezéshez eltároljuk a legkülső művelete erősségét (változó, szorzás-osztás vagy összeadás-kivonás), és ez alapján döntjük el, kell-e zárójel. A bal oldalon zárójel kell, ha az operandus gyengébb műveletű, mint a jel. A jobb oldalon akkor kell zárójel, ha az operandus gyengébb, vagy azonos erősségű és a művelet kivonás vagy osztás. Összeadásnál a jobb oldal soha nem kap zárójelet, így minimális zárójelezés adódik. Az időigény a kifejezés hosszában lineáris, a sztringek másolása miatt legfeljebb négyzetes, de 1000 karakternél ez bőven belefér.
*/
/*
Hint 1: || A verem segítségével egyetlen balról jobbra haladó bejárással megoldható; minden részkifejezéshez tárold, melyik művelet áll a legkülső szinten. ||
Hint 2: || Zárójelet csak akkor tegyél, ha a műveleti sorrend miatt másképp nem lenne helyes. Figyelj a jobb oldalra: kivonásnál és osztásnál az azonos erősségű részkifejezés is zárójelet kér, összeadásnál viszont soha nem kell zárójel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    // a verem elemei: (kifejezés szövege, erősség); 3 = változó, 2 = * vagy /, 1 = + vagy -
    vector<pair<string, int>> st;
    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            st.push_back({string(1, c), 3});
            continue;
        }
        pair<string, int> r = st.back();
        st.pop_back();
        pair<string, int> l = st.back();
        st.pop_back();

        int pr = (c == '+' || c == '-') ? 1 : 2;
        string ls = l.first, rs = r.first;
        if (l.second < pr) ls = "(" + ls + ")";
        if (r.second < pr || (r.second == pr && (c == '-' || c == '/'))) rs = "(" + rs + ")";
        st.push_back({ls + c + rs, pr});
    }

    cout << st.back().first << '\n';
    return 0;
}
