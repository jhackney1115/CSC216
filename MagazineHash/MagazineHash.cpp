#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>

using namespace std;

bool canCreateNote(const string& note,const 
        vector<string>& magazineArticles) {
    unordered_map<char, int> charCount;

    // Count characters from magazine articles
    for (const string& article : magazineArticles) {
        for (char ch : article) {
            if(ch!=' '){   
                if (isalpha(ch)) {
                    ch = tolower(ch);
                }
                charCount[ch]++;
            }
        }
    }

    // Check if we can make the note
    for (char ch : note) {
        if (isalpha(ch)) {
            ch = tolower(ch);
        }
        if(ch!=' '){
            if (charCount[ch] > 0) {
                charCount[ch]--;
            } else {
                return false;  
                // Not enough of this character to make note
            }
        }
    }

    return true;
}

int main() {
    string note = "Hello, World!";
    vector<string> magazines = {
        "Hello there, traveler!",
        "Wonders of the WORLD await!"
    };

    vector<string> magazines2 = {
        "Hello there, traveler!",
        "worl"
    };

    vector<string> magazines3 = {
        "Hello,",
        "world!"
    };

    //Should return yes
    if (canCreateNote(note, magazines)) {
        cout << "Yes, the note can be constructed.\n";
    } else {
        cout << "No, the note cannot be constructed.\n";
    }
    //Should return no
    if (canCreateNote(note, magazines2)) {
        cout << "Yes, the note can be constructed.\n";
    } else {
        cout << "No, the note cannot be constructed.\n";
    }
    //Should return yes, because white space is ignored
    if (canCreateNote(note, magazines3)) {
        cout << "Yes, the note can be constructed.\n";
    } else {
        cout << "No, the note cannot be constructed.\n";
    }

    

    return 0;
}
