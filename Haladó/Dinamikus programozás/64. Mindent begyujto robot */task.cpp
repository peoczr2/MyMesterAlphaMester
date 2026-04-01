/*
Mivel a robot nem mehet balra, az oszlopokat balrol jobbra pontosan egyszer dolgozza fel. Egy
adott oszlopban eleg az ott levo alkatreszek legfelso es legalso sorat ismerni: ha ezeket a
szelso pontokat bejarjuk, akkor a kozottuk levo osszes alkatresz is automatikusan begyujtodik.
Csak az ilyen "jelentos" oszlopokat kell megtartani; az elso oszlophoz hozzavesszuk a startot,
az utolsohoz a celt. DP-ben azt taroljuk, mennyi ido kell addig, amig az aktualis jelentos oszlop
vegere erunk, es ott az intervallum also, illetve felso vegpontjaban allunk. A kovetkezo oszlopra
ugy lepunk at, hogy a koztuk levo vizszintes tavolsag fix, az aktualis oszlop intervallumat pedig
minimalis fuggoleges bejarassal fedezzuk le.
*/
/*
Hint 1: || Egy oszlopban eleg a legfelso es a legalso fontos sort figyelni. ||
Hint 2: || A robot egy oszlop teljes begyujtese utan optimalisan valamelyik szelso pontban all. ||
Hint 3: || Ugralj csak a fontos oszlopok kozott; a koztuk levo jobbra lepesek koltsege fix. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

static int cover_cost(int start_row, int end_row, int low, int high) {
    int span = high - low;
    int through_low = abs(start_row - low) + span + abs(high - end_row);
    int through_high = abs(start_row - high) + span + abs(low - end_row);
    return min(through_low, through_high);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols;
    cin >> rows >> cols;

    const int inf = numeric_limits<int>::max() / 4;
    vector<int> low(cols + 1, inf);
    vector<int> high(cols + 1, -1);

    while (true) {
        int row, col;
        cin >> row >> col;
        if (row == 0 && col == 0) {
            break;
        }
        low[col] = min(low[col], row);
        high[col] = max(high[col], row);
    }

    low[1] = min(low[1], 1);
    high[1] = max(high[1], 1);
    low[cols] = min(low[cols], rows);
    high[cols] = max(high[cols], rows);

    vector<int> important_columns;
    for (int col = 1; col <= cols; ++col) {
        if (high[col] != -1) {
            important_columns.push_back(col);
        }
    }

    int first_col = important_columns.front();
    int dp_low = cover_cost(1, low[first_col], low[first_col], high[first_col]);
    int dp_high = cover_cost(1, high[first_col], low[first_col], high[first_col]);
    int previous_col = first_col;
    int previous_low = low[first_col];
    int previous_high = high[first_col];

    for (int idx = 1; idx < static_cast<int>(important_columns.size()); ++idx) {
        int col = important_columns[idx];
        int delta = col - previous_col;
        int next_low = min(
            dp_low + delta + cover_cost(previous_low, low[col], low[col], high[col]),
            dp_high + delta + cover_cost(previous_high, low[col], low[col], high[col])
        );
        int next_high = min(
            dp_low + delta + cover_cost(previous_low, high[col], low[col], high[col]),
            dp_high + delta + cover_cost(previous_high, high[col], low[col], high[col])
        );

        dp_low = next_low;
        dp_high = next_high;
        previous_col = col;
        previous_low = low[col];
        previous_high = high[col];
    }

    cout << dp_high << '\n';
    return 0;
}