require 'mkmf'

extension_name = "jmutil_ruby"

dir_config('jmutil')  # Should point to .. for simple local testing
find_library("jmutil", "_ZN2JM4Util9FileUtils6existsEPKc")

create_makefile(extension_name)

