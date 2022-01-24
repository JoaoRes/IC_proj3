#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include <cstring>

#define CAPACITY 500000 // Size of the Hash Table
using namespace std;
set<char> alphabet;

unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

typedef struct Ht_item Ht_item;

// Define the Hash Table Item here
struct Ht_item {
    char* key;
    int value;
    int *array;
};

typedef struct HashTable HashTable;

// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
    int array_Size;
};

Ht_item* create_item(char* key, int value, int n) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    //item->value = (char*) malloc (strlen(value) + 1);
    item ->array = (int*) calloc(n, sizeof(int));

    strcpy(item->key, key);
    item->value= 1;

    return item;
}

HashTable* create_table(int size, int array_size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->array_Size = array_size;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;

    return table;
}

void free_item(Ht_item* item) {
    // Frees an item
    free(item->key);
    //free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    // Frees the table
    for (int i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
}

void ht_insert(HashTable* table, char* key,char next_char) {
    // Create the item

    Ht_item* item = create_item(key, 1,table->array_Size);

    // Compute the index
    unsigned long index = hash_function(key);

    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }

        // Insert directly
        table->items[index] = item;
        int alfa_index = std::distance(alphabet.begin(), alphabet.find(next_char));
        //cout << "alfa_index = "<< alfa_index << " char ="<<next_char<<endl;
        table->items[index]->array[alfa_index]++;

        table->count++;
    }

    else {
        // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0) {
            int alfa_index = std::distance(alphabet.begin(), alphabet.find(next_char));
            //cout << "alfa_index = "<< alfa_index << " char ="<<next_char<<endl;
            table->items[index]->array[alfa_index]++;
            return;
        }

        else {
            // Scenario 2: Collision
            // We will handle case this a bit later
            handle_collision(table, index, item);
            return;
        }
    }
}

 int ht_search(HashTable* table, char* key) {
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash_function(key);
    Ht_item* item = table->items[index];

    // Ensure that we move to a non NULL item
    if (item != NULL) {
        if (strcmp(item->key, key) == 0)
            return item->value;
    }
    return -1;
}

void print_search(HashTable* table, char* key) {
    int val;
    if ((val = ht_search(table, key)) == -1) {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%d\n", key, val);
    }
}

void print_table(HashTable* table) {
    printf("\nHash Table\n-------------------\n");
    string reset = "\033[0m";
    string red = "\033[1;31m";
    string green = "\033[1;32m";
    string blue = "\033[1;34m";
    string yellow = "\033[1;33m";
    string black = "\033[1;30m";
    string white = "\033[1;37m";

    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, ", i);
            char* string = (char*) malloc (strlen(table->items[i]->key)*2 + 1);
            int s_i = 0;
            for (const char* p = table->items[i]->key; *p != '\0'; ++p) {
                int c = (unsigned char) *p;
                switch (c)
                {
                    case '\\':
                        string[s_i++]='\\';
                        string[s_i++]='\\';
                        //printf("\\\\");
                        break;
                    case '\n':
                        //printf("\\n");
                        string[s_i++]='\\';
                        string[s_i++]='n';
                        break;
                    case '\r':
                        //printf("\\r");
                        string[s_i++]='\\';
                        string[s_i++]='r';
                        break;
                    case '\t':
                        //printf("\\t");
                        string[s_i++]='\\';
                        string[s_i++]='t';
                        break;

                        // TODO: Add other C character escapes here.  See:
                        // <https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences>

                    default:
                        if (isprint(c)){
                            //putchar(c);
                            string[s_i++]=c;
                        }
                        break;
                }
            }
            printf("%s  ",table->items[i]->key);
            for( int ind = 0; ind < table->array_Size; ++ind )
                if (table->items[i]->array[ind] == 0)
                    cout << " " << black<< table->items[i]->array[ind] <<reset <<" ";
                else if (table->items[i]->array[ind] == 1)
                    cout << " " << red<< table->items[i]->array[ind] <<reset <<" ";
                else if (table->items[i]->array[ind] == 2)
                    cout << " " << yellow<< table->items[i]->array[ind] <<reset <<" ";
                else if (table->items[i]->array[ind] == 3)
                    cout << " " << blue<< table->items[i]->array[ind] <<reset <<" ";
                else if (table->items[i]->array[ind] == 4)
                    cout << " " << green<< table->items[i]->array[ind] <<reset <<" ";
                else if (table->items[i]->array[ind] >= 5)
                    cout << " " << white<< table->items[i]->array[ind] <<reset <<" ";
                //printf( " %d ", table->items[i]->array[ind] );
            printf("\n");
            //printf("%s , %s ;: Value:%d\n",string,table->items[i]->key, table->items[i]->value);

        }
    }
    printf("-------------------\n\n");
}


int main(int argc, char* argv[]){
    string filename(argv[1]);
    int k = stoi(argv[2]);
    char byte = 0;


    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (input_file.get(byte)) {
        alphabet.insert(tolower(byte));
    }

    HashTable* ht = create_table(CAPACITY,alphabet.size());
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
    cout << endl;
    cout << endl;
    input_file.close();
    print_table(ht);

    return EXIT_SUCCESS;
}