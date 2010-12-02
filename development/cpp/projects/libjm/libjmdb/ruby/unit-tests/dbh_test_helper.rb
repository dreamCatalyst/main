# This file is a part of the libjm project
# Copyright 2010 - Jonathan Maasland - nochoice AT xs4all DOT nl
#
# dbh_test_helper.rb - A small module to include in databasehandler unittests.

module DBHTestHelper
  def check_no_error(dbh = nil)
    dbh = @dbh unless dbh
    assert_equal([ 0, "" ], [ dbh.errorCode, dbh.errorMessage ],
                 "errorCode is NO_ERROR and errorMessage is empty")
  end
  
  def check_error_is_set(dbh = nil)
    dbh = @dbh unless dbh
    # TODO find out how we can use CONNECTION_ERROR here
    assert_not_equal(0, dbh.errorCode, "the errorCode is set")
    assert_not_equal("", dbh.errorMessage, "the errorMessage is set")
  end
end
