#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct Position {
    int row;
    int col;

    void print()
    {
        std::cout << "(" << row << ", " << col << ")" << std::endl;
    }
};

// moves
// change in row, change in col
std::pair<int, int> moves[]{
    std::pair(-2,  1), // Move Type 0
    std::pair(-1,  2), // Move Type 1
    std::pair( 1,  2), // Move Type 2
    std::pair( 2,  1), // Move Type 3
    std::pair( 2, -1), // Move Type 4
    std::pair( 1, -2), // Move Type 5
    std::pair(-1, -2), // Move Type 6
    std::pair(-2, -1)  // Move Type 7
};

const int MOVES_MAX = 8;

void assert_move_bounds(int move_type)
{
    if (move_type < 0 || move_type > MOVES_MAX) {
        throw std::invalid_argument(std::string("Invalid move type: ") + std::to_string(move_type));
    }
}


class Board {
    private:

    std::vector<std::vector<int>> board;
    int num_len{1};
    int num_rows{0};
    int num_cols{0};
    int move_num{1};
    int move_max{0};

    unsigned long long try_num{1};

    std::string num_to_string(int n)
    {
        std::stringstream sstream;
        sstream << std::setw(this->num_len) << std::setfill('0') << n;
        return sstream.str();
    }

    bool move_knight(Position pos, int move_type)
    {
        if (this->move_num > this->move_max)
        {
            return true;
        }

        Position new_pos;
        try
        { 
            new_pos = calc_move(pos, move_type);
        } catch (...) {
            return false;
        }

        if (is_occupied(new_pos)) 
        {
            return false;
        }

        try_num++;
        if (try_num % 100'000 == 0)
        {
            std::cout << "Try Number: " << try_num
                      << ", Move: " << this->move_num << " of " << this->move_max << std::endl;
        }

        set_square(new_pos);

        int new_move{0};
        for (; new_move < MOVES_MAX; new_move++)
        {
            if (move_knight(new_pos, new_move))
            {
                return true;
            }
        }

        if (new_move == MOVES_MAX) {
            move_num--;
            reset_square(new_pos);
        }

        return false;
    }

    Position calc_move(Position pos, int move_type)
    {
        assert_move_bounds(move_type);
        auto move = moves[move_type];

        Position new_pos = Position{pos.row + move.first, pos.col + move.second};

        assert_valid_position(new_pos);
        return new_pos;
    }

    void assert_valid_position(Position pos)
    {
        if (pos.row < 0 || pos.row >= this->num_rows ||
            pos.col < 0 || pos.col >= this->num_cols)
        {
            throw std::out_of_range(
                std::string("Invalid position: (Row: ") +
                std::to_string(pos.row) +
                " Col: " + std::to_string(pos.col) + ")");
        }
    }

    bool is_occupied(Position pos)
    {
        auto row = this->board.at(pos.row);
        return 0 != row.at(pos.col);
    }

    void set_square(Position pos, int value = -1)
    {
        assert_valid_position(pos);

        if (value < 0)
        {
            value = move_num;
            move_num++;
        }
        board[pos.row][pos.col] = value;
    }

    void reset_square(Position pos)
    {
        set_square(pos, 0);
    }

    public:
    Board(int num_rows, int num_cols)
    {
        // initialize the board
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        board.resize(num_rows, std::vector<int>(num_cols, 0));

        // set the number of digits for the numbers
        this->move_max = board.size() * board.at(0).size();
        num_len = std::to_string(this->move_max).length();
    }

    void solve(Position pos = Position{0, 0})
    {
        set_square(pos);

        for (int move = 0; move < MOVES_MAX; move++)
        {
           move_knight(pos, move);

            if (this->move_num > this->move_max)
            {
                std::cout << "SUCCESS!!! (" << this->try_num << " tries)" << std::endl;
                print();
                break;
            }
        }
    }

    void print()
    {
        for (auto row : board)
        {
            for (auto cell : row)
            {
                std::cout << num_to_string(cell) << " ";
            }
            std::cout << std::endl; 
        }
    }
};

int main() {
    Board board(8, 8);
    board.solve();
    return 0;
}