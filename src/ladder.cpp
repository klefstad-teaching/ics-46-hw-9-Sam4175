#include "ladder.h"
// #include <cassert>

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
    exit(EXIT_FAILURE);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > d) return false;
    
    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff > d) return false;
            if (len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else { ++i; ++j; }
        }
        else {
            ++i; ++j;
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};
    if (word_list.find(end_word) == word_list.end()) return {};

    queue<vector<string>> ladders;
    set<string> used_words;
    ladders.push({begin_word});
    used_words.insert(begin_word);

    while (!ladders.empty()) {
        int size = ladders.size();
        set<string> new_used_words;  // words discovered at the current level

        for (int i = 0; i < size; ++i) {
            vector<string> ladder = ladders.front();
            ladders.pop();
            string last_word = ladder.back();

            vector<string> candidates;

            // 1. Substitution: change each letter to every other letter.
            for (int pos = 0; pos < last_word.size(); ++pos) {
                string candidate = last_word;
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == last_word[pos])
                        continue;
                    candidate[pos] = c;
                    if (word_list.find(candidate) != word_list.end() &&
                        used_words.find(candidate) == used_words.end())
                    {
                        candidates.push_back(candidate);
                    }
                }
            }

            // 2. Insertion: insert a letter at every possible position.
            for (int pos = 0; pos <= last_word.size(); ++pos) {
                string candidate = last_word;
                for (char c = 'a'; c <= 'z'; ++c) {
                    candidate.insert(candidate.begin() + pos, c);
                    if (word_list.find(candidate) != word_list.end() &&
                        used_words.find(candidate) == used_words.end())
                    {
                        candidates.push_back(candidate);
                    }
                    candidate.erase(candidate.begin() + pos);  // restore candidate
                }
            }

            // 3. Deletion: remove one letter at each position.
            if (last_word.size() > 1) {  // Ensure result is non-empty.
                for (int pos = 0; pos < last_word.size(); ++pos) {
                    string candidate = last_word;
                    candidate.erase(candidate.begin() + pos);
                    if (word_list.find(candidate) != word_list.end() &&
                        used_words.find(candidate) == used_words.end())
                    {
                        candidates.push_back(candidate);
                    }
                }
            }

            // Remove duplicate candidates (if any) and sort them lexicographically.
            sort(candidates.begin(), candidates.end());
            candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

            // Process candidates in sorted order.
            for (const string &candidate : candidates) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(candidate);
                if (candidate == end_word)
                    return new_ladder;
                ladders.push(new_ladder);
                new_used_words.insert(candidate);
            }
        }
        // Mark all words found in this level as used.
        used_words.insert(new_used_words.begin(), new_used_words.end());
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        exit(EXIT_FAILURE);
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    
    // Print each word in the ladder
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " ";
        cout << ladder[i];
    }
    // Print a trailing space and newline
    cout << " " << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
