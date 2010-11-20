
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
    intMin = -2147483647;
    intMax = 2147483647;

    sf = StringField.new("#{intMax}")
    assert_equal(intMax, sf.getInt(), "getInt() correctly returns a maximum positive integer")
    sf = StringField.new("#{intMin}")
    assert_equal(intMin, sf.getInt(), "getInt() correctly returns a minimum negative integer")
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

  def test_getLong
    # long is the same as int actually :)
    # testing one value for posterity
    intMax = 2147483647;
    sf = StringField.new("#{intMax}")
    assert_equal(intMax, sf.getLong(), "getLong() correctly returns a maximum positive integer")
  end

  def test_getUInt
    uintMax = 4294967295
    sf = StringField.new("#{uintMax}")
    assert_equal(uintMax, sf.getUInt(), "getUInt() correctly returns for a maximum positive unsigned integer")

    sf = StringField.new("-1")
    assert_equal(0, sf.getUInt(), "getUInt returns 0 for negative value")
  end
end
