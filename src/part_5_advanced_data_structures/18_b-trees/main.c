#include "part_5_advanced_data_structures/18_b-trees/b-trees.h"

int main(void) {
    BTreeNode* root = btree_init();

    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) btree_tree_insert(&root, values[i]);

    printf("Initial B-tree: ");
    btree_traverse(root);
    printf("\n");

    btree_delete_key(&root, 6);
    printf("After deleting 6: ");
    btree_traverse(root);
    printf("\n");

    btree_delete_key(&root, 13); 
    btree_delete_key(&root, 7);
    btree_delete_key(&root, 4); 
    btree_delete_key(&root, 17);
    btree_delete_key(&root, 10);

    printf("After more deletions: ");
    btree_traverse(root);
    printf("\n");

    btree_free(root);
    return 0;
}