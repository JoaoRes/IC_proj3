#include "fcm.hh"

using namespace std;

int main(int argc, char* argv[]){
    double min_entropy_diference=121231231231;
    int language=0;
    int k = stoi(argv[1]);
    double alfa = stod(argv[2]);
    string avaluation(argv[3]);
    char byte = 0;
    //HashTable* ht = create_table(CAPACITY,alphabet.size());
    string filename[] = {"textos/czech.txt","textos/dutch.txt","textos/eng.txt","textos/esp.txt","textos/fin.txt","textos/fr.txt","textos/ger.txt","textos/ita.txt","textos/pol.txt","textos/pt.txt","textos/slovak.txt","textos/swe.txt"};
    for(int i=0; i<12 ;i++){
        ifstream input_file(filename[i]);
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
        ht2 = create_table(CAPACITY,alphabet.size());
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
        set<char, greater<char>>::iterator itr;
        cout << "\nAlphabet : \n";

        for (itr = alphabet.begin(); itr != alphabet.end(); itr++) {
            cout << *itr << " ";
        }

        //ht2 = create_table(CAPACITY,alphabet.size());
        deep_copy_hashtable(ht, ht2);
        clean_items(ht2);

        char* old_str1 = (char*)malloc(sizeof(char) * k);
        int relative1 = 0;
        input_file2.clear();
        input_file2.seekg(0);
        for (relative1= 0; relative1 <k ; relative1++) {
            input_file2.get(byte);
            old_str1[relative1++] = tolower(byte);

        }
        while (input_file2.get(byte)) {
            ht_insert_second(ht2, old_str1,tolower(byte));//Ntolower(byte));
            std::memmove(old_str1, old_str1 + 1, k);
            old_str1[k-1] = tolower(byte);
        }
        ht_insert_second(ht2, old_str1,tolower(byte));
        // print all elements of the set s2

        cout << endl;
        cout << endl;
        input_file.close();
        input_file2.close();
        entropy(ht,alfa);
        entropy(ht2,alfa);

        cout << "ref" << filename[i];
        print_entropy(ht);
        cout << endl;

        cout << "text";
        print_entropy(ht2);
        cout << endl;

        cout << "entropia ht2: " << ht2->entropy << endl;

        if((min_entropy_diference > abs(ht2->entropy - ht->entropy)) && (ht2->entropy != 0)){
            min_entropy_diference = abs(ht2->entropy - ht->entropy);
            language=i;
        }

        if(i==9){
            print_table(ht);
            print_table(ht2);
        }

        alphabet.clear();
        free_table(ht);
        free_table(ht2);
    }

    cout << "min_entr " << min_entropy_diference << endl;
    cout << "language " << filename[language] << endl;
    

    return EXIT_SUCCESS;
}