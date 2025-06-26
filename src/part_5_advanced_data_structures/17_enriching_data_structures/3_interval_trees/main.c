#include "part_5_advanced_data_structures/17_enriching_data_structures/enriching_data_structures.h"

#define TASK 6

int main(void) {
    IntervalRBTree* tree = interval_rb_tree_init();

    interval_rb_insert(tree, (Interval){15, 20});
    interval_rb_insert(tree, (Interval){10, 30});
    interval_rb_insert(tree, (Interval){17, 19});
    interval_rb_insert(tree, (Interval){5, 20});
    interval_rb_insert(tree, (Interval){12, 15});
    interval_rb_insert(tree, (Interval){30, 40});

    printf("Inorder traversal:\n");
    interval_rb_tree_inorder_traversal(tree->root, tree->nil);

    switch (TASK)
    {
        case 1: {
            Interval query1 = {14, 16};
            printf("\nChecking for overlap with [%d, %d]:\n", 
                query1.low, query1.high);
            
            IntervalRBNode* result1 = tree->root;

            while (result1 != tree->nil) {
                if (check_overlap(result1->interval, query1))
                    printf("Overlapping with [%d, %d]\n", 
                        result1->interval.low, result1->interval.high);
                if (result1->left != tree->nil && result1->left->max >= query1.low) 
                    result1 = result1->left; 
                else result1 = result1->right;
            }

            break;
        }

        case 2: {
            // 17.3-2
            Interval query2 = {16, 18};
            IntervalRBNode* result2 = find_overlap_with_smallest_low(tree, query2);

            if (result2 != tree->nil) printf(
                "Overlapping interval with the lowest low value: [%d, %d]",
                result2->interval.low, result2->interval.high);
            else printf("There's no valid interval");

            break;
        }

        case 3: {
            // 17.3-3
            Interval query3 = {10, 18};
            find_overlapping_intervals(tree, tree->root, query3);

            break;
        }

        case 4: {
            // 17.3-4
            Interval query4 = {10, 30};
            IntervalRBNode* result4 = interval_search_exactly(tree, query4);
            printf("Result node has max value of: %d\n", result4->max);

            break;
        }

        case 5: {
            // 17.3-5
            MinGapRBTree* tree = min_gap_rb_tree_init();

            min_gap_rb_tree_insert(tree, 20);
            min_gap_rb_tree_insert(tree, 13);
            min_gap_rb_tree_insert(tree, 15);
            min_gap_rb_tree_insert(tree, 25);
            min_gap_rb_tree_insert(tree, 30);

            MinGapRBNode* node = tree->root; 
            MinGapRBNode* successor = min_gap_rb_node_find_successor(node);
            printf("Successor of node with key %d is %d\n", 
                node->key, successor->key);

            MinGapRBNode* predecessor = min_gap_rb_node_find_predecessor(node);
            printf("Predecessor of node with key %d is %d\n",
                node->key, predecessor->key);

            int minGap = min_gap_rb_tree_get_min_gap(tree);
            printf("Minimum gap in the set represented by the MinGapRBTree: %d\n", 
                minGap);

            break;
        }

        case 6: {
            // 17.3-6
            Rect rects[] = {
                {1, 4, 1, 4},
                {2, 5, 2, 5},
                {6, 8, 6, 8},
                {7, 9, 7, 9}
            };

            int n = sizeof(rects) / sizeof(rects[0]);

            if (check_rect_overlap(rects, n)) 
                printf("Detected overlapping rectangles!");

            break;
        }
        
        default: {
            break;
        }
    }
    
    return 0;
}