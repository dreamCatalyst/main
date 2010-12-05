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
    result = statement.executeSelectQuery
    check_select_result(result, 2)
  end
  
  # ----------------- Simple bind tests
  
  def test_bind_int_by_name
    statement = prepare_query("select * from Customer where id=$id")
    statement.bind("$id", 1)
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  def test_bind_int_by_index
    statement = prepare_query("select * from Customer where id=$id")
    statement.bind(1, 1)
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  def test_bind_int64_by_name
    statement = prepare_query("select * from Item where retailId=$retailId")
    statement.bind("$retailId", 1234567890123456789)
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  def test_bind_int64_by_index
    statement = prepare_query("select * from Item where retailId=$retailId")
    statement.bind(1, 1234567890123456789)
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  def test_bind_double_by_name
    statement = prepare_query("select * from Item where price=$price")
    statement.bind("$price", 18.95)
    result = statement.executeSelectQuery
    check_select_result(result, 2)
  end
  
  def test_bind_double_by_index
    statement = prepare_query("select * from Item where price=$price")
    statement.bind(1, 18.95)
    result = statement.executeSelectQuery
    check_select_result(result, 2)
  end
  
  def test_bind_string_by_name
    statement = prepare_query("select * from Customer where firstName=$name")
    statement.bind("$name", "Jonathan")
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  def test_bind_string_by_index
    statement = prepare_query("select * from Customer where firstName=$name")
    statement.bind(1, "Jonathan")
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  # ---------------- More complex bind tests
  
  def test_bind_multiple_variables_by_name
    statement = prepare_query(
      "select * from Customer where firstName=$fname and lastName=$lname")
    statement.bind("$fname", "Jonathan")
    statement.bind("$lname", "Maasland")
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  def test_bind_multiple_variables_by_index
    statement = prepare_query(
      "select * from Customer where firstName=$fname and lastName=$lname")
    statement.bind(1, "Jonathan")
    statement.bind(2, "Maasland")
    result = statement.executeSelectQuery
    check_select_result(result, 1)
  end
  
  def test_bind_multiple_variable_types_by_index
    statement = prepare_query(
      "select * from Item where price=$price and name like $name")
    statement.bind(1, 18.95)
    statement.bind(2, "%Weeds%")
    result = statement.executeSelectQuery
    check_select_result(result, 2)
  end
  
  def test_bind_multiple_variable_types_by_name
    statement = prepare_query(
      "select * from Item where price=$price and name like $name")
    statement.bind("$price", 18.95)
    statement.bind("$name", "%Weeds%")
    result = statement.executeSelectQuery
    check_select_result(result, 2)
  end
  
  def test_multiple_executions
    statement = prepare_query(
      "select * from Customer where firstName like $fname")
    statement.bind("$fname", "Jonathan")
    result1 = statement.executeSelectQuery
    check_select_result(result1, 1)
    
    statement.bind("$fname", "%")
    result2 = statement.executeSelectQuery
    check_select_result(result2, 2)
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
