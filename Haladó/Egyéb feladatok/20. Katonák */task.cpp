/*
Megoldás:
Mivel pontosan N katona van egy N x N táblán, a kívánt végállapotban minden sorban és minden
oszlopban pontosan egy katona áll. A teljes lépésszám a vízszintes és függőleges elmozdulások
összege, ezért ez a két irány egymástól függetlenül optimalizálható.

Az optimális oszlop-hozzárendelés az, hogy az x koordináta szerint rendezett katonák a 1..N
oszlopokat kapják. Ugyanígy az optimális sor-hozzárendelés az, hogy az y koordináta szerint rendezett
katonák az 1..N sorokat kapják. Ez minimális Manhattan-összköltséget ad.

A mozgássor előállításához először függőlegesen mozgatunk. Egy adott oszlopban a katonák sorrendje
nem változik meg, ezért a lefelé mozgó katonákat alulról fölfelé, a felfelé mozgókat felülről lefelé
mozgatva mindenki a legrövidebb úton eljut a céljába ütközés nélkül. Ezután minden sorban már
pontosan egy katona áll, így a vízszintes mozgatások tetszőleges sorrendben, szintén közvetlenül
elvégezhetők.

Az algoritmus O(N log N) idejű a rendezések miatt, a parancsok száma legfeljebb 2N.
*/
/*
Hint 1: || A minimális összes vízszintes eltolás ugyanaz a klasszikus párosítási feladat, mint amikor rendezett pontokat rendezett célokhoz illesztünk. ||
Hint 2: || A sor- és oszlopcélokat egymástól függetlenül is ki lehet számolni, mert a Manhattan-távolság szétválik két részre. ||
Hint 3: || Ha először mindenkit a cél-sorába viszel, utána minden sorban csak egy katona marad, így a vízszintes mozgatás már nem tud ütközni. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Soldier {
    int id;
    int x;
    int y;
    int targetX;
    int targetY;
    int currentX;
    int currentY;
};

struct Command {
    int x;
    int y;
    char dir;
    int steps;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Soldier> soldiers(n);
    for (int i = 0; i < n; ++i) {
        cin >> soldiers[i].x >> soldiers[i].y;
        soldiers[i].id = i;
        soldiers[i].currentX = soldiers[i].x;
        soldiers[i].currentY = soldiers[i].y;
    }

    vector<int> orderX(n), orderY(n);
    for (int i = 0; i < n; ++i) {
        orderX[i] = i;
        orderY[i] = i;
    }

    sort(orderX.begin(), orderX.end(), [&](int left, int right) {
        if (soldiers[left].x != soldiers[right].x) {
            return soldiers[left].x < soldiers[right].x;
        }
        if (soldiers[left].y != soldiers[right].y) {
            return soldiers[left].y < soldiers[right].y;
        }
        return soldiers[left].id < soldiers[right].id;
    });
    sort(orderY.begin(), orderY.end(), [&](int left, int right) {
        if (soldiers[left].y != soldiers[right].y) {
            return soldiers[left].y < soldiers[right].y;
        }
        if (soldiers[left].x != soldiers[right].x) {
            return soldiers[left].x < soldiers[right].x;
        }
        return soldiers[left].id < soldiers[right].id;
    });

    for (int i = 0; i < n; ++i) {
        soldiers[orderX[i]].targetX = i + 1;
        soldiers[orderY[i]].targetY = i + 1;
    }

    long long totalTime = 0;
    for (const Soldier &soldier : soldiers) {
        totalTime += abs(soldier.targetX - soldier.x) + abs(soldier.targetY - soldier.y);
    }

    vector<vector<int>> columns(n + 1);
    for (int i = 0; i < n; ++i) {
        columns[soldiers[i].currentX].push_back(i);
    }
    for (int x = 1; x <= n; ++x) {
        sort(columns[x].begin(), columns[x].end(), [&](int left, int right) {
            return soldiers[left].currentY < soldiers[right].currentY;
        });
    }

    vector<Command> commands;

    for (int x = 1; x <= n; ++x) {
        for (int id : columns[x]) {
            if (soldiers[id].targetY < soldiers[id].currentY) {
                commands.push_back({soldiers[id].currentX, soldiers[id].currentY, 'L', soldiers[id].currentY - soldiers[id].targetY});
                soldiers[id].currentY = soldiers[id].targetY;
            }
        }
        for (int pos = static_cast<int>(columns[x].size()) - 1; pos >= 0; --pos) {
            int id = columns[x][pos];
            if (soldiers[id].targetY > soldiers[id].currentY) {
                commands.push_back({soldiers[id].currentX, soldiers[id].currentY, 'F', soldiers[id].targetY - soldiers[id].currentY});
                soldiers[id].currentY = soldiers[id].targetY;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (soldiers[i].targetX < soldiers[i].currentX) {
            commands.push_back({soldiers[i].currentX, soldiers[i].currentY, 'B', soldiers[i].currentX - soldiers[i].targetX});
            soldiers[i].currentX = soldiers[i].targetX;
        } else if (soldiers[i].targetX > soldiers[i].currentX) {
            commands.push_back({soldiers[i].currentX, soldiers[i].currentY, 'J', soldiers[i].targetX - soldiers[i].currentX});
            soldiers[i].currentX = soldiers[i].targetX;
        }
    }

    vector<int> yByX(n + 1);
    for (const Soldier &soldier : soldiers) {
        yByX[soldier.targetX] = soldier.targetY;
    }

    cout << totalTime << '\n';
    for (int x = 1; x <= n; ++x) {
        if (x > 1) {
            cout << ' ';
        }
        cout << yByX[x];
    }
    cout << '\n';

    cout << commands.size() << '\n';
    for (const Command &command : commands) {
        cout << command.x << ' ' << command.y << ' ' << command.dir << ' ' << command.steps << '\n';
    }

    return 0;
}