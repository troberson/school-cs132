////
// Author:       Tamara Roberson
// Section:      S
// Assignment:   #1
// Description:  Knight's Tour (Minimal version)
// A knight on a chessboard can move 2 steps in one direction and 1
// step at a right angle or vice versa. Can a knight start on any
// position and reach all squares on the board without standing on one
// twice? Board size and starting position in this impilementation are
// hard-coded in main(). Program prints status updates and final
// result to stdout.
////

#include <iomanip> 
#include <iostream>
#include <vector>

using namespace std;

int moves[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};

class Game
{
    vector<vector<int>> board;
    int num_rows, num_cols, num_squares;
    int squares{1};
    unsigned long long tries{1};

    bool move_knight(int row, int col, int* move)
    {
        if (squares >= num_squares)
            return true;

        int new_row = row + move[0];
        int new_col = col + move[1];
        if (new_row < 0 || new_row > num_rows - 1 || new_col < 0 || new_col > num_cols - 1)
            return false;

        int& cell = board[new_row][new_col];
        if (cell)
            return false;

        tries++;
        if (tries % 100000 == 0)
            cout << tries << endl;

        cell = ++squares;

        for (auto& m:moves) {
            if (move_knight(new_row, new_col, m))
                return true;
        }

        squares--;
        cell = 0;
        return false;
    }

    public:
    Game(int rows, int cols) : num_rows(rows), num_cols(cols)
    {
        num_squares = rows * cols;
        board.resize(rows);
        for (auto& r:board)
            r.resize(cols);
    }

    void solve(int start_row = 0, int start_col = 0)
    {
        board[start_row][start_col] = squares;

        for (auto& m:moves) {
            if (move_knight(start_row, start_col, m))
                break;
        }

        cout << tries << endl;
        for (auto& r:board) {
            for (auto& c:r) {
                cout << setw(2) << setfill('0') << c << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Game(8,8).solve();
    return 0;
}
