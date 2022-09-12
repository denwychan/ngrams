/*
 * Implementation of a random text writer using a reference text and N-grams approach. The user is
 * prompted to select the reference text, which is then used to build a N-grams maps with N being
 * the number of consecutive words used as a string to look up the next word. For example,
 * "Girls just want to have fundamental coding skills." for 4-grams
 * 1. {{Girls, just, want, to} : {have}, {just, want, to, have} : {fundamental}...}
 * The user can define N for N-grams and the number of random text to generate
 */

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
void getWordTokens(Vector<string> &tokenVec);
int getValidInteger(const string &promptMessage,
                    const string &repromptMessage,
                    int lowerBound,
                    bool exitWhen0 = false);
void getNGramsMap(Map<Vector<string>, Vector<string>> &map, const Vector<string> &tokenVec, int n);
void getRandomText(const Map<Vector<string>, Vector<string>> map,
                   int n,
                   int numWordsToGen);

int main() {
    // Greet the user
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;
    cout << endl;

    // Instatiate a vector for the word tokens from the text file and a map for the Ngrams

    Vector<string> tokenVec;
    Map<Vector<string>, Vector<string>> map;

    // Ask for input text file from user to create the word tokens
    getWordTokens(tokenVec);

    // Get value of N which is least 2-gram to create the Ngrams map
    int n = getValidInteger("Value of N? ", "N must be 2 or greater", 2);
    cout << endl;
    getNGramsMap(map, tokenVec, n);

    // Repeatedly ask the user for the number of random words to be generated until they enter 0
    // to quit
    while (true) {
        int numWordsToGen = getValidInteger("# of random words to generate (0 to quit)? ",
                                            "Must be at least " + to_string(n) + " words.",
                                            n,
                                            true);
        if (numWordsToGen == 0) {
            break;
        }
        getRandomText(map, n, numWordsToGen);
        cout << endl;
    }
    cout << "Exiting." << endl;
    return 0;
}

/*
 * Function: getWordTokens
 * Usage: Prompts the user to get the reference text by typing the file name in order to get the
 * word tokens from the file. Reprompts the user if an invalid file name is given.
*/
void getWordTokens(Vector<string> &tokenVec) {
    string filename = promptUserForFile(
                "Input file name? ", "Unable to open that file. Try again.");

    // Read the file into a string and instantiate a token scanner to get tokes from the text
    string text = readEntireFile(filename);
    TokenScanner scanner(text);
    // Make scanner ignore white spaces and punctuation
    scanner.ignoreWhitespace();
    scanner.addWordCharacters("!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~");
    // Put the tokens into a vector for reading
    while (scanner.hasMoreTokens()) {
        tokenVec.add(scanner.nextToken());
    }
}

/*
 * Function: getValidInteger
 * Usage: Ensure user integer input is above a lower bound, other reprompt the user to re-enter.
 * When existWhen0 is set to true, allows the user to exit the function when 0 is entered.
*/
int getValidInteger(const string &promptMessage,
                    const string &repromptMessage,
                    int lowerBound,
                    bool exitWhen0) {
    while (true) {
        int userInput = getInteger(promptMessage);
        if (exitWhen0) {
            if (userInput == 0) {
                return userInput;
            }
        }
        if (userInput >= lowerBound) {
            return userInput;
        } else {
            cout << repromptMessage << endl;
        }
    }
}

/*
 * Function: getNGramsMap

 * Usage:Creates a map of the n-grams of words as the key and the following words as a value

 * 1. Create a window of n-grams as a list of n words
 * 2. Add the list to a map as a key, and add the following word as the value
 * 3. Remove the first item in the window and move onto the next n-grams
 * 4. Repeat until the end of the text, the n-gram will wrap around the text for n-1 words to get to
 * the end
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
void getNGramsMap(Map<Vector<string>, Vector<string>> &map, const Vector<string> &tokenVec, int n) {
     for (int i = 0; i < tokenVec.size(); i++) {
        // Create a window of n-grams and add the first word
        Vector<string> window {tokenVec.get(i)};

        Vector<string> tokenValue;
        // Add the n-grams remainder to the window
        for (int j = i + 1; j < i + n; j ++) {
            window.add(tokenVec.get(j % tokenVec.size())); // Use mod for the index so the tokens
            // can wrap around the text
        }
         // Add the window as the key and the suffix as the value to the map
         tokenValue.add(tokenVec.get((i + n) % tokenVec.size()));
         map.put(window, tokenValue);
         // Clear the window to 'slide' across the text
         window.clear();
     }
}

/*
 * Function: getRandomText
 * Usage: Generate random text based on the number of words specified and the ngrams map generated.
 * 1. Pick random start key from ngrams map and the associated value to generate the random text
 * 2. Discard the first word in the start key add the value for the next look up
 * 2. Continue doing the same for subsequent words until the the whole corpus is generated
 */
void getRandomText(const Map<Vector<string>, Vector<string>> map,
                   int n,
                   int numWordsToGen) {
    // Get random start key from ngrams map
    Vector<Vector<string> > keys = map.keys();
    int randKeyIndex = randomInteger(0, keys.size() -1);
    Vector<string> startKey = keys[randKeyIndex];
    // Instantiate a vector to store random text generated
    Vector<string> randomText;
    // Add the random start key to the start of the random text
    for (string key : startKey) {
        randomText += key;

    }
    // Continue until the random text corpus reaches the number of random words to generate
    while (randomText.size() != numWordsToGen) {
        // Get the values corresponding to the start key and select a random word and add it
        // to the random text generated
        Vector<string> valueVec = map.get(startKey);
        int randIndex = randomInteger(0, valueVec.size()-1);
        string randWord = map.get(startKey)[randIndex];
        randomText.add(randWord);
        // Refresh the start by removing the first element and appending the random word
        startKey.remove(0);
        startKey.add(randWord);
    }
    // Display the final random text as string
    string finalText;
    for (string word : randomText) {
        finalText += word + " ";
    }
    cout << "... " << finalText << "..." << endl;
}
