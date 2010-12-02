# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
#

module DBHTestBase
module TestSelect
  def test_execute_select
    @dbh.execute("create table Test( id number )")
    10.times do |i| @dbh.execute("insert into Test (id) VALUES (#{i})") end
    check_no_error
    
    resultSet = @dbh.executeSelectQuery("select id from Test");
    check_no_error
    assert_not_nil(resultSet, "executeSelectQuery returns non-nil")
    assert_equal(10, resultSet.rowCount, "resultSet.rowCount() returns the correct number of rows")
    
    # Column related tests
    colInfo = resultSet.getColumnInformation
    assert_not_nil(colInfo, "getColumnInformation() returns a valid object")
    assert_equal(1, colInfo.numColumns(), "the correct number of columns is returned")
    assert_equal("id", colInfo.columnName(0), "columnName() returns the correct name")
    assert_equal(0, colInfo.columnIndex("id"), "columnIndex() returns the correct index for fieldname")
    # TODO howto handle non-existing column names
    
    # Iterator row moving related tests
    row = resultSet.current();
    assert_not_nil(row, "current() returns a valid object")
    row2 = resultSet.current();
    # assert_equal(row, row2, "current() returns the same object") # TODO swig trickiness
    
    rowList = [ row ]
    9.times do |idx|
      row2 = resultSet.next();
      assert(!rowList.include?(row2), "next() returns a different row object every time")
      assert_not_nil(row2, "the returned value of next() isn't nil")
      assert_equal( idx+1, row2.getInt("id"), "getInt('id') returns the correct value")
      assert_equal( idx+1, row2.getInt(0), "getInt(0) returns the correct value")
      rowList << row2
    end
    row2 = resultSet.next();
    assert_nil(row2, "moving past the last row returns nil")
    assert_nil(resultSet.current(), "current() also returns nil after moving past the end")
  end
end
end