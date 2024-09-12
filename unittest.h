/*
    ~This is some unittest for the function we have implemented for BTL1
    ~Author: vuxnx
    
    ~I would be very grateful if you could find any bugs in my test.
     Additionally, I hope we can cooperate to make a much more qualified test. 

*/

/*
    ~To use this test, you have one folder which contains 4 files:
    + iList.h
    + XArrayList.h
    + Point.h
    + main.cpp
    Note: You have to put these files in same folder (No need to seperate to different folder)
         
*/

#ifndef UNITTEST_H
#define UNITTEST_H
#include <iostream>
#include <iomanip>
#include "XArrayList.h"
#include "Point.h"
#include <cassert>

using namespace std;

/*

        BELOW CLASS IS INHERITATE FORM XARRAYLIST

*/

template <class T>
class XArrayListTest : public XArrayList<T> {
public:
    XArrayListTest(
        void (*deleteUserData)(XArrayList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0,
        int capacity = 10)
        : XArrayList<T>(deleteUserData, itemEqual, capacity) {}

    void testCopyFrom(const XArrayListTest<T> &list) {
        this->copyFrom(list);
    }
    void testRemoveInternalData() {
        this->removeInternalData();
    }

    auto get_customDeleteFunction() {
        return this->deleteUserData;
    }

    auto get_customEqualFunction() {
        return this->itemEqual;
    }

    T* get_data() {
        return this->data;
    }
    int get_capacity(){
        return this->capacity;
    }
};

// Custom equal Func

bool customEqual(int& a, int& b) {
    // Custom comparison function
    return a == b;
}

// Custom delte Func. Actually, I'm not sure how this func behaves :)

void customDelete(XArrayList<int>* list) {
    // Custom delete function to clean up data (if needed)
    cout << "Custom delete function called.\n";
}


/*

        TEST ZONE

*/


void ConstructorTest1() {
    // Init default constructor
    XArrayList<int> iList;
    // Assert that the list is empty (count = 0)
    assert(iList.size() == 0);
    assert(iList.empty());
    cout << "PASS: ConstructorTest1" << endl;
}

void ConstructorTest2() {
    // Init constructor with capacity 5
    XArrayList<int> iList(0, 0, 5);

    // Add element to check if the capacity equal to 5
    for (int i = 0; i < 5; i++)
        iList.add(i, i * i);

    // Try to get element at index 5
    bool flag = 0;
    try {
        iList.get(5);
    } catch (std::out_of_range& e) {
        flag = 1;
    }
    assert(flag && "Index is out of range!");
    cout << "PASS: ConstructorTest2" << endl;
}

void ConstructorTest3() {
    // Init constructor with 2 pointer function
    XArrayList<Point*> list1(&XArrayList<Point*>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));
    list1.add(new Point(12.5f, 22.3f));

    for (XArrayList<Point*>::Iterator it = list1.begin(); it != list1.end(); it++)
        cout << **it << endl;

    Point* p1 = new Point(24.6f, 23.1f); // found in list
    Point* p2 = new Point(124.6f, 23.1f); // not found
    assert(list1.contains(p1) == 1);
    assert(list1.contains(p2) == 0);

    /// Different results if not pass &Point::equals
    cout << endl << endl;
    XArrayList<Point*> list2(&XArrayList<Point*>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));
    list2.add(new Point(12.5f, 22.3f));

    for (XArrayList<Point*>::Iterator it = list2.begin(); it != list2.end(); it++)
        cout << **it << endl;
    assert(list2.contains(p1) == 0);
    assert(list2.contains(p2) == 0);
    delete p1; delete p2;
    cout << "PASS: ConstructorTest3" << endl;
}

void test_removeInternalData_noCustomDelete() {
    XArrayListTest<int> list1;
    list1.add(1);
    list1.add(2);
    list1.add(3);
    assert(list1.size() == 3);
    list1.testRemoveInternalData();
    assert(list1.size() == 0);
    cout << "Test removeInternalData without custom delete PASSED!" << endl;
}

void test_removeInternalData_withCustomDelete() {
    XArrayListTest<int> list2(&customDelete);
    list2.add(1);
    list2.add(2);
    list2.add(3);
    assert(list2.size() == 3);
    list2.testRemoveInternalData();
    assert(list2.size() == 0);
    cout << "Test removeInternalData with custom delete PASSED!" << endl;
}

void test_CopyConstructor() {
    XArrayListTest<int> list1(&customDelete, &customEqual, 5);

    list1.add(1);
    list1.add(2);
    list1.add(3);

    XArrayListTest<int> list2(list1);

    assert(list2.size() == list1.size());
    for (int i = 0; i < list1.size(); i++) {
        assert(list2.get(i) == list1.get(i));
    }

    assert(list2.get_customDeleteFunction() != 0);
    assert(list2.get_customEqualFunction() != 0);

    cout << "PASS: Copy Constructor test" << endl;
}

void test_CopyAssignment() {
    XArrayListTest<int> list1(&customDelete, &customEqual, 5);

    list1.add(1);
    list1.add(2);
    list1.add(3);

    XArrayListTest<int> list2;
    list2 = list1;
    assert(list2.size() == list1.size());
    for (int i = 0; i < list1.size(); i++) {
        assert(list2.get(i) == list1.get(i));
    }

    assert(list2.get_customDeleteFunction() != 0);
    assert(list2.get_customEqualFunction() != 0);

    cout << "PASS: Copy Assignment test" << endl;
}

void test_add_one_arg(){
    XArrayListTest<int>fList;
    for(int i = 0; i < 10; i++)
        fList.add(i);
    fList.add(10);
    string seq_flist = fList.toString();
    string expect = "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]";
    assert(seq_flist == expect);
    cout << "PASS: add one arg"<<endl;
}

void test_add_two_arg(){
    XArrayListTest<int>fList;
    for(int i = 0; i < 10; i++)
        fList.add(i, i + 1);
    string seq_flist = fList.toString();
    string expect = "[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]";
    assert(seq_flist == expect);
    cout << "PASS: add two arg"<<endl;
}

void test_removeAt(){
    XArrayListTest<int>iList;
    // Add 10 elements
    for(int i = 0 ; i < 10; i++)
        iList.add(i, i);
    
    // This list is now: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    iList.removeAt(3);

    // After remove this, now it is: [0, 1, 2, 4, 5, 6, 7, 8, 9]

    string after_state = iList.toString();

    assert(after_state == "[0, 1, 2, 4, 5, 6, 7, 8, 9]");

    iList.removeAt(0);

    after_state = iList.toString();

    assert(after_state == "[1, 2, 4, 5, 6, 7, 8, 9]");

    cout << "PASS: test removeAt" << endl;    
}

void test_removeItem(){
    XArrayListTest<int>iList;
    // Add 10 elements
    for(int i = 0 ; i < 5; i++)
        iList.add(i, i);
    
    iList.add(2);

    bool flag1 = iList.removeItem(2);

    string after_state = iList.toString();

    assert(flag1 == true && after_state == "[0, 1, 3, 4, 2]");

    bool flag2 = iList.removeItem(5);

    after_state = iList.toString();

    assert(flag2 == false && after_state == "[0, 1, 3, 4, 2]");

    cout << "PASS: test remove Item" << endl;
}

void test_empty(){
    XArrayListTest<int>iList;
    for(int i = 0 ; i < 10; i++) iList.add(i);
    iList.clear();
    assert(iList.empty() == true);
    cout << "PASS: test empty" << endl;
}

void test_size(){
    XArrayListTest<int>iList;
    for(int i = 0; i < 5; i++) iList.add(i);
    assert(iList.size() == 5);
    iList.clear();
    assert(iList.size() == 0);
    cout << "PASS: test size" << endl;
}

void test_get(){
    XArrayListTest<int>iList;
    for(int i = 0; i < 5; i++) iList.add(i);
    int idx1 = iList.get(4);
    assert(idx1 == 4);
    try{
        idx1 = iList.get(7);
    }catch(...){
        cout << "PASS: test get" << endl;
    }
}

void test_indexOf(){
    XArrayList<int>iList;
    for(int i = 0 ; i < 10; i++) iList.add(i);
    assert(iList.indexOf(6) == 6);
    assert(iList.indexOf(20) == -1);
    cout << "PASS: test IndexOf" << endl;
}

void test_contains(){
    XArrayList<int>iList;
    for(int i = 0 ; i < 10; i++) iList.add(i);
    assert(iList.contains(6) == true);
    assert(iList.contains(20) == false);
    cout << "PASS: test contains" << endl;
}

void test_checkIndex(){
    XArrayListTest<int>iList;
    for(int i = 0; i < 5; i++) iList.add(i);
    int idx1;
    int idx2;
    try{
        idx1 = iList.get(7);
    }catch(...){
        cout << "PASS: test checkIndex" << endl;
    }

    try{
        idx2 = iList.get(-7);
    }catch(...){
        cout << "PASS: test checkIndex" << endl;
    }

}

void xlistDemo1(){
    XArrayList<int> iList;
    for(int i = 0; i< 10 ; i++)
        iList.add(i, i*i);
    string seq_iList = iList.toString();
    string expect = "[0, 1, 4, 9, 16, 25, 36, 49, 64, 81]";
    assert(seq_iList == expect);
    int item = 81;
    int foundIdx = iList.indexOf(item);
    assert(foundIdx == 9);
    cout << "PASS: xlistDemo1" << endl;
}

void xlistDemo2(){
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));  
    assert(alist.toString() == "[P( 23.20, 25.40,  0.00), P( 24.60, 23.10,  0.00)]");
    cout << "PASS: xlistDemo2" << endl;
}

void xlistDemo3(){
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));  
    
    int idx1 = alist.indexOf(Point(24.6f, 23.1f));
    int idx2 = alist.indexOf(Point(24.61f, 23.1f));
    
    assert(idx1 == 1);
    assert(idx2 == -1);
    cout << "PASS: xListDemo3" << endl;
}

void xlistDemo4(){
    XArrayList<Point*> list1(&XArrayList<Point*>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));  
    list1.add(new Point(12.5f, 22.3f)); 
    
    for(XArrayList<Point*>::Iterator it = list1.begin(); it != list1.end(); it++)
        cout << **it << endl;
    
    Point* p1 = new Point(24.6f, 23.1f); //found in list
    Point* p2 = new Point(124.6f, 23.1f); //not found
    assert(list1.contains(p1) == true);
    assert(list1.indexOf(p1) == 1);
    assert(list1.contains(p2) == false);
    
    ///Different results if not pass &Point::equals
    cout << endl << endl;
    XArrayList<Point*> list2(&XArrayList<Point*>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));  
    list2.add(new Point(12.5f, 22.3f)); 
    
    for(XArrayList<Point*>::Iterator it = list2.begin(); it != list2.end(); it++)
        cout << **it << endl;
    
    assert(list2.contains(p1) == false);
    assert(list2.contains(p2) == false);
    
    delete p1; delete p2;
    cout << "PASS: xListDemo4" << endl;
}

void TEST_RAW(){
    ConstructorTest1();
    ConstructorTest2();
    ConstructorTest3();
    test_removeInternalData_noCustomDelete();
//  test_removeInternalData_withCustomDelete();
    test_CopyConstructor();
    test_CopyAssignment();
    test_add_one_arg();
    test_add_two_arg();
    test_removeAt();
    test_removeItem();
    test_empty();
    test_size();
    test_get();
    test_indexOf();
    test_contains();
    test_checkIndex();
    xlistDemo1();
    xlistDemo2();
    xlistDemo3();
    xlistDemo4();
    cout << "ALL TESTS PASSED!" << endl;
}


#endif // UNITTEST_H
