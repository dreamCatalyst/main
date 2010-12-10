# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# mysql_test_helper.rb -

require 'yaml'

class MysqlTestConfig
  @@inst = nil
  
  def self.instance
    if(@@inst.nil?)
      @@inst = YAML::load_file("unit-tests/fixtures/mysql/configuration.yaml")
    end
    @@inst
  end
  
  def self.method_missing(meth_sym, *args)
    if(args.length == 0)
      instance().__send__(meth_sym)
    else
      instance().__send__(meth_sym, args[0])
    end
  end
  
  attr_reader :host, :username, :password, :database, :portNumber
  
  [ :host, :username, :password, :database, :portNumber ].each do |attrSym|
    attrName = attrSym.to_s
    eval %{
      def #{attrName}=(arg)
        @#{attrName} = arg
        @is_connection_string_dirty = true
      end
      }
  end
  
  def initialize
    @is_connection_string_dirty = true
    @connection_string = ""
  end
  
  def connection_string
    if(@is_connection_string_dirty)
      build_connection_string
    end
    return @connection_string
  end
  
  def build_connection_string
    @connection_string = "mysql::" + @host
    @connection_string << "@" << @portNumber.to_s unless @portNumber == 0
    @connection_string << "::" << @username << "::" << @password
    @connection_string << "::" << @database unless @database == ""
    @is_connection_string_dirty = false
  end
  
  def self.reload_configuration
    @@inst = nil
    self.instance
  end
end

module MysqlTestHelper
  
  def setup_mysql_test_connection
    init_test_fixture
    @dbh = MysqlDatabaseHandler.new(get_connection_string)
  end
  
  def reset_test_configuration
    MysqlTestConfig::reload_configuration
  end
  
  def get_connection_string
    MysqlTestConfig::connection_string
  end
  
  def init_test_fixture
    old_database = MysqlTestConfig::instance.database
    MysqlTestConfig::database = ""
    @dbh = MysqlDatabaseHandler.new(get_connection_string)
    execute_fixtures_file
    @dbh.close
    MysqlTestConfig::database = old_database
  end
  
  def execute_fixtures_file
    @currentStatement = ""
    IO.readlines("unit-tests/fixtures/mysql/mysql_test_database.sql").each do |line|
      @currentStatement << line
      if(line.end_with?(";\n"))
        @currentStatement.chop!.chop!
        @dbh.execute(@currentStatement)
        check_no_error
        @currentStatement = ""
      end
    end
  end
end
