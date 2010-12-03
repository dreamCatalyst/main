# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
#

module DBHTestBase
module TestPreparedStatement
  # Helper method to test the correctness of a resultset
  def check_select_result(result_set, expected_row_count)
    check_no_error
    assert_not_nil(result_set, "executeSelect returns a valid object")
    assert_equal(expected_row_count, result_set.rowCount, "resultset has the correct number of rows")
  end
  
  def prepare_query(sql)
    statement = @dbh.prepareQuery(sql)
    check_no_error
    assert_not_nil(statement, "prepareQuery returns a valid object")
    return statement
  end
  
  def test_pstatement_novars
    statement = prepare_query("select * from Customer")
    result = statement.executeSelectQuery();
    check_select_result(result, 2)
  end
  
  def test_bind_named_int_var
    statement = prepare_query("select * from Customer where id=$id")
    statement.bind("$id", 1)
    result = statement.executeSelectQuery();
    check_select_result(result, 1)
  end
  
  def test_bind_named_int64
    #assert(false, "test not written")
  end
  
  def test_bind_named_double
    #assert(false, "test not written")
  end
  
  def test_bind_named_string
    #assert(false, "test not written")
  end
  
  def test_bind_index_int
    #assert(false, "test not written")
  end
  
  def test_bind_indexed_int64
    #assert(false, "test not written")
  end
  
  def test_bind_indexed_double
    #assert(false, "test not written")
  end
  
  def test_bind_indexed_string
    #assert(false, "test not written")
  end
  
  def test_bind_multiple_variables
    #assert(false, "test not written")
  end
  
  def test_multiple_executions
    #assert(false, "test not written")
  end
  
  def test_sqlinjection
    statement = prepare_query("insert into Address (street,zipcode,city) values ($street,$zip,$city)")
    street = "someValue"
    zip = "zipcode"
    city = "'); delete from Address; ('"
    statement.bind("$street", street)
    statement.bind("$zip", zip)
    statement.bind("$city", city)
    statement.execute
    check_no_error
    rs = @dbh.executeSelectQuery("select * from Address");
    assert_equal(3, rs.rowCount, "sql-injection was handled correctly")
    # assert_equal(city, rs.getRowList()[2].getField("city"), "the corrupt value was inserted correctly")
    rs.next; rs.next
    row = rs.current;
    assert_equal(city, row.getField("city").getString(), "the corrupt value was inserted correctly")
  end
  
end
end
