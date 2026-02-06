
#include <iostream>

/* ************************************************************************** */

// #include "..."
#include "../container/container.hpp"
#include "../container/traversable.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../set/set.hpp"
#include "../set/vec/setvec.hpp"
#include "../set/lst/setlst.hpp"

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"


using namespace std;

/* ************************************************************************** */

void myTestVectorInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended Vector<int> Test:" << endl;
    try {
        lasd::SortableVector<int> emptyVec;
        Empty(loctestnum, loctesterr, emptyVec, true);
        Size(loctestnum, loctesterr, emptyVec, true, 0);

        loctestnum++; 
        try {
            emptyVec[0]; 
            cerr << "Error: emptyVec[0] on empty vector did not throw exception." << endl;
            loctesterr++;
        } catch (const std::out_of_range & exc) {
            cout << "Passed: emptyVec[0] on empty vector correctly threw out_of_range." << endl;
        } catch (const std::length_error & exc) {
            cout << "Passed: emptyVec[0] on empty vector correctly threw length_error." << endl;
        } catch (...) {
            cerr << "Error: emptyVec[0] on empty vector threw wrong exception type." << endl;
            loctesterr++;
        }

        lasd::SortableVector<int> singleElemVec(1);
        singleElemVec[0] = 42;
        Size(loctestnum, loctesterr, singleElemVec, true, 1);
        loctestnum++;
        if (singleElemVec[0] == 42) {
            std::cout << "Test " << loctestnum << " passed (singleElemVec[0] == 42). Expected and actual: 42" << std::endl;
        } else {
            loctesterr++;
            std::cout << "Test " << loctestnum << " FAILED (singleElemVec[0] == 42). Expected: 42, Actual: " << singleElemVec[0] << std::endl;
        }
        Exists(loctestnum, loctesterr, singleElemVec, true, 42);
        Exists(loctestnum, loctesterr, singleElemVec, false, 0);

        lasd::SortableVector<int> originalVec(5);
        for (uint i = 0; i < 5; ++i) originalVec[i] = i * 10;
        lasd::SortableVector<int> copiedVec(originalVec); 
        EqualVector(loctestnum, loctesterr, originalVec, copiedVec, true);
        originalVec[0] = 99; 
        NonEqualVector(loctestnum, loctesterr, originalVec, copiedVec, true); 
        lasd::SortableVector<int> assignTarget(2);
        assignTarget[0] = 100; assignTarget[1] = 200;
        assignTarget = copiedVec; 
        EqualVector(loctestnum, loctesterr, copiedVec, assignTarget, true);
        assignTarget = assignTarget; 
        EqualVector(loctestnum, loctesterr, copiedVec, assignTarget, true); 

        lasd::SortableVector<int> movedVec(std::move(copiedVec)); 
        Size(loctestnum, loctesterr, movedVec, true, 5); 
        Empty(loctestnum, loctesterr, copiedVec, true); 
        Size(loctestnum, loctesterr, copiedVec, true, 0); 

        lasd::SortableVector<int> moveAssignTarget(1);
        moveAssignTarget[0] = 555;
        moveAssignTarget = std::move(movedVec); 
        Size(loctestnum, loctesterr, moveAssignTarget, true, 5);
        Empty(loctestnum, loctesterr, movedVec, false); 
        Size(loctestnum, loctesterr, movedVec, false, 0);

        lasd::SortableVector<int> clearVec(3);
        clearVec[0] = 1; clearVec[1] = 2; clearVec[2] = 3;
        clearVec.Clear();
        Empty(loctestnum, loctesterr, clearVec, true);
        Size(loctestnum, loctesterr, clearVec, true, 0);
        clearVec.Clear(); 
        Empty(loctestnum, loctesterr, clearVec, true);

        lasd::SortableVector<int> testBoundsVec(3);
        testBoundsVec[0] = 10;
        testBoundsVec[1] = 20;
        testBoundsVec[2] = 30;

        loctestnum++;
        try {
            testBoundsVec[3]; 
            cerr << "Error: testBoundsVec[3] did not throw out_of_range." << endl;
            loctesterr++;
        } catch (const std::out_of_range &exc) {
            cout << "Passed: testBoundsVec[3] correctly threw out_of_range." << endl;
        } catch (...) {
            cerr << "Error: testBoundsVec[3] threw wrong exception type." << endl;
            loctesterr++;
        }

        loctestnum++;
        try {
            testBoundsVec[3] = 40; 
            cerr << "Error: testBoundsVec[3] = 40 did not throw out_of_range." << endl;
            loctesterr++;
        } catch (const std::out_of_range &exc) {
            cout << "Passed: testBoundsVec[3] = 40 correctly threw out_of_range." << endl;
        } catch (...) {
            cerr << "Error: testBoundsVec[3] = 40 threw wrong exception type." << endl;
            loctesterr++;
        }


    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended Vector<int> Test! " << endl;
    }
    cout << "End of Extended Vector<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestVectorDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended Vector<double> Test:" << endl;
    try {
        lasd::SortableVector<double> originalVec(3);
        originalVec[0] = 1.1; originalVec[1] = 2.2; originalVec[2] = 3.3;
        cout << "Original vector (double): ";
        TraversePreOrder(loctestnum, loctesterr, originalVec, true, &TraversePrint<double>); cout << endl;

        lasd::SortableVector<double> copiedVec(originalVec);
        cout << "Copied vector (double): ";
        TraversePreOrder(loctestnum, loctesterr, copiedVec, true, &TraversePrint<double>); cout << endl;
        EqualVector(loctestnum, loctesterr, originalVec, copiedVec, true);

        originalVec[0] = 99.9; 
        NonEqualVector(loctestnum, loctesterr, originalVec, copiedVec, true);

        lasd::SortableVector<double> assignTarget(1);
        assignTarget[0] = 0.0;
        assignTarget = copiedVec;
        cout << "Assign target (double, after assignment): ";
        TraversePreOrder(loctestnum, loctesterr, assignTarget, true, &TraversePrint<double>); cout << endl;
        EqualVector(loctestnum, loctesterr, copiedVec, assignTarget, true);

        lasd::SortableVector<double> movedVec(std::move(copiedVec));
        cout << "Moved vector (double): ";
        TraversePreOrder(loctestnum, loctesterr, movedVec, true, &TraversePrint<double>); cout << endl;
        Empty(loctestnum, loctesterr, copiedVec, true);
        Size(loctestnum, loctesterr, copiedVec, true, 0);

        lasd::SortableVector<double> moveAssignTarget(0);
        moveAssignTarget = std::move(movedVec);
        cout << "Move assign target (double): ";
        TraversePreOrder(loctestnum, loctesterr, moveAssignTarget, true, &TraversePrint<double>); cout << endl;
        Empty(loctestnum, loctesterr, movedVec, true);
        Size(loctestnum, loctesterr, movedVec, true, 0);

        lasd::SortableVector<double> clearVec(2);
        clearVec[0] = 10.5; clearVec[1] = 20.5;
        clearVec.Clear();
        Empty(loctestnum, loctesterr, clearVec, true);
        Size(loctestnum, loctesterr, clearVec, true, 0);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended Vector<double> Test! " << endl;
    }
    cout << "End of Extended Vector<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestVectorString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended Vector<string> Test:" << endl;
    try {
        lasd::SortableVector<string> originalVec(2);
        originalVec[0] = "Hello"; originalVec[1] = "World";
        cout << "Original vector (string): ";
        TraversePreOrder(loctestnum, loctesterr, originalVec, true, &TraversePrint<string>); cout << endl;

        lasd::SortableVector<string> copiedVec(originalVec);
        cout << "Copied vector (string): ";
        TraversePreOrder(loctestnum, loctesterr, copiedVec, true, &TraversePrint<string>); cout << endl;
        EqualVector(loctestnum, loctesterr, originalVec, copiedVec, true);

        originalVec[0] = "Goodbye"; 
        NonEqualVector(loctestnum, loctesterr, originalVec, copiedVec, true);

        lasd::SortableVector<string> assignTarget(1);
        assignTarget[0] = "Old";
        assignTarget = copiedVec;
        cout << "Assign target (string, after assignment): ";
        TraversePreOrder(loctestnum, loctesterr, assignTarget, true, &TraversePrint<string>); cout << endl;
        EqualVector(loctestnum, loctesterr, copiedVec, assignTarget, true);

        lasd::SortableVector<string> movedVec(std::move(copiedVec));
        cout << "Moved vector (string): ";
        TraversePreOrder(loctestnum, loctesterr, movedVec, true, &TraversePrint<string>); cout << endl;
        Empty(loctestnum, loctesterr, copiedVec, true);
        Size(loctestnum, loctesterr, copiedVec, true, 0);

        lasd::SortableVector<string> moveAssignTarget(0);
        moveAssignTarget = std::move(movedVec);
        cout << "Move assign target (string): ";
        TraversePreOrder(loctestnum, loctesterr, moveAssignTarget, true, &TraversePrint<string>); cout << endl;
        Empty(loctestnum, loctesterr, movedVec, true);
        Size(loctestnum, loctesterr, movedVec, true, 0);

        lasd::SortableVector<string> clearVec(2);
        clearVec[0] = "A"; clearVec[1] = "B";
        clearVec.Clear();
        Empty(loctestnum, loctesterr, clearVec, true);
        Size(loctestnum, loctesterr, clearVec, true, 0);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended Vector<string> Test! " << endl;
    }
    cout << "End of Extended Vector<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void myTestListInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended List<int> Test:" << endl;
    try {
        lasd::List<int> emptyList;
        Empty(loctestnum, loctesterr, emptyList, true);
        Size(loctestnum, loctesterr, emptyList, true, 0);

        loctestnum++;
        try {
            emptyList.Front();
            cerr << "Error: emptyList.Front() on empty list did not throw exception." << endl;
            loctesterr++;
        } catch (const std::length_error & exc) {
            cout << "Passed: emptyList.Front() on empty list correctly threw length_error." << endl;
        } catch (const std::out_of_range & exc) { 
            cout << "Passed: emptyList.Front() on empty list correctly threw out_of_range." << endl;
        } catch (...) {
            cerr << "Error: emptyList.Front() on empty list threw wrong exception type." << endl;
            loctesterr++;
        }
        
        loctestnum++;
        try {
            emptyList.Back();
            cerr << "Error: emptyList.Back() on empty list did not throw exception." << endl;
            loctesterr++;
        } catch (const std::length_error & exc) {
            cout << "Passed: emptyList.Back() on empty list correctly threw length_error." << endl;
        } catch (const std::out_of_range & exc) {
            cout << "Passed: emptyList.Back() on empty list correctly threw out_of_range." << endl;
        } catch (...) {
            cerr << "Error: emptyList.Back() on empty list threw wrong exception type." << endl;
            loctesterr++;
        }

        lasd::List<int> singleElemList;
        InsertAtFront(loctestnum, loctesterr, singleElemList, true, 100);
        Size(loctestnum, loctesterr, singleElemList, true, 1);
        GetFront(loctestnum, loctesterr, singleElemList, true, 100);
        GetBack(loctestnum, loctesterr, singleElemList, true, 100);
        Exists(loctestnum, loctesterr, singleElemList, true, 100);
        Exists(loctestnum, loctesterr, singleElemList, false, 0);

        FrontNRemove(loctestnum, loctesterr, singleElemList, true, 100);
        Empty(loctestnum, loctesterr, singleElemList, true);
        Size(loctestnum, loctesterr, singleElemList, true, 0);

        lasd::List<int> originalList;
        InsertAtBack(loctestnum, loctesterr, originalList, true, 1);
        InsertAtBack(loctestnum, loctesterr, originalList, true, 2);
        InsertAtBack(loctestnum, loctesterr, originalList, true, 3);
        lasd::List<int> copiedList(originalList);
        EqualList(loctestnum, loctesterr, originalList, copiedList, true);
        RemoveFromFront(loctestnum, loctesterr, originalList, true); 
        NonEqualList(loctestnum, loctesterr, originalList, copiedList, true); 

        lasd::List<int> assignTargetList;
        InsertAtBack(loctestnum, loctesterr, assignTargetList, true, 10);
        assignTargetList = copiedList;
        EqualList(loctestnum, loctesterr, copiedList, assignTargetList, true);
        assignTargetList = assignTargetList; 
        EqualList(loctestnum, loctesterr, copiedList, assignTargetList, true);

        lasd::List<int> movedList(std::move(copiedList));
        Size(loctestnum, loctesterr, movedList, true, 3);
        Empty(loctestnum, loctesterr, copiedList, true);
        Size(loctestnum, loctesterr, copiedList, true, 0);

        lasd::List<int> moveAssignTargetList;
        InsertAtBack(loctestnum, loctesterr, moveAssignTargetList, true, 555);
        moveAssignTargetList = std::move(movedList);
        Size(loctestnum, loctesterr, moveAssignTargetList, true, 3);
        Empty(loctestnum, loctesterr, movedList, false);
        Size(loctestnum, loctesterr, movedList, false, 0);

        lasd::List<int> clearList;
        InsertAtBack(loctestnum, loctesterr, clearList, true, 1);
        InsertAtBack(loctestnum, loctesterr, clearList, true, 2);
        clearList.Clear();
        Empty(loctestnum, loctesterr, clearList, true);
        Size(loctestnum, loctesterr, clearList, true, 0);
        clearList.Clear(); 
        Empty(loctestnum, loctesterr, clearList, true);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended List<int> Test! " << endl;
    }
    cout << "End of Extended List<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestListDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended List<double> Test:" << endl;
    try {
        lasd::List<double> lst1;
        InsertAtBack(loctestnum, loctesterr, lst1, true, 1.1);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 2.2);
        InsertAtBack(loctestnum, loctesterr, lst1, true, 3.3);
        TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<double>); cout << endl; // 1.1 2.2 3.3

        RemoveFromFront(loctestnum, loctesterr, lst1, true); 
        GetFront(loctestnum, loctesterr, lst1, true, 2.2);

        RemoveFromBack(loctestnum, loctesterr, lst1, true); 
        GetFront(loctestnum, loctesterr, lst1, true, 2.2);
        Size(loctestnum, loctesterr, lst1, true, 1);

        FrontNRemove(loctestnum, loctesterr, lst1, true, 2.2); 
        Empty(loctestnum, loctesterr, lst1, true);
        Size(loctestnum, loctesterr, lst1, true, 0);

        lasd::List<double> selfAssignList;
        InsertAtBack(loctestnum, loctesterr, selfAssignList, true, 10.0);
        InsertAtBack(loctestnum, loctesterr, selfAssignList, true, 20.0);
        selfAssignList = selfAssignList;
        Size(loctestnum, loctesterr, selfAssignList, true, 2);
        GetFront(loctestnum, loctesterr, selfAssignList, true, 10.0);

        lasd::List<double> emptyList;
        selfAssignList = emptyList;
        Empty(loctestnum, loctesterr, selfAssignList, true);

        lasd::List<double> anotherEmptyList;
        anotherEmptyList.Clear();
        Empty(loctestnum, loctesterr, anotherEmptyList, true);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended List<double> Test! " << endl;
    }
    cout << "End of Extended List<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestListString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended List<string> Test:" << endl;
    try {
        lasd::List<string> lst1;
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("First"));
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Second"));
        InsertAtBack(loctestnum, loctesterr, lst1, true, string("Third"));
        TraversePreOrder(loctestnum, loctesterr, lst1, true, &TraversePrint<string>); cout << endl;

        RemoveFromFront(loctestnum, loctesterr, lst1, true); 
        GetFront(loctestnum, loctesterr, lst1, true, string("Second"));

        RemoveFromBack(loctestnum, loctesterr, lst1, true); 
        GetFront(loctestnum, loctesterr, lst1, true, string("Second"));
        Size(loctestnum, loctesterr, lst1, true, 1);

        FrontNRemove(loctestnum, loctesterr, lst1, true, string("Second")); 
        Empty(loctestnum, loctesterr, lst1, true);
        Size(loctestnum, loctesterr, lst1, true, 0);

        lasd::List<string> selfAssignList;
        InsertAtBack(loctestnum, loctesterr, selfAssignList, true, string("A"));
        InsertAtBack(loctestnum, loctesterr, selfAssignList, true, string("B"));
        selfAssignList = selfAssignList;
        Size(loctestnum, loctesterr, selfAssignList, true, 2);
        GetFront(loctestnum, loctesterr, selfAssignList, true, string("A"));

        lasd::List<string> emptyList;
        selfAssignList = emptyList;
        Empty(loctestnum, loctesterr, selfAssignList, true);

        lasd::List<string> anotherEmptyList;
        anotherEmptyList.Clear();
        Empty(loctestnum, loctesterr, anotherEmptyList, true);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended List<string> Test! " << endl;
    }
    cout << "End of Extended List<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestListCopyAssignmentLeak(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of List<int> Copy Assignment Leak Test:" << endl;
    try {
        // Lista di destinazione più lunga di quella sorgente
        lasd::List<int> longList;
        for (int i = 0; i < 10; ++i) longList.InsertAtBack(i);

        lasd::List<int> shortList;
        for (int i = 0; i < 3; ++i) shortList.InsertAtBack(100 + i);

        // Copy assignment: la lista lunga diventa uguale a quella corta
        longList = shortList;

        // Controllo dimensione e valori
        Size(loctestnum, loctesterr, longList, true, 3);
        for (int i = 0; i < 3; ++i) {
            int val = longList.FrontNRemove();
            if (val != 100 + i) {
                loctesterr++;
                cout << "Error: Value mismatch after copy assignment. Expected " << (100 + i) << ", got " << val << endl;
            }
            loctestnum++;
        }
        Empty(loctestnum, loctesterr, longList, true);

        // Se usi Valgrind o AddressSanitizer, qui non devono risultare memory leak!
        cout << "If you run this test with Valgrind or ASan, there should be NO memory leaks!" << endl;

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in List<int> Copy Assignment Leak Test!" << endl;
    }
    cout << "End of List<int> Copy Assignment Leak Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void myTestVectorListInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended VectorList<int> Test:" << endl;
    try {
        lasd::Vector<int> vec1(3);
        vec1[0] = 10; vec1[1] = 20; vec1[2] = 30;
        lasd::List<int> list1(vec1); 
        cout << "List constructed from Vector: ";
        TraversePreOrder(loctestnum, loctesterr, list1, true, &TraversePrint<int>); cout << endl;
        Size(loctestnum, loctesterr, list1, true, 3);
        
        lasd::Vector<int> vec2(list1); 
        cout << "Vector constructed from List: ";
        TraversePreOrder(loctestnum, loctesterr, vec2, true, &TraversePrint<int>); cout << endl;
        Size(loctestnum, loctesterr, vec2, true, 3);

        lasd::Vector<int> vecAssign;
        vecAssign = list1; 
        cout << "Vector after assignment from List: ";
        TraversePreOrder(loctestnum, loctesterr, vecAssign, true, &TraversePrint<int>); cout << endl;
        EqualVector(loctestnum, loctesterr, vecAssign, vec2, true);

        lasd::List<int> listAssign;
        listAssign = vec1; 
        cout << "List after assignment from Vector: ";
        TraversePreOrder(loctestnum, loctesterr, listAssign, true, &TraversePrint<int>); cout << endl;
        EqualList(loctestnum, loctesterr, listAssign, list1, true);

        vec1.Clear();
        Empty(loctestnum, loctesterr, vec1, true);
        list1.Clear();
        Empty(loctestnum, loctesterr, list1, true);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended VectorList<int> Test! " << endl;
    }
    cout << "End of Extended VectorList<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestVectorListDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended VectorList<double> Test:" << endl;
    try {
        lasd::Vector<double> vec1(2);
        vec1[0] = 1.1; vec1[1] = 2.2;
        lasd::List<double> list1(vec1);
        cout << "List constructed from Vector (double): ";
        TraversePreOrder(loctestnum, loctesterr, list1, true, &TraversePrint<double>); cout << endl;
        Size(loctestnum, loctesterr, list1, true, 2);
        
        lasd::Vector<double> vec2(list1);
        cout << "Vector constructed from List (double): ";
        TraversePreOrder(loctestnum, loctesterr, vec2, true, &TraversePrint<double>); cout << endl;
        Size(loctestnum, loctesterr, vec2, true, 2);

        lasd::Vector<double> vecAssign;
        vecAssign = list1;
        EqualVector(loctestnum, loctesterr, vecAssign, vec2, true);

        lasd::List<double> listAssign;
        listAssign = vec1;
        EqualList(loctestnum, loctesterr, listAssign, list1, true);

        vec1.Clear();
        Empty(loctestnum, loctesterr, vec1, true);
        list1.Clear();
        Empty(loctestnum, loctesterr, list1, true);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended VectorList<double> Test! " << endl;
    }
    cout << "End of Extended VectorList<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestVectorListString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended VectorList<string> Test:" << endl;
    try {
        lasd::Vector<string> vec1(2);
        vec1[0] = "Hello"; vec1[1] = "World";
        lasd::List<string> list1(vec1);
        cout << "List constructed from Vector (string): ";
        TraversePreOrder(loctestnum, loctesterr, list1, true, &TraversePrint<string>); cout << endl;
        Size(loctestnum, loctesterr, list1, true, 2);
        
        lasd::Vector<string> vec2(list1);
        cout << "Vector constructed from List (string): ";
        TraversePreOrder(loctestnum, loctesterr, vec2, true, &TraversePrint<string>); cout << endl;
        Size(loctestnum, loctesterr, vec2, true, 2);

        lasd::Vector<string> vecAssign;
        vecAssign = list1;
        EqualVector(loctestnum, loctesterr, vecAssign, vec2, true);

        lasd::List<string> listAssign;
        listAssign = vec1;
        EqualList(loctestnum, loctesterr, listAssign, list1, true);

        vec1.Clear();
        Empty(loctestnum, loctesterr, vec1, true);
        list1.Clear();
        Empty(loctestnum, loctesterr, list1, true);

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error in Extended VectorList<string> Test! " << endl;
    }
    cout << "End of Extended VectorList<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* *********************************************************************************** */

void myTestSetInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended Set<int> Test:" << endl;

    lasd::Vector<int> initialVec(5);
    initialVec[0] = 50; initialVec[1] = 20; initialVec[2] = 80; initialVec[3] = 10; initialVec[4] = 20;
    
    lasd::List<int> initialList;
    initialList.InsertAtBack(30);
    initialList.InsertAtBack(10);
    initialList.InsertAtBack(70);
    initialList.InsertAtBack(30);


    lasd::Set<int>* setsToTest[] = {new lasd::SetVec<int>(), new lasd::SetLst<int>()};
    string setNames[] = {"SetVec<int>", "SetLst<int>"};

    for (int i = 0; i < 2; ++i) {
        lasd::Set<int> &set = *setsToTest[i];
        string name = setNames[i];
        cout << "\n--- Testing " << name << " ---" << endl;

        try {
            set.Clear();
            Empty(loctestnum, loctesterr, set, true);
            Size(loctestnum, loctesterr, set, true, 0);

            loctestnum++;
            try {
                set.Min();
                cerr << "Error: " << name << ".Min() on empty set did not throw." << endl;
                loctesterr++;
            } catch (const std::length_error &exc) {
                cout << "Passed: " << name << ".Min() on empty set correctly threw length_error." << endl;
            } catch (...) {
                cerr << "Error: " << name << ".Min() on empty set threw wrong exception type." << endl;
                loctesterr++;
            }

            loctestnum++;
            try {
                set.RemoveMin();
                cerr << "Error: " << name << ".RemoveMin() on empty set did not throw." << endl;
                loctesterr++;
            } catch (const std::length_error &exc) {
                cout << "Passed: " << name << ".RemoveMin() on empty set correctly threw length_error." << endl;
            } catch (...) {
                cerr << "Error: " << name << ".RemoveMin() on empty set threw wrong exception type." << endl;
                loctesterr++;
            }


            InsertC(loctestnum, loctesterr, set, true, 10);
            InsertC(loctestnum, loctesterr, set, true, 5);
            InsertC(loctestnum, loctesterr, set, true, 15);
            InsertC(loctestnum, loctesterr, set, false, 10); 
            Size(loctestnum, loctesterr, set, true, 3); 

            Exists(loctestnum, loctesterr, set, true, 5);
            Exists(loctestnum, loctesterr, set, true, 10);
            Exists(loctestnum, loctesterr, set, true, 15);
            Exists(loctestnum, loctesterr, set, false, 0);
            Exists(loctestnum, loctesterr, set, false, 20);

            Remove(loctestnum, loctesterr, set, true, 5);
            Size(loctestnum, loctesterr, set, true, 2);
            Exists(loctestnum, loctesterr, set, false, 5);
            Remove(loctestnum, loctesterr, set, false, 5); 

            Min(loctestnum, loctesterr, set, true, 10);
            Max(loctestnum, loctesterr, set, true, 15);

            RemoveMin(loctestnum, loctesterr, set, true);
            Size(loctestnum, loctesterr, set, true, 1);
            Min(loctestnum, loctesterr, set, true, 15);
            Max(loctestnum, loctesterr, set, true, 15);
            
            RemoveMax(loctestnum, loctesterr, set, true); 
            Empty(loctestnum, loctesterr, set, true);
            Size(loctestnum, loctesterr, set, true, 0);

            InsertC(loctestnum, loctesterr, set, true, 10);
            InsertC(loctestnum, loctesterr, set, true, 20);
            InsertC(loctestnum, loctesterr, set, true, 30);
            InsertC(loctestnum, loctesterr, set, true, 40);
            Size(loctestnum, loctesterr, set, true, 4); 

            Predecessor(loctestnum, loctesterr, set, true, 25, 20);
            Predecessor(loctestnum, loctesterr, set, false, 10, 10);
            Predecessor(loctestnum, loctesterr, set, false, 5, 5); 

            Successor(loctestnum, loctesterr, set, true, 25, 30);
            Successor(loctestnum, loctesterr, set, false, 40, 40);
            Successor(loctestnum, loctesterr, set, false, 45, 45);

            PredecessorNRemove(loctestnum, loctesterr, set, true, 25, 20); 
            Size(loctestnum, loctesterr, set, true, 3); 
            Exists(loctestnum, loctesterr, set, false, 20);

            SuccessorNRemove(loctestnum, loctesterr, set, true, 10, 30); 
            Size(loctestnum, loctesterr, set, true, 2); 
            Exists(loctestnum, loctesterr, set, false, 30);

            lasd::SetVec<int> refSetVecFromInitial(initialVec); 
            lasd::SetLst<int> refSetLstFromInitial(initialList); 
            
            if (name == "SetVec<int>") {
                lasd::SetVec<int> copyConstructedVec(refSetVecFromInitial); 
                EqualSetVec(loctestnum, loctesterr, refSetVecFromInitial, copyConstructedVec, true);
                
                lasd::SetVec<int> assignCopiedVec;
                assignCopiedVec = refSetVecFromInitial;
                EqualSetVec(loctestnum, loctesterr, refSetVecFromInitial, assignCopiedVec, true);
                
                lasd::SetVec<int> moveConstructedVec(std::move(refSetVecFromInitial));
                Size(loctestnum, loctesterr, moveConstructedVec, true, 4); 
                Empty(loctestnum, loctesterr, refSetVecFromInitial, true);
                Size(loctestnum, loctesterr, refSetVecFromInitial, true, 0);

                lasd::SetVec<int> moveAssignedVec;
                moveAssignedVec = std::move(moveConstructedVec);
                Size(loctestnum, loctesterr, moveAssignedVec, true, 4);
                Empty(loctestnum, loctesterr, moveConstructedVec, true);
                Size(loctestnum, loctesterr, moveConstructedVec, true, 0);

            } else { 
                lasd::SetLst<int> copyConstructedLst(refSetLstFromInitial); 
                EqualSetLst(loctestnum, loctesterr, refSetLstFromInitial, copyConstructedLst, true);

                lasd::SetLst<int> assignCopiedLst;
                assignCopiedLst = refSetLstFromInitial;
                EqualSetLst(loctestnum, loctesterr, refSetLstFromInitial, assignCopiedLst, true);
                
                lasd::SetLst<int> moveConstructedLst(std::move(refSetLstFromInitial));
                Size(loctestnum, loctesterr, moveConstructedLst, true, 3); 
                Empty(loctestnum, loctesterr, refSetLstFromInitial, true);
                Size(loctestnum, loctesterr, refSetLstFromInitial, true, 0);

                lasd::SetLst<int> moveAssignedLst;
                moveAssignedLst = std::move(moveConstructedLst);
                Size(loctestnum, loctesterr, moveAssignedLst, true, 3);
                Empty(loctestnum, loctesterr, moveConstructedLst, true);
                Size(loctestnum, loctesterr, moveConstructedLst, true, 0);
            }

            set.Clear();
            Empty(loctestnum, loctesterr, set, true);
            Size(loctestnum, loctesterr, set, true, 0);

        } catch (...) {
            loctestnum++; loctesterr++;
            cout << endl << "Unmanaged error in " << name << " Test! " << endl;
        }
        delete setsToTest[i]; 
    }

    cout << "End of Extended Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestSetDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended Set<double> Test:" << endl;

    lasd::Vector<double> initialVecD(4);
    initialVecD[0] = 1.1; initialVecD[1] = 3.3; initialVecD[2] = 2.2; initialVecD[3] = 3.3; 

    lasd::List<double> initialListD;
    initialListD.InsertAtBack(5.5);
    initialListD.InsertAtBack(4.4);
    initialListD.InsertAtBack(5.5);

    lasd::Set<double>* setsToTest[] = {new lasd::SetVec<double>(), new lasd::SetLst<double>()};
    string setNames[] = {"SetVec<double>", "SetLst<double>"};

    for (int i = 0; i < 2; ++i) {
        lasd::Set<double> &set = *setsToTest[i];
        string name = setNames[i];
        cout << "\n--- Testing " << name << " ---" << endl;

        try {
            set.Clear();

            loctestnum++;
            try {
                set.Max();
                cerr << "Error: " << name << ".Max() on empty set did not throw." << endl;
                loctesterr++;
            } catch (const std::length_error &exc) {
                cout << "Passed: " << name << ".Max() on empty set correctly threw length_error." << endl;
            } catch (...) {
                cerr << "Error: " << name << ".Max() on empty set threw wrong exception type." << endl;
                loctesterr++;
            }

            InsertC(loctestnum, loctesterr, set, true, 1.0);
            InsertC(loctestnum, loctesterr, set, true, 3.0);
            InsertC(loctestnum, loctesterr, set, true, 2.0);
            InsertC(loctestnum, loctesterr, set, false, 2.0);
            Size(loctestnum, loctesterr, set, true, 3);

            Exists(loctestnum, loctesterr, set, true, 2.0);
            Remove(loctestnum, loctesterr, set, true, 2.0);
            Exists(loctestnum, loctesterr, set, false, 2.0);
            Size(loctestnum, loctesterr, set, true, 2);

            Min(loctestnum, loctesterr, set, true, 1.0);
            Max(loctestnum, loctesterr, set, true, 3.0);

            Predecessor(loctestnum, loctesterr, set, true, 2.5, 1.0);
            Successor(loctestnum, loctesterr, set, true, 1.5, 3.0);

            lasd::SetVec<double> refSetVecDFromInitial(initialVecD);
            lasd::SetLst<double> refSetLstDFromInitial(initialListD);

            if (name == "SetVec<double>") {
                lasd::SetVec<double> copyConstructedVec(refSetVecDFromInitial);
                EqualSetVec(loctestnum, loctesterr, refSetVecDFromInitial, copyConstructedVec, true);
            } else {
                lasd::SetLst<double> copyConstructedLst(refSetLstDFromInitial);
                EqualSetLst(loctestnum, loctesterr, refSetLstDFromInitial, copyConstructedLst, true);
            }
            set.Clear();

        } catch (...) {
            loctestnum++; loctesterr++;
            cout << endl << "Unmanaged error in " << name << " Test! " << endl;
        }
        delete setsToTest[i];
    }
    cout << "End of Extended Set<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestSetString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of Extended Set<string> Test:" << endl;

    lasd::Vector<string> initialVecS(4);
    initialVecS[0] = "Apple"; initialVecS[1] = "Banana"; initialVecS[2] = "Cherry"; initialVecS[3] = "Apple"; 

    lasd::List<string> initialListS; 
    initialListS.InsertAtBack("Xylophone"); 
    initialListS.InsertAtBack("Zebra");
    initialListS.InsertAtBack("Xylophone");

    lasd::Set<string>* setsToTest[] = {new lasd::SetVec<string>(), new lasd::SetLst<string>()};
    string setNames[] = {"SetVec<string>", "SetLst<string>"};

    for (int i = 0; i < 2; ++i) {
        lasd::Set<string> &set = *setsToTest[i];
        string name = setNames[i];
        cout << "\n--- Testing " << name << " ---" << endl;

        try {
            set.Clear();

            loctestnum++;
            try {
                set.MaxNRemove();
                cerr << "Error: " << name << ".MaxNRemove() on empty set did not throw." << endl;
                loctesterr++;
            } catch (const std::length_error &exc) {
                cout << "Passed: " << name << ".MaxNRemove() on empty set correctly threw length_error." << endl;
            } catch (...) {
                cerr << "Error: " << name << ".MaxNRemove() on empty set threw wrong exception type." << endl;
                loctesterr++;
            }

            InsertC(loctestnum, loctesterr, set, true, string("Orange"));
            InsertC(loctestnum, loctesterr, set, true, string("Apple"));
            InsertC(loctestnum, loctesterr, set, true, string("Banana"));
            InsertC(loctestnum, loctesterr, set, false, string("Apple")); 
            Size(loctestnum, loctesterr, set, true, 3); 

            Exists(loctestnum, loctesterr, set, true, string("Apple"));
            Exists(loctestnum, loctesterr, set, false, string("Grape"));

            Min(loctestnum, loctesterr, set, true, string("Apple"));
            Max(loctestnum, loctesterr, set, true, string("Orange"));

            Remove(loctestnum, loctesterr, set, true, string("Banana"));
            Size(loctestnum, loctesterr, set, true, 2); 

            Predecessor(loctestnum, loctesterr, set, true, string("Lemon"), string("Apple"));
            Successor(loctestnum, loctesterr, set, true, string("Lemon"), string("Orange"));

            RemoveMin(loctestnum, loctesterr, set, true);
            Size(loctestnum, loctesterr, set, true, 1);
            Min(loctestnum, loctesterr, set, true, string("Orange"));

            RemoveMax(loctestnum, loctesterr, set, true);
            Empty(loctestnum, loctesterr, set, true);

            lasd::SetVec<string> refSetVecSFromInitial(initialVecS);
            lasd::SetLst<string> refSetLstSFromInitial(initialListS);

            if (name == "SetVec<string>") {
                lasd::SetVec<string> copyConstructedVec(refSetVecSFromInitial);
                EqualSetVec(loctestnum, loctesterr, refSetVecSFromInitial, copyConstructedVec, true);
            } else { 
                lasd::SetLst<string> copyConstructedLst(refSetLstSFromInitial);
                EqualSetLst(loctestnum, loctesterr, refSetLstSFromInitial, copyConstructedLst, true);
            }
            set.Clear();

            InsertC(loctestnum, loctesterr, set, true, string("C"));
            InsertC(loctestnum, loctesterr, set, true, string("A"));
            InsertC(loctestnum, loctesterr, set, true, string("B"));
            FoldPreOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string(""), string("ABC"));
            FoldPostOrder(loctestnum, loctesterr, set, true, &FoldStringConcatenate, string(""), string("CBA")); 

        } catch (...) {
            loctestnum++; loctesterr++;
            cout << endl << "Unmanaged error in " << name << " Test! " << endl;
        }
        delete setsToTest[i];
    }
    cout << "End of Extended Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* *********************************************************************************** */

void mytest() {
  uint testnum = 0, testerr = 0;

  cout << "Begin of My Test:" << endl;

  // Test Vector
  myTestVectorInt(testnum, testerr);
  myTestVectorDouble(testnum, testerr);
  myTestVectorString(testnum, testerr);

  // Test List
  myTestListInt(testnum, testerr);
  myTestListDouble(testnum, testerr);
  myTestListString(testnum, testerr);
  myTestListCopyAssignmentLeak(testnum, testerr);

  // Test VectorList
  myTestVectorListInt(testnum, testerr);
  myTestVectorListDouble(testnum, testerr);
  myTestVectorListString(testnum, testerr);

  // Test Set (SetVec e SetLst)
  myTestSetInt(testnum, testerr);
  myTestSetDouble(testnum, testerr);
  myTestSetString(testnum, testerr);

  cout << "End of My Test! (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
}
