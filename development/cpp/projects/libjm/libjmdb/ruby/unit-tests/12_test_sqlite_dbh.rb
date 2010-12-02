# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# 12_test_sqlite_dbh - Defines the base-tests for the sqlite handler
# See also: dbh_test_base.rb

require 'dbh_test_base'
require 'jmdb'
include Jmdb

SqliteFilename = "sqlitedbh_testdb.sqlite"

setup = lambda do
  # Possibly do some type of fixture loading here later on
  DatabaseHandlerFactory.open("sqlite::#{SqliteFilename}")
end

teardown = lambda do |dbh|
  dbh.close
  File.delete(SqliteFilename)
end

define_dbh_testclasses("Sqlite", setup, teardown)
