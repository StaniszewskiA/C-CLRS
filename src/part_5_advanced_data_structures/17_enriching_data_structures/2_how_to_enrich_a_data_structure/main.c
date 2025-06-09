#include "part_5_advanced_data_structures/17_enriching_data_structures/enriching_data_structures.h"

#define TASK 2

int main(void) {
    RedBlackTree* T = rb_tree_create();

    rb_tree_insert(T, 20);
    rb_tree_insert(T, 15);
    rb_tree_insert(T, 25);
    rb_tree_insert(T, 10);
    rb_tree_insert(T, 5);
    rb_tree_insert(T, 1);
    rb_tree_insert(T, 30);

    printf("Inorder traversal with sizes:\n");
    rb_tree_inorder_traversal(T, T->root);

    switch (TASK) {
        case 1: {
            RedBlackNode* minNode = rb_tree_find_min(T);
            printf("Minimum key node: %d\n", minNode->key);

            RedBlackNode* maxNode = rb_tree_find_max(T);
            printf("Maximum key node: %d\n", maxNode->key);

            RedBlackNode* node = T->root->left->left;
            if (node != T->nil) {
                RedBlackNode* successor = rb_tree_find_successor(T, node);
                if (successor) {
                    printf("Successor of node with key %d is %d\n", node->key, successor->key);
                }
            }

            RedBlackNode* rootNode = T->root;
            RedBlackNode* predecessor = rb_tree_find_predecessor(T, rootNode);
            if (predecessor) {
                printf("Predecessor of node with key %d is %d\n", rootNode->key, predecessor->key);
            }
            break;
        }
        case 2: {
            RedBlackNode* maxNode = rb_tree_find_max(T);
            int blackHeight = calculate_black_height(T, maxNode);
            int depth = calculate_depth(T, maxNode);
            
            printf("Black height of the max node: %d\n", blackHeight);
            printf("Depth of the max node: %d\n", depth);
            break;
        }
        default:
            break;
    }

    return 0;
}
