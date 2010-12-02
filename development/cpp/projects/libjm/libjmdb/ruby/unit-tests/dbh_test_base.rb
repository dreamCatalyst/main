# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# dbh_test_base.rb - Provides the define_dbh_testclasses method which can be
# used to dynamically create new test classes for specific connectors.
# Each submodule of DBHTestBase will become a new testclass for each connector.
#
# See also: dbh_all_tests.rb for all the tests that are defined.

require 'test/unit'
require 'dbh_all_tests'
require 'dbh_test_helper'

module DBHTestBase
  @@setup_blocks = {}
  @@teardown_blocks = {}
  
  def self.register(name, setup_proc, teardown_proc)
    @@setup_blocks[name] = setup_proc
    @@teardown_blocks[name] = teardown_proc
  end
  
  def self.setup_for(name)
    @@setup_blocks[name].call
  end
  
  def self.teardown_for(name, connector)
    @@teardown_blocks[name].call(connector)
  end
end

def define_dbh_testclasses(name_prefix, setup_proc, teardown_proc)
  DBHTestBase.register(name_prefix, setup_proc, teardown_proc)
  DBHTestBase.constants.each do |tc|
    new_name = name_prefix + "_" + tc
    eval %{
      class #{new_name} < Test::Unit::TestCase
        include DBHTestBase::#{tc}
        include DBHTestHelper
        
        def setup
          @dbh = DBHTestBase.setup_for("#{name_prefix}")
        end
        
        def teardown
          DBHTestBase.teardown_for("#{name_prefix}", @dbh)
        end
      end
  }
  end
end
