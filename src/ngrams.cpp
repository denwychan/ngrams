// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

// Imports
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
using namespace std;

// Function prototypes
void getTextFile(string &text);

int main() {
    // Greet the user
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you" << endl;
    cout << endl;

    // Instatiate a string for the text file
    string text;

    // Ask for input text file from user
    getTextFile(text);
//    cout << text << endl;

    while (true) {
        // Get value of N
        int n = getInteger("Value of N? ", "Please enter a valid integer value. ");
//        cout << "N is " << n << endl;
        cout << endl;

        // Ask for number of random words to generate
        int numWordsToGen = getInteger("# of random words to generate (0 to quit)? ",
                                       "Please enter a valid integer value. ");
//        cout << "Random words to generate " << numWordsToGen << endl;
        cout << endl;

         // Quit if user enters 0
        if (numWordsToGen == 0){
            break;
        }
    }

    cout << "Exiting." << endl;
    return 0;
}

/*
 * Use Map collection
 *
 * Markov chain
 *
 * Algorithm Step 1: Building a Map of N-Grams
 *
 * for n-gram, wrap around the text n-1 times to get to the end of the passage e.g. 3-gram iterate
 * 2 times
 * Leave case and punctuation
 *
 *
 */

/*
 * Function: getTextFile
 * Usage: Prompts the user to get the reference text by typing the file name. Reprompts the
 * user if an invalid file name is given.
*/

void getTextFile(string &text) {
    string filename = promptUserForFile(
                "Input file name? ","Unable to open that file. Try again.");
    text = readEntireFile(filename);
    }
