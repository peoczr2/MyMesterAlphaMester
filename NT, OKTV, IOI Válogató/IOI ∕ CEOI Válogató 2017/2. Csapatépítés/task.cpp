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
    for (int day = 1; day <= MAXD; ++day) {
        trainActive += trainDiff[day];
        offerActive += offerDiff[day];
        if (trainActive > 0 && offerActive > 0) {
            target[day] = 1;
            ++maxCoveredDays;
        }
    }

    priority_queue<pair<int, int>> pq;
    vector<int> answer;
    int nextStart = 1;
    int day = 1;
    while (day <= MAXD) {
        while (day <= MAXD && !target[day]) ++day;
        if (day > MAXD) break;

        while (nextStart <= day) {
            for (const auto &offer : starts[nextStart]) {
                pq.push(offer);
            }
            ++nextStart;
        }

        while (!pq.empty() && pq.top().first < day) pq.pop();
        if (pq.empty()) {
            ++day;
            continue;
        }

        auto [right, index] = pq.top();
        answer.push_back(index);
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