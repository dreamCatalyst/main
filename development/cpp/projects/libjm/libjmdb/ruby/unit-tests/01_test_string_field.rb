# This file is part of the libjm project
# Copyright (C) 2010  Jonathan Maasland
require 'test/unit'
require 'jmdb_ruby'

include Jmdb_ruby;


class TestStringField < Test::Unit::TestCase

  def test_creation_no_arg
    sf = StringField.new
    assert(sf.isNull(), "creating a StringField with no args creates a null value")
  end

  def test_creation_w_arg
    sf = StringField.new("Hello world")
    assert(!sf.isNull(), "creating a StringField with an argument creates a non-null value")
    assert_equal("Hello world", sf.getString(), "getString() returns the initialized value")
  end

  def test_getInt
    sf = StringField.new("#{IntMax}")
    assert_equal(IntMax, sf.getInt(), "getInt() correctly returns a maximum positive integer")
    sf = StringField.new("#{IntMin}")
    assert_equal(IntMin, sf.getInt(), "getInt() correctly returns a minimum negative integer")
    sf = StringField.new("0")
    assert_equal(0, sf.getInt(), "getInt() correctly returns 0")
    sf = StringField.new("garbage")
    assert_equal(0, sf.getInt(), "getInt() returns 0 for garbage input");
  end

  def test_getDouble
    # A double in c++ can hold 15 digits
    d = 1234567890.12345
    sf = StringField.new("#{d}")
    assert_equal(d, sf.getDouble(), "getDouble() correctly returns a long positive double");
    sf = StringField.new("#{-d}")
    assert_equal(-d, sf.getDouble(), "getDouble() correctly returns a long negative double");
    sf = StringField.new("garbage")
    assert_equal(0, sf.getInt(), "getDouble() returns 0 for garbage input");
  end

  def test_getInt64
    sf = StringField.new("#{Int64Max}")
    assert_equal(Int64Max, sf.getInt64(), "getInt64() correctly returns a maximum positive 64bit integer")
    sf = StringField.new("#{Int64Min}")
    assert_equal(Int64Min, sf.getInt64(), "getInt64() correctly returns a maximum negative 64bit integer")
  end
end
