# This file is part of the libjm project
# Copyright (C) 2010  Jonathan Maasland
require 'test/unit'
require 'int_limits'
require 'jmdb'

include Jmdb;


class TestIntField < Test::Unit::TestCase

  def setup
    @fMin = IntField.new(IntMin)
    @fMax = IntField.new(IntMax)
    @f64Min = IntField.new(Int64Min)
    @f64Max = IntField.new(Int64Max)
  end

  def test_creation_no_arg
    f = IntField.new
    assert(f.isNull(), "creating a IntField with no args creates a null value")
  end

  def test_creation_w_arg
    f = IntField.new(100)
    assert(!f.isNull(), "creating a IntField with an argument creates a non-null value")
    assert_equal(100, f.getInt(), "getInt() returns the initialized value")
  end

  def test_getInt
    assert_equal(IntMin, @fMin.getInt(), "getInt() returns minimum integer correctly")
    assert_equal(IntMax, @fMax.getInt(), "getInt() returns maximum integer correctly")
  end

  def test_getString
    assert_equal("#{IntMin}", @fMin.getString(), "getString() returns correctly for minimum integer");
    assert_equal("#{IntMax}", @fMax.getString(), "getString() returns correctly for maximum integer");
    assert_equal("#{Int64Min}", @f64Min.getString(), "getString() returns correctly for minimum 64bit integer");
    assert_equal("#{Int64Max}", @f64Max.getString(), "getString() returns correctly for maximum 64bit integer");
  end

  def test_getDouble
    # written purely for test-coverage. can't really test the accuracy
    assert_equal(IntMin, @fMin.getDouble(), "getDouble() returns correctly for minimum integer");
    assert_equal(IntMax, @fMax.getDouble(), "getDouble() returns correctly for maximum integer");
  end
  
  def test_getInt64
    assert_equal(IntMin, @fMin.getInt64(), "getInt64() returns correctly for minimum integer");
    assert_equal(IntMax, @fMax.getInt64(), "getInt64() returns correctly for maximum integer");
  end
end
