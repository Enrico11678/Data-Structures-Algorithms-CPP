
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec: virtual public Heap<Data>,
protected SortableVector<Data> {
  // Must extend Heap<Data>,
  // Could extend SortableVector<Data>

private:

  // ...

protected:

  using Container::size;
  using SortableVector<Data>::Elements;

  // ...

public:

  // Default constructor
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  HeapVec(const TraversableContainer<Data> &); // A heap obtained from a TraversableContainer
  HeapVec(MappableContainer<Data> &&); // A heap obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HeapVec(const HeapVec &);

  // Move constructor
  HeapVec(HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  HeapVec & operator=(const HeapVec &);

  // Move assignment
  HeapVec & operator=(HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const HeapVec &) const noexcept;
  inline bool operator!=(const HeapVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  bool IsHeap() const noexcept override; // Override Heap member

  inline void Heapify() override; // Override Heap member

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() noexcept override; // Override SortableLinearContainer member

  /* ************************************************************************ */

  using SortableVector<Data>::Clear;
  using SortableVector<Data>::Size;
  using SortableVector<Data>::Empty;
  using SortableVector<Data>::operator==;
  using SortableVector<Data>::operator!=;
  using SortableVector<Data>::Exists;
  
  // Specific member functions (inherited from LinearContainer)

  inline const Data & operator[](const ulong) const override; 
  inline const Data & Front() const override; 
  inline const Data & Back() const override; 

protected:

  // Auxiliary functions, if necessary!
  
  void HeapifyRecursive(ulong);

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
