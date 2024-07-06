#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class WordFrequencyCounter {
private:
    map<string, int> wordFreq;

    static string cleanWord(const string& word) {
        string cleanedWord;
        for (char ch : word) {
            if (isalpha(ch) || ch == '-') {
                cleanedWord += tolower(ch);
            }
        }
        return cleanedWord;
    }

public:
    void addWordsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file " << filename << endl;
            return;
        }

        string word;
        while (file >> word) {
            string cleanedWord = cleanWord(word);
            if (!cleanedWord.empty()) {
                wordFreq[cleanedWord]++;
            }
        }

        file.close();
    }

    void printWordFrequencies() const {
        for (const auto& pair : wordFreq) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void printMostFrequentWord() const {
        auto mostFreq = max_element(wordFreq.begin(), wordFreq.end(),
            [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second < b.second;
            });

        if (mostFreq != wordFreq.end()) {
            cout << "Most frequent word: " << mostFreq->first
                << " (occurs " << mostFreq->second << " times)" << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file " << filename << " for writing" << endl;
            return;
        }

        for (const auto& pair : wordFreq) {
            file << pair.first << ": " << pair.second << endl;
        }

        file.close();
        cout << "Results saved to file " << filename << endl;
    }
};

int main() {
    WordFrequencyCounter counter;
    string filename = "input.txt";

    counter.addWordsFromFile(filename);

    cout << "Word Frequencies:" << endl;
    counter.printWordFrequencies();

    counter.printMostFrequentWord();

    string outputFilename = "output.txt";
    counter.saveToFile(outputFilename);

    return 0;
}
