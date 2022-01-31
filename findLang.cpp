#include "fcm.hh"

using namespace std;

int main(int argc, char* argv[]){
    double min_entropy_diference=121231231231;
    double analysis_entropy=0, ref_entropy=0;
    int language=0;
    int k = stoi(argv[1]);
    double alfa = stod(argv[2]);
    string avaluation(argv[3]);
    char byte = 0;
    string filename[] = {"textos/czech.txt","textos/dutch.txt","textos/eng.txt","textos/esp.txt","textos/fin.txt","textos/fr.txt","textos/ita.txt","textos/pol.txt","textos/pt.txt","textos/slovak.txt","textos/swe.txt"};
    double entropias[11];
    double entr[11];
    for(int i=0; i<11 ;i++){
        // open files
        ifstream input_file(filename[i]);
        ifstream input_file2(avaluation);
        if (!input_file.is_open() || !input_file2.is_open()) {
            cerr << "Could not open the file - '"
                << filename << "'" << endl;
            return EXIT_FAILURE;
        }

        // Create alphabet
        while (input_file.get(byte)) {
            alphabet.insert(tolower(byte));
        }

        // Create 2 hashtables
        ht = create_table(CAPACITY,alphabet.size());
        ht2 = create_table(CAPACITY,alphabet.size());
        
        // Create Model from reference text
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
        
        // print all elements of the set s2
        set<char, greater<char>>::iterator itr;
        cout << "\nAlphabet : \n";

        for (itr = alphabet.begin(); itr != alphabet.end(); itr++) {
            cout << *itr << " ";
        }

        cout << endl;
        cout << endl;

        //Calculate and print entropy of reference text
        entropy(ht,alfa);
        cout << "Texto de Referencia: " << filename[i] << " ";
        print_entropy(ht);
        cout << endl;
        ref_entropy = ht->entropy;
        entropias[i] = ref_entropy;

        //Deep Copy of hashtable
        deep_copy_hashtable(ht, ht2);

        //free table and close file of reference text
        free_table(ht);

        //Clear table to insert occurences
        clean_items(ht2);


        // Calculate similarity of 2nd text
        // fill hashtable with occurences
        byte=0;
        char* old_str1 = (char*)malloc(sizeof(char) * k);
        int relative1 = 0;
        input_file2.clear();
        input_file2.seekg(0);
        for (relative1= 0; relative1<k ; relative1++) {
            input_file2.get(byte);
            old_str1[relative1++] = tolower(byte);
        }
        while (input_file2.get(byte)) {
            ht_insert_second(ht2, old_str1,tolower(byte));//Ntolower(byte));
            std::memmove(old_str1, old_str1 + 1, k);
            old_str1[k-1] = tolower(byte);
        }
        ht_insert_second(ht2, old_str1,tolower(byte));

        input_file2.close();

        //Calculate and print entropy of text in analysis
        entropy(ht2,alfa);
        cout << "Texto em Analise: ";
        print_entropy(ht2);
        cout << endl;
        analysis_entropy = ht2->entropy;
        entr[i] = analysis_entropy;

        alphabet.clear();
        //---------------------------
        free_table(ht2);
        //---------------------------

        if((min_entropy_diference > abs(analysis_entropy - ref_entropy)) && (analysis_entropy != 0)){
            min_entropy_diference = abs(analysis_entropy - ref_entropy);
            language=i;
        }

        cout << "---------------------------------------------------------------------------------------------------------" << endl;
    }

    cout << endl;
    cout << endl;
    cout << endl;
    cout << "---------------------- RESULTS ----------------------" << endl;
    for(int i=0 ; i<11 ; i++){
        cout << "Texto de Referencia: " << filename[i] << " \t -> \tEntropia modelo: " << entropias[i] << " \t\tNbits analise: "<<  entr[i] << "\t\t diferenca = "<< abs(entr[i]  - entropias[i]) << endl;
    }
    cout << "Language " << filename[language].substr(filename[language].find("/")+1) << endl;
    cout << "Estimated Bytes " << analysis_entropy << endl;

    
    return EXIT_SUCCESS;
}