#ifndef COP4530_VECTOR_HHP
#define COP4530_VECTOR_HHP
/********************************
 * COP 4530
 * FSU Department of Computer Sience
 ********************************/
#include "Vector.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// constructor, destructor, and copy constructor
template <typename T>
Vector<T>::Vector(){ // default zero parameter constructor
    theSize = 0;
    theCapacity = 0;
    array = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector &rhs){ // copy constructor
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    array = new T[theCapacity];
    for(int i=0; i<rhs.theSize; i++){
        array[i] = rhs.array[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector &&rhs){ // move constructor
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    array = rhs.array;
    rhs.clear();
}

// num elements with value of val
template <typename T>
Vector<T>::Vector(int num, const T& val){ 
    theSize = num;
    theCapacity = num;
    array = new T[theCapacity];
    for(int i=0; i<num; i++){
        array[i] = val;
    }
}

// constructs with elements [start, end)
template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end){
    theCapacity = 0;
    for(const_iterator it = start; it < end; it++){ 
        theCapacity++;
    }
    array = new T[theCapacity];
    theSize = 0;
    for(const_iterator it = start; it < end; it++){ 
        array[theSize++] = *it; 
    }
}

template <typename T>
Vector<T>::~Vector(){ // destructor
    delete[] array;
}

// operators

// index operator
template <typename T>
T& Vector<T>::operator[](int index){
    if(index >= 0 && index < theSize){
        return array[index];
    }else{
        cout << "index out of bounds" << endl;
        throw invalid_argument("index out of bounds"); 
    }
}

template <typename T>
const T& Vector<T>::operator[](int index) const{
    if(index >= 0 and index < theSize){
        return array[index];
    }else{
        cout << "index out of bounds" << endl;
        throw invalid_argument("index out of bounds"); 
    }
}

// copy assignment operator
template <typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T> &rhs){
    theSize = rhs.theSize;
    if(theCapacity < rhs.theCapacity){
        theCapacity = rhs.theCapacity;
        delete[] array;
        array = new T[theCapacity];
    }
    for(int i=0; i<rhs.theSize; i++){
        array[i] = rhs.array[i];
    }
}

// move assignment operator
template <typename T>
Vector<T> & Vector<T>::operator=(Vector<T> &&rhs){
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    delete[] array;
    array = rhs.array;
    rhs.clear();
}

// at function. safer than operator[
template <typename T>
T& Vector<T>::at(int loc ){
    if(loc >= 0 and loc < theSize){
        return array[loc];
    }else{
        cout << "loc out of bounds" << endl;
        throw invalid_argument("loc out of bounds"); 
    }
}

template <typename T>
const T& Vector<T>::at(int loc ) const{
    if(loc >= 0 and loc < theSize){
        return array[loc];
    }else{
        cout << "loc out of bounds" << endl;
        throw invalid_argument("loc out of bounds"); 
    }
}

template <typename T>
T &Vector<T>::front(){ // reference to the first element
    if(theSize > 0){
        return array[0];
    }else{
        cout << "empty" << endl;
        throw invalid_argument("empty"); 
    }
}

template <typename T>
const T& Vector<T>::front() const{
    if(theSize > 0){
        return array[0];
    }else{
        cout << "empty" << endl;
        throw invalid_argument("empty"); 
    }
}

template <typename T>
T &Vector<T>::back(){ // reference to the last element
    if(theSize > 0){
        return array[theSize - 1];
    }else{
        cout << "empty" << endl;
        throw invalid_argument("empty"); 
    }
}

template <typename T>
const T & Vector<T>::back() const{
    if(theSize > 0){
        return array[theSize - 1];
    }else{
        cout << "empty" << endl;
        throw invalid_argument("empty"); 
    }
} 

// accessor member functions
template <typename T>
int Vector<T>::size() const{ // number of elements
    return theSize;
}

template <typename T>
int Vector<T>::capacity() const{ // capacity of vector
    return theCapacity;
}

template <typename T>
bool Vector<T>::empty() const{ // check if list is empty
    if(theSize == 0){
        return true;
    }
    return false;
}

// mutator member functions
template <typename T>
void Vector<T>::clear(){ // delete all elements
    theSize = 0;
	array =nullptr;
}


template <typename T>
void Vector<T>::doubleCapacity(){
    if(theSize == theCapacity){
        if(theCapacity == 0){
            theCapacity = 1;
        }else{
            theCapacity *= 2;
        }
        T* newarray = new T[theCapacity];
        for(int i=0; i<theSize; i++){
            newarray[i] = array[i];
        }
        delete[] array;
        array = newarray;
    }
}


template <typename T>
void Vector<T>::push_back(const T & val){ // insert to the end
    doubleCapacity();
    array[theSize++] = val;
}

template <typename T>
void Vector<T>::pop_back(){ // delete last element
    theSize--;
}

template <typename T>
void Vector<T>::resize(int num, T val){ // resize vector 
    if(num > theSize){
        if(num > theCapacity){
            theCapacity = num;
            T* newarray = new T[num];
            for(int i=0; i<theSize; i++){
                newarray[i] = array[i];
            }
            delete[] array;
            array = newarray;
        }
        for(int i=theSize; i<num;i++){
            array[i] = val;
        }
    }else{
        array[num] =val;
    }
}

template <typename T>
void Vector<T>::reserve(int newCapacity){ // reserve memory
    // not sure have this right
    if(newCapacity > theSize){
        T* newarray = new T[newCapacity];
        for(int i=0; i<theSize; i++){
            newarray[i] = array[i];
        }
        delete[] array;
        array = newarray;
    }    
}

// print out all elements. ofc is deliminitor
template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const{ 
    for(int i=0; i<theSize; i++){
        os << array[i];
        if(i < theSize - 1){
            os << ofc;
        }
    }
    //os << endl;  //test provided end of line
}

// iterator support
template <typename T>
typename Vector<T>::iterator Vector<T>::begin(){ // iterator to first element
    return Vector<T>::iterator(&Vector<T>::array[0]);
}

template <typename T>
typename Vector<T>::const_iterator begin(){
    return Vector<T>::const_iterator(&Vector<T>::array[0]);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end(){// end marker iterator
    return Vector<T>::iterator(&Vector<T>::array[Vector<T>::size()]); 
}

template <typename T>
typename Vector<T>::const_iterator end(){
    return Vector<T>::const_iterator(&Vector<T>::array[Vector<T>::size()]); 
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(Vector<T>::iterator itr, const T& val){ // insert val ahead of itr
    T prevVal = *itr;
    T replVal = val;
    while(itr < end()){
        *itr = replVal;
        itr++;
        replVal = prevVal;
        prevVal = *itr;
    }
    push_back(replVal);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator itr){ // erase one element
    T nextVal = *(itr + 1);
    while(itr < end()){
        *itr = nextVal;
        itr++;
        nextVal = *(itr + 1);
    }
    pop_back();
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator start, Vector<T>::iterator end){ // erase [start, end)
    for(Vector<T>::iterator it = end - 1; it >= start; it--){
        erase(it);
    }
}   

// overloading comparison operators
template <typename T>
bool operator==(const Vector<T> & lhs, const Vector<T> &rhs){
    bool result = true;
    if(lhs.size() != rhs.size()){
        result = false;
    }
    for(int i=0; i<lhs.size(); i++){
        if(lhs.at(i) != rhs.at(i)){
            result = false;
            break;
        }
    }
    return result;
}

template <typename T>
bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs){
    return !(lhs == rhs);
}

// overloading output operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const Vector<T> &v){
    v.print(os);
    return os;
}

#endif
