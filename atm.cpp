#include "funcs.hpp"
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>

void criaDB()
{
   sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("example2.db", &DB);

	if (exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
	}
	else
   {
		std::cout << "Opened Database Successfully!" << std::endl;
   }
	sqlite3_close(DB);
}

void showMenu()
{
   std::cout << "+------------------------+" << '\n'; 
   std::cout << "|    Caixa eletrônico    |" << '\n';
   std::cout << "|------------------------|" << '\n';
   std::cout << "| 1. Chegar saldo        |" << '\n';
   std::cout << "| 2. Depositar           |" << '\n';
   std::cout << "| 3. Sacar               |" << '\n';
	std::cout << "| 4. Sair                |" << '\n';
   std::cout << "+------------------------+" << '\n';
   std::cout << ">";
}

void showSaldo()
{
	std::cout << "Saldo" << '\n';
   printf("Saldo\n");
}

void makeDeposit()
{
	std::cout << "Depositar" << '\n';
}

void withdraw()
{
	std::cout << "Sacar" << '\n';
}

void run()
{
   int option;

   while(true){
      
      showMenu();
      std::cin >> option;

      if(option == 1)
      {
         //system("clear");
         void showSaldo();
      }
      else if(option == 2)
      {
	     void makeDeposit();
         //system("clear");
      }
      else if(option == 3)
      {
	     void withdraw();
         //system("clear");
      }
      else if(option == 4)
      {
         std::cout << "Saindo..." << '\n';
         break;
      }
      else
      {
         std::cout << "Opção inválida, tente novamente" << '\n';
         //system("clear");
      }
   }
}