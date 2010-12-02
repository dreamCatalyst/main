# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
#

module DBHTestBase
module TestExecute
  def test_executing_statements
    n = @dbh.execute("create table Test( id number )")
                     assert_equal(0, n, "execute('create table') returns NO_ERROR")
    check_no_error
    
    n = @dbh.execute("insert into Test (id) values (1)")
    assert_equal(0, n, "execute('insert into') returns NO_ERROR")
    assert_equal(1, @dbh.affectedRowCount, "affectedRowCount returns 1")
    check_no_error
    
    n = @dbh.execute("update Test set id=id+10")
    assert_equal(0, n, "execute('update') returns NO_ERROR")
    assert_equal(1, @dbh.affectedRowCount, "affectedRowCount returns 1")
    check_no_error
    
    n = @dbh.execute("delete from Test where id > 10")
    assert_equal(0, n, "execute('delete from') returns NO_ERROR")
    assert_equal(1, @dbh.affectedRowCount, "affectedRowCount returns 1")
    check_no_error
  end
end
end