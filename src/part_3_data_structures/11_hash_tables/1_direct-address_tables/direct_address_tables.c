#include "part_3_data_structures/11_hash_tables/hash_tables.h"

void dat_init(DirectAccessTable* dat) {
    for (int i = 0; i < DAT_SIZE; i++) {
        dat[i].isPresent = 0;
    }
}

void dat_insert(DirectAccessTable* dat, int key, int value) {
    if (key <= 0 || key >= DAT_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }
    dat[key].value = value;
    dat[key].isPresent = 1;
}

int dat_search(DirectAccessTable* dat, int key) {
    return (key >= 0 && key < DAT_SIZE && dat[key].isPresent) ? key : NIL;
}

void dat_delete(DirectAccessTable* dat, int key) {
    if (key < 0 || key >= DAT_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }
    dat[key].isPresent = 0;
}

int dat_find_max_key(DirectAccessTable* dat, int idx) {
    if (idx < 0) return NIL;
    else if (dat_search(dat, idx) != NIL) return idx;
    else return dat_find_max_key(dat, idx - 1);
}

int dat_get_max_key(DirectAccessTable* dat) {
    return dat_find_max_key(dat, DAT_SIZE - 1);
}

void bv_init(BitVector* bv) {
    *bv = 0;
}

void bv_set_bit(BitVector* bv, int idx) {
    if (idx >= 0 && idx < BIT_VECTOR_SIZE) {
        *bv |= (1 << idx);
    }
}

void bv_clear_bit(BitVector* bv, int idx) {
    if (idx >= 0 && idx < BIT_VECTOR_SIZE) {
        *bv &= ~(1 << idx);
    }
}

int bv_check_bit(BitVector bv, int idx) {
    if (idx >= 0 && idx < BIT_VECTOR_SIZE) {
        return (bv & (1 << idx)) != 0;
    }
    return 0;
}

void print_bit_vector(BitVector bv) {
    for (int i = BIT_VECTOR_SIZE - 1; i >= 0; i--) {
        printf("%d ", bv_check_bit(bv, i));
    }
    printf("\n");
}

void dll_dat_init(DllDirectAccessTable* dllDat) {
    for (int i = 0; i < DAT_SIZE; i++) {
        dllDat[i].head = NULL;  
    }
}

void dll_dat_insert(DllDirectAccessTable* dllDat, int key, int sattelite_data) {
    if (key < 0 || key >= DAT_SIZE) {
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

DllDatElement* dll_dat_search(DllDirectAccessTable* dllDat, int key) {
    if (key < 0 || key >= DAT_SIZE) {
        printf("Key %d is out of range!\n", key);
        return NULL;
    }
    return dllDat[key].head;
}

void dll_dat_delete(
    DllDirectAccessTable* dllDat, 
    int key, 
    DllDatElement* target
) {
    if (key < 0 || key >= DAT_SIZE || target == NULL) {
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

void print_dll_dat(DllDirectAccessTable* dllDat, int key) {
    if (key < 0 || key >= DAT_SIZE) {
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

void da_dict_init(DirectAddressDict* daDict) {
    daDict->arr = (HugeArrayEntry*)malloc(DAT_SIZE * sizeof(HugeArrayEntry));
    daDict->stack = (int*)malloc(DAT_SIZE * sizeof(int));
    daDict->stack_size =  0;

    for (int i = 0; i < DAT_SIZE; i++) {
        daDict->arr[i].key = NIL;   
        daDict->arr[i].stackPtr = NULL;  
    }
}

void da_dict_insert(DirectAddressDict* daDict, int key) {
    if (key < 0 || key >= DAT_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }

    if (daDict->arr[key].key != NIL) {
        printf("Key %d in already present.\n", key);
        return;
    }

    int* stack_elem = &daDict->stack[daDict->stack_size++];
    daDict->arr[key].key = key;
    daDict->arr[key].stackPtr = stack_elem;
}

int da_dict_search(DirectAddressDict* daDict, int key) {
    if (key < 0 || key >= DAT_SIZE) {
        printf("Key %d is out of range.\n", key);
        return NIL; 
    }

    if (daDict->arr[key].key != NIL && daDict->arr[key].stackPtr != NULL) {
        return daDict->arr[key].key;
    }

    return NIL;
}

void da_dict_delete(DirectAddressDict* daDict, int key) {
    if (key < 0 || key >= DAT_SIZE) {
        printf("Key %d is out of range!\n", key);
        return;
    }

    if (daDict->arr[key].key == NIL) {
        printf("Key %d is not present.\n", key);
        return;
    }

    daDict->arr[key].stackPtr = NULL;
    daDict->arr[key].key = NIL;

    daDict->stack_size--;
}

void print_da_dict(DirectAddressDict* daDict) {
    for (int i = 0; i < DAT_SIZE; i++) {
        if (daDict->arr[i].key != NIL) {
            printf("Key %d is present.\n", daDict->arr[i].key);
        }
    }
}