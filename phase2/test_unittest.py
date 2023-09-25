# -*- coding: utf-8 -*-
"""
Test program comparing solutions with the builtin list-based one.

@author: EDA Team
"""

# Classes provided by EDA Team
from bst import BinarySearchTree
import unittest
from phase2 import BST2
from phase2 import create_tree

class Test(unittest.TestCase):
    def setUp(self):
        # INPUT TREES FOR THE TESTS OF FIND_DIST_K FUNCTION:

        self.emptytree = BST2()

        self.tree = BST2()
        input_list_01 = [5, 12, 2, 1, 0, 10, 25, 3, 9]
        for x in input_list_01:
            self.tree.insert(x)


        # INPUT TREES FOR THE TESTS OF CREATE_TREE FUNCTION:
        self.empty_tree1 = BinarySearchTree() # Empty tree
        self.empty_tree2 = BinarySearchTree()
        self.tree1 = BinarySearchTree()
        for x in [23, 56, 44, 82, 19, 7, 10]:
            self.tree1.insert(x) # self.tree1 is a BST2 with 7 nodes.
        
        self.tree2 = BinarySearchTree()
        for x in [40]: # Tree with just one node.
            self.tree2.insert(x)

        self.tree3 = BinarySearchTree()
        for x in [34, 67, 89, 12, 0, 6, 7]:
            self.tree3.insert(x)

        self.tree4 = BinarySearchTree()
        for x in [-5, 7, 9, 12, 40, 65]:
            self.tree4.insert(x)

        self.tree5 = BinarySearchTree()
        for x in [7, 45, 23, 65, 13, 90, 33]:
            self.tree5.insert(x)

        self.tree6 = BinarySearchTree()
        for x in [2, 5, 19, 25, 32, 47, 50,62]:
            self.tree6.insert(x)

# TESTS FIND_DIST_K:

    #Checks the base case
    def test_01_find_dist_k(self):
        print('Case 1 find_dist_k: base case')
        self.assertEqual(self.tree.find_dist_k(2, 2), [0, 12], 'Error: checking the base case')

    #Checks the case where the given node is the root
    def test_02_find_dist_k(self):
        print('Case 2 find_dist_k: root node')
        self.assertEqual(self.tree.find_dist_k(5, 2), [1, 3, 10, 25], 'Error: in case the given node is the root')

    #Checks the case that the given node is a leaf
    def test_03_find_dist_k(self):
        print('Case 3 find_dist_k: leaf node')
        self.assertEqual(self.tree.find_dist_k(0, 2), [2], 'Error: in case the given node is a leaf')

    #Checks the case where the given node does not exist
    def test_04_find_dist_k(self):
        print('Case 4 find_dist_k: not existing node')
        self.assertEqual(self.tree.find_dist_k(100, 2), [], 'Error: with a node that does not exist')

    #checks the function with an empty tree
    def test_05_find_dist_k(self):
        print('Case 5 find_dist_k: empty tree')
        self.assertEqual(self.emptytree.find_dist_k(5, 2), [], 'Error: empty tree')

    #Checks the case whre the function is guven an invalid k
    def test_06_find_dist_k(self):
        print('Case 6 find_dist_k: invalid k')
        self.assertEqual(self.tree.find_dist_k(5, -1), [], 'Error: invalid k')
        

# TESTS CREATE_TREE FUNCTION:

    def test1_create_tree(self):
        print('Case1 create_tree function: 2 non-empty binary search trees, opc = merge')
        actual_output = create_tree(self.tree1, self.tree2, 'merge')
        expected_output = BinarySearchTree()
        for x in [23, 56, 44, 82, 19, 7, 10, 40]:
            expected_output.insert(x)
        self.assertEqual(actual_output.level_order_list(), expected_output.level_order_list(), 'Fail: error when merging the trees')
    
    def test2_create_tree(self):
        print('Case2 create_tree function: 2 non-empty binary search trees, opc = intersection')
        actual_output = create_tree(self.tree3, self.tree4, 'intersection')
        expected_output = BinarySearchTree()
        for x in [12,7]:
            expected_output.insert(x)
        self.assertEqual(actual_output.level_order_list(), expected_output.level_order_list(), 'Fail: error when intersecting the trees')
    
    def test3_create_tree(self):
        print('Case3 create_tree function: 2 non-empty binary search trees, opc = difference')
        actual_output = create_tree(self.tree3, self.tree4, 'difference')
        expected_output = BinarySearchTree()
        for x in [34,67,89,0,6]:
            expected_output.insert(x) 
        self.assertEqual(actual_output.level_order_list(), expected_output.level_order_list(), 'Fail: error when differencing the trees')
   
    def test4_create_tree(self):
        print('Case4 create_tree function: 2 empty binary search trees, opc = merge')
        actual_output = create_tree(self.empty_tree1, self.empty_tree2, 'merge')
        expected_output = BinarySearchTree()
        self.assertEqual(actual_output.level_order_list(), expected_output.level_order_list(), 'Fail: error when merging the trees')
    
    def test5_create_tree(self):
        print('Case5 create_tree function: 2 non-empty binary search trees with no elements in common, opc = merge')
        actual_output = create_tree(self.tree5, self.tree6, 'intersection')
        expected_output = BinarySearchTree()
        self.assertEqual(actual_output.level_order_list(), expected_output.level_order_list(), 'Fail: error when intersecting the trees')
    
    def test6_create_tree(self):
        print('Case6 create_tree function: 2 non-empty binary search trees that are equal, opc = difference')
        actual_output = create_tree(self.tree5, self.tree5, 'difference')
        expected_output = BinarySearchTree()
        self.assertEqual(actual_output.level_order_list(), expected_output.level_order_list(), 'Fail: error when differencing the trees')    


# Some usage examples
if __name__ == '__main__':
    unittest.main()
