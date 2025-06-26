#include "part_3_data_structures/12_binary_search_trees/binary_search_trees.h"

#define TASK 3

int main(void) {
    BSTNodeWithParent* root = bts_with_node_parent_init(50);

    root = bts_with_node_parent_insert(root, 30);
    root = bts_with_node_parent_insert(root, 20);
    root = bts_with_node_parent_insert(root, 40);
    root = bts_with_node_parent_insert(root, 70);
    root = bts_with_node_parent_insert(root, 60);
    root = bts_with_node_parent_insert(root, 80);

    switch (TASK)
    {
    case 1: {        
        bts_with_node_parent_tree_print_min_max(root);

        BSTNodeWithParent* node = root->left; 
        BSTNodeWithParent* pred = bts_with_node_parent_tree_predecessor(node);
        if (pred != NULL)
            printf("Predecessor of %d is %d\n", node->key, pred->key);
        else
            printf("No predecessor for %d\n", node->key);

        break;
    }
    case 2: {
        const int searchKey = 40;
        BSTNodeWithParent* searchResult = bts_with_node_parent_tree_search(root, searchKey);
        if (searchResult != NULL)
            printf("Key %d found in the tree.\n", searchKey);
        else
            printf("Key %d not found in the tree.\n", searchKey);

        break;
    }
    case 3: {
        BSTNodeWithParent* node = root->left; 
        BSTNodeWithParent* succ = bts_with_node_parent_tree_successor(node);
        if (succ != NULL)
            printf("Successor of %d is %d\n", node->key, succ->key);
        else
            printf("No successor for %d\n", node->key);

        break;
    }
    default:
        break;
    }

    return 0;
}