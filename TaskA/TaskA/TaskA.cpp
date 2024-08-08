#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <map>
#include <string>
using namespace std;

//See bottom of main
int findArg(int argc, char* argv[], string pattern);


/*
 *
 * The user can launch application as follows:
 *
 * TaskA <filename> <search term> [-regex]
 * 
 * <database file>              REQUIRED. Specifies the file to search (required). This is ALWAYS the first parameter. The file must exist in order to be searched
 * <search term>                REQUIRED. The search term as either a single word or a regular expression. 
                                This is a single word, made up of alpha-numeric characters only.
 * -regex                       OPTIONAL. If this flag is present, then the search term is a regular expression (as opposed to a single word). 
                                It must be a valid regex expression.
 *
 * ****************
 * *** EXAMPLES ***
 * ****************
 *
 * TaskA lorum.txt comp1000             Searches for the string comp1000 in the file lorum.txt
 * TaskA lorum.txt "^(\\d)\\d" -regex   Searches the file lorum.txt for all patterns that match the regular expression "^(\\d)\\d" 
 * TaskA lorum.txt -regex "^(\\d)\\d"   Searches the file lorum.txt for all patterns that match the regular expression "^(\\d)\\d" 
 * TaskA lorum.txt                      Error - search expression provided
 * 
 * *************
 * *** NOTES ***
 * *************
 *
 * o Try to write your code such that is can be reused in other tasks.
 * o Code should be consistently indented and commented
 * o Consider error conditions, such as missing parameters or non-existent files
*/


int main(int argc, char* argv[])
{
    // argv is an array of strings, where argv[0] is the path to the program, argv[1] is the first parameter, ...
    // argc is the number of strings in the array argv
    // These are passed to the application as command line arguments
    // Return value should be EXIT_FAILURE if the application exited with any form of error, or EXIT_SUCCESS otherwise
    

    if (argc == 3) {
        // Welcome message
        cout << "TaskA (c)2024" << endl;

        // Get parameters for the simple case
        string fileName; 
        string searchString; 

        // Prompt user to enter file name and search string
        cout << "Enter file name: ";
        cin >> fileName;
        cout << "Enter search string: ";
        cin >> searchString;

        // Confirm
        cout << "TaskA " << fileName << " " << searchString << endl;

        // Open the file
        ifstream file(fileName);
        if (file.is_open()) {
            // Read the file contents
            string fileContent((istreambuf_iterator<char>(file)),
                istreambuf_iterator<char>());

            // Display the file contents
            cout << "File contents:" << endl;
            cout << fileContent << endl;

            // Initialize the index variable to the position of the first occurrence of searchString in fileContent
            int index = fileContent.find(searchString);

            // Initialize a counter to keep track of the number of occurrences of searchString
            int count = 0;

            // Loop until searchString is not found in fileContent
            while (index != string::npos) {
                // Print a message indicating that searchString was found at the current index
                cout << "Found '" << searchString << "' at index " << index << " in the file contents" << endl;

                // Increment the counter
                count++;

                // Search for the next occurrence of searchString, starting from the position after the current index
                index = fileContent.find(searchString, index + 1);
            }

            // If no occurrences of searchString were found, print a message indicating that
            if (count == 0) {
                cout << "Did not find '" << searchString << "' in the file contents" << endl;
            }
            // Otherwise, print the total number of occurrences
            else {
                cout << "Total occurrences of '" << searchString << "': " << count << endl;
            }

            // Split the file content into individual words
            vector<string> words;
            stringstream ss(fileContent);
            string word;
            while (ss >> word) {
                words.push_back(word);
            }

            // Calculate the percentage of words that match the searchString
            double percentage = (static_cast<double>(count) / words.size()) * 100;

            // Display the results
            cout << "Total words: " << words.size() << endl;
            printf("Percentage of words that match '%s': %.2f%%\n", searchString.c_str(), percentage);

            // Close the file
            file.close();
        }
        else {
            cerr << "Error: Unable to open file " << fileName << endl;
            return EXIT_FAILURE;
        }

        // Done
        return EXIT_SUCCESS;
    }
    else {
        cerr << "Usage: TaskA <file_name> <search_string>" << endl;
        return EXIT_FAILURE;
    }
}


// Find an argument on the command line and return the location
int findArg(int argc, char* argv[], string pattern) {
    int count = 0;
    for (int n = 1; n < argc; n++) {
        string s1(argv[n]);
        if (s1 == pattern) {
            cout << "Found '" << pattern << "' at index " << n << endl;
            count++;
        }
    }
    if (count > 0) {
        cout << "Total occurrences of '" << pattern << "': " << count << endl;
    }
    else {
        cout << "'" << pattern << "' not found" << endl;
    }
    return count;
}

  


