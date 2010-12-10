project(libjmdb)
cmake_minimum_required(VERSION 2.8)

include(CheckIncludeFiles)

option(WITH_SQLITE3 "Compile with support for sqlite3" ON)
option(WITH_MYSQL "Compile with support for mysql" ON)

if(${WITH_SQLITE3})
  check_include_files("sqlite3.h" HAVE_SQLITE3)
  if(${HAVE_SQLITE3})
    message("compiling sqlite3 support")
  else(${HAVE_SQLITE3})
    message(SEND_ERROR "sqlite3.h not found")
  endif(${HAVE_SQLITE3})
else(${WITH_SQLITE3})
  message("disabling sqlite3 support")
endif(${WITH_SQLITE3})

if(${WITH_MYSQL})
  check_include_files("mysql/mysql.h" HAVE_MYSQL)
  if(${HAVE_MYSQL})
    message("compiling mysql support")
  else(${HAVE_MYSQL})
    message(SEND_ERROR "mysql/mysql.h not found")
  endif(${HAVE_MYSQL})
else(${WITH_MYSQL})
  message("disabling mysql support")
endif(${WITH_MYSQL})

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

# Add the libjmutil source directory to the include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libjmutil)

# -------------- next target ------------

add_library(jmdb SHARED
  jmdb_databasehandlerfactory.cpp
  jmdb_columninformation.cpp
  jmdb_field.cpp
  jmdb_resultrow.cpp
  jmdb_preparedstatement.cpp
  jmdb_sqlitedatabasehandler.cpp
  jmdb_sqliteresultrow.cpp
  jmdb_sqliteresultset.cpp
  jmdb_sqlitepreparedstatement.cpp
  jmdb_mysqldatabasehandler.cpp
)
target_link_libraries(jmdb sqlite3 mysqlclient jmutil)

# -------------- install files ----------
