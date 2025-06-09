#include "part_5_advanced_data_structures/17_enriching_data_structures/enriching_data_structures.h"

#define TASK 6

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
    rb_tree_inorder_traversal(T, T->nil);

    switch (TASK)
    {
        case 1: {
            // 17.1-1
            int target1 = 4; 
            RedBlackNode* result1 = os_select(T->root, target1, T->nil); 
            if (result1) printf("%d-th smallest element is: %d\n", 
                target1, result1->key);
            break;
        }

        case 2: {
            // 17.1-2
            int result2 = os_rank(T, T->root->right);  
            if (result2) printf("Rank of the target node: %d\n", result2);
            break;
        }

        case 3: {
            // 17.1-3
            int target3 = 4; 
            RedBlackNode* result3 = os_select_iterative(T->root, target3, T->nil); 
            if (result3) printf("%d-th smallest element is: %d\n", 
                target3, result3->key);
            break;
        }

        case 4: {
            // 17.1-4
            int target4 = 5; 
            int result4 = os_key_rank(T, T->root, target4);  
            printf("Rank of the node with key %d is: %d\n", target4, result4);
            break;
        }

        case 6: {
            // 17.1-8
            AngledPoint points[] = {
                {1.0, 2.0, 0.0},  
                {2.0, 3.0, 0.0}, 
                {3.0, 1.0, 0.0}, 
                {4.0, 2.0, 0.0}, 
            };

            int n8 = sizeof(points) / sizeof(points[0]); 
            printf("Total intersecting chords: %d\n", 
                count_intersections(points, n8));

            break;
        }
        
        default:
            break;
    }

    return 0;
}