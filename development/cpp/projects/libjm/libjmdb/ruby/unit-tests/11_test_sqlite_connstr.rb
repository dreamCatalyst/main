# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# 11_test_sqlite_connstr.rb - Tests for calling open with different values

require 'test/unit'
require 'dbh_test_helper'
require 'jmdb'
include Jmdb

class TestSqliteConnstr < Test::Unit::TestCase
  include DBHTestHelper  # for check_no_error and check_error_is_set
  
  DB_filename = "jmdb_sqlite_test.db"
  Conn_str = "sqlite::#{DB_filename}"
  
  def setup
    @dbh = SqliteDatabaseHandler.new(Conn_str)
  end
  
  def teardown
    @dbh.close
    File.delete(DB_filename) if(File.exists?(DB_filename))
  end
  
  def test_constructor_no_args
    dbh = SqliteDatabaseHandler.new
    assert(!dbh.isOpen, "default constructed handler is in a closed state")
    check_no_error(dbh)
  end
  
  def test_constructor_w_args
    assert(@dbh.isOpen, "constructed handler is in an open state")
    check_no_error
    
    assert_equal(0, @dbh.close, "close() returns 0")
    assert(!@dbh.isOpen, "handler is in a closed state")
    assert(File.exists?(DB_filename), "the database actually exists on disk")
    check_no_error
  end
  
  def test_calling_open_twice
    @dbh = SqliteDatabaseHandler.new(Conn_str)
    assert(@dbh.isOpen(), "handler is in an open state")
    assert_equal(1, @dbh.open(Conn_str), "calling open() on an already opened handler returns CONNECTION_ERROR")
    check_error_is_set
  end
  
  def test_open_invalid_strings
    dbh = SqliteDatabaseHandler.new
    assert_equal(1, dbh.open(""), "open() returns CONNECTION_ERROR for an empty string");
    check_error_is_set(dbh)
    assert_equal(1, dbh.open("garbage"), "open() returns CONNECTION_ERROR for a garbage string");
    check_error_is_set(dbh)
    assert_equal(1, dbh.open("sqlite::"), "open() returns CONNECTION_ERROR when missing filename");
    check_error_is_set(dbh)
    # TODO add test for opening to non-existant path
    # TODO maybe add test for opening read-only path?
  end
end
