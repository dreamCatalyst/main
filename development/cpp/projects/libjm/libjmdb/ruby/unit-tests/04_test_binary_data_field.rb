require 'test/unit'
require 'jmdb_ruby'

include Jmdb_ruby;


class TestBinaryDataField < Test::Unit::TestCase

  def setup
    @data = "data"
    @len = 4
    @f = BinaryDataField.new(@data, @len)
  end

  def test_creation_no_arg
    f = BinaryDataField.new
    assert(f.isNull, "creating a BinaryDataField with no args creates a null value")
  end

  def test_creating_w_arg
    assert(!@f.isNull, "creating a BinaryDataField with args creates a non-null value")
    data,len = @f.getBinary;
    assert_equal(@len, len, "getBinary returns the correct length")
    assert_equal(@data, data, "getBinary returns the correct data")
  end

  def test_other_methods
    assert_equal("", @f.getString, "getString() returns an empty string")

    %w{ getInt getLong getDouble getUInt getULong }.each do |meth|
      assert_equal(0, @f.__send__(meth), "#{meth}() returns 0")
    end
  end

end
