#include "fcm.hh"

using namespace std;

int main(int argc, char* argv[]){
    string filename(argv[1]);
    int k = stoi(argv[2]);
    double alfa = stod(argv[3]);
    string avaluation(argv[4]);
    char byte = 0;

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
    
    input_file.close();

    cout << "----------------- MODEL CREATED ---------------------" << endl;
    cout << endl;
    cout << endl;
    
    // print all elements of the set s2
    // cout << "\nAlphabet : \n";

    // for (itr = alphabet.begin(); itr != alphabet.end(); itr++) {
    //     cout << *itr << " ";
    // }

    char* old_str1 = (char*)malloc(sizeof(char) * (k));
    int relative1;
    for (relative1= 0; relative1 < k ; relative1++) {
        input_file2.get(byte);
        old_str1[relative1++] = tolower(byte);
    }
    
    double nbits=0;
    int ocurrences=0;
    // read other bytes
    while (input_file2.get(byte)) {
        // char exists
        cout << "1" << endl;
        if(alphabet.find(tolower(byte)) != alphabet.end()){
            cout << "2" << endl;
            int wordIDX = ht_search1(ht,old_str1);
            // word exists
            if(wordIDX >= 0){
                cout << "3" << endl;
                int alfaIDX = std::distance(alphabet.begin(), alphabet.find(tolower(byte)));
                cout << "ALPHABET SIZE: " << alphabet.size() << endl;
                cout << "charIDX: " << alfaIDX << endl; // valor válido
                cout << "wordIDX: " << wordIDX << endl; // valor válido
                cout << "31" << endl;
                double up = (double) (ht->items[wordIDX]->array[alfaIDX] + alfa); // segmentation fault
                double down = (double) ht->items[wordIDX]->cocurrences + alfa*alphabet.size();
                double p = (double) up / (double) down;
                nbits += (double) -log2(p);
            }else{
                cout << "4" << endl;
                double val = (double)1/alphabet.size();
                nbits+= (double) -log2(val);
            }
        }else{
            cout << "5" << endl;
            double val = (double)1/alphabet.size();
            nbits+= (double) -log2(val);
        }

        cout << "6" << endl;
        std::memmove(old_str1, old_str1 + 1, k);
        old_str1[k-1] = tolower(byte);
        ocurrences++;
        cout << "7" << endl;
    }
    input_file2.close();
    free_table(ht);


    cout << endl;
    cout << endl;
    double bitChar = (double) nbits/ocurrences;
    cout << "nbits " <<nbits<< endl;
    cout <<  bitChar << endl;

    //print_table(ht);
    //cout << "-----------------------------------HASH 1--------------------------------" << endl;
    //print_table(ht2);

    //print_entropy(ht);

    return EXIT_SUCCESS;
}