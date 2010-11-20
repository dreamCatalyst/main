# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# 05_test_dbhfactory.rb - Tests the DatabaseHandlerFactory class

require 'test/unit'
require 'jmdb'
include Jmdb

class TestDBHFactory < Test::Unit::TestCase
	def test_invalid_connectionstrings
		assert_nil(DatabaseHandlerFactory::open(""), "open() returns null for an empty string")
		assert_nil(DatabaseHandlerFactory::open("some_string"), "open() returns null for a gargbage string")
	end
	
	def test_sqlite_connection
		dbh = DatabaseHandlerFactory::open("sqlite::sqlite_test.db")
		assert_not_nil(dbh, "open() returns non-null for a simple sqlite connectionstring")
		assert(dbh.isOpen, "the databasehandler is in an open state")
		assert_equal(0, dbh.errorCode, "the errorCode is NO_ERROR")
		assert_equal("", dbh.errorMessage, "the errorMessage is empty")
		
		assert_equal(0, dbh.close, "close() returns 0")
		assert(!dbh.isOpen, "after close() isOpen returns false")
		assert(File.exists?("sqlite_test.db"), "the database actually exists on disk")
		File.delete("sqlite_test.db")
	end
end
