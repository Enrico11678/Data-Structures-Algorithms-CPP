
#include <iostream>
#include <climits>
#include <limits>

/* ************************************************************************** */

// #include "..."
#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/heap/heap.hpp"
#include "../zlasdtest/pq/pq.hpp"

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"

#include "../heap/heap.hpp"
#include "../heap/vec/heapvec.hpp"

#include "../pq/pq.hpp"
#include "../pq/heap/pqheap.hpp"

/* ************************************************************************** */

using namespace std;

void myTestHeapVecInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of HeapVec<int> Test:" << endl;
    try {
      // Heap vuoto
      lasd::HeapVec<int> emptyHeap;
      Empty(loctestnum, loctesterr, emptyHeap, true);
      Size(loctestnum, loctesterr, emptyHeap, true, 0);
      IsHeap(loctestnum, loctesterr, emptyHeap, true);

      // Heap con un solo elemento
      lasd::Vector<int> singleVec(1);
      SetAt(loctestnum, loctesterr, singleVec, true, 0, 42);
      lasd::HeapVec<int> singleHeap(singleVec);
      Size(loctestnum, loctesterr, singleHeap, true, 1);
      IsHeap(loctestnum, loctesterr, singleHeap, true);

      // Heap con elementi uguali
      lasd::Vector<int> eqVec(10);
      for (ulong i = 0; i < 10; ++i)
        SetAt(loctestnum, loctesterr, eqVec, true, i, 7);
      lasd::HeapVec<int> eqHeap(eqVec);
      IsHeap(loctestnum, loctesterr, eqHeap, true);

      // Heap con valori crescenti e decrescenti
      lasd::Vector<int> upVec(20), downVec(20);
      for (ulong i = 0; i < 20; ++i) {
        SetAt(loctestnum, loctesterr, upVec, true, i, static_cast<int>(i));
        SetAt(loctestnum, loctesterr, downVec, true, i, static_cast<int>(19 - i));
      }
      lasd::HeapVec<int> upHeap(upVec), downHeap(downVec);
      IsHeap(loctestnum, loctesterr, upHeap, true);
      IsHeap(loctestnum, loctesterr, downHeap, true);

      // Heap con valori estremi
      lasd::Vector<int> extVec(3);
      SetAt(loctestnum, loctesterr, extVec, true, 0, INT_MAX);
      SetAt(loctestnum, loctesterr, extVec, true, 1, INT_MIN);
      SetAt(loctestnum, loctesterr, extVec, true, 2, 0);
      lasd::HeapVec<int> extHeap(extVec);
      IsHeap(loctestnum, loctesterr, extHeap, true);

      // Copy e move constructor
      lasd::HeapVec<int> copyHeap(upHeap);
      EqualLinear(loctestnum, loctesterr, copyHeap, upHeap, true);
      lasd::HeapVec<int> moveHeap(std::move(copyHeap));
      Empty(loctestnum, loctesterr, copyHeap, true);
      EqualLinear(loctestnum, loctesterr, moveHeap, upHeap, true);

      // Copy e move assignment
      lasd::HeapVec<int> assignHeap;
      assignHeap = downHeap;
      EqualLinear(loctestnum, loctesterr, assignHeap, downHeap, true);
      lasd::HeapVec<int> emptyHeap3;
      assignHeap = emptyHeap3;
      Empty(loctestnum, loctesterr, assignHeap, true);
      lasd::HeapVec<int> emptyHeap4;
      assignHeap = std::move(emptyHeap4);
      Empty(loctestnum, loctesterr, assignHeap, true);

      // Sort e Heapify
      lasd::HeapVec<int> sortHeap(downVec);
      sortHeap.Sort();
      IsHeap(loctestnum, loctesterr, sortHeap, false);
      sortHeap.Heapify();
      IsHeap(loctestnum, loctesterr, sortHeap, true);

      // Traversal, Map, Fold
      TraversePreOrder(loctestnum, loctesterr, sortHeap, true, &TraversePrint<int>);
      MapPreOrder(loctestnum, loctesterr, sortHeap, true, &MapInvert<int>);
      FoldPreOrder(loctestnum, loctesterr, sortHeap, true, &FoldAdd<int>, 0, -190);

      // Eccezioni: accesso fuori range
      GetAt(loctestnum, loctesterr, sortHeap, false, 100, 0);

      // Eccezioni: accesso su heap vuoto
      lasd::HeapVec<int> emptyHeap2;
      GetAt(loctestnum, loctesterr, emptyHeap2, false, 0, 0);

      // Accesso in range (indice valido)
      GetAt(loctestnum, loctesterr, sortHeap, true, 5, sortHeap[5]);

      // Test di distruzione implicita (heap che esce dallo scope)
      lasd::Vector<int> v(10);
      for (ulong i = 0; i < 10; ++i)
        SetAt(loctestnum, loctesterr, v, true, i, int(i));
      lasd::HeapVec<int> scopedHeap(v);
      Size(loctestnum, loctesterr, scopedHeap, true, 10);
      IsHeap(loctestnum, loctesterr, scopedHeap, true);
      // scopedHeap verrà distrutto qui

      lasd::Vector<int> v2(20);
      for (ulong i = 0; i < 20; ++i)
        SetAt(loctestnum, loctesterr, v2, true, i, int(i * 2));
      lasd::HeapVec<int> heapCopy(v2);
      lasd::HeapVec<int> heapCopy2(heapCopy);
      EqualLinear(loctestnum, loctesterr, heapCopy, heapCopy2, true);
      // heapCopy2 verrà distrutto qui

      // Test operator== e operator!= e Exists
      lasd::Vector<int> v3(3), v4(3);
      SetAt(loctestnum, loctesterr, v3, true, 0, 1);
      SetAt(loctestnum, loctesterr, v3, true, 1, 2);
      SetAt(loctestnum, loctesterr, v3, true, 2, 3);
      SetAt(loctestnum, loctesterr, v4, true, 0, 1);
      SetAt(loctestnum, loctesterr, v4, true, 1, 2);
      SetAt(loctestnum, loctesterr, v4, true, 2, 3);
      lasd::HeapVec<int> h1(v3), h2(v4);
      if (h1 == h2) {
        loctestnum++;
        cout << "HeapVec<int> == test: Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<int> == test: Error" << endl;
      }
      if (!(h1 != h2)) {
        loctestnum++;
        cout << "HeapVec<int> != test: Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<int> != test: Error" << endl;
      }
      if (h1.Exists(2)) {
        loctestnum++;
        cout << "HeapVec<int> Exists(2): Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<int> Exists(2): Error" << endl;
      }
      if (!h1.Exists(99)) {
        loctestnum++;
        cout << "HeapVec<int> Exists(99): Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<int> Exists(99): Error" << endl;
      }


    } catch (...) {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of HeapVec<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestHeapVecDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of HeapVec<double> Test:" << endl;
    try {
      // Heap vuoto
      lasd::HeapVec<double> emptyHeap;
      Empty(loctestnum, loctesterr, emptyHeap, true);
      Size(loctestnum, loctesterr, emptyHeap, true, 0);
      IsHeap(loctestnum, loctesterr, emptyHeap, true);

      // Heap con un solo elemento
      lasd::Vector<double> singleVec(1);
      SetAt(loctestnum, loctesterr, singleVec, true, 0, 42.5);
      lasd::HeapVec<double> singleHeap(singleVec);
      Size(loctestnum, loctesterr, singleHeap, true, 1);
      IsHeap(loctestnum, loctesterr, singleHeap, true);

      // Heap con elementi uguali
      lasd::Vector<double> eqVec(10);
      for (ulong i = 0; i < 10; ++i)
        SetAt(loctestnum, loctesterr, eqVec, true, i, 7.7);
      lasd::HeapVec<double> eqHeap(eqVec);
      IsHeap(loctestnum, loctesterr, eqHeap, true);

      // Heap con valori crescenti e decrescenti
      lasd::Vector<double> upVec(20), downVec(20);
      for (ulong i = 0; i < 20; ++i) {
        SetAt(loctestnum, loctesterr, upVec, true, i, static_cast<double>(i));
        SetAt(loctestnum, loctesterr, downVec, true, i, static_cast<double>(19 - i));
      }
      lasd::HeapVec<double> upHeap(upVec), downHeap(downVec);
      IsHeap(loctestnum, loctesterr, upHeap, true);
      IsHeap(loctestnum, loctesterr, downHeap, true);

      // Heap con valori estremi
      lasd::Vector<double> extVec(3);
      SetAt(loctestnum, loctesterr, extVec, true, 0, std::numeric_limits<double>::max());
      SetAt(loctestnum, loctesterr, extVec, true, 1, std::numeric_limits<double>::lowest());
      SetAt(loctestnum, loctesterr, extVec, true, 2, 0.0);
      lasd::HeapVec<double> extHeap(extVec);
      IsHeap(loctestnum, loctesterr, extHeap, true);

      // Copy e move constructor
      lasd::HeapVec<double> copyHeap(upHeap);
      EqualLinear(loctestnum, loctesterr, copyHeap, upHeap, true);
      lasd::HeapVec<double> moveHeap(std::move(copyHeap));
      Empty(loctestnum, loctesterr, copyHeap, true);
      EqualLinear(loctestnum, loctesterr, moveHeap, upHeap, true);

      // Copy e move assignment
      lasd::HeapVec<double> assignHeap;
      assignHeap = downHeap;
      EqualLinear(loctestnum, loctesterr, assignHeap, downHeap, true);
      lasd::HeapVec<double> emptyHeap3;
      assignHeap = emptyHeap3;
      Empty(loctestnum, loctesterr, assignHeap, true);
      lasd::HeapVec<double> emptyHeap4;
      assignHeap = std::move(emptyHeap4);
      Empty(loctestnum, loctesterr, assignHeap, true);

      // Sort e Heapify
      lasd::HeapVec<double> sortHeap(downVec);
      sortHeap.Sort();
      IsHeap(loctestnum, loctesterr, sortHeap, false);
      sortHeap.Heapify();
      IsHeap(loctestnum, loctesterr, sortHeap, true);

      // Traversal, Map, Fold
      TraversePreOrder(loctestnum, loctesterr, sortHeap, true, &TraversePrint<double>);
      MapPreOrder(loctestnum, loctesterr, sortHeap, true, &MapInvert<double>);
      FoldPreOrder(loctestnum, loctesterr, sortHeap, true, &FoldAdd<double>, 0.0, -190.0);

      // Eccezioni: accesso fuori range
      GetAt(loctestnum, loctesterr, sortHeap, false, 100, 0.0);

      // Eccezioni: accesso su heap vuoto
      lasd::HeapVec<double> emptyHeap2;
      GetAt(loctestnum, loctesterr, emptyHeap2, false, 0, 0.0);

      // Accesso in range (indice valido)
      GetAt(loctestnum, loctesterr, sortHeap, true, 5, sortHeap[5]);

      // Test di distruzione implicita (heap che esce dallo scope)
      lasd::Vector<double> v(10);
      for (ulong i = 0; i < 10; ++i)
        SetAt(loctestnum, loctesterr, v, true, i, static_cast<double>(i));
      lasd::HeapVec<double> scopedHeap(v);
      Size(loctestnum, loctesterr, scopedHeap, true, 10);
      IsHeap(loctestnum, loctesterr, scopedHeap, true);
      // scopedHeap verrà distrutto qui

      lasd::Vector<double> v2(20);
      for (ulong i = 0; i < 20; ++i)
        SetAt(loctestnum, loctesterr, v2, true, i, static_cast<double>(i * 2));
      lasd::HeapVec<double> heapCopy(v2);
      lasd::HeapVec<double> heapCopy2(heapCopy);
      EqualLinear(loctestnum, loctesterr, heapCopy, heapCopy2, true);
      // heapCopy2 verrà distrutto qui

      // Test operator== e operator!= e Exists
      lasd::Vector<double> v3(2), v4(2);
      SetAt(loctestnum, loctesterr, v3, true, 0, 1.1);
      SetAt(loctestnum, loctesterr, v3, true, 1, 2.2);
      SetAt(loctestnum, loctesterr, v4, true, 0, 1.1);
      SetAt(loctestnum, loctesterr, v4, true, 1, 2.2);
      lasd::HeapVec<double> h1(v3), h2(v4);
      if (h1 == h2) {
        loctestnum++;
        cout << "HeapVec<double> == test: Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<double> == test: Error" << endl;
      }
      if (!(h1 != h2)) {
        loctestnum++;
        cout << "HeapVec<double> != test: Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<double> != test: Error" << endl;
      }
      if (h1.Exists(2.2)) {
        loctestnum++;
        cout << "HeapVec<double> Exists(2.2): Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<double> Exists(2.2): Error" << endl;
      }
      if (!h1.Exists(99.9)) {
        loctestnum++;
        cout << "HeapVec<double> Exists(99.9): Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "HeapVec<double> Exists(99.9): Error" << endl;
      }

    } catch (...) {
      loctestnum++; loctesterr++;
      cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of HeapVec<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestHeapVecString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of HeapVec<string> Test:" << endl;
    try {
        // Heap vuoto
        lasd::HeapVec<std::string> emptyHeap;
        Empty(loctestnum, loctesterr, emptyHeap, true);
        Size(loctestnum, loctesterr, emptyHeap, true, 0);
        IsHeap(loctestnum, loctesterr, emptyHeap, true);

        // Heap con stringa vuota
        lasd::Vector<std::string> vecEmptyStr(1);
        SetAt(loctestnum, loctesterr, vecEmptyStr, true, 0, std::string(""));
        lasd::HeapVec<std::string> heapEmptyStr(vecEmptyStr);
        Size(loctestnum, loctesterr, heapEmptyStr, true, 1);
        IsHeap(loctestnum, loctesterr, heapEmptyStr, true);

        // Heap con stringhe palindrome
        lasd::Vector<std::string> vecPalindrome(4);
        SetAt(loctestnum, loctesterr, vecPalindrome, true, 0, std::string("anna"));
        SetAt(loctestnum, loctesterr, vecPalindrome, true, 1, std::string("otto"));
        SetAt(loctestnum, loctesterr, vecPalindrome, true, 2, std::string("radar"));
        SetAt(loctestnum, loctesterr, vecPalindrome, true, 3, std::string("civic"));
        lasd::HeapVec<std::string> heapPalindrome(vecPalindrome);
        IsHeap(loctestnum, loctesterr, heapPalindrome, true);

        // Confronto con se stesso (deve essere uguale)
        EqualLinear(loctestnum, loctesterr, heapPalindrome, heapPalindrome, true);

        // Copy constructor e confronto
        lasd::HeapVec<std::string> heapPalindromeCopy(heapPalindrome);
        EqualLinear(loctestnum, loctesterr, heapPalindrome, heapPalindromeCopy, true);

        // Verifica che l'accesso costante funzioni e che i dati siano uguali
        if (heapPalindromeCopy.Size() > 0) {
          if (heapPalindromeCopy[0] == heapPalindrome[0]){ 
            loctestnum++;
          } else { 
            loctestnum++; 
            loctesterr++; 
          }
          if (heapPalindromeCopy.Front() == heapPalindrome.Front()){
            loctestnum++; 
          } else { 
            loctestnum++; 
            loctesterr++; 
          }
          if (heapPalindromeCopy.Back() == heapPalindrome.Back()){
            loctestnum++; 
          } else { 
            loctestnum++; 
            loctesterr++; 
          }
        }

        // Move constructor e confronto
        lasd::HeapVec<std::string> heapPalindromeMove(std::move(heapPalindromeCopy));
        Empty(loctestnum, loctesterr, heapPalindromeCopy, true);
        EqualLinear(loctestnum, loctesterr, heapPalindrome, heapPalindromeMove, true);

        // Confronto con un heap di stringhe diverse
        lasd::Vector<std::string> vecOther(4);
        SetAt(loctestnum, loctesterr, vecOther, true, 0, std::string("test"));
        SetAt(loctestnum, loctesterr, vecOther, true, 1, std::string("heap"));
        SetAt(loctestnum, loctesterr, vecOther, true, 2, std::string("palindrome"));
        SetAt(loctestnum, loctesterr, vecOther, true, 3, std::string("otto"));
        lasd::HeapVec<std::string> heapOther(vecOther);
        EqualLinear(loctestnum, loctesterr, heapPalindrome, heapOther, false);

        // Heap con caratteri speciali
        lasd::Vector<std::string> vecSpecial(3);
        SetAt(loctestnum, loctesterr, vecSpecial, true, 0, std::string("\n\t"));
        SetAt(loctestnum, loctesterr, vecSpecial, true, 1, std::string("!@#$%^&*()"));
        SetAt(loctestnum, loctesterr, vecSpecial, true, 2, std::string("abc"));
        lasd::HeapVec<std::string> heapSpecial(vecSpecial);
        IsHeap(loctestnum, loctesterr, heapSpecial, true);

        // Heap con stringhe uguali
        lasd::Vector<std::string> eqVec(5);
        for (ulong i = 0; i < 5; ++i)
            SetAt(loctestnum, loctesterr, eqVec, true, i, std::string("same"));
        lasd::HeapVec<std::string> eqHeap(eqVec);
        IsHeap(loctestnum, loctesterr, eqHeap, true);

        // Copy e move constructor su heap vuoto e non
        lasd::HeapVec<std::string> copyHeap(heapSpecial);
        EqualLinear(loctestnum, loctesterr, copyHeap, heapSpecial, true);
        lasd::HeapVec<std::string> moveHeap(std::move(copyHeap));
        Empty(loctestnum, loctesterr, copyHeap, true);
        EqualLinear(loctestnum, loctesterr, moveHeap, heapSpecial, true);

        lasd::HeapVec<std::string> copyEmpty(emptyHeap);
        Empty(loctestnum, loctesterr, copyEmpty, true);
        lasd::HeapVec<std::string> moveEmpty(std::move(copyEmpty));
        Empty(loctestnum, loctesterr, copyEmpty, true);
        Empty(loctestnum, loctesterr, moveEmpty, true);

        // Copy e move assignment su heap vuoto e non
        lasd::HeapVec<std::string> assignHeap;
        assignHeap = eqHeap;
        EqualLinear(loctestnum, loctesterr, assignHeap, eqHeap, true);
        lasd::HeapVec<std::string> emptyHeap2;
        assignHeap = emptyHeap2;
        Empty(loctestnum, loctesterr, assignHeap, true);
        lasd::HeapVec<std::string> emptyHeap3;
        assignHeap = std::move(emptyHeap3);
        Empty(loctestnum, loctesterr, assignHeap, true);

        // Sort e Heapify su dati strani
        lasd::HeapVec<std::string> sortHeap(vecSpecial);
        sortHeap.Sort();
        IsHeap(loctestnum, loctesterr, sortHeap, false);
        sortHeap.Heapify();
        IsHeap(loctestnum, loctesterr, sortHeap, true);

        // Traversal e Fold
        TraversePreOrder(loctestnum, loctesterr, sortHeap, true, &TraversePrint<std::string>);
        // Concatenazione di tutte le stringhe
        FoldPreOrder(loctestnum, loctesterr, sortHeap, true, &FoldStringConcatenate, std::string(""), std::string("abc!@#$%^&*()\n\t"));

        // Accesso fuori range
        GetAt(loctestnum, loctesterr, sortHeap, false, 100, std::string(""));

        // Accesso su heap vuoto
        lasd::HeapVec<std::string> emptyHeap4;
        GetAt(loctestnum, loctesterr, emptyHeap4, false, 0, std::string(""));

        // Accesso in range (indice valido)
        if (sortHeap.Size() > 1)
            GetAt(loctestnum, loctesterr, sortHeap, true, 1, sortHeap[1]);

        // Test di distruzione implicita (heap che esce dallo scope)
        lasd::Vector<std::string> v(10);
        for (ulong i = 0; i < 10; ++i)
          SetAt(loctestnum, loctesterr, v, true, i, "str" + std::to_string(i));
        lasd::HeapVec<std::string> scopedHeap(v);
        Size(loctestnum, loctesterr, scopedHeap, true, 10);
        IsHeap(loctestnum, loctesterr, scopedHeap, true);
        // scopedHeap verrà distrutto qui

        lasd::Vector<std::string> v2(20);
        for (ulong i = 0; i < 20; ++i)
          SetAt(loctestnum, loctesterr, v2, true, i, "x" + std::to_string(i));
        lasd::HeapVec<std::string> heapCopy(v2);
        lasd::HeapVec<std::string> heapCopy2(heapCopy);
        EqualLinear(loctestnum, loctesterr, heapCopy, heapCopy2, true);
        // heapCopy2 verrà distrutto qui

        // Test operator== e operator!= e Exists
        lasd::Vector<std::string> v3(2), v4(2);
        SetAt(loctestnum, loctesterr, v3, true, 0, std::string("a"));
        SetAt(loctestnum, loctesterr, v3, true, 1, std::string("b"));
        SetAt(loctestnum, loctesterr, v4, true, 0, std::string("a"));
        SetAt(loctestnum, loctesterr, v4, true, 1, std::string("b"));
        lasd::HeapVec<std::string> h1(v3), h2(v4);
        if (h1 == h2) {
          loctestnum++;
          cout << "HeapVec<string> == test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "HeapVec<string> == test: Error" << endl;
        }
        if (!(h1 != h2)) {
          loctestnum++;
          cout << "HeapVec<string> != test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "HeapVec<string> != test: Error" << endl;
        }
        if (h1.Exists("b")) {
          loctestnum++;
          cout << "HeapVec<string> Exists(\"b\"): Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "HeapVec<string> Exists(\"b\"): Error" << endl;
        }
        if (!h1.Exists("z")) {
          loctestnum++;
          cout << "HeapVec<string> Exists(\"z\"): Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "HeapVec<string> Exists(\"z\"): Error" << endl;
        }

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of HeapVec<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void myTestPQHeapInt(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQHeap<int> Test:" << endl;
    try {
        // PQ vuota
        lasd::PQHeap<int> pqEmpty;
        Empty(loctestnum, loctesterr, pqEmpty, true);
        Size(loctestnum, loctesterr, pqEmpty, true, 0);

        // Tip/Remove su vuota (devono lanciare)
        Tip(loctestnum, loctesterr, pqEmpty, false, 0);
        RemoveTip(loctestnum, loctesterr, pqEmpty, false);
        TipNRemove(loctestnum, loctesterr, pqEmpty, false, 0);

        // Inserimento e rimozione singolo elemento
        pqEmpty.Insert(42);
        Size(loctestnum, loctesterr, pqEmpty, true, 1);
        Tip(loctestnum, loctesterr, pqEmpty, true, 42);
        TipNRemove(loctestnum, loctesterr, pqEmpty, true, 42);
        Empty(loctestnum, loctesterr, pqEmpty, true);

        // Inserimento multiplo, inclusi duplicati e valori estremi
        pqEmpty.Insert(INT_MAX);
        pqEmpty.Insert(INT_MIN);
        pqEmpty.Insert(0);
        pqEmpty.Insert(0);
        pqEmpty.Insert(100);
        pqEmpty.Insert(-100);
        pqEmpty.Insert(INT_MAX);
        Size(loctestnum, loctesterr, pqEmpty, true, 7);  

        // Test con valori speciali (overflow, underflow) 
        pqEmpty.Insert(std::numeric_limits<int>::max());
        pqEmpty.Insert(std::numeric_limits<int>::min());
        Tip(loctestnum, loctesterr, pqEmpty, true, std::numeric_limits<int>::max());
        TipNRemove(loctestnum, loctesterr, pqEmpty, true, std::numeric_limits<int>::max());

        // Tip e rimozione ripetuta
        Tip(loctestnum, loctesterr, pqEmpty, true, INT_MAX);
        TipNRemove(loctestnum, loctesterr, pqEmpty, true, INT_MAX);
        Tip(loctestnum, loctesterr, pqEmpty, true, INT_MAX);
        RemoveTip(loctestnum, loctesterr, pqEmpty, true);
        Tip(loctestnum, loctesterr, pqEmpty, true, 100);

        // Change su indici validi e non
        Change(loctestnum, loctesterr, pqEmpty, true, 0, 9999);
        Change(loctestnum, loctesterr, pqEmpty, false, 100, 0); // fuori range

        // Accesso diretto
        GetAt(loctestnum, loctesterr, pqEmpty, true, 0, pqEmpty[0]);
        GetAt(loctestnum, loctesterr, pqEmpty, false, 100, 0);

        // Copy e move constructor/assignment
        lasd::PQHeap<int> pqCopy(pqEmpty);
        EqualLinear(loctestnum, loctesterr, pqCopy, pqEmpty, true);
        lasd::PQHeap<int> pqMove(std::move(pqCopy));
        Empty(loctestnum, loctesterr, pqCopy, true);
        EqualLinear(loctestnum, loctesterr, pqMove, pqEmpty, true);

        lasd::PQHeap<int> pqAssign;
        pqAssign = pqMove;
        EqualLinear(loctestnum, loctesterr, pqAssign, pqMove, true);
        lasd::PQHeap<int> pqAssignMove;
        pqAssignMove = std::move(pqAssign);
        Empty(loctestnum, loctesterr, pqAssign, true);

        // Stress test: inserimento e rimozione massiva
        for (int i = 0; i < 1000; ++i) 
          pqAssignMove.Insert(i);
        Size(loctestnum, loctesterr, pqAssignMove, true, 1000 + pqEmpty.Size());
        for (int i = 0; i < 500; ++i) 
          pqAssignMove.TipNRemove();
        Size(loctestnum, loctesterr, pqAssignMove, true, 500 + pqEmpty.Size());

        // Svuotamento completo
        pqAssignMove.Clear();
        Empty(loctestnum, loctesterr, pqAssignMove, true);

        // Test di distruzione implicita (PQHeap che esce dallo scope)
        lasd::PQHeap<int> pq;
        for (int i = 0; i < 10; ++i)
          pq.Insert(i);
        Size(loctestnum, loctesterr, pq, true, 10);
        Tip(loctestnum, loctesterr, pq, true, 9);
        // pq verrà distrutto qui

        lasd::PQHeap<int> pqCopy2;
        for (int i = 0; i < 20; ++i)
          pqCopy.Insert(i * 2);
        lasd::PQHeap<int> pqCopy3(pqCopy2);
        EqualLinear(loctestnum, loctesterr, pqCopy2, pqCopy3, true);
        // pqCopy2 verrà distrutto qui

        // Test operator== e operator!= e Exists
        lasd::PQHeap<int> pq1, pq2;
        pq1.Insert(1); pq1.Insert(2); pq1.Insert(3);
        pq2.Insert(1); pq2.Insert(2); pq2.Insert(3);
        if (pq1 == pq2) {
          loctestnum++;
          cout << "PQHeap<int> == test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<int> == test: Error" << endl;
        }
        if (!(pq1 != pq2)) {
          loctestnum++;
          cout << "PQHeap<int> != test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<int> != test: Error" << endl;
        }
        if (pq1.Exists(2)) {
          loctestnum++;
          cout << "PQHeap<int> Exists(2): Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<int> Exists(2): Error" << endl;
        }
        if (!pq1.Exists(99)) {
          loctestnum++;
          cout << "PQHeap<int> Exists(99): Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<int> Exists(99): Error" << endl;
        }

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQHeap<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestPQHeapDouble(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQHeap<double> Test:" << endl;
    try {
        // PQ vuota
        lasd::PQHeap<double> pqEmpty;
        Empty(loctestnum, loctesterr, pqEmpty, true);
        Size(loctestnum, loctesterr, pqEmpty, true, 0);

        // Tip/Remove su vuota (devono lanciare)
        Tip(loctestnum, loctesterr, pqEmpty, false, 0.0);
        RemoveTip(loctestnum, loctesterr, pqEmpty, false);
        TipNRemove(loctestnum, loctesterr, pqEmpty, false, 0.0);

        // Inserimento e rimozione singolo elemento
        pqEmpty.Insert(42.42);
        Size(loctestnum, loctesterr, pqEmpty, true, 1);
        Tip(loctestnum, loctesterr, pqEmpty, true, 42.42);
        TipNRemove(loctestnum, loctesterr, pqEmpty, true, 42.42);
        Empty(loctestnum, loctesterr, pqEmpty, true);

        // Inserimento multiplo, inclusi duplicati e valori estremi
        pqEmpty.Insert(std::numeric_limits<double>::max());
        pqEmpty.Insert(std::numeric_limits<double>::lowest());
        pqEmpty.Insert(0.0);
        pqEmpty.Insert(0.0);
        pqEmpty.Insert(100.5);
        pqEmpty.Insert(-100.5);
        pqEmpty.Insert(std::numeric_limits<double>::max());
        Size(loctestnum, loctesterr, pqEmpty, true, 7);

        // Tip e rimozione ripetuta
        Tip(loctestnum, loctesterr, pqEmpty, true, std::numeric_limits<double>::max());
        TipNRemove(loctestnum, loctesterr, pqEmpty, true, std::numeric_limits<double>::max());
        Tip(loctestnum, loctesterr, pqEmpty, true, std::numeric_limits<double>::max());
        RemoveTip(loctestnum, loctesterr, pqEmpty, true);
        Tip(loctestnum, loctesterr, pqEmpty, true, 100.5);

        // Change su indici validi e non
        Change(loctestnum, loctesterr, pqEmpty, true, 0, 9999.99);
        Change(loctestnum, loctesterr, pqEmpty, false, 100, 0.0); // fuori range

        // Accesso diretto
        GetAt(loctestnum, loctesterr, pqEmpty, true, 0, pqEmpty[0]);
        GetAt(loctestnum, loctesterr, pqEmpty, false, 100, 0.0);

        // Copy e move constructor/assignment
        lasd::PQHeap<double> pqCopy(pqEmpty);
        EqualLinear(loctestnum, loctesterr, pqCopy, pqEmpty, true);
        lasd::PQHeap<double> pqMove(std::move(pqCopy));
        Empty(loctestnum, loctesterr, pqCopy, true);
        EqualLinear(loctestnum, loctesterr, pqMove, pqEmpty, true);

        lasd::PQHeap<double> pqAssign;
        pqAssign = pqMove;
        EqualLinear(loctestnum, loctesterr, pqAssign, pqMove, true);
        lasd::PQHeap<double> pqAssignMove;
        pqAssignMove = std::move(pqAssign);
        Empty(loctestnum, loctesterr, pqAssign, true);

        // Stress test: inserimento e rimozione massiva
        for (int i = 0; i < 1000; ++i) pqAssignMove.Insert(static_cast<double>(i) / 10.0);
        Size(loctestnum, loctesterr, pqAssignMove, true, 1000 + pqEmpty.Size());
        for (int i = 0; i < 500; ++i) pqAssignMove.TipNRemove();
        Size(loctestnum, loctesterr, pqAssignMove, true, 500 + pqEmpty.Size());

        // Svuotamento completo
        pqAssignMove.Clear();
        Empty(loctestnum, loctesterr, pqAssignMove, true);

        // Test di distruzione implicita (PQHeap che esce dallo scope)

        lasd::Vector<double> v(10);
        for (ulong i = 0; i < 10; ++i)
          SetAt(loctestnum, loctesterr, v, true, i, static_cast<double>(i));
        lasd::PQHeap<double> pqFromVec(v);
        Size(loctestnum, loctesterr, pqFromVec, true, 10);
        Tip(loctestnum, loctesterr, pqFromVec, true, 9.0);
        // pqFromVec verrà distrutto qui

        lasd::PQHeap<double> pqCopyBlock;
        for (int i = 0; i < 20; ++i)
          pqCopyBlock.Insert(i * 2.5);
        lasd::PQHeap<double> pqCopy2(pqCopyBlock);
        EqualLinear(loctestnum, loctesterr, pqCopyBlock, pqCopy2, true);
        // pqCopy2 verrà distrutto qui

        // Test operator== e operator!= e Exists
        lasd::PQHeap<double> pq1, pq2;
        pq1.Insert(1.1); pq1.Insert(2.2);
        pq2.Insert(1.1); pq2.Insert(2.2);
        if (pq1 == pq2) {
          loctestnum++;
          cout << "PQHeap<double> == test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<double> == test: Error" << endl;
        }
        if (!(pq1 != pq2)) {
          loctestnum++;
          cout << "PQHeap<double> != test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<double> != test: Error" << endl;
        }
        if (pq1.Exists(2.2)) {
          loctestnum++;
          cout << "PQHeap<double> Exists(2.2): Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<double> Exists(2.2): Error" << endl;
      }
      if (!pq1.Exists(99.9)) {
        loctestnum++;
        cout << "PQHeap<double> Exists(99.9): Correct!" << endl;
      } else {
        loctestnum++; loctesterr++;
        cout << "PQHeap<double> Exists(99.9): Error" << endl;
      }

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQHeap<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

void myTestPQHeapString(uint & testnum, uint & testerr) {
    uint loctestnum = 0, loctesterr = 0;
    cout << endl << "Begin of PQHeap<string> Test:" << endl;
    try {
        // PQ vuota
        lasd::PQHeap<std::string> pqEmpty;
        Empty(loctestnum, loctesterr, pqEmpty, true);
        Size(loctestnum, loctesterr, pqEmpty, true, 0);

        // Tip/Remove su vuota (devono lanciare)
        Tip(loctestnum, loctesterr, pqEmpty, false, std::string(""));
        RemoveTip(loctestnum, loctesterr, pqEmpty, false);
        TipNRemove(loctestnum, loctesterr, pqEmpty, false, std::string(""));

        // Inserimento e rimozione singolo elemento
        pqEmpty.Insert("ciao");
        Size(loctestnum, loctesterr, pqEmpty, true, 1);
        Tip(loctestnum, loctesterr, pqEmpty, true, std::string("ciao"));
        TipNRemove(loctestnum, loctesterr, pqEmpty, true, std::string("ciao"));
        Empty(loctestnum, loctesterr, pqEmpty, true);

        // Inserimento multiplo, inclusi duplicati e stringhe speciali
        pqEmpty.Insert("anna");
        pqEmpty.Insert("otto");
        pqEmpty.Insert("radar");
        pqEmpty.Insert("civic");
        pqEmpty.Insert("otto");
        pqEmpty.Insert("!@#$%");
        pqEmpty.Insert("");
        pqEmpty.Insert("zzzz");
        Size(loctestnum, loctesterr, pqEmpty, true, 8);

        // Tip e rimozione ripetuta
        Tip(loctestnum, loctesterr, pqEmpty, true, std::string("zzzz"));
        TipNRemove(loctestnum, loctesterr, pqEmpty, true, std::string("zzzz"));
        Tip(loctestnum, loctesterr, pqEmpty, true, std::string("radar"));
        RemoveTip(loctestnum, loctesterr, pqEmpty, true);
        Tip(loctestnum, loctesterr, pqEmpty, true, std::string("otto"));

        // Change su indici validi e non
        Change(loctestnum, loctesterr, pqEmpty, true, 0, std::string("palindrome"));
        Change(loctestnum, loctesterr, pqEmpty, false, 100, std::string("fail"));

        // Accesso diretto
        GetAt(loctestnum, loctesterr, pqEmpty, true, 0, pqEmpty[0]);
        GetAt(loctestnum, loctesterr, pqEmpty, false, 100, std::string(""));

        // Copy e move constructor/assignment
        lasd::PQHeap<std::string> pqCopy(pqEmpty);
        EqualLinear(loctestnum, loctesterr, pqCopy, pqEmpty, true);
        lasd::PQHeap<std::string> pqMove(std::move(pqCopy));
        Empty(loctestnum, loctesterr, pqCopy, true);
        EqualLinear(loctestnum, loctesterr, pqMove, pqEmpty, true);

        lasd::PQHeap<std::string> pqAssign;
        pqAssign = pqMove;
        EqualLinear(loctestnum, loctesterr, pqAssign, pqMove, true);
        lasd::PQHeap<std::string> pqAssignMove;
        pqAssignMove = std::move(pqAssign);
        Empty(loctestnum, loctesterr, pqAssign, true);

        // Stress test: inserimento e rimozione massiva
        for (int i = 0; i < 1000; ++i) pqAssignMove.Insert("str" + std::to_string(i));
        Size(loctestnum, loctesterr, pqAssignMove, true, 1000 + pqEmpty.Size());
        for (int i = 0; i < 500; ++i) pqAssignMove.TipNRemove();
        Size(loctestnum, loctesterr, pqAssignMove, true, 500 + pqEmpty.Size());

        // Svuotamento completo
        pqAssignMove.Clear();
        Empty(loctestnum, loctesterr, pqAssignMove, true);

        // Test di distruzione implicita (PQHeap che esce dallo scope)
        lasd::PQHeap<std::string> pq;
        for (int i = 0; i < 10; ++i)
          pq.Insert("str" + std::to_string(i));
        Size(loctestnum, loctesterr, pq, true, 10);
        Tip(loctestnum, loctesterr, pq, true, std::string("str9"));
        // pq verrà distrutto qui

        lasd::PQHeap<std::string> pqCopyBlock;
        for (int i = 0; i < 20; ++i)
          pqCopyBlock.Insert("x" + std::to_string(i));
        lasd::PQHeap<std::string> pqCopy2(pqCopyBlock);
        EqualLinear(loctestnum, loctesterr, pqCopyBlock, pqCopy2, true);
        // pqCopy2 verrà distrutto qui

        // Test operator== e operator!= e Exists
        lasd::PQHeap<std::string> pq1, pq2;
        pq1.Insert("a"); pq1.Insert("b");
        pq2.Insert("a"); pq2.Insert("b");
        if (pq1 == pq2) {
          loctestnum++;
          cout << "PQHeap<string> == test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<string> == test: Error" << endl;
        }
        if (!(pq1 != pq2)) {
          loctestnum++;
          cout << "PQHeap<string> != test: Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<string> != test: Error" << endl;
        }
        if (pq1.Exists("b")) {
          loctestnum++;
          cout << "PQHeap<string> Exists(\"b\"): Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<string> Exists(\"b\"): Error" << endl;
        }
        if (!pq1.Exists("z")) {
          loctestnum++;
          cout << "PQHeap<string> Exists(\"z\"): Correct!" << endl;
        } else {
          loctestnum++; loctesterr++;
          cout << "PQHeap<string> Exists(\"z\"): Error" << endl;
        }

    } catch (...) {
        loctestnum++; loctesterr++;
        cout << endl << "Unmanaged error! " << endl;
    }
    cout << "End of PQHeap<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    testnum += loctestnum;
    testerr += loctesterr;
}

/* ************************************************************************** */

void mytest() {
  uint testnum = 0, testerr = 0;

  cout << "Begin of MyTest:" << endl;

  myTestHeapVecInt(testnum, testerr);
  myTestHeapVecDouble(testnum, testerr);
  myTestHeapVecString(testnum, testerr);

  myTestPQHeapInt(testnum, testerr);
  myTestPQHeapDouble(testnum, testerr);
  myTestPQHeapString(testnum, testerr);

  cout << "\nEnd of My Test! (Errors/Tests: " << testerr << "/" << testnum << ")\n" << endl;
}
