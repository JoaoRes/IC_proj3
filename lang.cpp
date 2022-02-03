#include "fcm.hh"

using namespace std;

int main(int argc, char* argv[]){
    string filename(argv[1]);
    int k = stoi(argv[2]);
    double alfa = stod(argv[3]);
    string avaluation(argv[4]);
    char byte = 0;
    //HashTable* ht = create_table(CAPACITY,alphabet.size());

    ifstream input_file(filename);
    ifstream input_file2(avaluation);
    if (!input_file.is_open() || !input_file2.is_open()) {
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
    for (relative= 0; relative <k ; relative++) {
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
    // set<char, greater<char>>::iterator itr;
    // cout << "\nAlphabet : \n";

    // for (itr = alphabet.begin(); itr != alphabet.end(); itr++) {
    //     cout << *itr << " ";

    // }

    char* old_str1 = (char*)malloc(sizeof(char) * k);
    int relative1 = 0;
    input_file.clear();
    input_file.seekg(0);
    for (relative1= 0; relative1 <k ; relative1++) {
        input_file.get(byte);
        old_str1[relative1++] = tolower(byte);

    }
    double nbits=0;
    int ocurrences=0;
    while (input_file.get(byte)) {
        int i;
        std::memmove(old_str1, old_str1 + 1, k);
        old_str1[k-1] = tolower(byte);
        i=ht_search(ht,old_str1);
        if(i > 0){
            if (ht->items[i]&& ht->items[i]->cocurrences) {
                for (int j = 0; j < ht->array_Size; j++) {
                    if (ht->items[i]->array[j] >= 0) {
                        cout<< "item[" << ht->items[i] << "] value : "<< ht->items[i]->array[j]<<endl;
                        nbits += -log2((double) (ht->items[i]->array[j] + alfa) / (ht->items[i]->cocurrences+alfa*ht->array_Size));                     
                    }
                }
            }
        }
        ocurrences++;
    }

    cout << endl;
    cout << endl;
    input_file.close();
    input_file2.close();
    entropy(ht,alfa);
    cout << "nbits " <<nbits<< endl;
    cout <<  nbits/(ht->occurrences+ocurrences) << endl;

    //print_table(ht);
    //cout << "-----------------------------------HASH 1--------------------------------" << endl;
    //print_table(ht2);

    print_entropy(ht);

    return EXIT_SUCCESS;
}