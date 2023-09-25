
import unittest
from phase1 import SList2

class Test(unittest.TestCase):


   	#setUp is a method which is ran before a test method is executed. 
   	#This is useful if you need some data (for example) to be present before running a test.
    def setUp(self):
        self.list1 = SList2()
        for i in range(7):
            self.list1.addLast(i+1)

        self.emptylist = SList2()

        self.list2 = SList2()
        for i in [1,1,2,3,3,3,4,4,5]:        
            self.list2.addLast(i)

        self.list3 = SList2()
        for i in [1,1,1,2,3,4,4,5]:        
            self.list3.addLast(i)

        self.list4 = SList2()
        for i in [1,1,2,3,4,5,5,5,5]:        
            self.list4.addLast(i)

        self.list5 = SList2()
        for i in [1,1,1,1]:        
            self.list5.addLast(i)

        self.loop1 = SList2()
        for i in range(7):
            self.loop1.addLast(i+1)
        self.loop1.create_loop(3)

        self.loop2 = SList2()
        for i in [1,1,1,1]:        
            self.loop2.addLast(i)
        self.loop2.create_loop(2)

        self.loop3 = SList2()
        for i in range(100):
            self.loop3.addLast(i+1)
        self.loop3.create_loop(3)

        pass        
	
    def test1delLargestSeq(self):
        print('Case 1: empty list')
        actual_output = self.emptylist.delLargestSeq()
        expected = SList2()
        self.assertEqual(actual_output, None, "Fail: delLargestSeq function for an empty list")
        self.assertEqual(str(self.emptylist), str(expected), "Fail: delLargestSeq function for an empty list")

    def test2delLargestSeq(self):
        print('Case 2: list without repetitions')
        actual_output = self.list1.delLargestSeq()
        expected = SList2()
        for i in range(6):
            expected.addLast(i+1)

        self.assertEqual(actual_output, None, "Fail: delLargestSeq function for a list without repetitions")
        self.assertEqual(str(self.list1), str(expected), "Fail: delLargestSeq function for a list without repetitions")
    
    def test3delLargestSeq(self):
        print('Case 3: list with repetitions in the middle')
        actual_output = self.list2.delLargestSeq()
        expected = SList2()
        for i in [1,1,2,4,4,5]:        
            expected.addLast(i)

        self.assertEqual(actual_output, None, "Fail: delLargestSeq function for a list with repetitions in the middle")
        self.assertEqual(str(self.list2), str(expected), "Fail: delLargestSeq function for a list with repetitions in the middle")

    def test4delLargestSeq(self):
        print('Case 4: list with repetitions at the beginning')
        actual_output = self.list3.delLargestSeq()
        expected = SList2()
        for i in [2,3,4,4,5]:        
            expected.addLast(i)

        self.assertEqual(actual_output, None, "Fail: delLargestSeq function for a list with repetitions at the beginning")
        self.assertEqual(str(self.list3), str(expected), "Fail: delLargestSeq function for a list with repetitions at the beginning")


    def test5delLargestSeq(self):
        print('Case 5: list with repetitions at the end')
        actual_output = self.list4.delLargestSeq()
        expected = SList2()
        for i in [1,1,2,3,4]:        
            expected.addLast(i)

        self.assertEqual(actual_output, None, "Fail: delLargestSeq function for a list with repetitions at the end")
        self.assertEqual(str(self.list4), str(expected), "Fail: delLargestSeq function for a list with repetitions at the end")

    def test6delLargestSeq(self):
        print('Case 6: list with repetition of only one element')
        actual_output = self.list5.delLargestSeq()
        expected = SList2()

        self.assertEqual(actual_output, None, "Fail: delLargestSeq function for a list with repetition of only one element")
        self.assertEqual(str(self.list5), str(expected), "Fail: delLargestSeq function for a list with repetition of only one element")


    def test1fix_loop(self):
        print('Case 7: list without any loop')
        expected = self.list1
        actual_output = self.list1.fix_loop()
        self.assertEqual(actual_output, False, "Fail: fix_loop function for a list without any loop")
        self.assertEqual(str(self.list1), str(expected), "Fail: fix_loop function for a list without any loop")

    def test2fix_loop(self):
        print('Case 8: empty list')
        expected = SList2()
        actual_output = self.emptylist.fix_loop()
        
        self.assertEqual(actual_output, False, "Fail: fix_loop function for an empty list")
        self.assertEqual(str(self.emptylist), str(expected), "Fail: fix_loop function for an empty list")

    def test3fix_loop(self):
        print('Case 9: list with a loop')
        expected = SList2()
        for i in range(7):
            expected.addLast(i+1)

        actual_output = self.loop1.fix_loop()
        
        self.assertEqual(actual_output, True, "Fail: fix_loop function for a list with a loop")
        self.assertEqual(str(self.loop1), str(expected), "Fail: fix_loop function for a list with a loop")

    def test4fix_loop(self):
        print('Case 10: list with a loop with the same element')
        expected = SList2()
        for i in [1,1,1,1]:
            expected.addLast(i)

        actual_output = self.loop2.fix_loop()
        
        self.assertEqual(actual_output, True, "Fail: fix_loop function for a list with a loop")
        self.assertEqual(str(self.loop2), str(expected), "Fail: fix_loop function for a list with a loop")

    def test5fix_loop(self):
        print('Case 11: fix_loop function for a big list')
        actual_output = self.loop3.fix_loop()
        expected = SList2()
        for i in range(100):
            expected.addLast(i+1)
        self.assertEqual(actual_output, True, "Fail: fix_loop function for a big list")
        self.assertEqual(str(self.loop3), str(expected), "Fail: fix_loop function for a big list")


    def test1leftrightShift(self):
        print('Case 12: leftrightShift function for an empty list')
        actual_output = self.emptylist.leftrightShift(True, 0)
        expected = SList2()
        self.assertEqual(actual_output, None, "Fail: leftrightShift function for an empty list")
        self.assertEqual(str(self.emptylist), str(expected), "Fail: leftrightShift function for an empty list")
    

    def test2leftrightShift(self):
        print('Case 13:  list shifted to the right 2 positions')
        actual_output = self.list1.leftrightShift(False, 2)
        expected = SList2()
        for i in [6,7,1,2,3,4,5]:
            expected.addLast(i)

        self.assertEqual(actual_output, None, "Fail: list shifted to the right 2 positions")
        self.assertEqual(str(self.list1), str(expected), "Fail: list shifted to the right 2 positions")
    
    
    def test3leftrightShift(self):
        print('Case 14:  list shifted to the left 5 positions')
        actual_output = self.list2.leftrightShift(True, 5)
        expected = SList2()
        for i in [3,4,4,5,1,1,2,3,3]:        
            expected.addLast(i)

        self.assertEqual(actual_output, None, "Fail: list shifted to the left 5 positions")
        self.assertEqual(str(self.list2), str(expected), "Fail: list shifted to the left 5 positions")

    def test4leftrightShift(self):
        print('Case 15:  leftrightshift with an index higher than the list size')
        actual_output = self.list3.leftrightShift(True, 15)
        expected = self.list3

        self.assertEqual(actual_output, None, "Fail: leftrightshift with an index higher than the list size")
        self.assertEqual(str(self.list3), str(expected), "Fail: leftrightshift with an index higher than the list size")

    




if __name__ == '__main__':
    unittest.main()






