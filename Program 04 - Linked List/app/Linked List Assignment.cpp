////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList (Main App)
//
// Description: Read two textfiles (infile1.txt, infile2.txt) into
// two DblLinkedLists as TRStrings. Then perform several tasks with lists,
// writing the list counts to the console each time:
//   * Copy the lists using an assigment operator.
//   * Find the set differences of the lists.
//   * Print counts with two words added (tests copy constructor)
//   * Print number of TRStrings constructed and the current count.
//   * Write the set differences to outfile1.txt and outfile2.txt.
////

#include <DblLinkedList.h>
#include <TRString.h>
#include <string_utils.h>

#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>

// alias the DblLinkedList of TRStrings as 'wordlist' for clarity
using wordlist = DblLinkedList;

/**
 * Read a file into a word list.
 *
 * @param filename The name of the file to open.
 * @returns A word list.
 */
wordlist read_file(const char* filename);


/**
 * Read word list from input stream
 *
 * @param input_stream The input stream to read from.
 * @returns A list of words.
 */
wordlist read_words(std::istream& input_stream);


/**
 * Write word list to a file.
 *
 * @param filename The name of the file to write to.
 * @param list A list of words.
 */
void write_file(const char* filename, const wordlist& list);


/**
 * Remove from list B the elements which are in list A.
 *
 * @param[in] list_a A list of words.
 * @param[out] list_b A list of words.
 */
void difference(const wordlist& list_a, wordlist& list_b);


/**
 * Output the list count with 'ZIP' and 'ZAP' added.
 *
 * @param list A list of words.
 */
void changer(wordlist list);


// MAIN
int main()
{
    wordlist list1;
    wordlist list2;
    wordlist modList1;
    wordlist modList2;

    // Read the input files
    try
    {
        list1 = read_file("infile1.txt");
        list2 = read_file("infile2.txt");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Lambda function to print all the list counts
    auto print_lists = [&]() {
        std::cout << "List1: " << list1.getCount() << " words\n"
                  << "List2: " << list2.getCount() << " words\n"
                  << "modList1: " << modList1.getCount() << " words\n"
                  << "modList2: " << modList2.getCount() << " words\n\n";
    };

    // Initial
    std::cout << "Initial Creation:\n";
    print_lists();

    // Copy to modList
    std::cout << "Set modList1 and 2:\n";
    modList1 = list1;
    modList2 = list2;
    print_lists();

    // Set differences
    std::cout << "Set differences:\n";
    try
    {
        difference(list2, modList1);
        difference(list1, modList2);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    print_lists();

    // Changer
    changer(modList1);
    changer(modList2);
    std::cout << "\nAfter changer:\n";
    print_lists();

    // TRString Created and Current Counts
    std::cout << "TRString Created: " << TRString::getCreatedCount()
              << "\nTRString Current: " << TRString::getCurrentCount()
              << "\n";


    // Write output
    try
    {
        write_file("outfile1.txt", modList1);
        write_file("outfile2.txt", modList2);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // Success
    return 0;
}


wordlist read_file(const char* filename)
{
    // open file
    std::ifstream input_file;
    input_file.open(filename);

    // fatal error if file could not be opened
    if (!input_file.is_open())
    {
        const char* msg = utils::string::string_concat(
            "Error opening input file: ", filename);

        throw std::ios::failure(msg);
    }

    // read words into a list of words
    wordlist words = read_words(input_file);

    // explicitly close input file
    input_file.close();

    return words;
}

wordlist read_words(std::istream& input_stream)
{
    wordlist list;

    // keep inserting words from the input stream to the list until we've
    // exhausted it
    while (input_stream)
    {
        TRString str;
        input_stream >> str;

        // don't add empty strings
        // the extraction operator doesn't normally extract empty strings
        // but the TRString overload strips punctuation, so we might have a
        // punctuation-only string that is now empty.
        if (!str.isEmpty())
        {
            list.insert(str);
        }
    }

    return list;
}


void write_file(const char* filename, const wordlist& list)
{
    // open file
    std::ofstream output_file;
    output_file.open(filename);

    // fatal error if file could not be opened
    if (!output_file.is_open())
    {
        const char* msg = utils::string::string_concat(
            "Error opening output file: ", filename);

        throw std::ios::failure(msg);
    }

    // write words into the file
    output_file << list << std::endl;

    // explicitly close output file
    output_file.close();
}


void difference(const wordlist& list_a, wordlist& list_b)
{
    // walk through list_a and remove all the strings from list_b
    list_a.resetIterator();
    while (list_a.hasMore())
    {
        auto str = list_a.next().value();
        list_b.remove(str);
    }
}


void changer(wordlist list)
{
    list.insert(TRString("ZIP"));
    list.insert(TRString("ZAP"));
    std::cout << "Inside changer function: size of list is "
              << list.getCount() << "\n";
}