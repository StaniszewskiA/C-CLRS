#include "part_3_data_structures/10_elementary_data_structures/elementary_data_structures.h"

#define TASK 1

int main(void) {
    switch (TASK) {
        case 1: {
            DoublyNode* head = NULL;

            doubly_list_insert_at_front(&head, 10);
            doubly_list_insert_at_front(&head, 20);
            doubly_list_insert_at_front(&head, 30);
            
            printf("List after insertions: ");
            print_doubly_list(head);  
            
            doubly_list_insert_at_idx(&head, 1, 25);
            printf("List after inserting 25 at index 1: ");
            print_doubly_list(head); 
            
            doubly_list_insert_at_idx(&head, 4, 5);
            printf("List after inserting 5 at index 4: ");
            print_doubly_list(head); 
        
        
            doubly_list_insert_at_idx(&head, 10, 100);  
        
            return 0;

            break; 
        }
        case 2: {
            break;
        }
        case 3: {
            DoublyNode* sentinel = doubly_list_create_sentinel();

            sentinel_doubly_list_insert_at_front(sentinel, 10);
            sentinel_doubly_list_insert_at_front(sentinel, 20);
            sentinel_doubly_list_insert_at_front(sentinel, 30);

            printf("List after insertions: ");
            sentinel_print_doubly_list(sentinel);  
            
            sentinel_doubly_list_insert_at_idx(sentinel, 1, 25);
            printf("List after inserting 25 at index 1: ");
            sentinel_print_doubly_list(sentinel); 
            
            sentinel_doubly_list_insert_at_idx(sentinel, 4, 5);
            printf("List after inserting 5 at index 4: ");
            sentinel_print_doubly_list(sentinel); 

            sentinel_doubly_list_insert_at_idx(sentinel, 10, 100);  

            sentinel_doubly_list_delete_head(sentinel);
            printf("List after deleting head: ");
            sentinel_print_doubly_list(sentinel);

            sentinel_doubly_list_delete_val(sentinel, 25);
            printf("List after deleting 25 by value: ");
            sentinel_print_doubly_list(sentinel);

            sentinel_doubly_list_delete_at_idx(sentinel, 1);
            printf("List after deleting node at index 1: ");
            sentinel_print_doubly_list(sentinel);

            sentinel_doubly_list_delete(sentinel);
            printf("List after deleting all nodes: ");
            sentinel_print_doubly_list(sentinel);

            break; 
        }
        case 4: {
            DoublyNode* L1 = doubly_list_create_sentinel();
            DoublyNode* L2 = doubly_list_create_sentinel();

            sentinel_doubly_list_insert_at_front(L1, 30);
            sentinel_doubly_list_insert_at_front(L1, 20);
            sentinel_doubly_list_insert_at_front(L1, 10);

            sentinel_doubly_list_insert_at_front(L2, 60);
            sentinel_doubly_list_insert_at_front(L2, 50);
            sentinel_doubly_list_insert_at_front(L2, 40);

            printf("L1 before union: ");
            sentinel_print_doubly_list(L1);
            
            printf("L2 before union: ");
            sentinel_print_doubly_list(L2);

            doubly_lists_union(L1, L2);

            printf("L1 after union: ");
            sentinel_print_doubly_list(L1);

            break;
        }
        case 5: {
            SinglyNode* head = NULL;

            singly_list_insert_at_front(&head, 10);
            singly_list_insert_at_front(&head, 20);
            singly_list_insert_at_front(&head, 30);
            print_singly_list(head);

            singly_list_delete_head(&head);
            print_singly_list(head);

            singly_list_delete_val(&head, 20);
            print_singly_list(head);
            
            singly_list_delete(&head);
            print_singly_list(head);

            break; 
        }
        case 6: {
            Stack stack;
            stack_init(&stack);

            stack_push(&stack, 100);
            stack_push(&stack, 200);
            stack_push(&stack, 300);

            print_stack(&stack); 

            printf("Popped: %d\n", stack_pop(&stack)); 
            printf("Top element: %d\n", stack_peek(&stack)); 

            print_stack(&stack);
            printf("Stack size: %d\n", stack_get_size(&stack)); 

            break;
        }
        case 7: {
            Deque dq;
            deque_init(&dq);

            enqueue_front(&dq, 10);
            enqueue_front(&dq, 20);
            enqueue_front(&dq, 30);

            print_deque(&dq);
            printf("Front: %d, Rear: %d\n", deque_peek_front(&dq), deque_peek_rear(&dq));

            printf("Dequeued: %d\n", dequeue_front(&dq));

            deque_delete(&dq);
            print_deque(&dq);

            break;
        }
        case 8: {
            SinglyNode* head = NULL;

            singly_list_insert_at_front(&head, 10);
            singly_list_insert_at_front(&head, 20);
            singly_list_insert_at_front(&head, 30);
            print_singly_list(head);

            singly_list_reverse(&head);
            print_singly_list(head);

            break;
        }
        case 9: {
            XorList L;
            xor_list_init(&L);

            xor_list_insert(&L, 10);
            xor_list_insert(&L, 20);
            xor_list_insert(&L, 30);

            print_xor_list(&L);

            XorNode* result = xor_list_search(&L, 20);
            if (result != NULL) {
                printf("Found node with key %d\n", result->key);
            }

            xor_list_delete(&L, 20);
            print_xor_list(&L);
            break;
        }
        default:
            break;
    }

    return 0;
}