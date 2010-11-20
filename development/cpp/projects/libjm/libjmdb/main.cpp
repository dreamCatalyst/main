#include <iostream>
using namespace std;

// Simple playing ground for quickly testing the library
// remove this in favor of tests later on.
// still undecided whether to test w ruby or c++ (leaning towards ruby)


#include "jmdb_sqlitedatabasehandler.h"
#include "jmdb_field.h"
using namespace JM::DB;


int main(int argc, char **argv) {
	cout << "starting program\n\n";
	
	
	cout << "creating a new connection to sqlite::somefile" << endl;
	SqliteDatabaseHandler handler;
	int r = handler.open("sqlite::./somefile.sqlitedb");
	
	if(r == DatabaseHandler::CONNECTION_ERROR) {
		cout << "error opening connection\n"
				"error-message: '" << handler.errorMessage() << "'\n";
		return -1;
	}
	cout << "connection was made succesfully" << endl;
	
	
	cout << "executing create table query" << endl;
	r = handler.execQuery("create table if not exists Helloworld(id int, msg text)");
	
	if(r != DatabaseHandler::NO_ERROR) {
		cout << "error after executing create table statement\n";
		cout << "error message: " << handler.errorMessage() << "\n";
		return -1;
	}
	cout << "all is good after create table query" << endl;
	
	
	cout << "executing insert statement" << endl;
	r = handler.execQuery("insert into Helloworld (id,msg) values(10, 'hello world')");
	
	if(r != DatabaseHandler::NO_ERROR) {
		cout << "error after executing insert statement\n";
		cout << "error message: " << handler.errorMessage() << "\n";
		return -1;
	}
	cout << "all is good after insert query" << endl;
	
	
	// add select query and iterate over the results
	ResultSet* rs = handler.selectQuery("select id,name from Helloworld");
	
	cout << "trying to close" << endl;
	r = handler.close();
	if(r == DatabaseHandler::CONNECTION_ERROR) {
		cout << "error closing the connection\n";
		return -1;
	}
	cout << "connection was closed succesfully" << endl;
	
	
	cout << "----------- testing Field\n";
	StringField sf("4294967295");
	unsigned long int l = sf.getULong();
	cout << "sf toUL(): " << l << endl;
	
	cout << "\nw00t everything went okay!\n";
	cout << "program done\n";
	return 0;
}
