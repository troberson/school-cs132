////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////

#include <TRString.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>


using wordlist = std::vector<TRString>;

/**
 * Sort string list in place.
 *
 * @note Uses bubble sort on the character values.
 *
 * @param strings A pointer to a list of strings.
 */
void sort_word_list(std::vector<TRString>* words)
{
    auto num_words = words->size();

    for (auto i = 0UL; i < num_words - 1; i++)
    {
        for (auto j = 0UL; j < num_words - i - 1; j++)
        {
            if (words->at(j).compareTo(words->at(j + 1)) > 0)
            {
                TRString temp = words->at(j);
                words->at(j) = words->at(j + 1);
                words->at(j + 1) = temp;
            }
        }
    }
}


/**
 * Read word list from input file
 *
 * @param filename The name of the file to read from.
 * @throw std::runtime_error If the file cannot be read.
 * @returns A list of words.
 */
std::vector<TRString> read_file(const char* filename, const int max_size = 100)
{
    // open the input file
    std::ifstream input_file;
    input_file.open(filename);

    // fatal error if file could not be opened
    if (!input_file.is_open())
    {
        throw std::runtime_error("Error opening input file.");
    }

    // create a list of words
    std::vector<TRString> words(max_size);

    // count the number of words read
    int word_count{0};

    // read in file
    while (words.at(word_count).read(input_file))
    {
        word_count++;
    };

    // close the input file
    input_file.close();

    // resize word list to number of words actually read
    words.resize(word_count);

    return words;
}

void write_file(const wordlist& words, const char* filename,
    const int words_per_line = 6, const int chars_per_word = 13)
{
    // open the output file
    std::ofstream output_file;
    output_file.open(filename);

    // fatal error if file could not be opened
    if (!output_file.is_open())
    {
        throw std::runtime_error("Error opening output file.");
    }

    const auto word_count = words.size();

    for (auto i = 0; i < word_count; i++)
    {
        TRString w = words.at(i);
        output_file << std::setw(chars_per_word);
        w.write(output_file);

        if (i % words_per_line == words_per_line - 1)
        {
            output_file << "\n";
        }
    }

    output_file << std::endl;

    output_file.close();
}

int main()
{
    std::vector<TRString> words;

    try
    {
        words = read_file("infile2.txt");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    sort_word_list(&words);

    try
    {
        write_file(words, "outfile.txt");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }


    return 0;
}
