#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef pair<int,int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define REP(i,a,b) for (int i = a; i <= b; i++)

// return the indices of all squares in a box, given the index of one square
vector<pi> get_box_indices(int row, int col) {
    int rel_row = row % 3;
    int row_box = (row - rel_row);
    int rel_col = col % 3;
    int col_box = (col - rel_col);
    vector<pi> indices;
    REP(i, 0, 2) {
        REP(j, 0, 2) {
            indices.PB(make_pair(row_box + i, col_box + j));
        }
    }
    return indices;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int board[9][9];
    REP(i, 0, 8) {
        REP(j, 0, 8) {
            char ij;
            cin >> ij;
            board[i][j] = ij - '0';
        }
    }

    // test input
    /*REP(i, 0, 8) {
        REP(j, 0, 8) {
            cout << board[i][j];
        }
        cout << "\n";
    }*/

    set<int> choices[9][9];
    bool solved = false;

    int all_numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    REP(i, 0, 8) {
        REP(j, 0, 8) {
            set<int> temp (all_numbers, all_numbers + 9);
            choices[i][j] = temp;
        }
    }

    while(!solved) {
        solved = true;
        REP(row, 0, 8) {
            REP(col, 0, 8) {
                if (board[row][col] == 0) {
                    solved = false;
                    // check if only one possibility remains
                    if (choices[row][col].size() == 1) {
                        board[row][col] = *choices[row][col].begin();
                        continue;
                    }
                    set<int> to_be_removed;
                    for (auto num : choices[row][col]) {
                        bool found_num = false;
                        // check row
                        REP(j, 0, 8) {
                            if (board[row][j] == num) {
                                to_be_removed.insert(num);
                                found_num = true;
                                break;
                            }
                        }
                        if (found_num) continue;
                        // check col
                        REP(i, 0, 8) {
                            if (board[i][col] == num) {
                                to_be_removed.insert(num);
                                found_num = true;
                                break;
                            }
                        }
                        if (found_num) continue;
                        // check box
                        int rel_row = row % 3;
                        int row_box = (row - rel_row);
                        int rel_col = col % 3;
                        int col_box = (col - rel_col);
                        REP(i, 0, 2) {
                            REP(j, 0, 2) {
                                if (board[row_box + i][col_box + j] == num) {
                                    to_be_removed.insert(num);
                                    found_num = true;
                                    break;
                                }
                            }
                        }
                    }
                    // remove the possibilities already present
                    for (auto num : to_be_removed) {
                        choices[row][col].erase(num);
                    }
                    // check again if only one possibility remains
                    if (choices[row][col].size() == 1) {
                        board[row][col] = *choices[row][col].begin();
                        continue;
                    }
                }
            }
        }
        cout << "---------\n";
        REP(i, 0, 8) {
            REP(j, 0, 8) {
                cout << board[i][j];
            }
            cout << "\n";
        }
    }
}
