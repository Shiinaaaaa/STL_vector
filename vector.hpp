#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <iostream>
#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {
    public:
        int maxsize = 10;
        int count = 0;
        T **array;
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        class const_iterator;
        class iterator {
        public:
            T **pointer = nullptr;
            vector<T> *v;
            int l = -1;
            /**
             * TODO add data members
             *   just add whatever you want.
             */
        public:
            iterator() = default;
            iterator(T **p , vector<T> *vv , int ll): pointer(p) , v(vv) , l(ll){}
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const {
                iterator tmp(pointer + n , v , l + n);
                return tmp;
                //TODO
            }
            iterator operator-(const int &n) const {
                return iterator(pointer - n , v , l - n);
                //TODO
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (v != rhs.v) throw invalid_iterator();
                return pointer - rhs.pointer;
                //TODO
            }
            iterator& operator+=(const int &n) {
                pointer += n;
                l += n;
                return *this;
                //TODO
            }
            iterator& operator-=(const int &n) {
                pointer -= n;
                l -= n;
                return *this;
                //TODO
            }
            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator tmp = *this;
                pointer++;
                l++;
                return tmp;
            }
            /**
             * TODO ++iter
             */
            iterator& operator++() {
                pointer++;
                l++;
                return *this;
            }
            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator tmp = *this;
                pointer--;
                l--;
                return tmp;
            }
            /**
             * TODO --iter
             */
            iterator& operator--() {
                pointer--;
                l--;
                return *this;
            }
            /**
             * TODO *it
             */
            T& operator*() const{
                return *(*pointer);
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return false;
                else return true;
            }
            bool operator==(const const_iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return false;
                else return true;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return true;
                else return false;
            }
            bool operator!=(const const_iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return true;
                else return false;
            }
        };
        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        private:
            T **pointer;
            const vector<T> *v;
            int l = -1;
        public:
            const_iterator() = default;
            const_iterator(T **p , const vector<T> *vv , int ll): pointer(p) , v(vv) , l(ll){}

            const_iterator operator+(const int &n) const {
                return const_iterator(pointer + n , v , l + n);
            }
            const_iterator operator-(const int &n) const {
                return const_iterator(pointer - n , v , l + n);
            }

            int operator-(const const_iterator &rhs) const {
                if (v != rhs.v) throw invalid_iterator();
                return pointer - rhs.pointer;
            }
            const_iterator& operator+=(const int &n) {
                pointer += n;
                l += n;
                return *this;
            }
            const_iterator& operator-=(const int &n) {
                pointer -= n;
                l -= n;
                return *this;
            }

            const_iterator operator++(int) {
                iterator tmp = *this;
                pointer++;
                l++;
                return tmp;
            }

            const_iterator& operator++() {
                pointer++;
                l++;
                return *this;
            }

            const_iterator operator--(int) {
                iterator tmp = *this;
                pointer--;
                l--;
                return tmp;
            }

            const_iterator& operator--() {
                pointer--;
                l--;
                return *this;
            }

            const T& operator*() const{
                return *(*pointer);
            }

            bool operator==(const iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return false;
                else return true;
            }
            bool operator==(const const_iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return false;
                else return true;
            }
            bool operator!=(const iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return true;
                else return false;
            }
            bool operator!=(const const_iterator &rhs) const {
                if (v != rhs.v || pointer != rhs.pointer) return true;
                else return false;
            }
        };

        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        vector() {
            array = new T* [maxsize];
        }
        vector(const vector &other) {
            maxsize = other.maxsize;
            count = other.count;
            array = new T* [other.maxsize];
            for (int i = 0 ; i < count ; ++i){
                array[i] = new T (*(other.array[i]));
            }
        }
        /**
         * TODO Destructor
         */
        ~vector() {
            for (int i = 0 ; i < count ; ++i){
                delete array[i];
            }
            delete []array;
            array = nullptr;
        }
        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (this == &other) return *this;
            for (int i = 0 ; i < count ; ++i){
                delete array[i];
            };
            delete []array;
            array = new T* [maxsize];
            maxsize = other.maxsize;
            count = other.count;
            for (int i = 0 ; i < count ; ++i){
                array[i] = new T (*(other.array[i]));
            }
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T & at(const size_t &pos) {
            if (pos < 0 || pos >= count) throw index_out_of_bound();
            return array[pos][0];
        }
        const T & at(const size_t &pos) const {
            if (pos < 0 || pos >= count) throw index_out_of_bound();
            return array[pos];
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos) {
            if (pos < 0 || pos >= count) throw index_out_of_bound();
            return array[pos][0];
        }
        const T & operator[](const size_t &pos) const {
            if (pos < 0 || pos >= count) throw index_out_of_bound();
            return array[pos][0];
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T & front() const {
            if (count == 0) throw container_is_empty();
            return array[0][0];
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T & back() const {
            if (count == 0) throw container_is_empty();
            return array[count - 1][0];
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(array , this , 0);
        }
        const_iterator cbegin() const {
            return const_iterator(array , this , 0);
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(array + count , this , count);
        }
        const_iterator cend() const {
            return const_iterator(array + count , this ,count);
        }
        /**
         * checks whether the container is empty
         */
        bool empty() const {
            if (count == 0) return true;
            else return false;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return count;
        }
        /**
         * clears the contents
         */
        void clear() {
            count = 0;
        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        void doubleSpace(){
            maxsize *= 2;
            T **tmp = new T* [maxsize];
            for (int i = 0 ; i < count ; ++i){
                tmp[i] = new T (array[i][0]);
                delete array[i];
            }
            delete []array;
            array = tmp;
        }

        iterator insert(iterator pos, const T &value) {
            if (pos.v != this) throw "error";
            if (count == maxsize) {
                doubleSpace();
            }
            if (count == 0) {
                push_back(value);
                return iterator(array , this , 0);
            }
            int p = pos.l;
            for (int i = count - 1 ; i >= p ; --i){
                array[i + 1] = array[i];
            }
            array[p] = new T(value);
            count++;
            return iterator(array + p , this , p);
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if (ind < 0 || ind >= count) throw index_out_of_bound();
            if (count == maxsize) {
                doubleSpace();
            }
            if (count == 0) {
                push_back(value);
                return iterator(array , this , 0);
            }
            //array[count] = new T (array[count - 1][0]);
            for (int i = count - 1 ; i >= ind ; --i){
                array[i + 1] = array[i];
            }
            array[ind] = new T(value);
            count++;
            return iterator(array + ind , this , ind);
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            if (pos.v != this) throw "error";
            int p = pos.l;
            delete array[p];
            for (int i = p ; i < count - 1; ++i){
                array[i] = array[i + 1];
            }
            array[count - 1] = nullptr;
            --count;
            return iterator(array + p , this , p);
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if (ind < 0 || ind >= count) throw index_out_of_bound();
            delete array[ind];
            for (int i = ind ; i < count - 1; ++i){
                array[i] = array[i + 1];
            }
            array[count - 1] = nullptr;
            --count;
            return iterator(array + ind , this , ind);
        }
        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (count == maxsize) {
                doubleSpace();
            }
            array[count] = new T (value);
            count++;
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if (count == 0) throw container_is_empty();
            delete array[count - 1];
            count--;
        }
    };

}

#endif
