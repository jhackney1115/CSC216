#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Helper function to clean a word of punctuation and lowercase it
string cleanWord(const string& word) {
    string cleaned;
    for (char c : word) {
        if (isalnum(c))
            cleaned += tolower(c);
    }
    return cleaned;
}

// Common words not to be indexed (Stop Words)
set<string> stopWords = {
    "a", "an", "and", "are", "as", "at", "be", "by", "for", "from",
    "has", "he", "in", "is", "it", "its", "of", "on", "that", "the",
    "to", "was", "were", "will", "with", "they", "them", "this"
};

int main() {
    string inputFilename = "input.txt";
    string outputFilename = "inverted_index.txt";

    ifstream inFile(inputFilename);
    if (!inFile) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    multimap<string, int> invertedIndex;
    string word;
    int index = 0;

    while (inFile >> word) {
        string cleaned = cleanWord(word);
        if (!cleaned.empty() && stopWords.find(cleaned) == 
        stopWords.end()) {
            invertedIndex.insert({cleaned, index});
        }
        ++index;
    }
    inFile.close();

    ofstream outFile(outputFilename);
    if (!outFile) {
        cerr << "Failed to open output file." << endl;
        return 1;
    }

    string currentWord;
    for (auto it = invertedIndex.begin(); it != 
    invertedIndex.end(); ) {
        currentWord = it->first;
        outFile << currentWord << ": [";

        auto range = invertedIndex.equal_range(currentWord);
        bool first = true;
        //Find all instances of the word
        for (auto wordIt = range.first; wordIt != 
        range.second; ++wordIt) {
            if (!first) outFile << ", ";
            outFile << wordIt->second;
            first = false;
        }
        outFile << ']' <<'\n';
        it = range.second; // Move to the next group of words
    }

    outFile.close();
    cout << "Inverted file index written to " << 
    outputFilename << endl;
    return 0;
}
