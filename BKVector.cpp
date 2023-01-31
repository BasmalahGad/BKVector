#include "BKVector.h"

/**
 * @brief increases the capacity of the vector by doubling it
 *
 * @tparam T
 */
template<class T> void BKVector<T>::increaseCap(){
    vecCapacity *= 2;
    T* newPtr = new T[vecCapacity];
    for (int i = 0; i < vecSize; ++i) {
        newPtr[i] = memoryPtr[i];
    }
    delete[] memoryPtr;
    memoryPtr = newPtr;
    for (int i = vecSize; i < vecCapacity; ++i) {
        memoryPtr[i] = 0;
    }
}

// initializer list
/**
 * @brief initializes the vector with the values in the initializer list
 *
 * @tparam T
 * @param list
 */
template<class T> BKVector<T>::BKVector(initializer_list<T> list) {
    vecSize = list.size();
    vecCapacity = list.size();
    memoryPtr = new T[vecCapacity];
    auto it = list.begin();
    for (int i = 0; i < vecSize; ++i) {
        memoryPtr[i] = *it;
        it++;
    }
}

// constructors
/**
 * @brief default constructor
 *
 * @tparam T
 */
template<class T> BKVector<T>::BKVector():vecCapacity(10), vecSize(0){
    memoryPtr = new T[vecCapacity];
}
/**
 * @brief constructor that takes the capacity
 *
 * @tparam T
 * @param cap
 */
template<class T> BKVector<T>::BKVector(int cap) : vecCapacity(cap), vecSize(0){
    memoryPtr = new T[cap];

    for (int i = 0; i < vecCapacity; ++i) {
        memoryPtr[i] = 0;
    }
}
/**
 * @brief constructor that takes an array and the size of the array
 *
 * @tparam T
 * @param arr
 * @param n
 */
template<class T> BKVector<T>::BKVector(T* arr, int n) : vecCapacity(n), vecSize(n){
    memoryPtr = new T[n];

    for (int i = 0; i < n; ++i) {
        memoryPtr[i] = arr[i];
    }
}
/**
 * @brief copy constructor
 *
 * @tparam T
 * @param another
 */
template<class T> BKVector<T>::BKVector(const BKVector& another){
    if(&another != this){
        vecSize = another.vecSize;
        vecCapacity = another.vecCapacity;
        memoryPtr = new T[vecCapacity];

        for (int i = 0; i < vecCapacity; ++i) {
            memoryPtr[i] = another.memoryPtr[i];
        }
    }
}
/**
 * @brief move constructor
 *
 * @tparam T
 * @param another
 */
template<class T> BKVector<T>::BKVector (const BKVector&& another){
    if(&another != this){
        vecSize = another.vecSize;
        vecCapacity = another.vecCapacity;
        memoryPtr = another.memoryPtr;
        another.memoryPtr = nullptr;
    }
}

// operators
/**
 * @brief overloading the [] operator to return the value at the index
 *
 * @tparam T
 * @param i
 * @return T&
 */
template<class T> T& BKVector<T>:: operator[](int i){
    if( (i < 0) || (i > vecSize)){throw out_of_range ("Invalid Index");}
    return memoryPtr[i];
}
// copy assignment
/**
 * @brief copy assignment
 *
 * @tparam T
 * @param another
 * @return BKVector<T>&
 */
template<class T> BKVector<T>& BKVector<T> :: operator= (const BKVector& another) {
    if(&another != this){
        delete[] memoryPtr;
        vecSize = another.vecSize;
        vecCapacity = another.vecCapacity;
        memoryPtr = new T[vecCapacity];

        for (int i = 0; i < vecCapacity; ++i) {
            memoryPtr[i] = another.memoryPtr[i];
        }
    }
}
// move assignment
/**
 * @brief move assignment
 *
 * @tparam T
 * @param another
 * @return BKVector<T>&
 */
template<class T> BKVector<T>& BKVector<T> :: operator= (const BKVector&& another){
    if(&another != this){
        delete[] memoryPtr;
        vecSize = another.vecSize;
        vecCapacity = another.vecCapacity;
        memoryPtr = another.memoryPtr;
        another.memoryPtr = nullptr;
    }
}

// methods
/**
 * @brief adds an item to the end of the vector
 *
 * @tparam T
 * @param item
 * @return int
 */
template<class T> int BKVector<T>::push_back(T item){
    if(vecSize >= vecCapacity){
        increaseCap();
    }
    memoryPtr[vecSize] = item;
    vecSize += 1;
    return vecSize;
}
/**
 * @brief clears the vector
 *
 * @tparam T
 */
template<class T> void BKVector<T>::clear(){
    for (int i = 0; i < vecSize; ++i) {
        memoryPtr[i] = 0;
    }
    vecSize = 0;
}
/**
 * @brief removes the last item from the vector
 *
 * @tparam T
 * @return T
 */
template<class T> T BKVector<T>::pop_back(){
    T lastItem = memoryPtr[vecSize - 1];
    vecSize -= 2;
    return lastItem;
}
/**
 * @brief resizes the vector to the given size
 *
 * @tparam T
 * @param sz
 * @return int
 */
template<class T> int BKVector<T>::resize(int sz) {
    if(sz > vecSize){
        T* tempPtr = new T [sz];
        for (int i = 0; i < vecSize; ++i) {
            tempPtr[i] = memoryPtr[i];
        }
        delete[] memoryPtr;
        memoryPtr = tempPtr;
        for (int i = vecSize; i < sz; ++i) {
            tempPtr[i] = 0;
        }
        vecSize = sz;
        vecCapacity = sz;
    }else{
        increaseCap();
    }
    return vecSize;
}
/**
 * @brief inserts an item at the given iterator
 *
 * @tparam T
 * @param it
 * @param item
 */
template<class T> void BKVector<T>::insert(Iterator it, T item) {
    if((it < begin()) || (it > end())){throw InvalidIteratorException();}

    int index = it - begin();
    if(vecSize >= vecCapacity){
        increaseCap();
    }
    T* tempPtr = new T [vecCapacity];
    int j = 0;
    for (int i = 0; i < vecSize; ++i) {
        if(i == index){
            tempPtr[j] = item;
            j++;
        }
        tempPtr[j] = memoryPtr[i];
        j++;
    }
    delete[] memoryPtr;
    memoryPtr = tempPtr;
    vecSize += 1;
}
/**
 * @brief erases the item at the given iterator
 *
 * @tparam T
 * @param it
 */
template<class T> void BKVector<T>::erase(Iterator it) {
    if((it < begin()) || (it > end())){throw InvalidIteratorException();}

    T* tempPtr = new T [vecCapacity - 1];
    int i = 0;
    for (auto itr = begin(); itr != end(); ++itr) {
        if(itr == it){
            continue;
        }
        tempPtr[i] = *itr;
        i++;
    }
    delete[] memoryPtr;
    memoryPtr = tempPtr;
    vecSize -= 1;
}
/**
 * @brief erases the items between the given iterators
 *
 * @tparam T
 * @param it1
 * @param it2
 */
template<class T> void BKVector<T>::erase(Iterator it1, Iterator it2) {
    if(((it1 < begin()) || (it1 > end())) || ((it2 < begin()) || (it2 > end()))){throw InvalidIteratorException();}

    if(it1 <= it2){
        if(it1 == it2){
            this->erase(it1);
            return;
        }
        int removeNum = it2 - it1;
        T* tempPtr = new T [vecCapacity - removeNum];
        int i = 0;
        for (auto itr = begin(); itr != end(); ++itr) {
            if((itr == it1) && (it1 < it2)){
                it1++;
                continue;
            }
            tempPtr[i] = *itr;
            i++;
        }
        delete[] memoryPtr;
        memoryPtr = tempPtr;
        vecSize -= removeNum;
        // 4
    }
}

// capacity methods
/**
 * @brief returns the size of the vector
 *
 * @tparam T
 * @return int
 */
template<class T> int BKVector<T> :: size() const{
    return vecSize;
}
/**
 * @brief returns the capacity of the vector
 *
 * @tparam T
 * @return int
 */
template<class T> int BKVector<T> :: capacity() const{
    return vecCapacity;
}
/**
 * @brief returns true if the vector is empty
 *
 * @tparam T
 * @return true
 * @return false
 */
template<class T> bool BKVector<T> ::empty() {
    return ((vecSize == 0 )? true : false);
}

// comparison operations
/**
 * @brief overloading the == operator to compare two vectors
 *
 * @tparam T
 * @param another
 * @return true
 * @return false
 */
template<class T> bool BKVector<T>::operator==(const BKVector<T>& another) {
    if(vecSize != another.vecSize){
        return false;
    }
    for (int i = 0; i < vecSize; ++i) {
        if(memoryPtr[i] != another.memoryPtr[i]){
            return false;
        }
    }
    return true;
}
/**
 * @brief overloading the < operator to return true if the first vector is less than the second
 *
 * @tparam T
 * @param another
 * @return true
 * @return false
 */
template<class T> bool BKVector<T>::operator< (const BKVector<T>& another) {
    int minSize = min(vecSize, another.vecSize);
    for (int i = 0; i < minSize; ++i) {
        if(memoryPtr[i] < another.memoryPtr[i]){
            return true;
        }
        if (memoryPtr[i] > another.memoryPtr[i]){
            return false;
        }
    }
    if(vecSize < another.vecSize){
        return true;
    }
    if (vecSize > another.vecSize){
        return false;
    }
    return false;
}
/**
 * @brief overloading the > operator to return true if the first vector is greater than the second
 *
 * @tparam T
 * @param another
 * @return true
 * @return false
 */
template<class T> bool BKVector<T>::operator> (const BKVector<T>& another){
    return (!(*this < another) && !(*this == another));
}
