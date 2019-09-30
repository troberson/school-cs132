////
// Author:       Tamara Roberson
// Section:      S
// Assignment:   #1
// Description:  Knight's Tour
// A knight on a chessboard can move 2 steps in one direction and 1
// step at a right angle or vice versa. Can a knight start on any
// position and reach all squares on the board without standing on one
// twice? Board size and starting position in this impilementation are
// hard-coded in main(). Program prints status updates and final
// result to stdout.
////

#include <array>     // std::array
#include <iomanip>   // std::setfill, std::setwidth
#include <iostream>  // std::cout, std::endl
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::invalid_argument, std::out_of_range
#include <string>    // std::string
#include <vector>    // std::vector

/***
 * Position
 *
 * Holds a (row, column) pair of integers to describe a position in a
 * table.
 */
class Position
{
    int row;
    int col;

  public:
    /***
     * Construct a Position object with the given row and class
     *
     * @param row position row (default: 0)
     * @param col position column (default: 0)
     */
    Position(int row = 0, int col = 0) : row(row), col(col)
    {
    }

    /***
     * The position's row
     *
     * @returns the row of the position
     */
    int get_row()
    {
        return row;
    }

    /***
     * The position's column
     *
     * @returns the column of the position
     */
    int get_col()
    {
        return col;
    }

    /***
     * A string representation of the position.
     *
     * @returns a string
     */
    std::string to_string()
    {
        std::ostringstream sstream{"{"};
        sstream << row << ", " << col << ")";
        return sstream.str();
    }

    /***
     * Add two positions.
     *
     * @param lhs a position
     * @param rhs a position
     * @returns the vector sum of the two positions
     */
    Position operator+(Position &rhs) const
    {
        return Position(row + rhs.get_row(), col + rhs.get_col());
    }
};


/***
 * Move
 *
 * A move type of relative (row, column) positions.
 *
 * @remark This inherits from Position but is conceptually distinct.
 */
class Move : public Position
{
  public:
    using Position::Position;
};


/***
 * Types of moves a knight can make
 */
namespace KnightMoves
{
    // Anonymous namespace to hide implementation
    namespace
    {
        // moves
        // (change in row, change in col)
        const std::array moves{
            Move(-2, 1),  // Move Type 0
            Move(-1, 2),  // Move Type 1
            Move(1, 2),   // Move Type 2
            Move(2, 1),   // Move Type 3
            Move(2, -1),  // Move Type 4
            Move(1, -2),  // Move Type 5
            Move(-1, -2), // Move Type 6
            Move(-2, -1)  // Move Type 7
        };

        /***
         * Assert that the given move number is valid
         *
         * @param move_type a number referencing a move type
         * @throw std::invalid_argument if move type is invalid
         */
        void assert_move_bounds(int move_type)
        {
            if (move_type < 0 || move_type >= moves.size())
            {
                throw std::invalid_argument(
                    std::string("Invalid move type: ") +
                    std::to_string(move_type));
            }
        }
    } // namespace

    /***
     * All moves
     *
     * @returns an array of all moves
     */
    auto get_all_moves()
    {
        return moves;
    }

    /***
     * Get move
     *
     * @param move_type a number referencing a move type
     * @returns a Move object
     */
    auto get_move(int move_type)
    {
        assert_move_bounds(move_type);
        return moves[move_type];
    }
}; // namespace KnightMoves


/***
 * Chess Board
 */
class Board
{
  private:
    std::vector<std::vector<int>> board;
    int num_digits{1}; // number of digits used in printing board
    int num_rows{0};   // number of rows of the board
    int num_cols{0};   // number of columns of the board
    int move_num{1};   // current move number
    int move_max{0};   // number of moves needed to complete the game

    unsigned long long try_num{1}; // current try number

    /***
     * Format a number for display
     *
     * @param n the number to format
     * @returns a string representation of the number
     */
    std::string num_to_string(const int n)
    {
        std::stringstream sstream;
        sstream << std::setw(this->num_digits) << std::setfill('0')
                << n;
        return sstream.str();
    }


    /***
     * Update status and print
     *
     * Prints current number of tries to stdout and increments
     */
    void update_status()
    {
        try_num++;
        if (try_num % 100'000 == 0)
        {
            std::cout << "Try Number: " << try_num
                      << ", Move: " << this->move_num << " of "
                      << this->move_max << std::endl;
        }
    }


    /***
     * Move the knight recursively
     *
     * @param pos the current position of the knight
     * @param move the move to make
     * @returns true if move is successful, false otherwise
     */
    bool move_knight(Position pos, Move move)
    {
        // Return true if board is complete
        if (this->move_num > this->move_max)
        {
            return true;
        }

        // Calculate new position after move
        // Return false if new position is invalid
        Position new_pos;
        try
        {
            new_pos = calc_move(pos, move);
        }
        catch (...)
        {
            return false;
        }

        // Retun false if new position is occupied
        if (is_occupied(new_pos))
        {
            return false;
        }

        // Print status
        update_status();

        // Assign square
        set_square(new_pos);

        // Try all possible moves from the new position
        auto all_moves = KnightMoves::get_all_moves();
        for (auto &new_move : all_moves)
        {
            // Return true if move is successful
            if (move_knight(new_pos, new_move))
            {
                return true;
            }
        }

        // If all moves were unsuccessful, backtrack
        move_num--;
        reset_square(new_pos);
        return false;
    }


    /***
     * Calculate new position based on current position and move
     *
     * @param pos current position
     * @param move move type
     * @returns new position
     */
    Position calc_move(Position pos, Move move)
    {
        Position new_pos = pos + move;

        assert_valid_position(new_pos);
        return new_pos;
    }


    /***
     * Assert position is valid
     *
     * @throw std::out_of_range if position is not on board
     * @param pos position
     */
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


    /***
     * Get square at the given position
     *
     * @throw std::out_of_range if position is not on board
     * @param pos position
     * @returns pointer to square
     */
    auto get_square(Position pos)
    {
        assert_valid_position(pos);
        return &this->board[pos.get_row()][pos.get_col()];
    }


    /***
     * Check if the position is occupied
     *
     * @param pos position
     * @returns true if position is occupied, false otherwise
     */
    bool is_occupied(Position pos)
    {
        return 0 != *get_square(pos);
    }


    /***
     * Assign a value to the given square
     *
     * @param pos position
     * @param value the value to assign (default: current move number)
     */
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


    /***
     * Reset the given square to 0
     *
     * @param pos position
     */
    void reset_square(Position pos)
    {
        set_square(pos, 0);
    }


  public:
    /***
     * Construct a new board
     *
     * @throw std::invalid_argument if number of columns or rows is
     *   negative or zero
     * @param num_rows number of rows for the board
     * @param num_cols number of columns for the board
     */
    Board(int num_rows, int num_cols)
    {
        // sanity check
        if (num_rows < 1 || num_cols < 1)
        {
            throw std::invalid_argument(
                "Board must have at least 1 row and 1 column");
        }

        // initialize the board
        this->num_rows = num_rows;
        this->num_cols = num_cols;
        board.resize(num_rows, std::vector<int>(num_cols, 0));

        // set the number of digits for the numbers
        this->move_max = board.size() * board.at(0).size();
        num_digits = std::to_string(this->move_max).length();
    }


    /***
     * Solve the problem
     *
     * @param pos starting position (default: (0, 0))
     */
    void solve(Position pos = Position{0, 0})
    {
        // assign the starting square
        set_square(pos);

        // walk through all possible moves
        for (auto &move : KnightMoves::get_all_moves())
        {
            move_knight(pos, move);

            if (this->move_num > this->move_max)
            {
                std::cout << "SUCCESS!!! (" << this->try_num
                          << " tries)" << std::endl;
                print();
                return;
            }
        }

        std::cout << "Unable to find solution" << std::endl;
    }


    /**
     * Print the board to stdout
     */
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


// MAIN
int main()
{
    // Create an 8x8 board
    Board board(8, 8);

    // Solve the board
    board.solve();

    // Return success
    return 0;
}


// EXAMPLE OUTPUT
// Try Number: 100000, Move: 56 of 64
// Try Number: 200000, Move: 55 of 64
// Try Number: 300000, Move: 55 of 64
// Try Number: 400000, Move: 50 of 64
// Try Number: 500000, Move: 54 of 64
// Try Number: 600000, Move: 49 of 64
// Try Number: 700000, Move: 49 of 64
// Try Number: 800000, Move: 53 of 64
// Try Number: 900000, Move: 52 of 64
// Try Number: 1000000, Move: 57 of 64
// Try Number: 1100000, Move: 56 of 64
// Try Number: 1200000, Move: 53 of 64
// Try Number: 1300000, Move: 57 of 64
// Try Number: 1400000, Move: 53 of 64
// Try Number: 1500000, Move: 57 of 64
// Try Number: 1600000, Move: 51 of 64
// Try Number: 1700000, Move: 55 of 64
// Try Number: 1800000, Move: 55 of 64
// Try Number: 1900000, Move: 54 of 64
// Try Number: 2000000, Move: 54 of 64
// Try Number: 2100000, Move: 55 of 64
// Try Number: 2200000, Move: 53 of 64
// Try Number: 2300000, Move: 55 of 64
// Try Number: 2400000, Move: 51 of 64
// Try Number: 2500000, Move: 55 of 64
// Try Number: 2600000, Move: 53 of 64
// Try Number: 2700000, Move: 57 of 64
// Try Number: 2800000, Move: 57 of 64
// Try Number: 2900000, Move: 50 of 64
// Try Number: 3000000, Move: 55 of 64
// Try Number: 3100000, Move: 52 of 64
// Try Number: 3200000, Move: 56 of 64
// SUCCESS!!! (3242065 tries)
// 01 38 55 34 03 36 19 22
// 54 47 02 37 20 23 04 17
// 39 56 33 46 35 18 21 10
// 48 53 40 57 24 11 16 05
// 59 32 45 52 41 26 09 12
// 44 49 58 25 62 15 06 27
// 31 60 51 42 29 08 13 64
// 50 43 30 61 14 63 28 07
