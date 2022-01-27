#include "fcm.hh"

using namespace std;

int main(int argc, char* argv[]){
    string filename(argv[1]);
    int k = stoi(argv[2]);
    double alfa = stod(argv[3]);
    char byte = 0;
    //HashTable* ht = create_table(CAPACITY,alphabet.size());

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file.get(byte)) {
        alphabet.insert(tolower(byte));
    }

    ht = create_table(CAPACITY,alphabet.size());
    char* old_str = (char*)malloc(sizeof(char) * k);
    int relative = 0;
    input_file.clear();
    input_file.seekg(0);
    for (relative= 0; relative<k ; relative++) {
        input_file.get(byte);
        old_str[relative++] = tolower(byte);

    }
    while (input_file.get(byte)) {
        ht_insert(ht, old_str,tolower(byte));
        std::memmove(old_str, old_str + 1, k);
        old_str[k-1] = tolower(byte);
    }
    ht_insert(ht, old_str,tolower(byte));
    // print all elements of the set s2
    set<char, greater<char>>::iterator itr;
    cout << "\nAlphabet : \n";

    for (itr = alphabet.begin(); itr != alphabet.end(); itr++) {
        cout << *itr << " ";

    }

    cout << endl;
    cout << endl;
    input_file.close();
    entropy(ht,alfa);

    print_table(ht);

    printf("\n\n\n");

    print_entropy(ht);
    return EXIT_SUCCESS;
}