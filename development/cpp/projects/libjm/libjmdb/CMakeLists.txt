project(libjmdb)
cmake_minimum_required(VERSION 2.8)

include(CheckIncludeFiles)


option(WITH_SQLITE3 "Compile with support for sqlite3" ON)
option(WITH_MYSQL "Compile with support for mysql" OFF)

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
  message(SEND_ERROR "support for mysql isn't implemented")
endif(${WITH_MYSQL})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# Add the libjmutil source directory to the include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libjmutil)

# -------------- next target ------------

add_library(jmdb SHARED jmdb_databasehandlerfactory.cpp jmdb_columninformation.cpp jmdb_field.cpp jmdb_resultrow.cpp 
    jmdb_sqlitedatabasehandler.cpp jmdb_sqliteresultrow.cpp jmdb_sqliteresultset.cpp )
target_link_libraries(jmdb sqlite3 jmutil)

# -------------- install files ----------
