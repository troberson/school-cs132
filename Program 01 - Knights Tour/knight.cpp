#include <array> // std::array
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Position
{
    int row;
    int col;

    public:

    Position(int row = 0, int col = 0) : row(row), col(col)
    {
    }

    int get_row()
    {
        return row;
    }

    int get_col()
    {
        return col;
    }

    void print()
    {
        std::cout << "(" << row << ", " << col << ")" << std::endl;
    }

    Position operator+(Position &rhs) const
    {
        return Position(row + rhs.get_row(), col + rhs.get_col());
    }
};

class Move : public Position
{
    public:
    using Position::Position;
};

namespace KnightMoves
{
    namespace
    {
        // moves
        // change in row, change in col
        const std::array moves {
            Move(-2,  1), // Move Type 0
            Move(-1,  2), // Move Type 1
            Move( 1,  2), // Move Type 2
            Move( 2,  1), // Move Type 3
            Move( 2, -1), // Move Type 4
            Move( 1, -2), // Move Type 5
            Move(-1, -2), // Move Type 6
            Move(-2, -1)  // Move Type 7
        };

        void assert_move_bounds(int move_type)
        {
            if (move_type < 0 || move_type >= moves.size()) {
                throw std::invalid_argument(std::string("Invalid move type: ") + std::to_string(move_type));
            }
        }
    }

    auto get_all_moves()
    {
        return moves;
    }

    auto get_move(int move_type)
    {
        assert_move_bounds(move_type);
        return moves[move_type];
    }
};


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

    bool move_knight(Position pos, Move move)
    {
        if (this->move_num > this->move_max)
        {
            return true;
        }

        Position new_pos;
        try
        { 
            new_pos = calc_move(pos, move);
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

        bool success;
        auto all_moves = KnightMoves::get_all_moves();
        for (auto& new_move : all_moves)
        {
            if (move_knight(new_pos, new_move))
            {
                success = true;
                return true;
            }
        }

        if (!success) {
            move_num--;
            reset_square(new_pos);
        }

        return false;
    }

    Position calc_move(Position pos, Move move)
    {
        Position new_pos = pos + move;

        assert_valid_position(new_pos);
        return new_pos;
    }

    void assert_valid_position(Position pos)
    {
        if (pos.get_row() < 0 || pos.get_row() >= this->num_rows ||
            pos.get_col() < 0 || pos.get_col() >= this->num_cols)
        {
            throw std::out_of_range(
                std::string("Invalid position: (Row: ") +
                std::to_string(pos.get_row()) +
                " Col: " + std::to_string(pos.get_col()) + ")");
        }
    }

    auto get_square(Position pos)
    {
        assert_valid_position(pos);
        return &this->board[pos.get_row()][pos.get_col()];
    }

    bool is_occupied(Position pos)
    {
        return 0 != *get_square(pos);
    }

    void set_square(Position pos, int value = -1)
    {
        assert_valid_position(pos);

        if (value < 0)
        {
            value = move_num;
            move_num++;
        }

        *get_square(pos) = value;
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

        auto all_moves = KnightMoves::get_all_moves();
        for (auto& move : all_moves)
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
