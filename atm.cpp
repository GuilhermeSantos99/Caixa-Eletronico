#include "funcs.hpp"
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include <cstddef>
#include <cstdio>
#include <string>

std::string saldo;

static int callback(void *data, int argc, char **argv, char **azColName)
{
  size_t i;
  fprintf(stderr, "%s: ", (const char *)data);
/*
  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }

  printf("\n");
*/
  //printf("%s\n", argv[1]);
  saldo = argv[1];
  return 0;
}

void updateDB(double novoSaldo)
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
   std::string saldoStr = std::to_string(novoSaldo);
   std::string sqlUpdateStr = "";

   sqlUpdateStr = "UPDATE money SET saldo = " + saldoStr + " WHERE id = 1";

   const char *sqlUpdate = sqlUpdateStr.c_str();

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
	exit = sqlite3_open("dbATM.db", &DB);

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

void selectSaldo()
{
   sqlite3* DB;
   int exit = 0;
   exit = sqlite3_open("dbATM.db", &DB);
   std::string data("");

   std::string sql("SELECT * FROM money;");
   if (!exit) {
      std::cout << "Banco de dados aberto com sucesso!" << std::endl;
   }
   else
   {
      std::cerr << "Erro ao abrir bando de dados " << sqlite3_errmsg(DB) << std::endl;
   }

   int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

   std::cout << "Saldo: R$" << saldo << '\n';


   if (!(rc != SQLITE_OK))
   {
      std::cout << "Operation OK!" << std::endl;
   }
   else {
      std::cerr << "Erro ao buscar informações do banco de dados" << std::endl;
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