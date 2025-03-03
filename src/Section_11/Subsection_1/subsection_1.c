#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TASK 5
#define NIL -1

//----------Direct Access Table----------
#define TABLE_SIZE 1000

typedef struct {
    int value;
    bool is_present;
} DirectAccessTable;

void init_dat(DirectAccessTable* dat) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        dat[i].is_present = false;
    }
}

void insert_dat(DirectAccessTable* dat, int key, int value) {
    if (key <= 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range!\n", key);
    }
    dat[key].value = value;
    dat[key].is_present = true;
}

int dat_search(DirectAccessTable* dat, int key) {
    return (key >= 0 && key < TABLE_SIZE && dat[key].is_present) ? key : NIL;
}

void delete_dat(DirectAccessTable* dat, int key) {
    if (key < 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range!\n", key);
    }
    dat[key].is_present = false;
}

int dat_table_maximum_key(DirectAccessTable* dat, int idx) {
    if (idx < 0) return NIL;
    else if (dat_search(dat, idx) != NIL) return idx;
    else dat_table_maximum_key(dat, idx - 1);
}

int dat_max_key(DirectAccessTable* dat) {
    return dat_table_maximum_key(dat, TABLE_SIZE - 1);
}

//----------Bit Vector----------
#define BIT_VECTOR_SIZE 20
typedef unsigned int BitVector;

void init_bv(BitVector* bv) {
    *bv = 0;
}

void set_bit(BitVector* bv, int idx) {
    if (idx >= 0 && idx < BIT_VECTOR_SIZE) {
        *bv |= (1 << idx);
    }
}

void clear_bit(BitVector* bv, int idx) {
    if (idx >= 0 && idx < BIT_VECTOR_SIZE) {
        *bv &= ~(1 << idx);
    }
}

bool check_bit(BitVector bv, int idx) {
    if (idx >= 0 && idx < BIT_VECTOR_SIZE) {
        return (bv & (1 << idx)) != 0;
    }
}

void print_bit_vector(BitVector bv) {
    for (int i = BIT_VECTOR_SIZE - 1; i >= 0; i--) {
        printf("%d ", check_bit(bv, i));
    }
    printf("\n");
}

//----------DAT with satelite data (as doubly linked list)----------
typedef struct DllDatElement {
    int satellite_data;
    struct DllDatElement* prev;
    struct DllDatElement* next;
} DllDatElement;

typedef struct DllDirectAccessTable {
    DllDatElement* head;
} DllDirectAccessTable;

void init_dllDat(DllDirectAccessTable* dllDat) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        dllDat[i].head = NULL;  
    }
}

void insert_dllDat(DllDirectAccessTable* dllDat, int key, int sattelite_data) {
    if (key < 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }

    DllDatElement* new_element = (DllDatElement*)malloc(sizeof(DllDatElement));
    new_element->satellite_data = sattelite_data;
    new_element->prev = NULL;   
    new_element->next = dllDat[key].head;

    if (dllDat[key].head != NULL) {
        dllDat[key].head->prev = new_element;
    }

    dllDat[key].head = new_element;
}

DllDatElement* search_dllDat(DllDirectAccessTable* dllDat, int key) {
    if (key < 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range!\n", key);
        return NULL;
    }
    return dllDat[key].head;
}

void delete_dllDat(
    DllDirectAccessTable* dllDat, 
    int key, 
    DllDatElement* target
) {
    if (key < 0 || key >= TABLE_SIZE || target == NULL) {
        printf("Invalid key or element to delete!\n");
        return;
    }
    
    if (dllDat[key].head == target) {
        dllDat[key].head = target->next;
        if (dllDat[key].head != NULL) {
            dllDat[key].head->prev = NULL;
        } 
    } else {
        if (target->prev != NULL) {
            target->prev->next = target->next;
        }
        if (target->next != NULL) {
            target->next->prev = target->prev;
        }
    }

    free(target);
}

void print_dllDat(DllDirectAccessTable* dllDat, int key) {
    if (key < 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }

    DllDatElement* curr = dllDat[key].head;
    printf("Elements for key %d: ", key);
    while (curr != NULL) {
        printf("%d ", curr->satellite_data);
        curr = curr->next;
    }
    printf("\n");
}

//----------Huge array----------
typedef struct HugeArrayEntry {
    int key;
    int* stack_ptr;
} HugeArrayEntry;

typedef struct  DirectAddressDict {
    HugeArrayEntry* arr;
    int* stack;
    int stack_size;
} DirectAddressDict;

void init_daDict(DirectAddressDict* daDict) {
    daDict->arr = (HugeArrayEntry*)malloc(TABLE_SIZE * sizeof(HugeArrayEntry));
    daDict->stack = (int*)malloc(TABLE_SIZE * sizeof(int));
    daDict->stack_size =  0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        daDict->arr[i].key = NIL;   
        daDict->arr[i].stack_ptr = NULL;  
    }
}

void insert_daDict(DirectAddressDict* daDict, int key) {
    if (key < 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }

    if (daDict->arr[key].key != NIL) {
        printf("Key %d in already present.\n", key);
        return;
    }

    int* stack_elem = &daDict->stack[daDict->stack_size++];
    daDict->arr[key].key = key;
    daDict->arr[key].stack_ptr = stack_elem;
}

int search_daDict(DirectAddressDict* daDict, int key) {
    if (key < 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range.\n", key);
        return NIL; 
    }

    if (daDict->arr[key].key != NIL && daDict->arr[key].stack_ptr != NULL) {
        return daDict->arr[key].key;
    }

    return NIL;
}

void delete_daDict(DirectAddressDict* daDict, int key) {
    if (key < 0 || key >= TABLE_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }

    if (daDict->arr[key].key == NIL) {
        printf("Key %d is not present.\n", key);
        return;
    }

    daDict->arr[key].stack_ptr = NULL;
    daDict->arr[key].key = NIL;

    daDict->stack_size--;
}

void print_daDict(DirectAddressDict* daDict) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (daDict->arr[i].key != NIL) {
            printf("Key %d is present.\n", daDict->arr[i].key);
        }
    }
}

//----------Main----------
int main(void) {
    switch (TASK)
    {
        case 1: {
            DirectAccessTable dat[TABLE_SIZE];
            init_dat(dat);

            insert_dat(dat, 10, 100);
            insert_dat(dat, 20, 200);
            insert_dat(dat, 30, 300);

            int key = 20;
            int found_key = dat_search(dat, key);
            if (found_key != NIL) {
                printf("Found: Key %d -> Value %d\n", found_key, (dat + found_key)->value);
            } else {
                printf("Key %d not found\n", key);
            }

            delete_dat(dat, 20);

            found_key = dat_search(dat, key);
            if (found_key != NIL) {
                printf("Found: Key %d -> Value %d\n", found_key, (dat + found_key)->value);
            } else {
                printf("Key %d not found\n", key);
            }

            break;
        }
        case 2: {
            DirectAccessTable dat[TABLE_SIZE];
            init_dat(dat);

            insert_dat(dat, 10, 100);
            insert_dat(dat, 20, 400);
            insert_dat(dat, 30, 300);

            int max_key = dat_max_key(dat);
            if (max_key != NIL) {
                printf("Maximum key present: %d\n", max_key);
            } else {
                printf("No keys present in the table.\n");
            }

            break;
        }
        case 3: {
            BitVector bv;
            init_bv(&bv);

            set_bit(&bv, 0);
            set_bit(&bv, 1);
            set_bit(&bv, 2);

            printf("Bit Vector Representation for set {0, 1, 2}: ");
            print_bit_vector(bv);

            clear_bit(&bv, 0);

            printf("Bit Vector Representation for set {1, 2}: ");
            print_bit_vector(bv);

            set_bit(&bv, 10);

            printf("Bit Vector Representation for set {1, 2, 10}: ");
            print_bit_vector(bv);

            break;
        }
        case 4: {
            DllDirectAccessTable dllDat[TABLE_SIZE];
            init_dllDat(dllDat);

            insert_dllDat(dllDat, 10, 100);
            insert_dllDat(dllDat, 10, 101);
            insert_dllDat(dllDat, 10, 102);
            
            insert_dllDat(dllDat, 20, 200);
            insert_dllDat(dllDat, 20, 201);
            insert_dllDat(dllDat, 20, 202);

            print_dllDat(dllDat, 10);
            print_dllDat(dllDat, 20);

            DllDatElement* first_elem = search_dllDat(dllDat, 10);

            if (first_elem != NULL) {
                printf("First element at key 10: %d\n", first_elem->satellite_data);
            }

            delete_dllDat(dllDat, 10, first_elem);
            print_dllDat(dllDat, 10);

            break;
        }
        case 5: {
            DirectAddressDict daDict;
            init_daDict(&daDict);

            insert_daDict(&daDict, 10);
            insert_daDict(&daDict, 20);
            insert_daDict(&daDict, 30);

            printf("Searching for key 20: %d\n", search_daDict(&daDict, 20));

            delete_daDict(&daDict, 20);

            printf("Searching for key 20: %d\n", search_daDict(&daDict, 20));

            print_daDict(&daDict);

            break;
        }
        default:
            break;
    }

    return 0;
}