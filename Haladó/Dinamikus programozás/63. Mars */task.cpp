/*
Mivel korlatlanul sok jarmu all rendelkezesre, minden olyan kozetmintas pontot kulon jarmuvel is
ossze lehet szedni, amely rajta van legalabb egy ervenyes (1,1)-tol (M,N)-ig vezeto uton. Ezert
csak azt kell eldonteni minden mezonek, hogy elerheto-e a startbol, illetve eljuthato-e belole a
celba, mikozben csak jobbra vagy lefele lepunk es nem megyunk sziklaba. Az ilyen pontokat egy
elore es egy hatra iranyu dinamikus elerhetosegi tabla adja meg. A valasz azoknak az 1-es
mezoknek a szama, amelyek mindket feltetelt teljesitik.
*/
/*
Hint 1: || Egy minta csak akkor gyujtheto be, ha van rajta atmeno ervenyes ut a starttol a celig. ||
Hint 2: || Keszits kulon elerhetoseget bal-felso iranybol es kulon jobb-also iranybol. ||
Hint 3: || Korlátlan sok jarmu mellett az ilyen mintak mind megszerezhetok. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols;
    cin >> rows >> cols;

    vector<vector<int>> cell(rows + 1, vector<int>(cols + 1, 0));
    for (int row = 1; row <= rows; ++row) {
        for (int col = 1; col <= cols; ++col) {
            cin >> cell[row][col];
        }
    }

    vector<vector<char>> from_start(rows + 1, vector<char>(cols + 1, false));
    vector<vector<char>> to_finish(rows + 1, vector<char>(cols + 1, false));

    if (cell[1][1] != 2) {
        from_start[1][1] = true;
    }
    for (int row = 1; row <= rows; ++row) {
        for (int col = 1; col <= cols; ++col) {
            if (cell[row][col] == 2) {
                continue;
            }
            if (row > 1 && from_start[row - 1][col]) {
                from_start[row][col] = true;
            }
            if (col > 1 && from_start[row][col - 1]) {
                from_start[row][col] = true;
            }
        }
    }

    if (cell[rows][cols] != 2) {
        to_finish[rows][cols] = true;
    }
    for (int row = rows; row >= 1; --row) {
        for (int col = cols; col >= 1; --col) {
            if (cell[row][col] == 2) {
                continue;
            }
            if (row < rows && to_finish[row + 1][col]) {
                to_finish[row][col] = true;
            }
            if (col < cols && to_finish[row][col + 1]) {
                to_finish[row][col] = true;
            }
        }
    }

    int answer = 0;
    for (int row = 1; row <= rows; ++row) {
        for (int col = 1; col <= cols; ++col) {
            if (cell[row][col] == 1 && from_start[row][col] && to_finish[row][col]) {
                ++answer;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}