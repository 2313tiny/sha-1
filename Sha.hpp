#ifndef SHA_HPP
#define SHA_HPP

#include"Garray.hpp"

#include<string>
#include<iostream>


const int MESSAGE_LENGTH =  512;
const int HASH_LENGTH = 160;
const int WORD = 80;
const int HASH = 5;
const int KEY = 4;

class SHA{
public:
	//reserve place for message and hash
	//each other will be fited standard
	SHA();  

	void set_login(const char * );
	void set_password(const char *);
	void show_message();	
	void show_hash() const;
	void show_one_of_five_32bit(GbitVector & arr);

	void show_one_of_sixteeen_32bit(GbitVector & arr);
//	bool get_bit(char arr, int i);
private: //utilities
	void clear_h_temp(); 
	void clear_512bit();
	void convert_message_to_512bit(const char *);
	void show_message_inner()const;
	
	void generate_five_of_five_32bit();
	void generate_one_of_five_32bit(GbitVector & arr, const char *message);
	
	void generate_one_of_4_key_32bit(GbitVector & arr, const char *);
	void divide_message_by_16_word();
	void generate_16_to_79_word();
	void generate_16_to_79_word_inner(int);
	void init_m_h_temp();

	void generate_4_key();
	void rotation_and_permutation(GbitVector & , GbitVector &,
				      GbitVector & , GbitVector &,
				      GbitVector & , GbitVector &, 
				      GbitVector & , GbitVector &);

	void logical_function_1(GbitVector & ,GbitVector &,
			     	GbitVector & , GbitVector &);
	void logical_function_2(GbitVector & ,GbitVector &,
			     	GbitVector & , GbitVector &);
	void logical_function_3(GbitVector & ,GbitVector &,
			     	GbitVector & , GbitVector &);
	void logical_function_4(GbitVector & ,GbitVector &,
			     	GbitVector & , GbitVector &);
	void add_abcde_to_01234(GbitVector & , GbitVector & ,
			     GbitVector & , GbitVector & ,
			     GbitVector & ,
			     GbitVector & , GbitVector &,
			     GbitVector & , 
			     GbitVector & , GbitVector & );	
	void generate_hex_symbol_from_binary();
	void convert_bin_to_hex_string(GbitVector &, std::string & );
	void compressing_action();
	void show_ouput_hash_string();
public:
	GbitVector m_message; // login + password
	GbitVector m_hash;    // result 
	 
	GbitVector m_h[HASH]; //5 module h0, h1, h2, h3, h4, init m_h_temp
	GbitVector m_w[WORD]; //80 word each one 32 bit

	GbitVector m_h_temp[HASH] ; //temp like a, b, c, d, e	
	GbitVector m_key[KEY];      // like K1, K2, K3, K4

	std::string m_digest; //ouput result string consist 40 hex symbol
	
	static int countOfLetter;
private:
	GbitVector f; //need only for helping purpose
	GbitVector k; //need only for helping purpose

};


#endif //SHA_HPP
