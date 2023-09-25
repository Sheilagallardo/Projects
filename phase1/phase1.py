from slistH import SList
from slistH import SNode

import sys



class SList2(SList):

# This function deletes all the elements of the largest sequence of equal numbers from the calling list.
    def delLargestSeq(self) -> None: 

        c = 0       # counter; counts the number of times an specific number appears in the list.
        max = 0     # maximum frequency of one of the numbers in the list.
        e = None    # stores the number that has the highest frequency.
        node = self._head

        if self.isEmpty():
            return
        
        while node.next:
            if node.next.elem == node.elem:
                c = c+1    # if the next element from the list is equal to the current element, we add one to the counter.
                if c>=max:
                    max = c   # if the counter is greater than the maximum frequency (max), then, we reassign the max with the value of the counter.
                    e = node.elem   # store the number which is being repeated with higher frequency.
            else:
                if c>=max:  # if next element != current element, we still check if the counter´s value is greater than the maximum frequency (max).
                    max = c # if so, reassign the max with the value of the counter.
                    e = node.elem
                c=0   # restore the counter to start counting another number´s frequency.
            node0 = node
            node = node.next

        # node = last node of the list; node0 = penultimate node of the list.

        if max == 0:  # if there´s no sequence (no repetition of numbers), we delete the last node.
            node0.next = None
        else:
            if self.index(e) == 0:  # if the first node with element e is the first one
                index = 0
                nodenext = self._head
                i=0
        # While to get the node which is just after the last node of the largest sequence.
                while nodenext and i<=(max):    
                    nodenext=nodenext.next
                    i+=1
                self._head = nodenext   # remove the largest sequence.
            
            else:
                index = self.index(e)-1
                nodeprev=self._head
                i=0
        # While to get the node which is just before the first node of the largest sequence.
                while nodeprev and i<index:
                    nodeprev=nodeprev.next
                    i+=1
        # While to get the node which is just after the last node of the largest sequence.
                nodenext = nodeprev
                while nodenext and i<(index+max+2):
                    nodenext=nodenext.next
                    i+=1

                nodeprev.next = nodenext  # we erase the nodes of the largest sequence.

        self._size += -max-1  # update size of the list once we have deleted the largest sequence of repeated numbers.

        pass


    # This function detects if the calling list contains a loop and, if so, breaks it.
    def fix_loop(self) -> bool:
        node = self._head
        c = 0  # counter.
        while node:
            node2 = self._head
            i = 0
            c += 1
            while i<c:
                if node.next == node2:  # if the the next node points to the current node, we have a loop.
                    node.next = None    # we erase the loop.
                    return True
                i += 1
                node2 = node2.next
            node = node.next

        return False
		
		
    def create_loop(self, position):
        # this method is used to force a loop in a singly linked list
        if position < 0 or position > len(self) - 1:
            raise ValueError(f"Position out of range [{0} - {len(self) - 1}]")

        current = self._head
        i = 0

        # We reach position to save the reference
        while current and i < position:
            current = current.next
            i += 1

        # We reach to tail node and set the loop
        start_node = current
        print(f"Creating a loop starting from {start_node.elem}")
        while current.next:
            current = current.next        
        current.next = start_node
		
		
	# This function left shifts (left =True) or right shifts (left =False) the list by n nodes.
    def leftrightShift(self,left,n) -> None:
        if n>self._size:
            print('Error: n is bigger than the list size.\n')
        elif self._size == 0:
            print('Error: empty list')
        else:
            i = 0
            node=self._head
            while node.next:
                node=node.next
            node.next = self._head  #we arrive to the end node and conect it to the head of the list to make a loop

            #now we cut the loop where the new list should start (moving all elements we are asked to move at once, instead of moving them one by one)
            if left:
                while i <n:
                    node = node.next
                    i = i+1
            else:
                while i <(self._size-n):
                    node = node.next
                    i = i+1
            next = node.next
            node.next = None
            self._head = next 
            
        pass



if __name__=='__main__':

    l=SList2()
    print("list:",str(l))
    print("len:",len(l))

    for i in range(7):
        l.addLast(i+1)

    print(l)
    print()

    l=SList2()
    print("list:",str(l))
    print("len:",len(l))

    for i in range(7):
        l.addLast(i+1)

    print(l)
    print()

    # No loop yet, no changes applied
    l.fix_loop()
    print("No loop yet, no changes applied")
    print(l)
    print()

    # We force a loop
    l.create_loop(position=6)
    l.fix_loop()
    print("Loop fixed, changes applied")
    print(l)
    print()
    print()

    
    l = SList2()
    for i in []:        
        l.addLast(i)
    print(l)
    print(l._size)
    print(l.delLargestSeq())
    print(l)
    print(l._size)
    print()
    print([])

    l=SList2()
    for i in range(7):
         l.addLast(i+1)

    print(l)
    l.leftrightShift(False, 2)
    print(l)





