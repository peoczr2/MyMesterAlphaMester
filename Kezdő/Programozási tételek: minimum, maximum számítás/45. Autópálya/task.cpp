/*
Megoldás lényege:
Az észlelések időrendben érkeznek, ezért egy autó pályán töltött ideje az első és az utolsó megfigyelésének időkülönbsége. Mivel a napok nincsenek megadva, de az időrend adott, az óra-perc érték csökkenésekor egy nappal (1440 perccel) előrébb toljuk az időt, így az éjfélen átnyúló út is helyesen számolódik. Autónként tároljuk az első és az utolsó időpontot, valamint az utolsó megfigyelt helyét. Két egymást követő megfigyelés egy irányított szakaszt jelent (A-ból B-be ment), ezt egy 2D számlálótömbben növeljük. A legforgalmasabb szakasz a legnagyobb számlálójú (A, B) pár: egyenlőségnél a kisebb A, majd a kisebb B nyer. Az időigény O(M log K + N), a memóriaigény O(N² + K).
*/
/*
Hint 1: || Autónként elég az első és az utolsó megfigyelés idejét, valamint az utolsó megfigyelt helyet tárolni. Az autókat a rendszámuk alapján azonosítsd. ||
Hint 2: || Ha egy autót két egymás utáni megfigyelésnél különböző hely követ, az autó ezen az egyirányú szakaszon haladt át. Ezt egy számlálótömbben (A-ból B-be) növeld, és a végén csak a legnagyobb számú párt keresd meg. ||
Hint 3: || Az autó pályán töltött ideje a két szélső megfigyelés időkülönbsége percben. Ha egy megfigyelés óra-perc értéke kisebb az előzőnél, az időrend szerint már másnapra léptünk, ezért ekkor adj hozzá 1440 percet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int places, observations;
    cin >> places >> observations;

    map<string, int> carId;
    vector<string> plates;
    vector<long long> firstTime, lastTime;
    vector<int> lastPlace;
    vector<vector<int>> dirCount(places + 2, vector<int>(places + 2, 0));

    long long dayOffset = 0;
    long long prevClock = -1;

    for (int i = 0; i < observations; i++) {
        string plate;
        int place, hour, minute;
        cin >> plate >> place >> hour >> minute;

        long long clock = hour * 60 + minute;
        if (prevClock >= 0 && clock < prevClock) {
            dayOffset += 24 * 60;
        }
        prevClock = clock;
        long long now = dayOffset + clock;

        auto it = carId.find(plate);
        if (it == carId.end()) {
            int id = plates.size();
            carId[plate] = id;
            plates.push_back(plate);
            firstTime.push_back(now);
            lastTime.push_back(now);
            lastPlace.push_back(place);
        } else {
            int id = it->second;
            dirCount[lastPlace[id]][place]++;
            lastPlace[id] = place;
            lastTime[id] = now;
        }
    }

    cout << plates.size() << "\n";
    for (size_t id = 0; id < plates.size(); id++) {
        cout << plates[id] << " " << (lastTime[id] - firstTime[id]) << (id + 1 < plates.size() ? " " : "");
    }
    cout << "\n";

    int bestA = 1, bestB = 2, bestCount = -1;
    for (int a = 1; a <= places; a++) {
        for (int b = a - 1; b <= a + 1; b += 2) {
            if (b < 1 || b > places) continue;
            if (dirCount[a][b] > bestCount) {
                bestCount = dirCount[a][b];
                bestA = a;
                bestB = b;
            }
        }
    }
    cout << bestA << " " << bestB << "\n";
    return 0;
}
