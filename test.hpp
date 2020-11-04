#ifndef TEST_HPP
#define TEST_HPP

#include"Sha.hpp" 
 
void test_v1()
{
	SHA sh;
	const char * login = "login";
	const char * pass = "password";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	login = "login@gmail.com";
	pass = "password";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	login = "olgin@gmail.com";
	pass = "password";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	login = "olgin@gmail.com";
	pass = "password";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	login = "login@gmail.com";
	pass = "password";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	login = "login@gmail.com";
	pass = "passwodr";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	login = "login";
	pass = "password";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";


	login = "login&al@";
	pass = "password)a+da";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	login = "login";
	pass = "passwodr";
	sh.set_login(login);
	sh.set_password(pass);
	sh.show_message();
	std::cout << "login: " << login << "    password: " << pass << "\n";

	
	SHA sh1;
	const char * login1 = "login";
	const char * pass1 = "password";
	sh1.set_login(login1);
	sh1.set_password(pass1);
	sh1.show_message();
	std::cout << "login1: " << login1 << "   password1: " << pass1 << "\n";

	SHA sh2;
	const char * login2 = "login";
	const char * pass2 = "password";
	sh2.set_login(login2);
	sh2.set_password(pass2);
	sh2.show_message();
	std::cout << "login1: " << login2 << "   password1: " << pass2 << "\n";

	SHA sh3;
	const char * login3 = "login";
	const char * pass3 = "password";
	sh3.set_login(login3);
	sh3.set_password(pass3);
	sh3.show_message();
	std::cout << "login1: " << login3 << "   password1: " << pass3 << "\n";
	std::cout << "\n..............\n\n\n\n";
}

void test_v2()
{
	SHA sh;
	const char * login = "login";
	const char * pass = "passwordlogin";
	sh.set_login(login);
	sh.set_password(pass);
	std::cout << std::setw(4) << "login = " << login;
	std::cout << std::setw(14) << "\npassword = " << pass << std::endl;;
	sh.show_message();
	std::cout << "\t------\t--------\n";

	SHA sh1;
	const char * login1 = "login";
	const char * pass1 = "passwordlogin";
	sh1.set_login(login1);
	sh1.set_password(pass1);
	std::cout << std::setw(4) << "login = " << login1;
	std::cout << std::setw(14) << "\npassword = " << pass1 << std::endl;;
	sh1.show_message();
	std::cout << "\t------\t--------\n";

	login1 = "login";
	pass1 = "passwordlogin";
	sh1.set_login(login1);
	sh1.set_password(pass1);
	sh1.show_message();
	std::cout << std::setw(4) << "login = " << login1;
	std::cout << std::setw(14) << "\npassword = " << pass1 << std::endl;;
	std::cout << "\t------\t--------\n";

	login1 = "olgin";
	pass1 = "passwordlogin";
	sh1.set_login(login1);
	sh1.set_password(pass1);
	sh1.show_message();
	std::cout << std::setw(4) << "login = " << login1;
	std::cout << std::setw(14) << "\npassword = " << pass1 << std::endl;;
	std::cout << "\t------\t--------\n";
	
	login1 = "login";
	pass1 = "passwordlogin";
	sh1.set_login(login1);
	sh1.set_password(pass1);
	sh1.show_message();
	std::cout << std::setw(4) << "login = " << login1;
	std::cout << std::setw(14) << "\npassword = " << pass1 << std::endl;;
	std::cout << " \n\n\n----------------\n";

}

 
void test_v3()
{
	SHA sh;
	char login[30] ;//= "login";
	char pass[30] ; // = "passwordlogin";
	
	for(int i = 0; i< 12; ++i){
		std::cout << GREEN << "login: " << RESET; 
		std::cin.getline(login, 30);
		std::cout << GREEN << "password: " << RESET;
		std::cin.getline(pass, 30);

		sh.set_login(login);
		sh.set_password(pass);
		sh.show_message();
		std::cout << "-------------------\n";
	}
}


 
#endif // TEST_HPP
