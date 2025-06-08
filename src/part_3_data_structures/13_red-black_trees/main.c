#include "part_3_data_structures/13_red-black_trees/red-black_trees.h"

int main(void) {    
    RedBlackTree *tree = malloc(sizeof(RedBlackTree));
    tree->nil = malloc(sizeof(RedBlackNode));
    tree->nil->color = BLACK;
    tree->nil->left = tree->nil->right = tree->nil->parent = NULL;
    tree->nil->data = 0;  
    tree->root = tree->nil;

    printf("Inserting values: 10, 20, 30, 15, 25, 5, 35\n");
    rb_tree_insert(tree, 10);
    rb_tree_insert(tree, 20);
    rb_tree_insert(tree, 30);
    rb_tree_insert(tree, 15);
    rb_tree_insert(tree, 25);
    rb_tree_insert(tree, 5);
    rb_tree_insert(tree, 35);

    printf("Tree after insertions (inorder): ");
    rb_tree_inorder_traversal(tree, tree->root);
    printf("\n");

    printf("Nodes in range [10, 25]: ");
    rb_tree_enumerate(tree, tree->root, 10, 25);
    printf("\n");

    RedBlackNode *target = rb_tree_search(tree, 20);
    if (target && target != tree->nil) {
        printf("Deleting node with value 20\n");
        rb_tree_delete(tree, target);
        
        printf("Tree after deletion (inorder): ");
        rb_tree_inorder_traversal(tree, tree->root);
        printf("\n");
        
        printf("Nodes in range [10, 25] after deletion: ");
        rb_tree_enumerate(tree, tree->root, 10, 25);
        printf("\n");
    } else printf("Node with value 20 not found\n");

    free(tree->nil);
    free(tree);
    
    return 0;
}