# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
#

require 'ftools'

# Why doesn't this work??  --aargh--
#
# TODO Add platform checks here later and make it work for all targets
#ldlib_path = ENV["LD_LIBRARY_PATH"]
#if(ldlib_path.nil? or ldlib_path == "")
#  ENV["LD_LIBRARY_PATH"] = ".:../lib"
#else
#  ENV["LD_LIBRARY_PATH"] = [ldlib_path, ".:../lib"].join(":")
#end
#
#puts "Set ldlib_path to: '#{ENV['LD_LIBRARY_PATH']}'"

require 'jmdb'
include Jmdb

SqlPath = "unit-tests/fixtures/sqlite/sqlite_test_database.sql"
DatabasePath = "unit-tests/fixtures/sqlite/testdb.sqlite"

def create_sqlite_testdb
  File.delete(DatabasePath) if File.exists?(DatabasePath)
  dbh = SqliteDatabaseHandler.new("sqlite::#{DatabasePath}")
  sql = File.read(SqlPath)
  dbh.execute(sql)
  if(dbh.errorCode != 0)
    puts "Error creating sqlite fixture database"
    puts "Error message: '#{dbh.errorMessage}'"
  end
end
