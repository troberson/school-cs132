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
void sort_word_list(wordlist* words);


/**
 * Read word list from input stream
 *
 * @param input_stream The input stream to read from.
 * @param words_per_long_word How many words to combine into a single string.
 *   (Default: 5)
 * @returns A list of words.
 */
wordlist read_words(std::istream& input_stream, int words_per_long_word = 5);

/**
 * Write word list to an output stream
 *
 * @param output_stream The output stream to write to.
 * @param words A list of words.
 */
void write_words(std::ostream& output_stream, const wordlist& words);


// MAIN
int main()
{
    // INPUT - read in a list of words from a text file
    std::ifstream input_file;
    input_file.open("infile3.txt");

    // fatal error if file could not be opened
    if (!input_file.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    // read words into a list of words
    wordlist words = read_words(input_file);

    // explicitly close input file
    input_file.close();


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

    // explicitly close output file
    output_file.close();

    // SUCCESS
    return 0;
}


// Sort
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
            if (words->at(j) > words->at(j + 1))
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


// Read
wordlist read_words(std::istream& input_stream, const int words_per_long_word)
{
    // create a list of words
    wordlist words;

    // keep reading until the input_stream is exhausted
    while (input_stream)
    {
        // multiple words in a row will be combined to create a long word
        TRString long_word;

        for (int i{0}; i < words_per_long_word; i++)
        {
            TRString tmp;
            if (input_stream >> tmp)
            {
                long_word += tmp;
            } else {
                break;
            }
        }

        words.push_back(long_word);
    }

    return words;
}


// Write
void write_words(std::ostream& output_stream, const wordlist& words)
{
    // Find the length needed for formatting
    // There is one extremely long word, so we actually want
    // the length of the *second* longest word.
    int max_length{0};
    int max_length_snd{0};
    for (const auto& w : words)
    {
        if (w.length() > max_length)
        {
            max_length_snd = max_length;
            max_length = w.length();
        }
    }

    // Output words in the following format:
    // <word>  <length>:<capacity>
    // The numbers should be aligned with the exception
    // of the extremely long word.
    for (const auto& w : words)
    {
        if (w.length() != max_length)
        {
            output_stream << std::setw(max_length_snd);
        }
        output_stream << std::left << w << "  "
            << w.length() << ":" << w.capacity() << "\n";
    }

    output_stream << "\n" << "TRStrings Created: " << TRString::getCreatedCount() << "\n"
        << "TRStrings Currently: " << TRString::getCurrentCount()
        << " (" << words.size() << " in wordlist)" << std::endl;
}


/*
Sample Output
(written to outfile.txt)

Ibegantocomparethe                18:20
Ifeltwasimpossible.Or             21:40
Theyseemedamazinglybusy.I         25:40
andrulesinhisbody?                18:20
anironcladorasteam                18:20
asaman'sbrainsits                 17:20
askmyselfforthefirst              20:20
begantoaskmyselfwhat              20:20
didaMartiansitwithin              20:20
each,ruling,directing,using,much  32:40
enginewouldseemtoan               19:20
intelligentloweranimal.ThisIsMyAmazinglyLongStringToMakeYourExtractionOperatorWorkCorrectly.  92:100
intelligentmechanisms?Suchathing  32:40
theycouldbe.Werethey              20:20
thingstohumanmachines,to          24:40
timeinmylifehow                   15:20

TRStrings Created: 179
TRStrings Currently: 16 (16 in wordlist)
*/
