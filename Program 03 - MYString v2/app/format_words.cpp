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
#include <vector>

// alias the vector of TRStrings as 'wordlist' for clarity and ergonomics
using wordlist = std::vector<TRString>;

/**
 * Sort string list in place.
 *
 * @note Uses bubble sort according to the comparison
 *   returned by TRString.compareTo().
 *
 * @param strings A pointer to a list of TRtrings.
 */
void sort_word_list(wordlist* words)
{
    // get the number of words in the list
    const auto num_words = words->size();

    // keep track of whether a swap was performed
    // so we can break early
    bool swapped;

    // outer loop
    for (auto i = 0UL; i < num_words - 1; i++)
    {
        // reset swap marker
        swapped = false;

        // inner loop
        for (auto j = 0UL; j < num_words - i - 1; j++)
        {
            // if word j should come after word j+1, swap them
            if (words->at(j).compareTo(words->at(j + 1)) > 0)
            {
                TRString temp = words->at(j);
                words->at(j) = words->at(j + 1);
                words->at(j + 1) = temp;

                swapped = true;
            }
        }

        // if no swap was performed, break early
        if (!swapped)
        {
            break;
        }
    }
}


/**
 * Read word list from input stream
 *
 * @param input_stream The input stream to read from.
 * @returns A list of words.
 */
wordlist read_words(std::istream& input_stream,
                    const int max_size = 100)
{
    // create a list of words
    wordlist words(max_size);

    // NOTE: we must assign to the vector index directly
    // rather than utilizing vector.push_back() because
    // the TRString class does not have a copy constructor

    // count the number of words read
    int word_count{0};

    // read in file
    while (input_stream >> words.at(word_count))
    {
        word_count++;
    };

    // resize word list to number of words actually read
    words.resize(word_count);

    return words;
}

/**
 * Write word list to an output stream
 *
 * @param output_stream The output stream to write to.
 * @param words A list of words.
 * @param words_per_line Words to write before a newline. (Default: 6)
 * @param chars_per_word Words will be space-padded and right-aligned
 *   in this size. (Default: 13)
 */
void write_words(std::ostream& output_stream, const wordlist& words,
                 const int words_per_line = 6,
                 const int chars_per_word = 13)
{
    // get the number of words in the list
    const auto word_count = words.size();

    for (auto i = 0; i < word_count; i++)
    {
        // get the current word
        TRString w = words.at(i);

        // zero-pad words up to chars_per_word
        output_stream << std::setw(chars_per_word);

        // write the string to the output_stream
        output_stream << w;

        // after every words_per_line, add a newline
        // don't add a newline if this is the last word
        if (i % words_per_line == words_per_line - 1 &&
            i != word_count - 1)
        {
            output_stream << "\n";
        }
    }

    // add a newline at the end of the file and flush
    output_stream << std::endl;
}


// MAIN
int main()
{
    // INPUT - read in a list of words from a text file
    std::ifstream input_file;
    input_file.open("infile2.txt");

    // fatal error if file could not be opened
    if (!input_file.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    // read words into a list of words
    wordlist words = read_words(input_file);


    // SORT - sort the list of words
    sort_word_list(&words);


    // OUPUT - write the list of words to the output file
    std::ofstream output_file;
    output_file.open("outfile.txt");

    // fatal error if file could not be opened
    if (!output_file.is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    // format words and write to the file
    write_words(output_file, words);

    // SUCCESS
    return 0;
}


// Sample Output
// (written to outfile.txt)
//             I            I            I      Martian           Or         Such
//          They         Were            a            a            a            a
//     amazingly           an           an          and      animal.           as
//           ask          ask          be.        began        began        body?
//         brain        busy.      compare        could          did   directing,
//         each,       engine         felt        first          for          his
//           how        human  impossible.           in           in  intelligent
//   intelligent     ironclad         life        lower    machines,        man's
//   mechanisms?         much           my       myself       myself           or
//         rules      ruling,         seem       seemed          sit         sits
//         steam          the          the         they         they        thing
//        things         time           to           to           to           to
//            to       using,          was         what       within        would
