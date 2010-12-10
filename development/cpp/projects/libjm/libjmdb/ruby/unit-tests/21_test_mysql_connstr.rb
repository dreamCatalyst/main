# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# 21_test_mysql_connstr.rb - Tests for calling open with different values

require 'test/unit'
require 'dbh_test_helper'
require 'mysql_test_helper'
require 'jmdb'
include Jmdb

class TestMysqlConnstr < Test::Unit::TestCase
  include DBHTestHelper
  include MysqlTestHelper
  
  def setup
    reset_test_configuration
    #setup_mysql_test_connection
  end
  
  def teardown
    @dbh.close unless @dbh.nil?
  end
  
  def test_constructor_no_args
    dbh = MysqlDatabaseHandler.new
    assert(!dbh.isOpen, "default constructed handler is in a closed state")
    check_no_error(dbh)
  end
  
  def test_constructor_w_args
    setup_mysql_test_connection
    check_no_error
    assert(@dbh.isOpen, "constructed handler is in an open state")
    
    assert_equal(0, @dbh.close, "close() returns NO_ERROR")
    assert(!@dbh.isOpen, "after calling close() the handler is in a closed state")
    check_no_error
  end
  
  def test_calling_open_twice
    setup_mysql_test_connection
    assert_equal(1, @dbh.open, "calling open on an already opened connection returns CONNECTION_ERROR")
    check_error_is_set
  end
  
  def test_connecting_with_no_database
    MysqlTestConfig::database = ""
    setup_mysql_test_connection
    assert(@dbh.isOpen, "constructed handler is in an open state")
    check_no_error
  end
  
  def test_connecting_with_port_nr
    MysqlTestConfig::portNumber = 3306  # default mysql port number
    setup_mysql_test_connection
    assert(@dbh.isOpen, "constructed handler is in an open state")
    check_no_error
  end
  
end
