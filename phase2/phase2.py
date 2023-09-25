"""
@author: EDA Team
"""

# Classes provided by EDA Team
from bintree import BinaryNode
from bst import BinarySearchTree


# Exercise #1
class BST2(BinarySearchTree):

    # This function receives two parameters n and k which are positive integers and will 
    # return a Python list containing all nodes that are at a distance k 
    # from the node whose element is n.

    def find_dist_k(self, n, k) -> list:
        lista = [] #create the list were we are going to store the nodes we want (it does not have to be returned since it is an input object that we modify)
        self._find_dist_k(self.root, n, k, lista) #call the recursive function with more parameters to solve the problem
        return lista

    def _find_dist_k(self, node: BinaryNode, n: int, k: int, lista: list)-> int: #main recursive function to compleate the task. It returns the distance.
        if node == None: #at first check if the tree is empty, later to take as the end of the recursive function
            return
        elif node.elem == n: #we have found the input node then we find its childs at distance k
            self._find_child_k(node, k, lista) #recursive function that help us to find the childs
            dist = 0 #since we are at the given node its actual distance is 0
            return dist #returns the distance to keep track of it
        else:
            distl = self._find_dist_k(node.left, n, k, lista) #recursive method to obtain the distance of the left nodes from our input node
            if distl != None: #if there is no node the path ends without finding a node of distance k then we can start checking the right nodes
                if distl + 1 == k: # if we are at distance k this is ano of the nodes we want to save
                    lista.append(node.elem)
                else: # if the distance is not k we can find the child nodes of our node of the remaining distance (k-1 and dist+1 because it is a further node)
                    self._find_child_k(node.right, (k-1)-(distl+1), lista)
                return distl + 1 
            distr = self._find_dist_k(node.right, n, k, lista) #do the same recursive method with the right nodes
            if distr != None:
                if distr + 1 == k:
                    lista.append(node.elem)
                else:
                    self._find_child_k(node.left, (k-1)-(distl+1), lista)
                return distr + 1
            return #when the recursion function ends we dont need to return anything

    def _find_child_k(self, node: BinaryNode, k: int, lista: list):
        if node is not None:
            if k==0: # if k (distance from node) is zero, then, we add to the python list the node.
                lista.append(node.elem)
            if node.left: # if left child, we call the function again, substracting one to the k, so that when it reaches zero, the node is added to the lista. 
                self._find_child_k(node.left, k-1, lista)
            if node.right: # if right child, we call the function again, substracting one to the k, so that when it reaches zero, the node is added to the lista.
                self._find_child_k(node.right, k-1, lista)
            return
    
    

# Exercise #2

# This function receives as parameters two binary search trees, tree1 and tree2, of integers.
# It also receives a third parameter, opc, whose values can be 'merge', intersection', or 'difference'.

def create_tree(input_tree1: BinarySearchTree, input_tree2: BinarySearchTree, opc: str) -> BinarySearchTree:
    tree = BinarySearchTree() # BST which will be caused by merge, intersection or difference.

    if opc == 'merge':
    # The function creates a new binary search tree ('tree') containing the elements of both tree1 and tree2.
         # we create an auxiliary function 'merge' which inserts nodes from tree1 and tree2 (which are not repeated).
        merge(input_tree1._root, tree) 
        merge(input_tree2._root, tree) 
        return tree
    
    elif opc == 'intersection':
    # The function creates a new binary search tree ('tree') containing only the elements that the trees, tree1 and tree2, have in common.
       # we create an auxiliary function 'intersection' which inserts nodes which tree1 and tree2 have in common.
        intersect(input_tree1._root, tree, input_tree1, input_tree2) 
        intersect(input_tree2._root, tree, input_tree1, input_tree2)
        return tree
    
    elif opc == 'difference':
    # The function creates a new binary search tree ('tree') containing the elements of tree1 that are not in tree2.
        # we create an auxiliary function 'difference' which inserts nodes from tree1 that are not in tree2.
        difference(input_tree1._root, tree, input_tree2)
        return tree
    else: # none of the commands above.
        print('invalid command')
        return
    
def merge(node: BinaryNode, tree: BinarySearchTree): # Auxiliar function to add the nodes of both input trees into the new 'merged' tree recursively.
    if node is not None:
        if tree.search(node.elem) == None: # checks if the node already exists in our new tree.
            tree.insert(node.elem)
        if node.left: # repeat the process for the left nodes.
            merge(node.left, tree)
        if node.right: # repeat the process for the right nodes.
            merge(node.right, tree)
    else:
        return

def intersect(node: BinaryNode, tree: BinarySearchTree, tree1: BinarySearchTree, tree2: BinarySearchTree): # Auxiliar function to add the nodes that both input trees (tree1 and tree2) have in common into the new 'intersection' tree recursively.
    if node is not None:
        if (tree.search(node.elem) == None) & (tree1.search(node.elem) != None) & (tree2.search(node.elem) != None): 
        # checks if the node already exists in our new tree and if the element is in both trees.
            tree.insert(node.elem)
        if node.left: # repeat the process for the left nodes.
            intersect(node.left, tree, tree1, tree2)
        if node.right: # repeat the process for the right nodes.
            intersect(node.right, tree, tree1, tree2)
    else:
        return

def difference(node: BinaryNode, tree: BinarySearchTree, tree2: BinarySearchTree): # Auxiliar function to add the elements from tree1 that are not in tree2 into the new 'difference' tree recursively.
    if node is not None:
        if (tree.search(node.elem) == None) & (tree2.search(node.elem) == None): 
        # checks if the node already exists in our new tree and if the element from tree1 is not in tree2.
            tree.insert(node.elem)
        if node.left: # repeat the process for the left nodes.
            difference(node.left, tree, tree2)
        if node.right: # repeat the process for the right nodes.
            difference(node.right, tree, tree2)
    else:
        return

    

# Some usage examples
if __name__ == '__main__':
    # input_list_01 = [5, 1, 7, 9, 23]
    # input_list_02 = [1, 9, 11]
    input_list_01 = [5, 12, 2, 1, 3, 9, 10, 11, 20, 4, 6]
    input_list_02 = [9, 3, 21]
    # Build and draw first tree
    tree1 = BST2()
    for x in input_list_01:
        tree1.insert(x)
    tree1.draw()

    print(tree1.find_dist_k(0, 2))
    # Build and draw second tree
    tree2 = BinarySearchTree()
    for x in input_list_02:
        tree2.insert(x)
    tree2.draw()

    function_names = ["merge", "intersection", "difference"]

    for op_name in function_names:
        res = create_tree(tree1, tree2, op_name)
        print(f"-- Result for {op_name} method. #{res.size()} nodes")
        res.draw()
