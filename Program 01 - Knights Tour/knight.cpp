#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Board {
    private:

    std::vector<std::vector<int>> board;

    std::string num_to_string(int n)
    {
        int max = board.size() * board.at(0).size();
        int max_len = std::to_string(max).length();
        std::stringstream sstream;
        sstream << std::setw(max_len) << std::setfill('0') << n;
        return sstream.str();
    }

    public:

    Board(int x_size, int y_size)
    {
        board.resize(x_size);
        int n{0};
        for (auto &row : board)
        {
            for (int i = 0; i < y_size; i++)
            {
                row.push_back(n);
                n++;
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
    Board board(5, 5);
    board.print();
    return 0;
}