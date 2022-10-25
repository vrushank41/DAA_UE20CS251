// Name: Vrushank G
// SRN: PES1UG20CS516
#include "bst.h"
#include <stdlib.h>
#include<stdio.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

// Initializes the root of the bst
void init_bst(bst_t *bst)
{
    bst->root = NULL;
}


// Insert element into a tree
static node_t* insertelem(node_t *root, int key, int *count_ptr)
{
    if(root == NULL){
        node_t *temp = (node_t *)malloc(sizeof(node_t));
        temp->key = key;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    (*count_ptr)++;
    if (key < root->key) {
        root->left = insertelem(root->left, key, count_ptr);
    }
    else {
        root->right = insertelem(root->right, key, count_ptr);
    }
    return root;
}

// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr
void insert(bst_t *tree, int key, int *count_ptr)
{
    node_t *head = tree->root;
    tree->root = insertelem(head, key, count_ptr);
}

// delete the given element from the tree
static node_t* deleteelem(node_t *root, int key, int *count_ptr)
{
    node_t *temp;
    node_t *next;
    if (root == NULL)
        return root;
    else
    {
        (*count_ptr)++;
        if (key < root->key)
            root->left = deleteelem(root->left, key, count_ptr);
        else
        {
            (*count_ptr)++;
            if (key > root->key)
                root->right = deleteelem(root->right, key, count_ptr);
            {
                (*count_ptr)++;
                if (root->left == NULL)
                {
                    temp = root->right;
                    free(root);
                    return temp;
                }
                else
                {
                    (*count_ptr)++;
                    if (root->right == NULL)
                    {
                        temp = root->left;
                        free(root);
                        return temp;
                    }
                    else
                    {
                        // inorder succuessor
                        next = root->right;
                        while (next->left != NULL)
                        {
                            (*count_ptr)++;
                            next = next->left;
                        }
                        root->key = next->key;
                        root->right = deleteelem(root->right, next->key, count_ptr);
                    }
                }
            }
        }
    }
    return root;
}

// Delete key from the BST
// Replaces node with in-order successor
void delete_element(bst_t *tree, int key, int *count_ptr)
{
    tree->root = deleteelem(tree->root, key, count_ptr);
}

static int searchelem(node_t *root, int key, int *count_ptr)
{
    
    if (root == NULL)
    {
        return -1;
    }
    (*count_ptr)++;
    if (root->key == key)
    {
        return key;
    }
    else
    {
        (*count_ptr)++;
        if (key < root->key)
        {
            searchelem(root->left, key, count_ptr);
        }
        else
            searchelem(root->right, key, count_ptr);
    }
}

// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{
    return searchelem(tree->root, key, count_ptr);
}

// find the max element and return to the wrapper function
static int maxelem(node_t *root, int *count_ptr)
{
    (*count_ptr)++;
    if (root->right == NULL){
        return root->key;
    }
    else
        maxelem(root->right, count_ptr);
}

// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{
    if(tree->root != NULL)
        return maxelem(tree->root, count_ptr);
    else
        return -1;
}

// clears all elements one by one
static void clear_ele(node_t *root)
{
    if (root == NULL)
        return;
    clear_ele(root->left);
    clear_ele(root->right);
    free(root);
}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    clear_ele(bst->root);
    bst->root = NULL;
}

// Deletes all the elements of the bst
void free_bst(bst_t *bst)
{
    clear_ele(bst->root);
}