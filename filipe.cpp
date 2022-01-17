#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include <cstring>

#define CAPACITY 500000 // Size of the Hash Table
using namespace std;

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
};

typedef struct HashTable HashTable;

// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
};

Ht_item* create_item(char* key, int value) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    //item->value = (char*) malloc (strlen(value) + 1);

    strcpy(item->key, key);
    item->value= 1;

    return item;
}

HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
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

void ht_insert(HashTable* table, char* key) {
    // Create the item
    Ht_item* item = create_item(key, 1);

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
        table->count++;
    }

    else {
        // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0) {
            table->items[index]->value++;
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
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_table(HashTable* table) {
    printf("\nHash Table\n-------------------\n");
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
            printf("%s , %s ;: Value:%d\n",string,table->items[i]->key, table->items[i]->value);
        }
    }
    printf("-------------------\n\n");
}


int main(int argc, char* argv[]){
    string filename(argv[1]);
    int k = stoi(argv[2]);
    vector<char> bytes;
    char byte = 0;
    set<char> alphabet;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    HashTable* ht = create_table(CAPACITY);
    int index = 0;
    char* str2 = (char*)malloc(sizeof(char) * k);
    int relative = 0;

    while (input_file.get(byte)) {
        alphabet.insert(byte);
        str2[index % k] = byte;
        if((index+1) % k == 0 && index != 0){
            ht_insert(ht, str2);
            cout<<str2<<endl;
        }

        index++;

    }

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