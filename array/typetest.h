/*
  This file is made by: ltnghia
  This test is for: user-defined type and use extra method to manipulate them.
*/

#ifndef XARRAYLIST_SOMECLASS_TEST_H
#define XARRAYLIST_SOMECLASS_TEST_H

#include <iostream>
#include <iomanip>
#include "XArrayList.h"
#include "Point.h"
#include "exception"
#include "cassert"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Student{
public:
    enum gender {M = 0, F = 1, UNKNOWN = 2} gd;
private:
    string name;
    int age;
    double GPA;
public:
    Student(string name = "", int age = 0, gender gd = UNKNOWN, double GPA = 0.0) :
        name(name), age(age), gd(gd), GPA(GPA) {}
    ~Student(){
        // cout << "Executing destructor for Student" << "\n";
    }
    string operator *(){
        return "Name: " + name + ", Age: " + to_string(age) + ", Gender: " + (gd == M? "Male" : (gd == F? "Female" : "Unknown"));
    }
    bool operator==(const Student& other) const{
        return name == other.name && age == other.age && gd == other.gd && GPA == other.GPA;
    }
    int getAge(){
        return age;
    }
    double getGPA(){
        return GPA;
    }
    string getName(){
        return name;
    }
};

void custom_deleteStudentInforPointer(XArrayList<Student*> *stu_list){
    int n = stu_list->size();
    for(int i = 0; i < n; i++){
        delete (stu_list -> get(i));
    }
    cout << "Executing custom deleteStudentInforPointer" << "\n"; 
}
void custom_deleteStudentInfor(XArrayList<Student> *stu_list){
    cout << "Executing custom deleteStudentInfor" << "\n";
}
bool isEqual(Student &lhs, Student &rhs){
    return lhs == rhs;
}
bool isEqual(Student* &lhs, Student* &rhs){
    return *lhs == *rhs;
}
string toString(Student &st){
    return "Name:" + st.getName() + "-Age:" + to_string(st.getAge()) + "-Gender:" + (st.gd == Student::M? "Male" : (st.gd == Student::F? "Female" : "Unknown")) + "-GPA:" + to_string(st.getGPA());
}
string toString(Student* &st){
    return toString(*st);
}
string toString(Student &&st){
    Student temp(st);
    return toString(temp);
}
ostream &operator<<(ostream &os, Student &other){
    os << "[" << toString(other) << "]";
    return os;
}

void test1(){
    XArrayList<Student> *stu_list = new XArrayList<Student>(&custom_deleteStudentInfor, &isEqual);
    Student s1("Jinx", 20, Student::M, 3.8);
    Student s2("Azir", 21, Student::F, 3.7);
    Student s3("Smother", 22, Student::UNKNOWN, 3.9);
    stu_list -> add(s1);
    stu_list -> add(s2);
    stu_list -> add(s3);
    Student stTemp("Teemo", 18, Student::UNKNOWN, 0.0);
    Student stTemp2("Azir", 21, Student::F, 3.7);
    cout << "stu_list -> contains(stTemp): " << boolalpha << stu_list -> contains(stTemp) <<"\n";
    cout << "stu_list -> contains(stTemp2): " << boolalpha << stu_list -> contains(stTemp2) << "\n";
    cout << stu_list -> toString(&toString) << "\n";
    delete stu_list;
    cout << "Test 1 finished" << "\n";
}
void test2(){
    XArrayList<Student> stu_list_nonpointer(&custom_deleteStudentInfor, &isEqual, 7);
    stu_list_nonpointer.add(Student("Jinx", 20, Student::M, 3.8));
    stu_list_nonpointer.add(Student("Azir", 21, Student::F, 3.7));
    stu_list_nonpointer.add(Student("Smother", 22, Student::UNKNOWN, 3.9));
    stu_list_nonpointer.add(Student("Teemo", 18, Student::UNKNOWN, 0.0));
    stu_list_nonpointer.add(Student("Azir", 21, Student::F, 3.7));
    cout << "stu_list_nonpointer.get(0):" << stu_list_nonpointer.get(0) << "\n";
    XArrayList<Student> anotherList = stu_list_nonpointer;
    assert(anotherList.toString(&toString) == stu_list_nonpointer.toString(&toString));
    assert(isEqual(anotherList.get(0), stu_list_nonpointer.get(0)));
    assert(anotherList.size() == 5);
    assert(toString(anotherList.removeAt(0)) == "Name:Jinx-Age:20-Gender:Male-GPA:3.800000");
    assert(anotherList.size() == 4);
    cout << "Test 2 finished" << "\n";
}
void test3(){
    XArrayList<Student*> *stu_list_pointer = new XArrayList<Student*>(//&XArrayList<Student*>::free, 
        &custom_deleteStudentInforPointer, &isEqual);
    Student* s1 = new Student("A", 10, Student::F, 10.0);
    Student* s2 = new Student("B", 9, Student::M, 9.9);
    Student* s3 = new Student("C", 7, Student::UNKNOWN, 8.0);
    Student* s4 = new Student("D", 8, Student::M, 9.6);
    stu_list_pointer -> add(s1);
    stu_list_pointer -> add(s2);
    stu_list_pointer -> add(s3);
    stu_list_pointer -> add(1, s4);
    for(int i = 0; i < stu_list_pointer -> size(); i++)
        cout << *stu_list_pointer -> get(i) << "\n";  
    cout << "Index of Student C is: " << stu_list_pointer -> indexOf(s3) << "\n";  
    cout << stu_list_pointer -> toString(&toString) << "\n";
    cout << boolalpha << stu_list_pointer -> empty() << "\n";
    delete stu_list_pointer;
    cout << "Test 3 finished" << "\n";
}
void test4(){
    XArrayList<Student*> *stu_list_pointer = new XArrayList<Student*>(//&XArrayList<Student*>::free, 
        &XArrayList<Student*>::free, &isEqual);
    Student* s1 = new Student("A", 10, Student::F, 10.0);
    Student* s2 = new Student("B", 9, Student::M, 9.9);
    Student* s3 = new Student("C", 7, Student::UNKNOWN, 8.0);
    Student* s4 = new Student("D", 8, Student::M, 9.6);
    stu_list_pointer -> add(s1);
    stu_list_pointer -> add(s2);
    stu_list_pointer -> add(s3);
    stu_list_pointer -> add(1, s4);
    // for(int i = 0; i < stu_list_pointer -> size(); i++)
    //     cout << *stu_list_pointer -> get(i) << "\n";  
    // cout << "Index of Student C is: " << stu_list_pointer -> indexOf(s3) << "\n";  
    // cout << stu_list_pointer -> toString(&toString) << "\n";
    // cout << boolalpha << stu_list_pointer -> empty() << "\n";
    delete stu_list_pointer;
    cout << "Test 4 finished" << "\n";
}
//----------------------------------------------------------------
string toString_strElement(string &str){
    return (str + " ");
}
bool isEqual(string &str1, string &str2){
    return  str1 == str2;
}
void test5(){
    XArrayList<string> str_list_nopointer(0, &isEqual, 10);
    str_list_nopointer.add("Hello");
    str_list_nopointer.add("World");
    str_list_nopointer.add("!");
    str_list_nopointer.add("I am");
    str_list_nopointer.add("Binomial distribution");    
    cout << str_list_nopointer.toString(&toString_strElement) << "\n";
    cout << str_list_nopointer.indexOf("Hello") << "\n";
    XArrayList<string> *list  = new XArrayList<string>(0, &isEqual, 20);
    list -> add("Bonjour!");
    list -> add("Je");
    list -> add("m'appelle Nghia");
    XArrayList<string> newList = *list;
    cout << newList.toString(&toString_strElement) << "\n";
    delete list;
}
#endif
