#include "part_5_advanced_data_structures/18_b-trees/b-trees.h"

#pragma region Joining and splitting 2-3-4 trees

void btree_split_helper(BTreeNode* node, int key, BTreeNode** leftRef, BTreeNode** rightRef) {
    if (!node) return;
    int i;
    for (i = 0; i < node->numKeys; i++) {
        if (!node->isLeaf) btree_split_helper(node->children[i], key, leftRef, rightRef);
        if (node->keys[i] < key) btree_tree_insert(leftRef, node->keys[i]);
        else if (node->keys[i] > key) btree_tree_insert(rightRef, node->keys[i]);
    }
    if (!node->isLeaf) btree_split_helper(node->children[i], key, leftRef, rightRef);
}

void btree_split_tree(BTreeNode* root, int key, BTreeNode** leftRef, BTreeNode** rightRef) {
    *leftRef = btree_init();
    *rightRef = btree_init();
    btree_split_helper(root, key, leftRef, rightRef);
}

BTreeNode* btree_join_trees(BTreeNode* left, int midKey, BTreeNode* right) {
    BTreeNode* newRoot = btree_node_init(0);
    newRoot->keys[0] = midKey;
    newRoot->children[0] = left;
    newRoot->children[1] = right;
    newRoot->numKeys = 1;
    return newRoot;
}

#pragma endregion Joining and splitting 2-3-4 trees

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

    BTreeNode *left = NULL, *right = NULL;
    btree_split_tree(root, 15, &left, &right);

    printf("Left (keys < 15):\n");
    btree_traverse(left);
    printf("\n");

    printf("Right (keys > 15):\n");
    btree_traverse(right);
    printf("\n");

    BTreeNode* joined = btree_join_trees(left, 15, right);
    printf("Joined B-tree with 15 in the middle:\n");
    btree_traverse(joined);
    printf("\n");

    btree_free(joined);

    btree_free(root);
    return 0;
}