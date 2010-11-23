# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# 11_test_sqlitedbh.rb - High-level testing of the SqliteDatabaseHandler

require 'test/unit'
require 'jmdb'
include Jmdb

class TestSqliteDBH < Test::Unit::TestCase
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
    assert(!dbh.isOpen, "handler is in a closed state")
    check_no_error(dbh)
  end
  
  def test_constructor_w_args
    assert(@dbh.isOpen, "handler is in an open state")
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
  
  def test_executing_statements
    n = @dbh.execute("create table Test( id number )")
    assert_equal(0, n, "execute('create table') returns NO_ERROR")
    check_no_error
    
    n = @dbh.execute("insert into Test (id) values (1)")
    assert_equal(0, n, "execute('insert into') returns NO_ERROR")
    assert_equal(1, @dbh.affectedRowCount, "affectedRowCount returns 1")
    check_no_error
    
    n = @dbh.execute("update Test set id=id+10")
    assert_equal(0, n, "execute('update') returns NO_ERROR")
    assert_equal(1, @dbh.affectedRowCount, "affectedRowCount returns 1")
    check_no_error
    
    n = @dbh.execute("delete from Test where id > 10")
    assert_equal(0, n, "execute('delete from') returns NO_ERROR")
    assert_equal(1, @dbh.affectedRowCount, "affectedRowCount returns 1")
    check_no_error
  end
  
  def test_execute_select
    @dbh.execute("create table Test( id number )")
    10.times do |i| @dbh.execute("insert into Test (id) VALUES (#{i})") end
    check_no_error
    
    resultSet = @dbh.executeSelectQuery("select id from Test");
    check_no_error
    assert_not_nil(resultSet, "executeSelectQuery returns non-nil")
    assert_equal(10, resultSet.rowCount, "resultSet.rowCount() returns the correct number of rows")
    
    # Column related tests
    colInfo = resultSet.getColumnInformation
    assert_not_nil(colInfo, "getColumnInformation() returns a valid object")
    assert_equal(1, colInfo.numColumns(), "the correct number of columns is returned")
    assert_equal("id", colInfo.columnName(0), "columnName() returns the correct name")
    assert_equal(0, colInfo.columnIndex("id"), "columnIndex() returns the correct index for fieldname")
    
    # Iterator row moving related tests
    row = resultSet.current();
    assert_not_nil(row, "current() returns a valid object")
    row2 = resultSet.current();
    # assert_equal(row, row2, "current() returns the same object") # TODO swig trickiness
    
    rowList = [ row ]
    9.times do |idx|
      row2 = resultSet.next();
      assert(!rowList.include?(row2), "next() returns a different row object every time")
      assert_not_nil(row2, "the returned value of next() isn't nil")
      assert_equal( idx+1, row2.getInt("id"), "getInt('id') returns the correct value")
      assert_equal( idx+1, row2.getInt(0), "getInt(0) returns the correct value")
    end
    row2 = resultSet.next();
    assert_nil(row2, "moving past the last row returns nil")
    assert_nil(resultSet.current(), "current() also returns nil after moving past the end")
  end
  
  def check_no_error(dbh = nil)
    dbh = @dbh unless dbh
    assert_equal([ 0, "" ], [ dbh.errorCode, dbh.errorMessage ],
                 "errorCode is NO_ERROR and errorMessage is empty")
  end
  
  def check_error_is_set(dbh = nil)
    dbh = @dbh unless dbh
    # TODO find out how we can use CONNECTION_ERROR here
    assert_not_equal(0, dbh.errorCode, "the errorCode is set")
    assert_not_equal("", dbh.errorMessage, "the errorMessage is set")
  end
end
