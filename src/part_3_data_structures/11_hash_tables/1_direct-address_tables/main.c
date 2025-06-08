#include "part_3_data_structures/11_hash_tables/hash_tables.h"

#define TASK 1

int main(void) {
    switch (TASK)
    {
        case 1: {
            DirectAccessTable dat[DAT_SIZE];
            dat_init(dat);

            dat_insert(dat, 10, 100);
            dat_insert(dat, 20, 200);
            dat_insert(dat, 30, 300);

            int key = 20;
            int found_key = dat_search(dat, key);
            if (found_key != NIL) {
                printf("Found: Key %d -> Value %d\n", found_key, (dat + found_key)->value);
            } else {
                printf("Key %d not found\n", key);
            }

            dat_delete(dat, 20);

            found_key = dat_search(dat, key);
            if (found_key != NIL) {
                printf("Found: Key %d -> Value %d\n", found_key, (dat + found_key)->value);
            } else {
                printf("Key %d not found\n", key);
            }

            break;
        }
        case 2: {
            DirectAccessTable dat[DAT_SIZE];
            dat_init(dat);

            dat_insert(dat, 10, 100);
            dat_insert(dat, 20, 400);
            dat_insert(dat, 30, 300);

            int max_key = dat_get_max_key(dat);
            if (max_key != NIL) {
                printf("Maximum key present: %d\n", max_key);
            } else {
                printf("No keys present in the table.\n");
            }

            break;
        }
        case 3: {
            BitVector bv;
            bv_init(&bv);

            bv_set_bit(&bv, 0);
            bv_set_bit(&bv, 1);
            bv_set_bit(&bv, 2);

            printf("Bit Vector Representation for set {0, 1, 2}: ");
            print_bit_vector(bv);

            bv_clear_bit(&bv, 0);

            printf("Bit Vector Representation for set {1, 2}: ");
            print_bit_vector(bv);

            bv_set_bit(&bv, 10);

            printf("Bit Vector Representation for set {1, 2, 10}: ");
            print_bit_vector(bv);

            break;
        }
        case 4: {
            DllDirectAccessTable dllDat[DAT_SIZE];
            dll_dat_init(dllDat);

            dll_dat_insert(dllDat, 10, 100);
            dll_dat_insert(dllDat, 10, 101);
            dll_dat_insert(dllDat, 10, 102);
            
            dll_dat_insert(dllDat, 20, 200);
            dll_dat_insert(dllDat, 20, 201);
            dll_dat_insert(dllDat, 20, 202);

            print_dll_dat(dllDat, 10);
            print_dll_dat(dllDat, 20);

            DllDatElement* first_elem = dll_dat_search(dllDat, 10);

            if (first_elem != NULL) {
                printf("First element at key 10: %d\n", first_elem->satellite_data);
            }

            dll_dat_delete(dllDat, 10, first_elem);
            print_dll_dat(dllDat, 10);

            break;
        }
        case 5: {
            DirectAddressDict daDict;
            da_dict_init(&daDict);

            da_dict_insert(&daDict, 10);
            da_dict_insert(&daDict, 20);
            da_dict_insert(&daDict, 30);

            printf("Searching for key 20: %d\n", da_dict_search(&daDict, 20));

            da_dict_delete(&daDict, 20);

            printf("Searching for key 20: %d\n", da_dict_search(&daDict, 20));

            print_da_dict(&daDict);

            break;
        }
        default:
            break;
    }

    return 0;
}