#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <unordered_map>
#include <string>

template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

 /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

private:
    /// Add whatever helper functions you need below
    void heapify_down();
    void heapify_up(int index, const T& item);

    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    std::pair<double, T> p = std::make_pair(priority, item);
    store_.push_back(p);
    heapify_up(store_.size()-1, item);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete
  int index = keyToLocation_.find(item)->second;
    if(c_(priority, store_[index].first)){
      store_[index].first = priority;
      heapify_up(index, item);
    }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator,Hasher>::heapify_up(int i, const T& item){
  //if you pushed a new item, add to map
  if(keyToLocation_.find(item) == keyToLocation_.end()){
    keyToLocation_.insert(std::make_pair(item, i));
  }

  while(i >= 0 && store_.size()>1){
    int p = (i-1)/m_;
    if(c_(store_[i].first, store_[p].first)){ //comparator
      //swapping values
      //updating the map for where the value now lives
      typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it = keyToLocation_.find(store_[p].second);
      it->second = i;

      typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it2 = keyToLocation_.find(store_[i].second);
      it2->second = p;
     
      //swap the values in the array
      std::pair<double, T> temp = store_[i];
      store_[i] = store_[p];
      store_[p] = temp;
      i=p;
    }
    else break;
  }

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::heapify_down(){
  int p=0;
  while((unsigned)p <= (store_.size()-1)){
    int start = (m_*p)+1;

    if((unsigned)start >= store_.size()){
      break;
    }

    double smallest = store_[start].first; //smallest priority
    int index = start;
    for(int i=start+1; i<start+m_; i++){
      if((unsigned)i < store_.size()){
        if(c_(store_[i].first, smallest)){
              index = i;
              smallest = store_[i].first;
        }
      }
    } 
    if(store_[index].first < store_[p].first){
    //updating the map for where the value now lives
      typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it = keyToLocation_.find(store_[index].second);
      it->second = (index-1)/m_;
      typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it2 = keyToLocation_.find(store_[(index-1)/m_].second);
      it2->second = index;

    //swapping the values
       if(c_(smallest, store_[p].first)){
         std::pair<double, T> temp = store_[index];
          store_[index] = store_[p];
          store_[p] = temp;
          p = index;
       }
      else break;

     
    }
  }

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
// If we get here we know the heap has at least 1 item
  // Add code to return the top element
    
  return store_[0].second;
}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    typename std::unordered_map<T, size_t, Hasher, TComparator>::iterator it2 = keyToLocation_.find(store_[store_.size()-1].second);
    it2->second = 0;
    keyToLocation_.erase(store_[0].second);

     //swap first and last element
    std::pair<double, T> temp = store_[0];
    store_[0] = store_[store_.size()-1];
    store_[store_.size()-1] = temp;
    store_.pop_back();
    heapify_down();
}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}


#endif