require 'test/unit'
require 'jmdb_ruby'

include Jmdb_ruby;


class TestIntField < Test::Unit::TestCase

  def setup
    @intMin = -2147483647;
    @intMax = 2147483647;
    @fMin = IntField.new(@intMin)
    @fMax = IntField.new(@intMax)
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
    assert_equal(@intMin, @fMin.getInt(), "getInt() returns minimum integer correctly")
    assert_equal(@intMax, @fMax.getInt(), "getInt() returns maximum integer correctly")
  end

  def test_getLong
    assert_equal(@intMin, @fMin.getLong(), "getLong() returns minimum integer correctly")
    assert_equal(@intMax, @fMax.getLong(), "getLong() returns maximum integer correctly")
  end

  def test_getString
    assert_equal("#{@intMin}", @fMin.getString(), "getString() returns correctly for minimum integer");
    assert_equal("#{@intMax}", @fMax.getString(), "getString() returns correctly for maximum integer");
  end

  def test_getDouble
    # written purely for test-coverage. can't really test this
    assert_equal(@intMin, @fMin.getDouble(), "getDouble() returns correctly for minimum integer");
    assert_equal(@intMax, @fMax.getDouble(), "getDouble() returns correctly for maximum integer");
  end

  def test_getUInt
    assert_equal(0, @fMin.getUInt(), "getUInt() returns 0 for minimum integer")
    assert_equal(@intMax, @fMax.getUInt(), "getUInt() return correctly for maximum integer");
  end

  def test_getULong
    assert_equal(0, @fMin.getULong(), "getULong() returns 0 for minimum integer")
    assert_equal(@intMax, @fMax.getULong(), "getULong() return correctly for maximum integer");
  end
end
