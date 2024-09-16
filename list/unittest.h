

#ifndef UNITTEST_H
#define UNITTEST_H

/*
    Note: Dont create a method to call all test functions, it causes error
    and lead to unexpected result.
*/

#include <iostream>
#include <cassert>
#include <iomanip>
#include "DLinkedList.h"
using namespace std;

template    <typename T>
class DLinkedListTest: public DLinkedList<T>{
    public:
        int get_count(){return this->count;}
          
};

// Flag for specific purpose, SOME functions will change it data.
string  alert = "";

template    <typename T>
void customDelete(DLinkedList<T>* tmp){
    cout << "CustomDelete called" << endl;
    alert = "CustomDelete called";
}

////////////////////////////////////////////////////////////////
////                     TEST ZONE                           ///
////////////////////////////////////////////////////////////////


void ConstructoTest1(){
    // This is test for constructor without additional arguments
    DLinkedListTest<int> *dList = new DLinkedListTest<int>;
    assert(dList->get_count() == 0);
    delete dList;
    cout << "PASS: constructor test without args" << endl;
}

void ConstructorTest2(){
    DLinkedList<int*> list1(&customDelete);
    list1.clear();
    assert(alert == "CustomDelete called");
    cout << "PASS: constructor test with custom delete" << endl;    
}

void test_copyConstructor(){
    DLinkedList<int>dList1;
    for(int i = 0 ; i < 10; i++)
        dList1.add(i);
    string array_dList1 = dList1.toString();
    DLinkedList<int>dList2(dList1);
    string array_dlist2 = dList2.toString();
    assert(array_dList1 == array_dlist2);
    cout << "PASS: copy Constructor" <<endl;
}

void test_AssignmentOp(){
    DLinkedList<int>dList1;
    for(int i = 0 ; i < 10; i++)
        dList1.add(i);
    string array_dList1 = dList1.toString();
    DLinkedList<int>dList2;
    dList2 = dList1;
    string array_dlist2 = dList2.toString();
    assert(array_dList1 == array_dlist2);
    cout << "PASS: assignment operator" << endl;
}

void test_add(){
    DLinkedListTest<int>dList1;
    for(int i = 0 ; i < 10; i++)
        dList1.add(i);
    string array = "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]";
    assert(dList1.get_count() == 10);
    assert(dList1.toString() == array);
    cout << "PASS: add" << endl;
}

void test_add_index(){
    DLinkedListTest<int>dList1;
    for(int i = 0; i < 10; i++)
        dList1.add(i, i);
    dList1.add(10, 10);
    string array = "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]";
    assert(array == dList1.toString());
    string excp;
    try{
        dList1.add(15, 15);
    }
    catch(...){
        excp = "Flag is caught!";
        assert(excp == "Flag is caught!");
    }
    cout << "PASS: test add index" <<endl;
}

void test_get_prev_node(){
    DLinkedListTest<int>dList;
    for(int i = 0; i < 10; i++) dList.add(i);
    dList.removeAt(0);
    assert(dList.toString() == "[1, 2, 3, 4, 5, 6, 7, 8, 9]");
    assert(dList.get_count() == 9);
    dList.removeAt(8);
    assert(dList.toString() == "[1, 2, 3, 4, 5, 6, 7, 8]");
    dList.removeAt(4);
    dList.toString() == "[1, 2, 3, 4, 6, 7, 8, 9]";
    cout << "PASS: get prev node" << endl;
}

void test_removeAt(){
    DLinkedList<int>dList;
    for(int i = 0 ; i < 10; i++) dList.add(i);
    dList.removeAt(0);
    assert(dList.toString() == "[1, 2, 3, 4, 5, 6, 7, 8, 9]");
    dList.add(0,0);
    dList.removeAt(2);
    assert(dList.toString() == "[0, 1, 3, 4, 5, 6, 7, 8, 9]");
    dList.removeAt(5);
    assert(dList.toString() == "[0, 1, 3, 4, 5, 7, 8, 9]");
    dList.removeAt(7);
    assert(dList.toString() == "[0, 1, 3, 4, 5, 7, 8]");
    cout << "PASS: test removeAt" << endl;
}

void test_empty(){
    DLinkedList<int>dList;
    assert(dList.empty() == true);
    for(int i = 0; i < 20; i++) dList.add(i);
    for(int i = 0; i < 20; i++) dList.removeAt(19 - i);
    assert(dList.empty() == true);
    cout << "PASS: test empty" <<endl;
}

void test_size(){
    DLinkedList<int>dList;
    assert(dList.size() == 0);
    dList.add(1);
    dList.add(2);
    assert(dList.size() == 2);
    dList.removeItem(2);
    assert(dList.size() == 1);
    cout << "PASS: test size" << endl;
}

void test_clear(){
    DLinkedList<int>dList;
    for(int i = 0; i < 10; i++) dList.add(i);
    assert(dList.size() == 10);
    dList.clear();
    assert(dList.size() == 0);
    DLinkedList<int>dList1(&customDelete);
    for(int i = 0; i < 10; i++) dList1.add(i);
    dList1.clear();
    assert(alert == "CustomDelete called");
    cout << "PASS: test clear" << endl;
}

void test_get(){
    DLinkedList<int>dList;
    for(int i = 0; i < 10; i ++) dList.add(i, i*i);
    assert(dList.get(0) == 0);
    assert(dList.get(9) == 81);
    try{
        dList.get(20);
    }catch(...){
        assert(1 == 1); // Condition to confirm the exception is caught
    }
    cout << "PASS: test get" << endl;
}

void test_indexOf(){
    DLinkedList<int>dList;
    for(int i = 0; i < 10; i++) dList.add(i);
    assert(dList.indexOf(5) == 5);
    assert(dList.indexOf(0) == 0);
    assert(dList.indexOf(20) == -1);
    cout << "PASS: test indexOf" << endl;
}

void test_removeItem(){
    DLinkedList<int>dList;
    dList.add(1);
    dList.add(2);
    dList.add(1);
    dList.add(3);
    dList.add(3);
    dList.add(6);
    dList.add(7);
    dList.add(8);
    bool flag_1 = dList.removeItem(0);
    assert(flag_1 == false);
    bool flag_2 = dList.removeItem(3);
    assert(flag_2 == true && dList.toString() == "[1, 2, 1, 3, 6, 7, 8]");
    bool flag_3 = dList.removeItem(7);
    assert(flag_3 == true && dList.toString() == "[1, 2, 1, 3, 6, 8]");
    cout << "PASS: test removeItem" << endl;

}

void test_contains(){
    DLinkedList<int>dList;
    for(int i = 0; i < 10; i++) dList.add(i);
    assert(dList.contains(0) == true);
    dList.removeAt(0);
    assert(dList.contains(0) == false);
    dList.clear();
    assert(dList.contains(0) == false);
    cout << "PASS: test contains" << endl;
}

void test_toString(){
    DLinkedList<int>dList;
    assert(dList.toString() == "[]");
    cout << "PASS: test to String" << endl;
}

#endif
