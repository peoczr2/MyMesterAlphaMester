/*
Megoldás:
Balról jobbra dolgozunk, és mindig fenntartjuk, hogy az eddig eltárolt programszuffix már nem
egyszerűsíthető korábbi helyen. Az újonnan beolvasott utasítást a végére tesszük, majd csak a végén
próbálunk rewrite-okat végrehajtani. Ez pontosan megfelel annak a megkötésnek, hogy csak akkor
szabad későbbi ponton átalakítani, ha előrébb már nincs lehetőség.

Az eljárás lényege egy veremszerű utasítástömb. A végén összevonjuk a szomszédos forgásokat,
illetve a tollállapottól függően az összevonható mozgásokat. Ha a végére egy újabb UP vagy DOWN
kerül, akkor visszanézünk az előző tollállító utasításig, és ellenőrizzük a szabályokban szereplő
mintákat: UP-forgások-DOWN, DOWN-forgások-UP, valamint a redundáns UP-...-UP és DOWN-...-DOWN
eseteket. Minden összevonás után újra megpróbáljuk a végszuffixet egyszerűsíteni.

Így minden rewrite a lehető legbaloldalibb érvényes helyen történik meg, és az eredmény a feladat
által kért normalizált program lesz.
*/
/*
Hint 1: || Nem kell újra és újra az egész programot végignézni: ha balról jobbra normalizálsz, mindig csak a legvége változhat meg. ||
Hint 2: || A mozgások összevonhatósága attól függ, hogy a két utasítás elején le volt-e engedve a toll. ||
Hint 3: || Az UP/DOWN szabályok mindig a két tollállító utasítás közti utasításblokkra vonatkoznak. ||
*/

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Type {
    Forward,
    Back,
    Left,
    Right,
    Up,
    Down,
};

struct Command {
    Type type;
    long long value;
};

bool isMove(Type type) {
    return type == Type::Forward || type == Type::Back;
}

bool isRotation(Type type) {
    return type == Type::Left || type == Type::Right;
}

bool isPen(Type type) {
    return type == Type::Up || type == Type::Down;
}

bool sameSign(long long a, long long b) {
    return (a > 0 && b > 0) || (a < 0 && b < 0);
}

bool oppositeSign(long long a, long long b) {
    return (a > 0 && b < 0) || (a < 0 && b > 0);
}

string nameOf(Type type) {
    switch (type) {
        case Type::Forward: return "FORWARD";
        case Type::Back: return "BACK";
        case Type::Left: return "LEFT";
        case Type::Right: return "RIGHT";
        case Type::Up: return "UP";
        case Type::Down: return "DOWN";
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Command> program;
    vector<int> penAfter;

    auto penBefore = [&](int index) {
        if (index == 0) {
            return 1;
        }
        return penAfter[index - 1];
    };

    auto appendCommand = [&](const Command &command) {
        int before = program.empty() ? 1 : penAfter.back();
        int after = before;
        if (command.type == Type::Up) {
            after = 0;
        } else if (command.type == Type::Down) {
            after = 1;
        }
        program.push_back(command);
        penAfter.push_back(after);
    };

    auto popBack = [&]() {
        program.pop_back();
        penAfter.pop_back();
    };

    auto setCommand = [&](int index, const Command &command) {
        program[index] = command;
        int before = (index == 0 ? 1 : penAfter[index - 1]);
        int after = before;
        if (command.type == Type::Up) {
            after = 0;
        } else if (command.type == Type::Down) {
            after = 1;
        }
        penAfter[index] = after;
        for (int i = index + 1; i < static_cast<int>(program.size()); ++i) {
            int current = penAfter[i - 1];
            if (program[i].type == Type::Up) {
                current = 0;
            } else if (program[i].type == Type::Down) {
                current = 1;
            }
            penAfter[i] = current;
        }
    };

    auto eraseSuffixSegment = [&](int left, int right, const vector<Command> &replacement) {
        while (static_cast<int>(program.size()) > left) {
            popBack();
        }
        for (const Command &command : replacement) {
            appendCommand(command);
        }
    };

    auto tryReduce = [&]() -> bool {
        if (program.empty()) {
            return false;
        }

        int last = static_cast<int>(program.size()) - 1;
        if ((isMove(program[last].type) || isRotation(program[last].type)) && program[last].value == 0) {
            popBack();
            return true;
        }

        if (program.size() >= 2) {
            int first = static_cast<int>(program.size()) - 2;
            int second = static_cast<int>(program.size()) - 1;

            if (isRotation(program[first].type) && isRotation(program[second].type)) {
                long long newValue = program[first].value;
                if (program[first].type == program[second].type) {
                    newValue += program[second].value;
                } else {
                    newValue -= program[second].value;
                }
                Command merged{program[first].type, newValue};
                popBack();
                setCommand(first, merged);
                return true;
            }

            if (isMove(program[first].type) && isMove(program[second].type)) {
                bool penDown = penBefore(first) == 1;
                bool canMerge = !penDown;
                if (penDown) {
                    if (program[first].type == program[second].type) {
                        canMerge = sameSign(program[first].value, program[second].value);
                    } else {
                        canMerge = oppositeSign(program[first].value, program[second].value);
                    }
                }
                if (canMerge) {
                    long long newValue = program[first].value;
                    if (program[first].type == program[second].type) {
                        newValue += program[second].value;
                    } else {
                        newValue -= program[second].value;
                    }
                    Command merged{program[first].type, newValue};
                    popBack();
                    setCommand(first, merged);
                    return true;
                }
            }
        }

        if (isPen(program.back().type)) {
            int end = static_cast<int>(program.size()) - 1;
            int start = end;
            while (start > 0 && !isPen(program[start - 1].type)) {
                --start;
            }
            if (start >= 1) {
                --start;
            } else if (!isPen(program[0].type)) {
                return false;
            }

            if (!isPen(program[start].type)) {
                return false;
            }

            int before = penBefore(start);
            bool onlyRotations = true;
            bool onlyMoveOrRotation = (end - start >= 2);
            for (int i = start + 1; i < end; ++i) {
                onlyRotations = onlyRotations && isRotation(program[i].type);
                onlyMoveOrRotation = onlyMoveOrRotation && (isMove(program[i].type) || isRotation(program[i].type));
            }

            if (program[start].type == Type::Down && program[end].type == Type::Up && before == 0 && end - start >= 2 && onlyRotations) {
                vector<Command> replacement(program.begin() + start + 1, program.begin() + end);
                eraseSuffixSegment(start, end, replacement);
                return true;
            }
            if (program[start].type == Type::Up && program[end].type == Type::Down && before == 1 && end - start >= 2 && onlyRotations) {
                vector<Command> replacement(program.begin() + start + 1, program.begin() + end);
                eraseSuffixSegment(start, end, replacement);
                return true;
            }
            if (program[start].type == Type::Down && program[end].type == Type::Down && end - start >= 2 && onlyMoveOrRotation) {
                popBack();
                return true;
            }
            if (program[start].type == Type::Up && program[end].type == Type::Up && end - start >= 2 && onlyMoveOrRotation) {
                popBack();
                return true;
            }
        }

        return false;
    };

    string token;
    while (cin >> token) {
        Command command;
        if (token == "FORWARD") {
            command.type = Type::Forward;
            cin >> command.value;
        } else if (token == "BACK") {
            command.type = Type::Back;
            cin >> command.value;
        } else if (token == "LEFT") {
            command.type = Type::Left;
            cin >> command.value;
        } else if (token == "RIGHT") {
            command.type = Type::Right;
            cin >> command.value;
        } else if (token == "UP") {
            command.type = Type::Up;
            command.value = 0;
        } else {
            command.type = Type::Down;
            command.value = 0;
        }

        appendCommand(command);
        while (tryReduce()) {
        }
    }

    for (const Command &command : program) {
        cout << nameOf(command.type);
        if (isMove(command.type) || isRotation(command.type)) {
            cout << ' ' << command.value;
        }
        cout << '\n';
    }

    return 0;
}