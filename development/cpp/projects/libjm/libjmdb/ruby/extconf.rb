require 'mkmf'

extension_name = "jmdb_ruby"

dir_config('jmdb')  # Should point to .. for simple local testing
find_library("jmdb", "_ZN2JM2DB11StringField9getStringEv")
create_makefile(extension_name)

