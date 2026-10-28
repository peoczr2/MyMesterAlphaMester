/*
Megoldás lényege:
A maximálisan lefedhető tréningnapok száma egyszerűen azoknak a napoknak a száma,
amelyeket legalább egy ajánlat lefed. Ezt két különbségi tömbbel számoljuk ki:
egyik a tréningnapokat, másik az ajánlatok unióját jelöli.

Ezután a célhalmaz minden napját minimális számú ajánlattal kell lefedni. Ez a
szokásos egydimenziós intervallumfedés: mindig a bal szélső még lefedetlen célpontnál
azt az ajánlatot választjuk, amelyik balról még eléri ezt a pontot és jobbra a
legtovább nyúlik. A napok száma és az ajánlatok határai legfeljebb 100000, ezért
egy napi söprés és egy prioritási sor elég gyors.
*/
/*
Hint 1: || Egy nap akkor számít, ha van rajta tréning és legalább egy ajánlat is lefedi. Napi söpréssel (különbségi tömbökkel) minden napra eldönthető, hogy mindkét feltétel teljesül-e. ||
Hint 2: || A kapott célnapokat kell a legkevesebb ajánlattal lefedni. Mindig a bal szélső, még le nem fedett célnapot vegyük, és azt az ajánlatot, amely már elkezdődött és a legtovább tart. ||
Hint 3: || Az ajánlatokat kezdőnapjuk szerint haladva prioritási sorba tesszük végpont szerint rendezve. A már lejárt ajánlatokat a sor tetejéről eldobjuk. Azonos végpontnál a kisebb sorszámút válasszuk. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MAXD = 100000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    if (!(cin >> M >> N)) return 0;

    vector<int> trainDiff(MAXD + 3, 0), offerDiff(MAXD + 3, 0);
    for (int i = 0; i < M; ++i) {
        int l, r;
        cin >> l >> r;
        ++trainDiff[l];
        --trainDiff[r + 1];
    }

    vector<vector<pair<int, int>>> starts(MAXD + 2);
    for (int i = 1; i <= N; ++i) {
        int l, r;
        cin >> l >> r;
        ++offerDiff[l];
        --offerDiff[r + 1];
        starts[l].push_back({r, i});
    }

    vector<char> target(MAXD + 2, 0);
    int trainActive = 0, offerActive = 0;
    int maxCoveredDays = 0;
    for (int day = 0; day <= MAXD; ++day) {
        trainActive += trainDiff[day];
        offerActive += offerDiff[day];
        if (trainActive > 0 && offerActive > 0) {
            target[day] = 1;
            ++maxCoveredDays;
        }
    }

    priority_queue<pair<int, int>> pq;
    vector<int> answer;
    int nextStart = 0;
    int day = 0;
    while (day <= MAXD) {
        while (day <= MAXD && !target[day]) ++day;
        if (day > MAXD) break;

        while (nextStart <= day) {
            for (const auto &offer : starts[nextStart]) {
                pq.push({offer.first, -offer.second});
            }
            ++nextStart;
        }

        while (!pq.empty() && pq.top().first < day) pq.pop();
        if (pq.empty()) {
            ++day;
            continue;
        }

        auto [right, negIndex] = pq.top();
        answer.push_back(-negIndex);
        day = right + 1;
    }

    cout << maxCoveredDays << '\n';
    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}