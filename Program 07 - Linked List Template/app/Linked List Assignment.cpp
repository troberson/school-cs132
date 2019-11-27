////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 7 - LinkedList Template (Main App)
//
// Description: Read two textfiles (infile1.txt, infile2.txt) into
// two DblLinkedLists as TRStrings. Then perform several tasks with lists,
// writing the list counts to the console each time:
//   * Copy the lists using an assigment operator.
//   * Find the set differences of the lists.
//   * Print counts with two words added (tests copy constructor)
//   * Print number of TRStrings constructed and the current count.
//   * Print the first five words of the set differences.
//   * Test DblLinkedLists with integers and doubles.
////

#include <DblLinkedList.h>
#include <TRString.h>
#include <string_utils.h>

#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>

// alias the DblLinkedList of TRStrings as 'wordlist' for clarity
using wordlist = DblLinkedList<TRString>;

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


/**
 * Output the first words from a list.
 *
 * @param list A list of words.
 * @param num The number of words to output.
 */
void printWords(wordlist list, int num);


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
              << "\n\n";

    std::cout << "First five words from modList1:\n";
    printWords(modList1, 5);

    std::cout << "\nFirst five words from modList2:\n";
    printWords(modList2, 5);


    std::cout << "\nNumeric Lists:\n";
    DblLinkedList<int> intList;
    for (int i = 20; i > 0; i -= 2)
        intList.insert(i);

    for (int i = 25; i > 0; i -= 5)
        intList.insert(i);

    std::cout << "intlist: " << intList << "  size:" << intList.size()
              << std::endl
              << std::endl;

    DblLinkedList<double> dblList;
    for (double i = 10.9; i > 0; i -= .57)
        dblList.insert(i);

    std::cout << "dblList: " << dblList << "  size:" << dblList.size()
              << std::endl
              << std::endl;

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
    list_a.process([&] {
        auto str = list_a.next().value();
        list_b.remove(str);
        return std::nullopt;
    });
}


void changer(wordlist list)
{
    list.insert(TRString("ZIP"));
    list.insert(TRString("ZAP"));
    std::cout << "Inside changer function: size of list is "
              << list.getCount() << "\n";
}

void printWords(wordlist list, int num)
{
    int count{0};
    list.process([&]() -> std::optional<bool> {
        std::cout << list.next().value() << " ";
        count++;

        if (count > num - 1)
        {
            std::cout << std::endl;
            return true;
        }
        return {};
    });
}