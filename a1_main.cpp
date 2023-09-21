
#include "Wordlist.h"
#include "Wordlist_base.h"
#include "test.h"

    Wordlist lst;


void read_from_terminal(const string& fileLoc)
{
    ifstream inFile(fileLoc);
    if (!inFile) {
        cout << "Error loading the file: ";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream lineStream(line);
        string word;
        while (lineStream >> word) {
            lst.add_word(word);
        }
    }

    inFile.close();

    // print the words in sorted order


    cout << lst.length();

    vector<string*> index = lst.get_sorted_index();
    for (int i = 0; i < index.size(); i++)
    {
        cout << (i + 1) << ". " << *index[i] << endl;
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    read_from_terminal(argv[1]);

    file.close();
    return EXIT_SUCCESS;
}
