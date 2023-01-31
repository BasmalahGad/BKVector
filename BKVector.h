#ifndef BKVECTOR_BKVECTTOR_H
#define BKVECTOR_BKVECTTOR_H
/**
 * @file BKVector
 * @author Basmala Mohamed Sayed Gad – Khadija Ayman Elsayed Eshra
 * @brief
 * @version 0.5
 * @date 2022-12-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;
/**
 * @brief This class inherits from the c++ class exception to throw an exception.
 *
 */
class InvalidIteratorException : exception{
public:
    InvalidIteratorException(){};
    virtual const char * what() const noexcept override{
        return "Invalid Iterator";
    }
};
/**
 * @brief The main class (Vector),
          that has all the methods, attributes and Iterator class to support the algorithms library.
 *
 * @tparam T
 */
template<class T>
class BKVector{
private:
    T* memoryPtr;
    int vecCapacity;
    int vecSize;
    void increaseCap();

public:
    class Iterator{
    private:
        T* ptr;

    public:
        using iterator_category = random_access_iterator_tag;
        using difference_type   = ptrdiff_t;
        using value_type = T;

        // constructor
        Iterator(T* inPtr):ptr(inPtr){}

        // methods
        /**
         * @brief overloading the * operator to return the value of the pointer
         *
         * @return T&
         */
        T& operator*() const {return *ptr;}
        /**
         * @brief //overloading the -> operator to return the pointer
         *
         * @return T*
         */
        T* operator->() {return ptr;}
        /**
         * @brief overloading the -= operator to decrement the pointer by num
         *
         * @param num
         * @return Iterator&
         */
        Iterator& operator-=(int num){
            ptr -= num;
            return *this;
        }
        /**
         * @brief overloading the += operator to increment the pointer by num
         *
         * @param num
         * @return Iterator&
         */
        Iterator& operator+=(int num){
            ptr += num;
            return *this;
        }
        /**
         * @brief overloading the -- operator to decrement the pointer by 1 (--t)
         *
         * @return Iterator&
         */
        Iterator& operator--(){
            ptr--;
            return *this;
        }
        /**
         * @brief overloading the -- operator to decrement the pointer by 1 (t--)
         *
         * @return Iterator
         */
        Iterator operator--(int){
            Iterator temp = *this;
            --(*this);
            return temp;
        }
        /**
         * @brief overloading the ++ operator to increment the pointer by 1 (++t)
         *
         * @return Iterator&
         */
        Iterator& operator++(){
            ptr++;
            return *this;
        }

        /**
         * @brief overloading the ++ operator to increment the pointer by 1 (t++)
         *
         * @return Iterator
         */
        Iterator operator++(int){
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        /**
         * @brief overloading the - operator to return a new iterator that points to the pointer - num
         *
         * @param num
         * @return Iterator
         */
        Iterator operator-(int num){
            ptr -= num;
            return *this;
        }
        /**
         * @brief overloading the + operator to return a new iterator that points to the pointer + num
         *
         * @param num
         * @return Iterator
         */
        Iterator operator+(int num){
            ptr += num;
            return *this;
        }
        /**
         * @brief overloading the - operator to return the difference between the two pointers
         *
         * @param another
         * @return int
         */
        int operator-(const Iterator& another){
            return (ptr - another.ptr);
        }
        /**
         * @brief overloading the == operator to return true if the two pointers are equal
         *
         * @param it1
         * @param it2
         * @return true
         * @return false
         */
        friend bool operator==(const Iterator& it1, const Iterator& it2){
            return (it1.ptr == it2.ptr);
        }
        /**
         * @brief overloading the != operator to return true if the two pointers are not equal
         *
         * @param it1
         * @param it2
         * @return true
         * @return false
         */
        friend bool operator!=(const Iterator& it1, const Iterator& it2){
            return (it1.ptr != it2.ptr);
        }
        /**
         * @brief overloading the <= operator to return true if the first pointer is less than or equal to the second pointer
         *
         * @param it1
         * @param it2
         * @return true
         * @return false
         */
        friend bool operator<=(const Iterator& it1, const Iterator& it2){
            return (it1.ptr <= it2.ptr);
        }
        /**
         * @brief overloading the >= operator to return true if the first pointer is greater than or equal to the second pointer
         *
         * @param it1
         * @param it2
         * @return true
         * @return false
         */
        friend bool operator>=(const Iterator& it1, const Iterator& it2){
            return (it1.ptr >= it2.ptr);
        }
        /**
         * @brief overloading the < operator to return true if the first pointer is less than the second pointer
         *
         * @param it1
         * @param it2
         * @return true
         * @return false
         */
        friend bool operator<(const Iterator& it1, const Iterator& it2){
            return (it1.ptr < it2.ptr);
        }
        /**
         * @brief overloading the > operator to return true if the first pointer is greater than the second pointer
         *
         * @param it1
         * @param it2
         * @return true
         * @return false
         */
        friend bool operator>(const Iterator& it1, const Iterator& it2){
            return (it1.ptr > it2.ptr);
        }
    };

    // initializer list
    BKVector(initializer_list<T>);

    // constructors
    BKVector();
    BKVector(int);
    BKVector(T*, int); // copy array into vector
    BKVector (const BKVector&); // copy constructor
    BKVector (const BKVector&&); // move constructor

    // destructor
    /**
     * @brief Destroy the BKVector object
     *
     */
    ~BKVector(){
        delete[] memoryPtr;
    }

    // operators
    T& operator[](int);

    // copy assignment
    BKVector& operator=(const BKVector&);
    // move assignment
    BKVector& operator=(const BKVector&&);

    // methods
    int push_back(T);
    void clear();
    T pop_back();
    int resize(int);
    void insert(Iterator, T);
    void erase(Iterator);
    void erase(Iterator, Iterator);

    // capacity operations
    int size() const;
    int capacity() const;
    bool empty();

    // friends functions
    /**
     * @brief verloading the << operator to print the vector
     *
     * @param out
     * @param output
     * @return ostream&
     */
    friend ostream& operator<< (ostream& out, const BKVector<T>& output){
        for (int i = 0; i < output.vecSize; ++i) {
            out << output.memoryPtr[i] << " ";
        }
        return out;
    }

    // comparison operations
    bool operator==(const BKVector<T>&);
    bool operator< (const BKVector<T>&);
    bool operator> (const BKVector<T>&);

    // iterators
    Iterator begin(){return Iterator(& memoryPtr[0]);}
    Iterator end(){return Iterator(& memoryPtr[vecSize]);}


};

#endif //BKVECTOR_BKVECTTOR_H
