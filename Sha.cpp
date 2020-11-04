#include "Sha.hpp" 

int SHA::countOfLetter = 1;

SHA::SHA() : m_message(MESSAGE_LENGTH) 
	   , m_hash(HASH_LENGTH)
	{
	
	}

void SHA::set_login(const char * login )
{
	
	//this part need for clear previous state for all value
	countOfLetter = 1;
	clear_512bit();
	m_digest.clear();
	clear_h_temp(); 
	generate_4_key();   //k1, k2, k3, k4
	generate_five_of_five_32bit(); //a, b, c, d ,e
	init_m_h_temp();
	for(int i = 0; i < LAYOUT; ++i){ //??
		f.set(i, false);
	}	
	for(int i = 0; i < LAYOUT; ++i){
		k.set(i, false);
	}

	//---*****--------
	convert_message_to_512bit(login);
}

void SHA::set_password(const char * pass)
{
	convert_message_to_512bit(pass);

	//appending a 1
	countOfLetter -= 1;
	//visual test
	//std::cout << "\n" << countOfLetter << "\n"; 
	int appendOneIndex = countOfLetter * 8;
	m_message.set(appendOneIndex, true);
	//append length of string	
	for (int i = MESSAGE_LENGTH-1; i >= MESSAGE_LENGTH - 64; --i){
		bool value = countOfLetter % 2 ;
		     countOfLetter = countOfLetter / 2; 
		     m_message.set(i, value);	
	}
}


void SHA::convert_message_to_512bit(const char * message)
{
	char * ptr = const_cast<char*>(message);
	while( '\0' != static_cast<char>(*ptr)){
					
		int letter = static_cast<int>(*ptr);
		int slider_begin = 7*countOfLetter ;
		int slider_end =  slider_begin - 7;
		if ( 1 != countOfLetter){
			slider_begin = 7 * countOfLetter + countOfLetter - 1;
			slider_end = slider_begin - 7;
		}
		for (int i = slider_begin; i >= slider_end ; --i){
			bool value = letter % 2 ;
			letter = letter / 2; 
			m_message.set(i, value);	
		}
		++ptr;
		++countOfLetter;
	}
}


void SHA::show_message_inner()const
{
	for (int i = 0 ; i < MESSAGE_LENGTH; ++i){
		if (0 !=  ((i+1)%8) ){
			std::cout << m_message.get(i);
		} else {
			std::cout << m_message.get(i);
			std::cout << "  ";
			}
		if ( 0 == (i+1) % LAYOUT ){
			std::cout << std::endl;
			}
		}
}

void SHA::show_hash() const
{
	for (int i = 0 ; i < HASH_LENGTH; ++i){
		if (0 !=  ((i+1)%8) ){
			std::cout << m_hash.get(i);
		} else {
			std::cout << m_hash.get(i);
			std::cout << "  ";
			}
		if ( 0 == (i+1) % LAYOUT ){
			std::cout << std::endl;
			}
		}
}

void SHA::show_message()
{
	//visual test
//	show_message_inner(); 
	generate_five_of_five_32bit();
	divide_message_by_16_word(); 	
	generate_16_to_79_word();            
	init_m_h_temp();
	generate_4_key();
	compressing_action();
	generate_hex_symbol_from_binary();
	show_ouput_hash_string();
}

void SHA::generate_five_of_five_32bit()
{
	generate_one_of_five_32bit(m_h[0], "aaaa");
	generate_one_of_five_32bit(m_h[1], "bbbb");
	generate_one_of_five_32bit(m_h[2], "dddd");
	generate_one_of_five_32bit(m_h[3], "eeee");
	generate_one_of_five_32bit(m_h[4], "ffff");
}


void SHA::show_one_of_five_32bit(GbitVector & arr)
{
	for (int i = 0 ; i < LAYOUT; ++i){
		if (0 !=  ((i+1)%8) ){
			std::cout << arr.get(i);
		} else {
			std::cout << arr.get(i);
			std::cout << "  ";
			}
		if ( 0 == (i+1) % LAYOUT ){
			std::cout << std::endl;
			}
	}
}

void SHA::show_one_of_sixteeen_32bit(GbitVector & arr)
{
	//std::cout << "word ... ";
	for (int i = 0 ; i < LAYOUT; ++i){
		if (0 !=  ((i+1)%8) ){
			std::cout << arr.get(i);
		} else {
			std::cout << arr.get(i);
			std::cout << "  ";
			}
		if ( 0 == (i+1) % LAYOUT ){
			std::cout << std::endl;
			}
	}
}

void SHA::generate_one_of_five_32bit(GbitVector & arr, const char * message)
{
	int count = 1;	
	char * ptr = const_cast<char*>(message);
	while( '\0' != static_cast<char>(*ptr)){
					
		int letter = static_cast<int>(*ptr);
		int slider_begin = 7*count ;
		int slider_end =  slider_begin - 7;
		if ( 1 != countOfLetter){
			slider_begin = 7 * count + count - 1;
			slider_end = slider_begin - 7;
		}
		for (int i = slider_begin; i >= slider_end ; --i){
			bool value = letter % 2 ;
			letter = letter / 2; 
			arr.set(i, value);	
		}
		++ptr;
		++count;
	}

}

void SHA::divide_message_by_16_word()
{
  for(int w = 0; w < 16; ++w){
	for (int i = 0; i < LAYOUT; ++i){
		bool value = m_message.get(i+ 32 * w);
		m_w[w].set(i, value);		
	}
  }
}

void SHA::generate_16_to_79_word()
{
	for (int index = 17; index < 80; ++index){
		generate_16_to_79_word_inner(index);
	}
}

void SHA::generate_16_to_79_word_inner(int index)
{
	bool value = false;
	for (int i = 0; i < LAYOUT; ++i){
		value = m_w[index - 3].get(i) ^  m_w[index-8].get(i) ^ 
			m_w[index -14].get(i) ^ m_w[index-16].get(i);
		m_w[index].set(i,value);
	}
	//shift left 1 digit
	value = m_w[index].get(0);
	m_w[index].shift_left(1);
	m_w[index].set(LAYOUT-1, value);	
}


void SHA::init_m_h_temp()
{
	m_h_temp[0] = m_h[0]; // a
	m_h_temp[1] = m_h[1]; // b
	m_h_temp[2] = m_h[2]; // c
	m_h_temp[3] = m_h[3]; // d 
	m_h_temp[4] = m_h[4]; // e
}

void SHA::generate_one_of_4_key_32bit(GbitVector & arr, const char *message)
{
	int count = 1;	
	char * ptr = const_cast<char*>(message);
	while( '\0' != static_cast<char>(*ptr)){
					
		int letter = static_cast<int>(*ptr);
		int slider_begin = 7*count ;
		int slider_end =  slider_begin - 7;
		if ( 1 != countOfLetter){
			slider_begin = 7 * count + count - 1;
			slider_end = slider_begin - 7;
		}
		for (int i = slider_begin; i >= slider_end ; --i){
			bool value = letter % 2 ;
			letter = letter / 2; 
			arr.set(i, value);	
		}
		++ptr;
		++count;
	}
}

void SHA::generate_4_key()
{
	generate_one_of_4_key_32bit(m_key[0], "BABE");
	generate_one_of_4_key_32bit(m_key[1], "YOUR");
	generate_one_of_4_key_32bit(m_key[2], "LIKE" );
	generate_one_of_4_key_32bit(m_key[3], "BOSS");
	
}

void SHA::rotation_and_permutation(GbitVector & a , GbitVector & b,
				   GbitVector & c, GbitVector & d,
				   GbitVector & e, GbitVector & f, 
				   GbitVector & key, GbitVector & word)
{

	GbitVector temp;
	a.shift_left_cyclic(5); //leftrotate 5
	temp = a + f + e + word + key;	
	e = d;
	d = c;
	b.shift_left_cyclic(30);//leftrotate 30
	c = b;
	b = a;
	a = temp;	
}


void SHA::logical_function_1(GbitVector & b,GbitVector & c,
			     GbitVector & d, GbitVector & f)
{
	for(int i = 0; i < LAYOUT; ++i){
		bool value1 = b.get(i) && c.get(i);
		bool value2 = ~b.get(i) && d.get(i);
		bool value = value1 || value2;
		f.set(i, value);
	}	

}

void SHA::logical_function_2(GbitVector & b,GbitVector & c,
			     GbitVector & d, GbitVector & f)
{
	for(int i = 0; i < LAYOUT; ++i){
		bool value = b.get(i) ^ c.get(i) ^ d.get(i);
		f.set(i, value);		
	}
}

void SHA::logical_function_3(GbitVector & b, GbitVector & c,
			     GbitVector & d, GbitVector & f)
{
	for(int i = 0; i < LAYOUT; ++i){
		bool value1 = b.get(i) && c.get(i);
		bool value2 = b.get(i) && d.get(i);
		bool value3 = c.get(i) && d.get(i);
		bool value = value1 || value2 || value3;
		f.set(i, value);
	}
}

void SHA::logical_function_4(GbitVector & b,GbitVector & c,
			     GbitVector & d, GbitVector & f)
{
	for(int i = 0; i < LAYOUT; ++i){
		bool value = b.get(i) ^ c.get(i) ^ d.get(i);
		f.set(i, value);		
	}
}

void SHA::compressing_action()
{
	for (int i = 0; i < WORD; ++i){
//	for (int i = 0; i < 1; ++i){	
		if( (i>= 0) && (i <=19) ){	
	  	  logical_function_1(m_h_temp[1], m_h_temp[2], m_h_temp[3], f);
		   k = m_key[0];
		  // std::cout << "\n f ...... "; //visual test
		  // show_one_of_five_32bit(f);
		} else if ((i>=20) && (i <= 39)){
	  	  logical_function_2(m_h_temp[1], m_h_temp[2], m_h_temp[3], f);
		   k = m_key[1];
		   //std::cout << "\n f ...... "; //visual test
		   // show_one_of_five_32bit(f);
		} else if ((i>=40) && (i <= 59)){
	  	  logical_function_3(m_h_temp[1], m_h_temp[2], m_h_temp[3], f);
		   k = m_key[2];
		  // std::cout << "\n f ...... "; //visual test
		  //show_one_of_five_32bit(f);
		} else if ((i>=60) && (i <= 79)){
	  	  logical_function_4(m_h_temp[1], m_h_temp[2], m_h_temp[3], f);
		   k = m_key[3];
		   //std::cout << "\n f ...... "; //visual test
		   // show_one_of_five_32bit(f);
		}		
		
		rotation_and_permutation(m_h_temp[0], m_h_temp[1], 
					 m_h_temp[2], m_h_temp[3],
					 m_h_temp[4], f,
					 k, m_w[i]);
		
		add_abcde_to_01234(m_h_temp[0], m_h_temp[1],
				     m_h_temp[2], m_h_temp[3],
				     m_h_temp[4],
				     m_h[0], m_h[1], m_h[2], 
				     m_h[3], m_h[4]);
	}	
}

void SHA::add_abcde_to_01234(GbitVector & a, GbitVector & b,
			     GbitVector & c, GbitVector & d,
			     GbitVector & e,
			     GbitVector & h0, GbitVector & h1,
			     GbitVector & h2, 
			     GbitVector & h3, GbitVector & h4)
{
	h0 = h0 + a;
	h1 = h1 + b;
	h2 = h2 + c;
	h3 = h3 + d;
	h4 = h4 + e;	
}

void SHA::convert_bin_to_hex_string(GbitVector & a, std::string & out)
{
//	for(int i = LAYOUT-1; i >= 0; --i){
	int i = 0;
	while( i < LAYOUT){
		int begin = i+3;
		int end = i;
		int sub = 1;
		int sum = 0;
		int count = 0;
		for (int p = begin; p >= end; --p){
			int digit = static_cast<int>(a.get(p));
	//visual test
	//		std::cout << digit << " " ;
			if(( begin == p) && (1 == digit)){
				sum = 1;
			} else { 
				if (1 == digit){
				  sub = 1;	
				  for(int i = 0; i < count; ++i){ sub *= 2; }
					sum = sum  + sub;
				} else {
					sum = sum;
				 	}
			}
			++count;
		}// std::cout << std::endl;
		//visual test
		//std::cout << "count = " << count << " ";
		//std::cout << "begin = " << begin << " end = " << end << "\t";
		//std::cout << "sum = " << sum << std::endl;
			if (sum < 10){ sum += 48; } else { sum += 87; }       
				std::string letter = {static_cast<char>(sum)} ;	
				out.append(letter);
		i = begin + 1;
	}
	out.append(" ");
}


void SHA::generate_hex_symbol_from_binary()
{
	convert_bin_to_hex_string(m_h[0], m_digest);
	convert_bin_to_hex_string(m_h[1], m_digest);
	convert_bin_to_hex_string(m_h[2], m_digest);
	convert_bin_to_hex_string(m_h[3], m_digest);
	convert_bin_to_hex_string(m_h[4], m_digest);
}


void SHA::show_ouput_hash_string()
{
	std::cout << YELLOW <<  "\n\n output digest " << RESET << std::endl;
	std::cout << m_digest << "\n\n";
	
}

void SHA::clear_512bit()
{
	for (int i = 0; i < MESSAGE_LENGTH; ++i){
		m_message.set(i, false);
	}
}

void SHA::clear_h_temp()
{
	for (int h = 0; h < HASH; ++h){
		for (int l = 0; l < LAYOUT; ++l){
			m_h_temp[h].set(l, false);
		}
	}	
}
