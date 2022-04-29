
#include <cstdio>
#include <algorithm>
#include <cmath>
#define  OUT_OF_RANGE_MSG "YOUR INDEX IS OUT OF RANGE"
#define STATIC_CAP 16
template<typename T,size_t C=16>


class vl_vector{
  T* vector;
  T static_vec[C];
  size_t static_capacity{};
  size_t elem_num{};
  size_t capacity_{};


  int capacity_func(int elem_num, int number_of_elem_to_add);
  T* reallocate_vector( T* old_vector, T* new_vector);


 public:
  vl_vector();

  vl_vector ( const vl_vector<T, C> &other)
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

//builds an empty vector
template<typename T, size_t C>
vl_vector<T, C>::vl_vector (): vector(nullptr), static_vec(),
                               static_capacity(C), elem_num(0), capacity_(C)
{
}

//copy constructor

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
      T* new_arr = new  T [capacity_];
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


//single-value constructor
template<typename T, size_t C>
vl_vector<T, C>::vl_vector (size_t c, const T& value): vector(nullptr),
                                                       static_capacity(C), elem_num(0)
{
  if (c <= this->static_capacity)
    {
      this->capacity_ = C;
      for (int i = 0; i < c; i++)
        {
          static_vec[i] = value;
          this->elem_num++;
        }
    }
  else
    {
      this->capacity_ = capacity_func (0, c);
      T* new_arr = new T(capacity_);
      for (int i = 0; i < c; i++)
        {
          new_arr[i] = value;
          this->elem_num++;
        }
      this->vector = new_arr;
    }
}


//destructor
template<typename T, size_t C>
vl_vector<T, C>::~vl_vector ()
{
  if (size()> this->static_capacity)
    {
      delete[] vector;
      vector= nullptr;
    }

}
template<typename T, size_t C>
size_t vl_vector<T, C>::size ()
{
  return this->elem_num;
}

template<typename T, size_t C>
size_t vl_vector<T, C>::capacity()
{
  return this-> capacity_;
}

template<typename T, size_t C>
bool vl_vector<T, C>::empty ()
{
  return !(this->elem_num);
}

template<typename T, size_t C>
T& vl_vector<T, C>::at (int index)
{
  if (index>= this->elem_num)
    {
      throw std::out_of_range("blah");
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

template<typename T, size_t C>
typename vl_vector<T, C>::iterator  vl_vector<T, C>::insert
    (vl_vector::iterator position, const T &value)
{
  if (elem_num + 1 <= static_capacity)
    {
      int seg_size = seg_size_func (begin(), position);
      std::copy_backward(position, this->end(), this->end()+1);
      *position = value;
      elem_num++;
      return position;
    }
  else
    {
      int seg_size1 = seg_size_func (begin(), position);
      if(elem_num == this->static_capacity)
        {
          this->capacity_ = capacity_func (this->elem_num,1);
          T *new_arr = new T[this->capacity_];
          this->vector = new_arr;
          std::copy (begin (), this->end (), this->vector);
          elem_num++;
          std::copy_backward (begin () + seg_size1, this->end (),
                              this->end() + 1);
          *(begin() + seg_size1) = value;
          return (begin() + seg_size1);
        }
      if (elem_num + 1 > capacity_)
        {
          this->capacity_ = capacity_func (this->elem_num,
                                           1);
          T *new_arr = new T[this->capacity_];
          this->vector = reallocate_vector (this->vector,
                                            new_arr);
          elem_num++;
          std::copy_backward(begin()+seg_size1, this->end(), this->end() +
                                                             1);
          *(begin()+seg_size1) = value;
          return begin()+seg_size1;
        }
      elem_num++;
      std::copy_backward(begin()+seg_size1, this->end()-1, this->end());
      *(begin()+seg_size1) = value;
      return begin()+seg_size1;
    }
}



template<typename T, size_t C>
template<class InputIterator>
typename vl_vector<T, C>::iterator vl_vector<T, C>::insert
    (vl_vector<T, C>::iterator position, InputIterator first, InputIterator last)
{
  int segment_size = seg_size_func (first, last);
  if (elem_num + segment_size <= static_capacity)
    {
      std::copy_backward(position, this->end(), this->end()
                                                +segment_size);
      iterator temp = position;
      while (first!= last)
        {
          *position = *first;
          position++;
          first++;
        }
      this->elem_num+=segment_size;
      return temp;
    }
  else
    {
      int segment_size2 = 0;
      vl_vector<T, C>::iterator temp = begin();
      while (temp!= position)
        {
          segment_size2++;
          temp++;
        }
      if (elem_num + segment_size > capacity_)
        {
          this->capacity_ = capacity_func (this->elem_num,
                                           segment_size);
          T *new_arr = new T[this->capacity_];
          if (this->vector)
            {
              this->vector = reallocate_vector (this->vector,
                                                new_arr);
            }
          else
            {
              this->vector= new_arr;
              std::copy (this->begin (), this->end (), this->vector);
            }
        }
      elem_num+=segment_size;
      T *new_arr = new T[this->capacity_];
      for (int i = 0; i < this->elem_num; i++)
        {
          new_arr[i] = this->vector[i];
        }
      int j=0;
      for(auto i = this->vector+segment_size2+segment_size; i!=end();
          i++)
        {
          *(i )=* (new_arr+segment_size2+j);
          j++;
        }
      delete[] new_arr;
      vl_vector<T, C>::iterator temp1 = begin()+segment_size2;
      while (first!= last)
        {
          *(temp1) = *first;
          temp1++;
          first++;
        }
      return begin()+segment_size2;
    }
}



template<typename T, size_t C>
void vl_vector<T, C>::pop_back ()
{
  if (!elem_num)
    {return;}
  this->elem_num--;
  if (vector && elem_num <=static_capacity)
    {
      this->capacity_ = this->static_capacity;
      std::copy (vector, vector+elem_num, static_vec);
      delete [] vector;
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



template<typename T, size_t C>
typename vl_vector<T, C>::iterator vl_vector<T, C>::erase
    (vl_vector<T, C>::iterator first, vl_vector<T, C>::iterator last)
{
  vl_vector<T, C>::iterator temp1 = first;
  vl_vector<T, C>::iterator temp2 = last;
  std::copy (temp2, this->end(), temp1);
  int segment_size = seg_size_func (first, last);
  if(elem_num<=static_capacity)
    {
      elem_num-=segment_size;
      return first;
    }
  if(elem_num- segment_size<=static_capacity)
    {
      int segment_size2 = 0;
      vl_vector<T, C>::iterator temp = begin();
      while (temp!= first)
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

template<typename T, size_t C>
T *vl_vector<T, C>::data ()
{
  if (elem_num <=static_capacity)
    {
      return static_vec;
    }
  else
    {
      return this->vector;
    }
}

template<typename T, size_t C>
const T *vl_vector<T, C>::data () const
{
  if (elem_num <static_capacity)
    {
      return static_vec;
    }
  else
    {
      return vector;
    }
}



template<typename T, size_t C>
bool vl_vector<T, C>::contains (T input)
{
  if (elem_num <static_capacity)
    {
      for(int i = 0; i< elem_num; i++)
        {
          if (static_vec[i]==input)
            {
              return true;
            }
        }
      return false;
    }
  else
    {
      for(int i = 0; i< elem_num; i++)
        {
          if (vector[i]==input)
            {
              return true;
            }
        }
      return false;
    }
}


template<typename T, size_t C>
vl_vector<T, C>& vl_vector<T, C>::operator= (const vl_vector<T, C>
                                             &other)
{
  if (this != &other)
    {
      this->elem_num = other.elem_num;
      this->static_capacity= other.static_capacity;
      this->capacity_= other.capacity_;
      if(this->elem_num> this->static_capacity)
        {
          delete[] this->vector;
        }
      if (other.elem_num < other.static_capacity)
        {
          std::copy (other.static_vec, other.static_vec + other.elem_num, this->static_vec);
        }
      else
        {
          T *new_arr = new T [other.capacity_];
          std::copy (other.vector, other.vector + other.elem_num, new_arr);
          this->vector = new_arr;
        }
    }
  return *this;
}

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


template<typename T, size_t C>
bool vl_vector<T, C>::operator== (const vl_vector<T, C> &other)
{
  if(elem_num!=other.elem_num ||capacity_!= other.capacity_)
    {
      return false;
    }
  if(elem_num <static_capacity)
    {
      for (int i = 0; i < elem_num; i++)
        {
          if (this->static_vec[i] != other.static_vec[i])
            {
              return false;
            }
        }
    }
  else
    {
      for(int i = 0; i<elem_num; i++)
        {
          if (this->vector[i] != other.vector[i])
            {
              return false;
            }
        }
    }
  return true;
}



template<typename T, size_t C>
bool vl_vector<T, C>::operator!= (const vl_vector<T, C> &other)
{
  if(elem_num!= other.elem_num|| capacity_!= other.capacity_ || static_capacity!= other.static_capacity)
    {
      return true;
    }
  if(elem_num <static_capacity)
    {
      for (int i = 0; i < elem_num; i++)
        {
          if (this->static_vec[i] != other.static_vec[i])
            {
              return true;
            }
        }
    }
  else
    {
      if (!vector|| !other.vector)
        {
          return true;
        }
      for(int i = 0; i<elem_num; i++)
        {
          if (this->vector[i] != other.vector[i])
            {
              return true;
            }
        }
    }
  return false;
}



