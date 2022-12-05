//
// Created by Tanya Fainstein on 05/12/2022.
//

#ifndef _VL_VECTOR_H_
#define _VL_VECTOR_H_


#include <cstdio>
#include <algorithm>
#include <cmath>
#define  OUT_OF_RANGE_MSG "YOUR INDEX IS OUT OF RANGE"
#define STATIC_CAP 16
template<typename T,size_t C=STATIC_CAP>

/**
 *Vl_vector, container, that is similar to std::vector, but more efficient, due to use of stack and heap,
 * according to its size.
 * @tparam T
 * @tparam C Capacity
 */
class vl_vector{
  //default initialised as private
  T* vector;
  T static_vec[C];
  size_t static_capacity{};
  size_t elem_num{};
  size_t capacity_{};


  int capacity_func(int elem_num, int number_of_elem_to_add);
  T* reallocate_vector( T* old_vector, T* new_vector);


 public:
  vl_vector();

  vl_vector ( const vl_vector<T, C> &other);
  template<class InputIterator>
  vl_vector(InputIterator first, InputIterator last);
  vl_vector(size_t c, const T& value);
  ~vl_vector();

  //operators//
  //======================================================================

  vl_vector<T, C> & operator =(const vl_vector<T, C> &other);
  T& operator [](size_t index);
  const T& operator [](size_t index) const;
  bool operator ==(const vl_vector<T, C> &other);
  bool operator !=(const vl_vector<T, C> &other);

  //iterators//
  // =====================================================================

  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator ;

  //regular iterator: const and non_const version
  iterator begin ()
  {
    return data();
  }
  const_iterator begin () const
  {
    return data();
  }
  const_iterator cbegin () const
  {
    return data();
  }
  iterator end ()
  {
    return data()+elem_num;
  }
  const_iterator end () const
  {
    return data()+elem_num;
  }
  const_iterator cend () const
  {
    data()+elem_num;
  }

  //reverse iterator: const and non const version
  reverse_iterator rbegin ()
  {
    return reverse_iterator(data()+ elem_num);
  }

  const_reverse_iterator rbegin () const
  {
    return const_reverse_iterator(data()+ elem_num);
  }
  const_reverse_iterator crbegin ()  const
  {
    return const_reverse_iterator(data()+ elem_num);
  }
  reverse_iterator rend ()
  {
    return reverse_iterator(begin());;
  }
  const_reverse_iterator rend () const
  {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crend () const
  {
    return const_reverse_iterator(begin());

  }


  //end of iterators
  // ===================================================================


  //Actions//
  //======================================================================

  size_t size();//returns size in o(1)
  size_t capacity();//returns_the_capacity
  bool empty();// checks if is empty
  T& at(int index); //returns the value that is storred at index
  const T& at(int index) const; //const version of above
  void push_back( const T& value);
  iterator insert(iterator position, const T& value);
  template<class InputIterator>
  iterator insert(iterator position, InputIterator first,
                  InputIterator last);
  void pop_back();
  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);
  void clear();
  T* data();
  const T *data () const;
  bool contains(T input);



};
//implementation
// ===========================================================================


/**
 * Constructor, that builds an empty vector.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 */
template<typename T, size_t C>
vl_vector<T, C>::vl_vector (): vector(nullptr), static_vec(),
                               static_capacity(C), elem_num(0), capacity_(C)
{
}

/**
 * Helper function of the Sequence based Constructor. Counts the size of the segment.
 * @tparam InputIterator Input iterator.
 * @param first first element.
 * @param last last element.
 * @return  size of segment.
 */
template<class InputIterator>
int seg_size_func(InputIterator first, InputIterator last)
{
  int segment_size = 0;
  while (first!= last)
    {
      segment_size++;
      first++;
    }

  return segment_size;
}


/**
 * Copy constructor.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param other vl_vector to copy
 */
template<typename T, size_t C>
vl_vector<T, C>::vl_vector ( const vl_vector<T, C> &other)
{
  this->static_capacity = other.static_capacity;
  this->elem_num = other.elem_num;
  this->capacity_ = other.capacity_;

  if(other.elem_num > other.static_capacity)

    {
      T* new_arr = new  T [capacity_];
      std::copy (other.vector, other.vector + other.elem_num, new_arr);
      this->vector = new_arr;
    }
  else
    {
      this->vector= nullptr;
      std::copy (other.static_vec, other.static_vec + other.elem_num,
                 this->static_vec);
    }
}





/**
 * Sequence based Constructor, that gets as input Input iterator and saves the values in the vector.
 * @tparam InputIterator Input Iterator.
 * @param first first element.
 * @param last last element.
 */
template<typename T, size_t C>
template<class InputIterator>
vl_vector<T, C>::vl_vector (InputIterator first, InputIterator last):
    vector(nullptr), static_capacity(C), elem_num(0), capacity_(C)

{
  int segment_size = seg_size_func (first, last);
  if (segment_size<=this->static_capacity)
    {
      int i = 0;
      while(first!= last)
        {
          static_vec[i] = *first;
          this->elem_num++;
          first++;
          i++;
        }
    }
  else
    {
      this->capacity_= capacity_func (0, segment_size);
      T* new_arr = new T [capacity_];
      int i = 0;
      while(first!= last)
        {
          new_arr[i] = *first;
          i++;
          first++;
          this->elem_num++;
        }
      this->vector = new_arr;

    }
}



/**
 * Single value constructor. gets as input value and number of objects to create and creates c elements
 * with value value.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param count  number of elements
 * @param value values
 */
template<typename T, size_t C>
vl_vector<T, C>::vl_vector (size_t count, const T& value): vector(nullptr),
                                                       static_capacity(C), elem_num(0)
{
  if (count <= this->static_capacity)
    {
      this->capacity_ = C;
      for (int i = 0; i < count; i++)
        {
          static_vec[i] = value;
          this->elem_num++;
        }
    }
  else
    {
      this->capacity_ = capacity_func (0, count);
      T* new_arr = new T(capacity_);
      for (int i = 0; i < count; i++)
        {
          new_arr[i] = value;
          this->elem_num++;
        }
      this->vector = new_arr;
    }
}


/**
 * Destructor
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 */
template<typename T, size_t C>
vl_vector<T, C>::~vl_vector ()
{
  if (size()> this->static_capacity)
    {
      delete[] vector;
      vector= nullptr;
    }

}

/**
 * Method that returns number of elements in the vector at this time.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @return Number of elements in the vector at this time.
 */
template<typename T, size_t C>
size_t vl_vector<T, C>::size ()
{
  return this->elem_num;
}



/**
 * Method that returns capacity of  the vector at this time.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @return Capacity of  the vector at this time.
 */
template<typename T, size_t C>
size_t vl_vector<T, C>::capacity()
{
  return this-> capacity_;
}



/**
 * Method that returns boolean of the emptiness of the vector.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @return true if vector is empty, else false.
 */
template<typename T, size_t C>
bool vl_vector<T, C>::empty ()
{
  return !(this->elem_num);
}



/**
 * Returns the element at the index.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param index 
 * @return element at the index, if index is valid. Else, throws mistake.
 */
template<typename T, size_t C>
T& vl_vector<T, C>::at (int index)
{
  if (index>= this->elem_num)
    {
      throw std::out_of_range("YOUR INDEX IS OUT OF RANGE");
    }
  if (this->elem_num<= this->static_capacity)
    {
      return static_vec[index];
    }
  else
    {
      return vector[index];
    }
}


/**
 * Returns the element at the index, const vertion
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param index
 * @return element at the index, if index is valid. Else, throws mistake.
 */
template<typename T, size_t C>
const T& vl_vector<T, C>::at (int index) const
{
  if (index >= this->elem_num)
    {
      throw std::out_of_range (OUT_OF_RANGE_MSG);
    }
  if (this->elem_num <= this->static_capacity)
    {
      return static_vec[index];
    }
  else
    {
      return vector[index];
    }
}




template<typename T, size_t C>
int vl_vector<T, C>::capacity_func (int elem_num_, int number_of_elem_to_add)
{
  int value_to_return = 3*(elem_num_+ number_of_elem_to_add)/2;
  return value_to_return;
}

template<typename T, size_t C>
T* vl_vector<T, C>::reallocate_vector (T *old_vector, T *new_vector)
{
  if(!old_vector)
    {
      T *new_arr1 = new T[this->capacity_];
      old_vector = new_arr1;
    }
  for (int i = 0; i < this->elem_num; i++)
    {
      new_vector[i] = old_vector[i];
    }
  delete[] old_vector;
  old_vector= nullptr;
  return new_vector;
}

/**
 * push_back method. The method gets as input an element and adds it tho the end of the vl_vector.(Uses the method
 * insert)
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param value Element to add.
 */
template<typename T, size_t C>
void vl_vector<T, C>::push_back ( const T& value)
{
  if (this->elem_num < this->static_capacity)
    {
      static_vec[elem_num] = value;
      elem_num++;
    }
  else
    {
      insert (end (), value);
    }
}



/**
 * insert method(first version). Gets as input element to add and the position(pointer to certain element in the vector)
 * The method will add this element before the position(on the left). and will return the position(pointer) to
 * a new element.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param position Position to add.
 * @param value  Element to add.
 * @return position(iterator)
 */
template<typename T, size_t C>
typename vl_vector<T, C>::iterator  vl_vector<T, C>::insert(vl_vector::iterator position, const T &value)
{
  if (elem_num + 1 <= static_capacity)
    {
      std::copy_backward(position, this->end(), this->end()+1);
      *position = value;
      elem_num++;
      return position;
    }
  else
    {
      int seg_size = seg_size_func (begin(), position);
      if(elem_num == this->static_capacity)
        {
          this->capacity_ = capacity_func (this->elem_num,1);
          T *new_arr = new T[this->capacity_];
          this->vector = new_arr;
          std::copy (this->begin(), this->end(), this->vector);
          elem_num++;
          std::copy_backward (begin () + seg_size, this->end(),
                              this->end() + 1);
          *(begin()+seg_size) = value;
          return (begin()+seg_size);
        }
      if (elem_num + 1 > capacity_)
        {
          this->capacity_ = capacity_func (this->elem_num,
                                           1);
          T *new_arr = new T[this->capacity_];
          this->vector = reallocate_vector (this->vector,
                                            new_arr);
          elem_num++;
          std::copy_backward(begin()+seg_size, this->end(), this->end() +
                                                             1);
          *(begin()+seg_size) = value;
          return begin()+seg_size;
        }
      elem_num++;
      std::copy_backward(begin()+seg_size, this->end()-1, this->end());
      *(begin()+seg_size) = value;
      return begin()+seg_size;
    }
}


/**
 * insert method(second version). Gets as input iterator that points to the certain element in the vector, and two
 * variables that represent the segment that we will insert before(on the left) of the position.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @tparam InputIterator InputIterator.
 * @param position  certain element in the vector, that before it we want to insert our segment.
 * @param first start of the segment(iterator).
 * @param last end of the vector(iterator).
 * @return iterator that points to the first element of the new segment elements.
 */
template<typename T, size_t C>
template<class InputIterator>
typename vl_vector<T, C>::iterator vl_vector<T, C>::insert
    (vl_vector<T, C>::iterator position, InputIterator first, InputIterator last)
{
  int segment_size = seg_size_func(first, last);
  if (elem_num + segment_size <= static_capacity){// if we work with the static version it is simple, just move and copy
      std::copy_backward(position, this->end(), this->end()+segment_size);
      iterator temp = position;
      while (first!= last){
          *position = *first;
          position++;
          first++;
        }
      this->elem_num+=segment_size;
      return temp;
    }
  else{// here we will need more work
      int segment_size2 = 0;
      vl_vector<T, C>::iterator temp = begin();
      while (temp!= position){
          segment_size2++;
          temp++;
        }
      if (elem_num + segment_size > capacity_){// here we need to resize our vector according to our new sizes
        // and place the old values to the new place
          this->capacity_ = capacity_func(this->elem_num,
                                           segment_size);
          T *new_arr = new T[this->capacity_];
          if (this->vector){// if we did have dynamic vector before
              this->vector = reallocate_vector (this->vector,
                                                new_arr);
            }
          else{// if we did not have dynamic vector before
              this->vector= new_arr;
              std::copy (this->begin (), this->end (), this->vector);
            }
        }

      elem_num+=segment_size;
      T *new_arr = new T[this->capacity_];// here we copy the array, so we won't lose the values at the next step,
      // if we would not do it there was a chance of stepping on the values.
      for (int i = 0; i < this->elem_num; i++)
        {
          new_arr[i] = this->vector[i];
        }
      int j=0;
      for(auto i = this->vector+segment_size2+segment_size; i!=end();// here we move elements from the "position" till
      // the end to the new position that is after the new elements that will be inserted
          i++){
          *i=* (new_arr+segment_size2+j);
          j++;
        }
      delete[] new_arr;// no more need in new_arr, free the memory!
      vl_vector<T, C>::iterator temp1 = begin()+segment_size2;// insertion of the new elements
      while (first!= last)
        {
          *(temp1) = *first;
          temp1++;
          first++;
        }
      return begin()+segment_size2;
    }
}


/**
 * pop_back method. The method deletes the last element in the vector.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 */
template<typename T, size_t C>
void vl_vector<T, C>::pop_back ()
{
  if (!elem_num){return;}
  this->elem_num--;// if we are in static case, it is enough to do just that
  if (vector && (elem_num <=static_capacity)){
      this->capacity_ = this->static_capacity;
      std::copy (vector, vector+elem_num, static_vec);
      delete [] vector;// do not forget to free
      vector = nullptr;
    }
}
template<typename T, size_t C>
typename vl_vector<T, C>::iterator vl_vector<T, C>::erase
    (vl_vector<T, C>::iterator position)
{
  int stat_cap = this->static_capacity;
  std::copy_backward(position+1, this->end(), end()-1 );
  if( elem_num>static_capacity &&elem_num-1<=static_capacity)
    {
      int segment_size2 = 0;
      vl_vector<T, C>::iterator temp = begin();
      while (temp!= position)
        {
          segment_size2++;
          temp++;
        }
      std::copy(this->vector, this->vector+ this->elem_num,
                static_vec);

      elem_num--;
      this->capacity_ = stat_cap;
      delete[] this->vector;
      this->vector = nullptr;
      vl_vector<T, C>::iterator temp2 = begin()+segment_size2;

      position = temp2;
    }
  else
    {
      elem_num--;
    }
  return position;
}


/**
 * The method gets 2 iterators that represent a segment in the vector and deletes this segment in the vector.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param first from here we need to delete.
 * @param last until here we want to delete.
 * @return we will return the iterator that points to a element that is on the right of the last element.
 */
template<typename T, size_t C>
typename vl_vector<T, C>::iterator vl_vector<T, C>::erase
    (vl_vector<T, C>::iterator first, vl_vector<T, C>::iterator last)
{
  vl_vector<T, C>::iterator temp1 = first;
  vl_vector<T, C>::iterator temp2 = last;
  std::copy (temp2, this->end(), temp1);
  int segment_size = seg_size_func (first, last);
  if(elem_num<=static_capacity)// if we was at the static version
    {
      elem_num-=segment_size;
      return first;
    }
  if(elem_num- segment_size<=static_capacity)// if after we deleted the elements we will enter to the stack,
    // and before we were at the heap
    {
      int segment_size2 = 0;
      vl_vector<T, C>::iterator temp = begin();
      while (temp!= first)// it is the same as func as seg_size_func
        {
          segment_size2++;
          temp++;
        }
      elem_num-=segment_size;
      for(int i =0; i<elem_num; i++)
        {
          this->static_vec[i] = this->vector[i];
        }
      this->capacity_ = static_capacity;
      delete[] vector;
      this->vector = nullptr;
      return begin()+segment_size2;
    }
  else
    {
      elem_num-=segment_size;
    }
  return first;

}

/**
 * deletes all the elements in the vector
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 */
template<typename T, size_t C>
void vl_vector<T, C>::clear ()
{
  if (elem_num >static_capacity)
    {
      delete[] vector;
      vector= nullptr;
    }
  this->elem_num = 0;
  this->capacity_= this->static_capacity;
}



/**
 * Returns the vector that now holds the data in the moment
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @return static vector or dynamic vector.
 */
template<typename T, size_t C>
T *vl_vector<T, C>::data ()
{
  if (elem_num <=static_capacity){
      return this->static_vec;
    }
  else{
      return this->vector;
    }
}
/**
 * Returns the vector that now holds the data in the moment(const version).
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @return static vector or dynamic vector.
 */
template<typename T, size_t C>
const T *vl_vector<T, C>::data () const{
  if (elem_num <static_capacity){
      return static_vec;
    }
  else{
      return vector;
    }
}


/**
 * The method gets as input the value of T type and returns boolean version of if it is in the array.
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param input  element to check.
 * @return bool value.
 */

template<typename T, size_t C>
bool vl_vector<T, C>::contains (T input)
{
  if (elem_num <static_capacity){
      for(int i = 0; i< elem_num; i++){
          if (static_vec[i]==input){
              return true;
            }
        }
      return false;
    }
  else{
      for(int i = 0; i< elem_num; i++){
          if (vector[i]==input){
              return true;
            }
        }
      return false;
    }
}

// operators implementation
/**
 * Implementation of operator = .
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param other other vector
 * @return vector
 */
template<typename T, size_t C>
vl_vector<T, C>& vl_vector<T, C>::operator= (const vl_vector<T, C>
                                             &other){
  if (this != &other){
      if(this->elem_num > this->static_capacity){
          delete[] this->vector;
        }
      this->elem_num = other.elem_num;
      this->static_capacity= other.static_capacity;
      this->capacity_= other.capacity_;
    
      if (other.elem_num < other.static_capacity){
          std::copy (other.static_vec, other.static_vec + other.elem_num, this->static_vec);
        }
      else{
          T *new_arr = new T [other.capacity_];
          std::copy (other.vector, other.vector + other.elem_num, new_arr);
          this->vector = new_arr;
        }
    }
  return *this;
}




/**
 * Implementation of operator[]
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param index index.
 * @return  value.
 */
template<typename T, size_t C>
T &vl_vector<T, C>::operator[] (size_t index)
{
  if(elem_num <=static_capacity)
    {
      return this->static_vec[index];
    }
  else
    {
      return this->vector[index];
    }

}


/**
 * Implementation of operator[](const version)
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param index index.
 * @return  value.
 */
template<typename T, size_t C>
const T& vl_vector<T, C>::operator[] (size_t index) const
{
  if(elem_num <=static_capacity)
    {
      return this->static_vec[index];
    }
  else
    {
      return this->vector[index];
    }
}




/**
 * Implementation of operator == .
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param other other vector
 * @return bool
 */
template<typename T, size_t C>
bool vl_vector<T, C>::operator== (const vl_vector<T, C> &other)
{
  if(elem_num!=other.elem_num ||capacity_!= other.capacity_)
    {
      return false;
    }
  if(elem_num <static_capacity){
      for (int i = 0; i < elem_num; i++){
          if (this->static_vec[i] != other.static_vec[i]){
              return false;
            }
        }
    }
  else{
      for(int i = 0; i<elem_num; i++){
          if (this->vector[i] != other.vector[i]){
              return false;
            }
        }
    }
  return true;
}


/**
 * Implementation of operator != .
 * @tparam T type of elements in vector.
 * @tparam C Capacity.
 * @param other other vector
 * @return bool
 */
template<typename T, size_t C>
bool vl_vector<T, C>::operator!= (const vl_vector<T, C> &other)
{
  if(elem_num!= other.elem_num|| capacity_!= other.capacity_ || static_capacity!= other.static_capacity)
    {
      return true;
    }
  if(elem_num <static_capacity){
      for (int i = 0; i < elem_num; i++){
          if (this->static_vec[i] != other.static_vec[i]){
              return true;
            }
        }
    }
  else{
      if (!vector|| !other.vector){
          return true;
        }
      for(int i = 0; i<elem_num; i++){
          if (this->vector[i] != other.vector[i]){
              return true;
            }
        }
    }
  return false;
}





#endif //_VL_VECTOR_H_
