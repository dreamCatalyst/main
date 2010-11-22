# This file is part of the libjm project
# Copyright (C) 2010  Jonathan Maasland
require 'test/unit'
require 'jmdb_ruby'

include Jmdb_ruby;


class TestRealField < Test::Unit::TestCase

  def setup
    @neg = -12345.6789
    @pos = 12345.6789
    @fNeg = RealField.new(@neg)
    @fPos = RealField.new(@pos)
  end

  def test_creation_no_arg
    f = RealField.new
    assert(f.isNull(), "creating a RealField with no args creates a null value")
  end

  def test_creation_w_arg
    assert(!@fNeg.isNull(), "creating a RealField with an argument creates a non-null value")
    assert_equal(@neg, @fNeg.getDouble, "getDouble() returns the initialized value")
  end

  def test_getDouble
    # @fNeg is already tested above
    assert_equal(@pos, @fPos.getDouble, "getDouble() returns correctly for a positive value")
  end

  def test_getString
    assert_equal("#{@neg}", @fNeg.getString, "getString() returns correctly for a negative value")
    assert_equal("#{@pos}", @fPos.getString, "getString() returns correctly for a positive value")

    f = RealField.new(0)
    assert_equal("0", f.getString, "getString() returns correctly for 0")
  end

  def test_getInt
    assert_equal(@neg.round, @fNeg.getInt, "getInt() returns a correctly rounded negative value")
    @neg = -12345.3456
    @fNeg = RealField.new(@neg)
    assert_equal(@neg.round, @fNeg.getInt, "getInt() returns a correctly rounded negative value")

    assert_equal(@pos.round, @fPos.getInt, "getInt() returns a correctly rounded positive value")
    @pos = 12345.3456
    @fPos = RealField.new(@pos)
    assert_equal(@pos.round, @fPos.getInt, "getInt() returns a correctly rounded positive value")
  end

  # same as test_getInt
  def test_getInt64
    assert_equal(@neg.round, @fNeg.getInt64, "getInt64() returns a correctly rounded negative value")
    @neg = -12345.3456
    @fNeg = RealField.new(@neg)
    assert_equal(@neg.round, @fNeg.getInt64, "getInt64() returns a correctly rounded negative value")

    assert_equal(@pos.round, @fPos.getInt64, "getInt64() returns a correctly rounded positive value")
    @pos = 12345.3456
    @fPos = RealField.new(@pos)
    assert_equal(@pos.round, @fPos.getInt64, "getInt64() returns a correctly rounded positive value")
  end

end
