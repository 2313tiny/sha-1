#include "Garray.hpp" 


GbitVector::GbitVector(int p_size)
{
	m_array = 0;
	m_size = 0;
	Resize(p_size);
	for (int i = 0; i < p_size; ++i){
		this->set(i, false);
	}
}


GbitVector::~GbitVector()
{
	if (0 != m_array){
		delete[] m_array;
		m_array = 0;
	}
}

GbitVector::GbitVector(const GbitVector & val)
{
	std::cout << "copy constructor" << std::endl;
/*	for(int i = 0; i < val.m_size; ++i){
		bool value = val.get(i);
		this->set(i, value);
	}
*/
}

GbitVector & GbitVector::operator=(const GbitVector & variable)
{
	for(int i = 0; i < LAYOUT; ++i){
		bool value = variable.get(i);
		this->set(i, value );
	}
	return *this;
}

GbitVector GbitVector::operator+(const GbitVector & var) const
{
	GbitVector result;
	bool value = false;
	bool carry = false;
	for(int i =LAYOUT-1 ; i >= 0; --i){
		value = var.get(i) ^ this->get(i) ^ carry;
		result.set(i, value);
		carry = ( (var.get(i) & this->get(i)) |
			  (var.get(i) & carry ) |
			  (this->get(i) & carry));	
	}	

	return result;	
}

void GbitVector::Resize(int p_size)
{
	unsigned long int* newvector = 0;
	if(0 == p_size % LAYOUT){
		p_size = p_size/LAYOUT;
	} else {
		p_size = (p_size/LAYOUT) + 1;
	}
	
	newvector =new unsigned long int[p_size];
	
	if(0 == newvector){
		return; 
	}
	int min;
	if (p_size < m_size){
		min = p_size;
	} else {
		min = m_size;
		}
	int index;
	for (index = 0; index < min; ++index){
		newvector[index] = m_array[index];
	}
	m_size = p_size;
	if( 0 != m_array ){
		delete[] m_array;
	}
	m_array = newvector;
}

//bool GbitVector::operator[](int p_index) const
bool GbitVector::get(int p_index) const
{
	int cell = p_index / LAYOUT;
	int bit = p_index % LAYOUT;
	//return (m_array[p_index](cell) & ( 1 << bit)) >> bit;
	return  (m_array[cell] & (1<< bit)) >>bit;
}


void GbitVector::set(int p_index, bool p_value)
{
	int cell = p_index / LAYOUT;
	int bit = p_index % LAYOUT;
	if (true == p_value){
		m_array[cell] = ( m_array[cell] | (1 << bit));		
	} else {
		m_array[cell] = (m_array[cell] & (~(1 << bit)));
	}	
} 


void GbitVector::shift_left(int index) //shift left
{
	for (int i = 0; i < index; ++i){
		m_array[0] =  m_array[0] >> 1;
	}
}

void GbitVector:: shift_left_cyclic(int index) //shift left cyclic
{
	for (int i = 0; i < index; ++i){
		bool value = this->get(0);
		m_array[0] = m_array[0] >> 1;
		this->set(LAYOUT-1, value);
	}
}


