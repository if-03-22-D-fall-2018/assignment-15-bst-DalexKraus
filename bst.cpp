/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include "bst.h"
#include "general.h"
#include <stdlib.h>
#include <stdio.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))

struct Node {
    int value;
    Node* left_node;
    Node* right_node;
};

/**
*** Initializes the binary search tree. Deletes all existing nodes in the tree
*** @return The number of deleted nodes
*/
Bst new_bst()
{
    return 0;
}

void delete_bst(Bst bst)
{
    if (bst == 0)
        return;

    delete_bst(bst->left_node);
    delete_bst(bst->right_node);

    sfree(bst);
}

/**
*** @return The depth of the BST
*/
int get_depth(Bst bst)
{
    if (bst == 0)
        return 0;

    int leftDepth = get_depth(bst->left_node);
    int rightDepth = get_depth(bst->right_node);

    return 1 + max(leftDepth, rightDepth);
}

/**
 *  Creates a new node
 * @param value The value of the node
 * @return Created Node
 */
Node* createNode(int value) {

    Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->right_node = 0;
    node->left_node = 0;

    return node;
}

/**
*** Adds a value to the BST
*/
void add(Bst* bst, int value)
{
    if (*bst == 0)
    {
        (*bst) = createNode(value);
        return;
    }
    if (value <= (*bst)->value)
    {
        if ((*bst)->left_node == 0)
        {
            (*bst)->left_node = createNode(value);
            return;
        }
        add(&(*bst)->left_node, value);
    }
    else if (value > (*bst)->value)
    {
        if ((*bst)->right_node == 0)
        {
            (*bst)->right_node = createNode(value);
            return;
        }
        add(&(*bst)->right_node, value);
    }
}

/**
*** @return The value of the root element of the BST
*/
int root_value(Bst bst)
{
    return bst == 0 ? 0 : bst->value;
}

/**
*** @return The left subtree of the BST
*/
Bst left_subtree(Bst root)
{
    return root->left_node;
}

/**
*** @return The right subtree of the BST
*/
Bst right_subtree(Bst root)
{
    return root->right_node;
}

/**
*** Traverses the BST depth first by first returning the root, then traversing the left
*** subtree, then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_pre_order(Bst bst, int *elements, int start)
{
    if (bst != 0)
    {
        elements[start] = bst->value;
        start++;
        start = traverse_pre_order(bst->left_node, elements, start);
        start = traverse_pre_order(bst->right_node, elements, start);
    }
    return start;
}

/**
*** Traverses the BST depth first by first traversing the left subtree, then adding the root,
*** then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_in_order(Bst bst, int *elements, int start)
{
    if (bst != 0)
    {
        start = traverse_in_order(bst->left_node, elements, start);
        elements[start] = bst->value;
        start++;
        start = traverse_in_order(bst->right_node, elements, start);
    }
    return start;
}

/**
*** Traverses the BST depth first by first traversing the left subtree, then traversing the right
*** subtree and finally adding the root.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_post_order(Bst bst, int *elements, int start)
{
    if (bst != 0)
    {
        start = traverse_post_order(bst->left_node, elements, start);
        start = traverse_post_order(bst->right_node, elements, start);
        elements[start] = bst->value;
        start++;
    }
    return start;
}

/**
*** Checks whether two trees are equal
*** @param bst1 First bst
*** @param bst2 Second bst
*** @return true if bst1 and bst2 are equal, false otherwise
*/
bool are_equal(Bst bst1, Bst bst2)
{
    if (bst1 == 0)
        return bst2 == 0;

    if (get_depth(bst1) == get_depth(bst2))
    {
        if (bst1->value == bst2->value)
        {
            return are_equal(bst1->left_node, bst2->left_node) && are_equal(bst1->right_node, bst2->right_node);
        }
    }

    return 0;
}

/**
*** Calculates the longest branch in the tree. If two branches are equally long
*** the left branch is taken.
*** @param bst Bst which longest branch should be found
*** @return A tree where each node has only one child equal to the longest
*** branch of bst
*/
void most_left_longest_branch(Bst bst, Bst* branch)
{
    if (bst != 0)
    {
        if (get_depth(bst->left_node) < get_depth(bst->right_node))
        {
            add(branch, bst->value);
            most_left_longest_branch(&(*bst->right_node), branch);
        }
        else if (get_depth(bst->left_node) >= get_depth(bst->right_node))
        {
            add(branch, bst->value);
            most_left_longest_branch(&(*bst->left_node), branch);
        }
    }
}

/**
*** Gets the number of non-empty subtrees of a tree
*** @param bst The tree which number of subtrees to get
*** @return The number of non-empty subtrees
*/
int get_number_of_subtrees(Bst bst)
{
    if (bst != 0)
    {
        int *elements = new int[get_depth(bst)];
        return traverse_pre_order(bst, elements, 0) - 1;
    }

    return -1;
}
