# This file is part of the libjm project
# Copyright (C) 2010  Jonathan Maasland
require 'test/unit'
require 'jmutil'

include Jmutil;

# TODO place common sub-project ruby stuff somewhere
# Code duplication is bad mkaay
IntMax = 2147483647
IntMin = -IntMax
Int64Max = 9223372036854775807
Int64Min = -Int64Max


class TestStringUtils < Test::Unit::TestCase
  def test_itoa
    assert_equal("#{IntMax}", itoa(IntMax), "itoa works for IntMax")
    assert_equal("#{IntMin}", itoa(IntMin), "itoa works for IntMin")
    assert_equal("#{Int64Max}", itoa(Int64Max), "itoa works for Int64Max")
    assert_equal("#{Int64Min}", itoa(Int64Min), "itoa works for Int64Min")
  end
end
