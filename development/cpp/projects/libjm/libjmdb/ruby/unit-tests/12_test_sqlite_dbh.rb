# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# 12_test_sqlite_dbh - Defines the base-tests for the sqlite handler
# See also: dbh_test_base.rb

require 'ftools'
require 'dbh_test_base'
require 'jmdb'
include Jmdb

OriginalDBPath = "unit-tests/fixtures/sqlite/testdb.sqlite"
CopyDBPath = "current_testdb.sqlite"

setup = lambda do
  File.delete(CopyDBPath) if File.exists?(CopyDBPath)
  File.copy(OriginalDBPath, CopyDBPath)
  DatabaseHandlerFactory.open("sqlite::#{CopyDBPath}")
end

teardown = lambda do |dbh|
  dbh.close
  File.delete(CopyDBPath)
end

define_dbh_testclasses("Sqlite", setup, teardown)
