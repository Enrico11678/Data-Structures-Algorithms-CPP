
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap: virtual public PQ<Data>,
protected HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  using HeapVec<Data>::size;
  using HeapVec<Data>::Elements;
  ulong capacity = 0;
  // ...

public:

  // Default constructor
  PQHeap() = default;

  /* ************************************************************************ */

  // Specific constructors
  PQHeap(const TraversableContainer<Data> &); // A priority queue obtained from a TraversableContainer
  PQHeap(MappableContainer<Data> &&); // A priority queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  PQHeap(const PQHeap &);

  // Move constructor
  PQHeap(PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~PQHeap();

  /* ************************************************************************ */

  // Copy assignment
  PQHeap & operator=(const PQHeap &);

  // Move assignment
  PQHeap & operator=(PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  inline const Data & Tip() const override; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override; // Override PQ member (must throw std::length_error when empty)

  void Insert(const Data &) override; // Override PQ member (Copy of the value)
  void Insert(Data &&) override; // Override PQ member (Move of the value)

  void Change(ulong, const Data &) override; // Override PQ member (Copy of the value)
  void Change(ulong, Data &&) override; // Override PQ member (Move of the value)

  /* ************************************************************************ */

  inline bool operator==(const PQHeap &) const noexcept;
  inline bool operator!=(const PQHeap &) const noexcept; 

  inline void Clear() override;
  void Resize(ulong) override;

  using HeapVec<Data>::Size;
  using HeapVec<Data>::Empty;
  using HeapVec<Data>::operator[];
  using HeapVec<Data>::Front;
  using HeapVec<Data>::Back;
  using HeapVec<Data>::Exists;
  
protected:

  // Auxiliary functions, if necessary!

  void HeapifyDown(ulong);
  void HeapifyUp(ulong);

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
