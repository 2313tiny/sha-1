
#ifndef GARRAY_HPP
#define GARRAY_HPP

//int const LAYOUT = 160;
// how many pigeonhole you have
// i.e number of bit for representing message, hash etc..
#include<iostream>
#include<cassert>
#include<limits>
#include<iomanip>


#define YELLOW "\033[01;033m"
#define GREEN "\033[01;032m"
#define RESET "\033[01;0m"
#define RED "\033[01;031m"

//const int LAYOUT = 512;
const int LAYOUT = 32; 

class GbitVector{
public:
	unsigned long int * m_array;
	int m_size;
public:
	GbitVector(int p_size = LAYOUT);
	~GbitVector();
	void Resize(int p_size);
	GbitVector(const GbitVector &);
//	bool operator[](int index) const; //access operator
	bool get(int index) const; //access operator
	void set(int p_index, bool p_value); //set operator 
	
	void shift_left(int index); //shift left
	void shift_left_cyclic(int index); //shift left cyclic
	
	GbitVector & operator=(const GbitVector & variable); //op=overload
	GbitVector operator+(const GbitVector & variable) const;//op+overload
//	void show_state_for_each_bit(); // all bit state inside the bitvector
};



/*

class GbitVector{
protected:
	unsigned long int * m_array;
	int LAYOUT;
public:
	GbitVector(int lay);
	~GbitVector();
	bool operator[](int index) const; //access operator
	void set(int index, bool value); //set/clear bit
	void shift_right(int index); //shift right
	void shift_left(int index); //shift left
	void show_state_for_each_bit(); // all bit state inside the bitvector
};
 
*/

#endif //GARRAY_HPP
