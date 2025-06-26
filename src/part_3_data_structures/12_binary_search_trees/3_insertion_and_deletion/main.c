#include "part_3_data_structures/12_binary_search_trees/binary_search_trees.h"

#define TASK 1

int main(void) {
    switch (TASK)
    {
    case 1: {        
        BSTNodeWithParent* root = bts_with_node_parent_init(50); 
        BSTNodeWithParent* newNode = bts_with_node_parent_init(40); 

        bts_with_node_parent_insert_node(root, newNode); 

        break;
    }
    case 2: {
        BST* tree = (BST*)malloc(sizeof(BST)); 
        tree->root = NULL; 

        BSTNodeWithParent* newNode = bts_with_node_parent_init(40); 

        bst_recursive_tree_insert(tree, newNode);

        BSTNodeWithParent* u = bts_with_node_parent_tree_search(tree->root, 40);  
        BSTNodeWithParent* v = bts_with_node_parent_tree_search(tree->root, 20);  

        bst_tree_transplant(tree, u, v); 

        BSTNodeWithParent* nodeToDelete = bts_with_node_parent_tree_search(tree->root, 40);  
        if (nodeToDelete != NULL) {
            bst_tree_delete(tree, nodeToDelete); 
        }
    }
    default:
        break;
    }

    return 0;
}