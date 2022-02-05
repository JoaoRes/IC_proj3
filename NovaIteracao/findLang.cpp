#include "fcm.hh"

using namespace std;

int main(int argc, char* argv[]){
    double min_nbitChar=121231231231;
    int language=0;
    int k = stoi(argv[1]);
    double alfa = stod(argv[2]);
    string avaluation(argv[3]);
    char byte = 0;
    string filename[] = {"textos/czech.txt","textos/dutch.txt","textos/eng.txt","textos/esp.txt","textos/fin.txt","textos/fr.txt","textos/ita.txt","textos/pol.txt","textos/pt.txt","textos/slovak.txt","textos/swe.txt"};
    double entropias[11];
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


        // Calculate similarity of 2nd text
        // fill hashtable with occurences
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
        cout << "nbits per Char: " <<nbits<< endl;
        cout <<  bitChar << endl;

        entropias[i]=bitChar;

        if(min_nbitChar>bitChar){
            min_nbitChar=bitChar;
            language=i;
        }

        cout << "---------------------------------------------------------------------------------------------------------" << endl;
    }

    cout << endl;
    cout << endl;
    cout << endl;
    cout << "---------------------- RESULTS ----------------------" << endl;
    for(int i=0 ; i<11 ; i++){
        cout << "Texto de Referencia: " << filename[i] << " \t -> \tNº Bits por carater " << entropias[i] << endl;
    }
    cout << "Language " << filename[language].substr(filename[language].find("/")+1) << endl;
    cout << "Estimated Bytes " << min_nbitChar << endl;

    
    return EXIT_SUCCESS;
}