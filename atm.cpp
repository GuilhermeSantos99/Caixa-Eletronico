#include "funcs.hpp"
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName)
{
  size_t i;
  fprintf(stderr, "%s: ", (const char *)data);

  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
  return 0;
}

void updateDB()
{
   sqlite3 *DB;
   int exit = 0;
   const char* data("CALLBACK FUNCTION");
   char *messaggeError = 0;

   // Abertura do banco de dados
   exit = sqlite3_open("dbATM.db", &DB);

   if (exit) {
      std::cerr << "Erro ao abrir DB" << sqlite3_errmsg(DB) << std::endl;
   } 
   else
   {
      std::cout << "Database aberto com sucesso" << std::endl;
   }

   // Instrução SQL
   double novoSaldo;
   const char* sqlUpdate = "UPDATE money"
                           "SET saldo = 1.0"
                           "WHERE id = 1";

   // Executar comando SQL
   exit = sqlite3_exec(DB, sqlUpdate, callback, (void *) data, &messaggeError);
   if ( exit != SQLITE_OK ) {
      std::cerr << "Não foi possível atualizar valores. " << sqlite3_errmsg(DB) << std::endl;
   } else
   {
      std::cout << "Operação realizada com sucesso" << std::endl;
   }
   
sqlite3_close(DB);
}

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

void criaTabela()
{
   sqlite3* DB;
   std::string sql = "CREATE TABLE money ("
                      "id    INTEGER PRIMARY KEY AUTOINCREMENT"
                      "            NOT NULL,"
                      "saldo REAL  NOT NULL"
                      ");";

   int exit = 0;
   exit = sqlite3_open("dbATM.db", &DB);
   char *messaggeError;
   exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

   if ( exit != SQLITE_OK ){
      std::cerr << "Erro ao criar tabela" << '\n';
   }
   else {
      std::cout << "Tabela criada com sucesso" << '\n';
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