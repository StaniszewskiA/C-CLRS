#include "part_3_data_structures/12_binary_search_trees/binary_search_trees.h"

int main(void) {
    BSTNode* root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = bst_insert(root, values[i]);

    printf("Inorder Traversal: ");
    bst_inorder_traversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    bst_preorder_traversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    bst_postorder_traversal(root);
    printf("\n");

    return 0;
}