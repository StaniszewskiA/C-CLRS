#include "part_3_data_structures/10_elementary_data_structures/elementary_data_structures.h"

#define TASK 1

int main(void) {
    switch (TASK) {
        case 1: {
            TreeNode* root = tree_node_create(1, NULL);
            root->left = tree_node_create(2, root);
            root->right = tree_node_create(3, root);
            root->left->left = tree_node_create(4, root->left);
            root->right->right = tree_node_create(5, root->right);

            printf("Tree (Pre-order): ");
            print_tree(root);
            printf("\n");

            tree_free(root);
            
            break;
        }   

        case 2: {
            TreeNode* root = tree_node_create(1, NULL);
            root->left = tree_node_create(2, root),
            root->right = tree_node_create(3, root),
            root->left->left = tree_node_create(4, root->left);
            root->right->right = tree_node_create(5, root->right);

            printf("Tree (pre-order, itrerative): ");
            print_tree_iterative(root);
            printf("\n");

            tree_free(root);
            break;
        }

        case 3: {
            TreeNode* root = tree_node_create(1, NULL);
            root->left = tree_node_create(2, NULL);  
            root->left->right = tree_node_create(3, NULL);  
            root->left->right->right = tree_node_create(4, NULL); 

            root->left->left = tree_node_create(5, NULL); 
            root->left->left->right = tree_node_create(6, NULL); 

            root->left->right->right->left = tree_node_create(7, NULL);  
            root->left->right->right->left->right = tree_node_create(8, NULL); 

            printf("Tree (SLBR, Iterative Without Stack): ");
            print_tree_recursive(root);
            printf("\n");

            tree_free(root);

            break;
        }

        case 4: {
            int maxDepth = 3;
            DepthTreeNode* root = create_depth_tree_node(1, 1);
            if (root == NULL) return EXIT_FAILURE;

            create_sample_depth_tree(root, 1, maxDepth);

            printf("Tree (Pre-order): ");
            print_depth_tree(root);
            printf("\n");

            printf("Tree Traversal:\n");
            depth_tree_traverse(root, root->b);
            break;
        }

        default:
            break;
    }
}