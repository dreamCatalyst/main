# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
#

module DBHTestBase
module TestColumnTypes

  def test_column_types
    strVal = "string"
    intVal = 1
    doubleVal = -100.504
    
    @dbh.execute( %{
      create table Test(id integer primary key autoincrement,
        stringField text, intField int, doubleField real);
      insert into Test (stringField,intField,doubleField) values
        ("#{strVal}", #{intVal}, #{doubleVal});
      insert into Test (stringField,intField,doubleField) values
        ( NULL, NULL, NULL );
    })
    check_no_error
    
    rs = @dbh.executeSelectQuery("select * from Test order by id")
    row1 = rs.next()
    assert_equal(1, row1.getInt("id"), "id is 1")
    assert_equal(strVal, row1.getString("stringField"), "getString() returns correctly for stringField")
    assert_equal(intVal, row1.getInt("intField"), "getInt() returns correctly for intField")
    assert_equal(doubleVal, row1.getDouble("doubleField"), "getDouble() returns correctly for doubleField")
    
    ["stringField", "intField", "doubleField"].each do |f|
      assert(!row1.isNull(f), "field '#{f}' is not null")
    end
    
    row2 = rs.next();
    assert_equal(2, row2.getInt("id"), "id is 2")
    ["stringField", "intField", "doubleField"].each do |f|
      assert(row2.isNull(f), "field '#{f}' _is_ null")
    end
  end

end
end