#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <initializer_list>

#include "List.h"

using namespace cop4530;

// Public constructor for const_iterator.
template <typename T>
List<T>::const_iterator::const_iterator( ){
    current = nullptr;
}

// Return the object stored at the current position.
// For const_iterator, this is an accessor with a
// const reference return type.
template <typename T>
const T & List<T>::const_iterator::operator* ( ) const{
    return retrieve();
}

// increment/decrement operators
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++ ( ){
    current = current->next;
    return *this;
}
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++ ( int ){
    const_iterator old = *this;
    ++(*this);
    return old;
}
// ****** not in book ******
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator-- ( ){
    current = current->prev;
    return *this; 
}
// ****** not in book ******
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator-- ( int ){
    const_iterator old = *this;
    --(*this);
    return old;
}

// comparison operators
template <typename T>
bool List<T>::const_iterator::operator== ( const const_iterator & rhs ) const{
    return current == rhs.current;
}
template <typename T>
bool List<T>::const_iterator::operator!= ( const const_iterator & rhs ) const{
    return !(*this == rhs);
}

// Protected helper in const_iterator that returns the object
// stored at the current position. Can be called by all
// three versions of operator* without any type conversions.
template <typename T>
T & List<T>::const_iterator::retrieve( ) const{
    return current->data;
}

// Protected constructor for const_iterator.
// Expects a pointer that represents the current position.
template <typename T>
List<T>::const_iterator::const_iterator( Node *p ){
    current = p;
}

// Public constructor for iterator.
// Calls the base-class constructor.
// Must be provided because the private constructor
// is written; otherwise zero-parameter constructor
// would be disabled.
template <typename T>
List<T>::iterator::iterator( ){
}
template <typename T>
T & List<T>::iterator::operator* ( ){
    return const_iterator::retrieve();
}

// Return the object stored at the current position.
// For iterator, there is an accessor with a
// const reference return type and a mutator with
// a reference return type. The accessor is shown first.
template <typename T>
const T & List<T>::iterator::operator* ( ) const{
    return const_iterator::operator*();
}

// increment/decrement operators
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++ ( ){
    this->current = this->current->next;
    return *this;
}
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++ ( int ){
    iterator old = *this;
    ++(*this);
    return old;
}
// ****** not in book ******
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator-- ( ){
    this->current = this->current->prev;
    return *this;
}
// ****** not in book ******
template <typename T>
typename List<T>::iterator List<T>::iterator::operator-- ( int ){
    iterator old = *this;
    --(*this);
    return old;   
}

// Protected constructor for iterator.
// Expects the current position.
template <typename T>
List<T>::iterator::iterator( Node *p ):List<T>::const_iterator::const_iterator{p}{// could not get to compile otherwise
}

template <typename T>
List<T>::List(){
    init();
} // default zero parameter constructor

template <typename T>
List<T>::List(const List &rhs){
    init();
    for(auto & x : rhs){
        push_back(x);
    }
}   // copy constructor

template <typename T>
List<T>::List(List && rhs){
    theSize = rhs.theSize;
    head = rhs.head;
    tail = rhs.tail;
    rhs.theSize = 0; // book had this, not sure why
    rhs.head = nullptr; // book had this, not sure why
    rhs.tail = nullptr; // book had this, not sure why
}       // move constructor

        // num elements with value of val
// ****** not in book ******
template <typename T>
List<T>::List(int num, const T& val){
    init();
    for(int i=0; i<num; i++){
        push_back(val);
    }
}

        // constructs with elements [start, end)
// ****** not in book ******
template <typename T>
List<T>::List(const_iterator start, const_iterator end){
    init();
    for( const_iterator itr = start; itr != end; itr++){
        push_back( itr.retrieve() );
    }
}

        // constructs with a copy of each of the elements in the initalizer_list
// ****** not in book ******
template <typename T>
List<T>::List (std::initializer_list<T> iList){
    init();
    for(T val : iList){
        push_back(val);
    }
}

template <typename T>
List<T>::~List( ){
    clear();
    delete head;
    delete tail;
}

        // copy assignment operator
template <typename T>
List<T> & List<T>::operator= ( const List & rhs ){
    List<T> copy = rhs;
    std::swap(*this, copy);
    return *this;
}

        // move assignment operator
template <typename T>
List<T> & List<T>::operator= ( List<T> && rhs ){
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

        // sets list to the elements of the initializer_list
// ****** not in book ******
template <typename T>
List<T> & List<T>::operator= (std::initializer_list<T> iList){
    List<T> tmp = List<T>(iList);
    std::swap(*this, tmp);
    return *this;
}

template <typename T>
void List<T>::init(){
    theSize = 0;
    head = new Node();
    tail = new Node();
    head->next = tail;
    head->prev = nullptr; // not in book
    tail->next = nullptr; // not in book
    tail->prev = head;    
}

// Accessor functions
template <typename T>
int List<T>::size() const{
    return theSize;
}       // number of elements
template <typename T>
bool List<T>::empty() const{
    return size() == 0;
}     // check if list is empty
template <typename T>
void List<T>::clear(){
    while(!empty()){
        pop_front();
    }
}           // delete all elements

// front, back, push_front, push_back, pop_front, and pop_back
// are the basic double-ended queue operations.

template <typename T>
T & List<T>::front(){
    return *begin();
};             // reference to the first element
template <typename T>
const T & List<T>::front( ) const{
    return *begin();
}
template <typename T>
T & List<T>::back(){
    return *--end();
}              // reference to the last element
template <typename T>
const T & List<T>::back( ) const{
    return *--end();
}

template <typename T>
void List<T>::push_front(const T & val){
    insert(begin(), val);
} // insert to the beginning
template <typename T>
void List<T>::push_front(T && val){
    insert(begin(), std::move(val));
}      // move version of insert
template <typename T>
void List<T>::push_back(const T & val){
    insert(end(), val);
}  // insert to the end
template <typename T>
void List<T>::push_back(T && val){
    insert(end(), std::move(val));
}       // move version of insert
template <typename T>
void List<T>::pop_front(){
    erase(begin());
}               // delete first element
template <typename T>
void List<T>::pop_back(){
    erase(--end());
}                // delete last element
// ****** not in book ******
template <typename T>
void List<T>::remove(const T &val){
    iterator itr = begin();
    while(itr != end()){
        if(itr.retrieve() == val){
            itr = erase(itr);
        }else{
            itr++;
        }
    }
}      // remove all elements with value = val

// ****** not in book ******
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){
    iterator itr = begin();
    while(itr != end()){
        if(pred(itr.retrieve())){
            itr = erase(itr);
        }else{
            itr++;
        }
    }    
}	// remove all elements for which Predicate pred
//  returns true. pred can take in a function object

// print out all elements. ofc is deliminitor
// ****** not in book ******
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const{
    const_iterator itr = begin();
    while(itr != end()){
        os << itr.retrieve() << ofc;
        itr++;
    }    
}

// Return iterator representing beginning of list.
// Mutator version is first, then accessor version.
template <typename T>
typename List<T>::iterator List<T>::begin(){
    return {head->next};
}               // iterator to first element
template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
    return {head->next};
}

// Return iterator representing endmarker of list.
// Mutator version is first, then accessor version.
template <typename T>
typename List<T>::iterator List<T>::end(){
    return {tail};
}                 // end marker iterator
template <typename T>
typename List<T>::const_iterator List<T>::end() const{
    return {tail};
} 

// ****** not in book ******
template <typename T>
List<T> List<T>::slice(iterator start, iterator end){
    return List(start, end);
} // slice [start, end)
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{ val, p->prev, p}};
}  // insert val ahead of itr
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val){
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{ std::move(val), p->prev, p}};    
}      // move version of insert
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr){
    Node *p = itr.current;
    iterator retVal{ p->next };
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;

    return retVal;
}                 // erase one element
template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){
    for( iterator itr = start; itr != end; ){
        itr = erase( itr );
    }
    return end;
} // erase [start, end)
// ??? not in book ******
template <typename T>
void List<T>::reverse(){
    iterator itrFor = begin();
    iterator oItrFor = begin();
    iterator itrBac = --end();
    while(itrFor != itrBac && oItrFor != itrBac){
        std::swap(itrFor.current->data, itrBac.current->data);        
        oItrFor = itrFor++;
        itrBac--;
    }     
}                 // reverse the order of all elements
// ****** not in book ******
template <typename T>
void List<T>::deduplicate(){
    iterator itr = begin();
    while(itr != end()){
        iterator start = itr;
        for(iterator itr2 = ++start; itr2 != end();){
            if(itr.retrieve() == itr2.retrieve()){
                itr2 = erase(itr2);
            }else{
                itr2++;
            }
        }
        itr++;
    }  
}             // remove the duplicates of any element
// ****** not in book ******
template <typename T>
int List<T>::findSlice(const List & rhs){
    int count = 0;
    typename List<T>::const_iterator itr = begin();
    typename List<T>::const_iterator itr2;
    while(itr != end()){
        itr2 = rhs.begin();
        if(*itr == *itr2){            
            while(*itr == *itr2 && itr2 != rhs.end()){
                itr++;
                itr2++;
            }
            if(itr2 == rhs.end()){
                count++;
            }
        }else{
            itr++;           
        }
    }
    return count;
} // count the occurrence of a slice in the list


// overloading comparison operators
// ****** not in book ******
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs){
    if(lhs.size() != rhs.size()){
        return false;
    }
    typename List<T>::const_iterator itr = lhs.begin();
    typename List<T>::const_iterator itr2 = rhs.begin();
    while(itr != lhs.end()){
        if(*itr != *itr2){
            return false;
        }
        itr++;
        itr2++;
    }
    return true;
}

// ****** not in book ******
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs){
    return !( lhs == rhs);
}

// overloading output operator
// ****** not in book ******
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l){
    l.print(os);
    return os;
}

#endif
