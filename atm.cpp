#include "funcs.hpp"
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <sqlite3.h>
#include <cstddef>
#include <cstdio>
#include <string>

std::string saldoStr;
std::unique_ptr<double>pSaldo(new double);

static int callback(void *data, int argc, char **argv, char **azColName)
{
  fprintf(stderr, "%s", (const char *)data);

  saldoStr = argv[1];
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
      std::cerr << "Erro ao abrir DB" << sqlite3_errmsg(DB) << '\n';
   } 
   else
   {
      std::cout << "Database aberto com sucesso" << '\n';
   }

   // Instrução SQL
   std::string saldoStr = std::to_string(novoSaldo);
   std::string sqlUpdateStr = "";

   sqlUpdateStr = "UPDATE money SET saldo = " + saldoStr + " WHERE id = 1";

   const char *sqlUpdate = sqlUpdateStr.c_str();

   // Executar comando SQL
   exit = sqlite3_exec(DB, sqlUpdate, callback, (void *) data, &messaggeError);
   if ( exit != SQLITE_OK ) {
      std::cerr << "Não foi possível atualizar valores. " << sqlite3_errmsg(DB) << '\n';
   } else
   {
      std::cout << "Operação realizada com sucesso" << '\n';
   }
   
   sqlite3_close(DB);
}

void criaDB()
{
   sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("dbATM.db", &DB);

	if (exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << '\n';
	}
	else
   {
		std::cout << "Opened Database Successfully!" << '\n';
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
   if (exit) {
      std::cerr << "Erro ao abrir bando de dados " << sqlite3_errmsg(DB) << '\n';
   }

   int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

   convertSaldo();

   if (rc != SQLITE_OK)
   {
      std::cerr << "Erro ao buscar informações do banco de dados" << '\n';
   }

   sqlite3_close(DB);
}

void convertSaldo()
{
   *pSaldo = std::stod(saldoStr);
}

void showMenu()
{
   std::cout << "+------------------------+" << '\n'; 
   std::cout << "|    Caixa eletrônico    |" << '\n';
   std::cout << "|------------------------|" << '\n';
   std::cout << "| 1. Consultar saldo     |" << '\n';
   std::cout << "| 2. Depositar           |" << '\n';
   std::cout << "| 3. Sacar               |" << '\n';
	std::cout << "| 4. Sair                |" << '\n';
   std::cout << "+------------------------+" << '\n';
   std::cout << ">";
}

void showSaldo()
{
   selectSaldo();
   std::cout << "Saldo: R$ " << *pSaldo << '\n';
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
         system("clear");
         std::cout << '\n';
         showSaldo();
         std::cout << '\n';
      }
      else if(option == 2)
      {
	     system("clear");
        std::cout << '\n';
        makeDeposit();
        std::cout << '\n';
      }
      else if(option == 3)
      {
	     system("clear");
        std::cout << '\n';
        withdraw();
        std::cout << '\n';
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