#include "ladder.cpp"

int main() {
    set<string> word_list;
    string dictionary_file = "src/words.txt";
    load_words(word_list, dictionary_file);
    
    string start_word, end_word;
    cout << "Enter the start word: ";
    cin >> start_word;
    cout << "Enter the end word: ";
    cin >> end_word;
    
    if (start_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return 1;
    }
    
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
    
    return 0;
}
