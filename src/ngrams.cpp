// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

// Imports
#include <iostream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include <string>
#include "map.h"
#include "vector.h"
#include "tokenscanner.h"
using namespace std;

// Function prototypes
//void getTextFile(string &text, Vector<string> &textVec);
void getTextFile(Vector<string> &lineVec, Vector<string> &wordVec);
//void getTextFile(string &text, TokenScanner &scanner);
//void getTextFile(string &text);
//void getTextFile(Vector<string> &textVec);
int getValidInteger(const string &promptMessage,
                    const string &repromptMessage,
                    int lowerBound,
                    int upperBound = INT_MAX);
void getNGramsMap(Map<Vector<string>, Vector<string>> &map, string &text, int n);

int main() {
    // Greet the user
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you" << endl;
    cout << endl;

    // Instatiate a vector for the text file
    string text;
//    TokenScanner scanner;

    Vector<string> lineVec;
    Vector<string> wordVec;
    Map<Vector<string>, Vector<string>> map;

    // Ask for input text file from user
    getTextFile(lineVec, wordVec);
//    getTextFile(textVec);
//    cout << text << endl;
//    cout << scanner << endl;
//    while (scanner.hasMoreTokens()){
//        cout << scanner.nextToken() << endl;
//    }
    cout << lineVec << endl;
    cout << wordVec << endl;

    while (true) {
        // Get value of N which is least 2-gram
        int n = getValidInteger("Value of N? ",
                                "Please enter an integer greater than 1",
                                2);
//        cout << "N is " << n << endl;
        cout << endl;

        // Ask for number of random words to generate which is < ngrams specified
        int numWordsToGen = getValidInteger("# of random words to generate (0 to quit)? ",
                                            "Please enter an integer greater or equal to " +
                                            to_string(n),
                                            n);
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
 * Function: getTextFile
 * Usage: Prompts the user to get the reference text by typing the file name. Reprompts the
 * user if an invalid file name is given.
*/

//void getTextFile(string &text, Vector<string> &textVec) {
//    string filename = promptUserForFile(
//                "Input file name? ","Unable to open that file. Try again.");
//    // Instantiate input file stream to read file contents into a vector of lines
//    text = readEntireFile(filename);
//    textVec = stringSplit(text, " ");
    // Make scanner ignore white spaces
//    scanner.ignoreWhitespace();
//    scanner.addWordCharacters("!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~");
//    scanner.setInput(text);
//}

void getTextFile(Vector<string> &lineVec, Vector<string> &wordVec) {
    string filename = promptUserForFile(
                "Input file name? ","Unable to open that file. Try again.");
    // Instantiate input file stream to read file contents into a vector of lines
    ifstream text;
    openFile(text, filename);
    readEntireFile(text, lineVec);
    // Split lines into individual words
    for (string line : lineVec){
        Vector<string> tempWords = (stringSplit(line, " "));
        for (string word : tempWords){
            // Add individual words into a vector of words only
            wordVec.add(word);
        }
    }
}

/*
 * Function: getValidInteger
 * Usage: Ensure user integer input is valid between a range, other reprompt the user to re-enter.
 * Params: promptMessage (string), lowerBound (integer), upperBound (integer - default INT_MAX)
 * ------------------------------------------------------------------------------------------------
 * Returns: userInput (Integer)
*/
int getValidInteger(const string &promptMessage,
                    const string &repromptMessage,
                    int lowerBound,
                    int upperBound) {
    while (true) {
        int userInput = getInteger(promptMessage);
        if (userInput >= lowerBound && userInput <= upperBound ) {
            return userInput;
        }
        cout << repromptMessage << endl;
    }
}

/*
 * Function: getNGRamsMap
 * Usage:
 * 1. Create a window of n-grams as a list of n words
 * 2. Add the list to a map as a key, and add the following word as the value
 * 3. Remove the first item in the window and move onto the next n-grams
 * 4. Repeat until the end of the text, the n-gram will wrap around the text for n-1 words to get to
 * the end
 * Leave case and punctuation
 *
 * Example: "Girls just want to have fundamental coding skills." for 2-grams
 * 1. window = {Girls, just}
 * 2. map = {{Girls, just} : {want}}
 * 3. window = {just, want}
 * 4. map = {{Girls, just} : {want},
 *           {{just, want} : {to}}
 * 5. map = {{Girls, just} : {want},
 *           {{just, want} : {to}}, ...
 *           {skills., Girls} : {just}}
 */

void getNGramsMap(Map<Vector<string>, Vector<string>> &map, Vector<string> &textVec, int n){
    Vector<string> window;
    // Create a window of n-grams as a list of n words

    //{"This is a line", "this is a second line"} Read line by line and then string split
//    for (string line : textVec){

//    }

//    for (int i = 0; i < n; i ++){
//        string token;
//        text >> token;
//        window.add(token);
//    }
}

/*
 * Function: getRandomText
 * Usage:
 * 1. Pick random key from ngrams map
 * 2. For subsequent words, use map to look up possible next words (discard first word in your key
 * and add new suffix for look up)
 * Prefix and suffix random text with "..."
 * - To choose a random prefix from a map, use map's 'keys' member function which returns a Vector
 * containing all of the keys in the map. For randomness in general, include "random.h" and
 * call the global function randomInteger(min, max)
 * - Loop over the elements of a vector or set using a for-each loop. A for-each also works on a
 * map, iterating over the keys in the map. Look up each associated value based on the key in the
 * loop.
 */



