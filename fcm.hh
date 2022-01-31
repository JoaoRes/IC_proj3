#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include <cstring>
#include <math.h>

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
    int cocurrences;
    int *array;
    double entropy;
};

typedef struct HashTable HashTable;
HashTable* ht;
HashTable* ht2;
// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
    int array_Size;
    double entropy;
    int occurrences;
};

Ht_item* create_item(char* key, int value, int n) {
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    //item->value = (char*) malloc (strlen(value) + 1);
    item ->array = (int*) calloc(n, sizeof(int));

    strcpy(item->key, key);
    item->cocurrences= 0;
    item->entropy = 0;

    return item;
}

HashTable* create_table(int size, int array_size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->occurrences=0;
    table->array_Size = array_size;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;

    return table;
}

void free_item(Ht_item* item) {
    // Frees an item
    free(item->key);
    free(item->array);
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

void deep_copy_hashtable(HashTable* src, HashTable* dst){
    for (int i=0; i<src->size; i++) {
        if (src->items[i]) {
            Ht_item* dst_item = create_item(src->items[i]->key, 1,src->array_Size);
            dst->items[i] = dst_item;
            // Compute the index
            unsigned long index = hash_function(src->items[i]->key);
            Ht_item* src_item = src->items[index];

            for (int j = 0; j < src->array_Size; j++) {
                dst->items[i]->array[j] = src->items[i]->array[j];
            }

            dst->items[i]->cocurrences=src->items[i]->cocurrences;
            dst->items[i]->entropy=src->items[i]->entropy;
        }
    }
}
void clean_items(HashTable* table){
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            for (int j = 0; j < table->array_Size; j++) {
                table->items[i]->array[j] = 0;
            }
            table->items[i]->cocurrences=0;
            table->items[i]->entropy=0;
        }
    }
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
        table->items[index]->cocurrences++;
        table->count++;
        table->occurrences++;
    }

    else {
        // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0) {
            if(next_char!= NULL) {
                int alfa_index = std::distance(alphabet.begin(), alphabet.find(next_char));
                //cout << "alfa_index = "<< alfa_index << " char ="<<next_char<<endl;
                table->items[index]->array[alfa_index]++;
            }
            table->items[index]->cocurrences++;
            table->occurrences++;
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

void ht_insert_second(HashTable* table, char* key,char next_char) {
    // Create the item

    Ht_item* item = create_item(key, 1,table->array_Size);


    // Compute the index
    unsigned long index = hash_function(key);

    Ht_item* current_item = table->items[index];


    if (current_item != NULL) {

        // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0) {
            if(next_char!= NULL) {
                int alfa_index = std::distance(alphabet.begin(), alphabet.find(next_char));
                //cout << "alfa_index = "<< alfa_index << " char ="<<next_char<<endl;
                table->items[index]->array[alfa_index]++;
            }
            table->items[index]->cocurrences++;
            table->occurrences++;
            return;
        }else {
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
            return item->cocurrences;
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
        //printf("Key:%s, Value:%d\n", key, val);
    }
}

void print_entropy(HashTable* table){
    cout << "File Nbits per char: "<< table->entropy<<endl;
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
            char *string = (char *) malloc(strlen(table->items[i]->key) * 2 + 1);
            int s_i = 0;
            for (const char *p = table->items[i]->key; *p != '\0'; ++p) {
                int c = (unsigned char) *p;
                switch (c) {
                    case '\\':
                        string[s_i++] = '\\';
                        string[s_i++] = '\\';
                        //printf("\\\\");
                        break;
                    case '\n':
                        //printf("\\n");
                        string[s_i++] = '\\';
                        string[s_i++] = 'n';
                        break;
                    case '\r':
                        //printf("\\r");
                        string[s_i++] = '\\';
                        string[s_i++] = 'r';
                        break;
                    case '\t':
                        //printf("\\t");
                        string[s_i++] = '\\';
                        string[s_i++] = 't';
                        break;

                        // TODO: Add other C character escapes here.  See:
                        // <https://en.wikipedia.org/wiki/Escape_sequences_in_C#Table_of_escape_sequences>

                    default:
                        if (isprint(c)) {
                            //putchar(c);
                            string[s_i++] = c;
                        }
                        break;
                }
            }
            printf("%s  ", table->items[i]->key);
            for (int ind = 0; ind < table->array_Size; ind++) {
                if (table->items[i]->array[ind] == 0)
                    cout << " " << black << table->items[i]->array[ind] << reset << " ";
                else if (table->items[i]->array[ind] == 1)
                    cout << " " << red << table->items[i]->array[ind] << reset << " ";
                else if (table->items[i]->array[ind] == 2)
                    cout << " " << yellow << table->items[i]->array[ind] << reset << " ";
                else if (table->items[i]->array[ind] == 3)
                    cout << " " << blue << table->items[i]->array[ind] << reset << " ";
                else if (table->items[i]->array[ind] == 4)
                    cout << " " << green << table->items[i]->array[ind] << reset << " ";
                else if (table->items[i]->array[ind] >= 5)
                    cout << " " << white << table->items[i]->array[ind] << reset << " ";
            }
            cout << " occurrences: " <<table->items[i]->cocurrences;
            cout << " entropy: " <<table->items[i]->entropy<<endl;

        }
    }
}

void entropy(HashTable* table,double alfa){
    double p;
    for (int i=0; i<table->size; i++) {
        if (table->items[i]&& table->items[i]->cocurrences) {
            for (int j = 0; j < table->array_Size; j++) {
                if (table->items[i]->array[j] >= 0) {
                    p = (double) (table->items[i]->array[j] + alfa) / (table->items[i]->cocurrences+alfa*table->array_Size);
                    //cout << "p " << p << endl;
                    table->items[i]->entropy += -p * log2(p);
                }
            }
            table->entropy+=(table->items[i]->entropy * table->items[i]->cocurrences / table->occurrences);
        }
    }
}
