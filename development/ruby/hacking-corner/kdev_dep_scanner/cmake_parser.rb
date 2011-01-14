#
#
#


#-----------------------------------------------
# TODO write the docs for this
# There are 4 classes and they are used as such blablabla
#
#-----------------------------------------------


class CMakeParserResult
  attr_accessor :subdirectories, :targets, :variables, :link_libraries, :filename

  def initialize(fn)
    @filename = fn
    @subdirectories = []
    @targets = []
    @variables = []
    @link_libraries = {}
  end
end

##
# type can be :executable, :library or :plugin
# libtype can be :shared, :static, :module, or "" for executables
class CMakeTarget
  attr_accessor :name, :type, :libtype, :sources
  def initialize
    @sources = []
    @libtype = ""
  end
end


class CMakeVariable
  attr_accessor :name, :values;
  def initialize
    @values = []
  end
end


##
# This is an internal class used by CMakeParser
class CMakeParserToken
  attr_reader :content

  def initialize
    @open_paren_count = 0
    @open_string = false
    @content = []
  end

  def content_string
    @content.join(" ")
  end

  def add_line(line)
    @content << parse_line(line)
  end

  def is_valid
    @open_paren_count == 0 and !@open_string
  end

  def parse_line(line)
    new_line = ""
    prev_char = nil
    line.each_char do |c|
      break if c == '#' and !@open_string
      parse_character(c, prev_char)
      prev_char = c
      new_line += c
    end
    new_line
  end

  def parse_character(c, prev)
    if c == '"' and !@open_string
      @open_string = true
    elsif c == '"' and @open_string and prev != '\\' 
      @open_string = false
    elsif !@open_string
      @open_paren_count += 1 if c == '('
      @open_paren_count -= 1 if c == ')'
    end
  end
end


##
#  TODO: write docs
#
class CMakeParser
  attr_reader :has_error, :result

  def set_error
    @has_error = true
    @result = nil
  end
 
  def reset(path)
    @result = CMakeParserResult.new(path)
    @has_error = false
    @current_token = nil
  end

  def parse(path)
    return set_error if path.nil? or !File.exist?(path)
    parse_path(path)
  end

  def parse_path(path)
    if File.directory?(path)
      parse_directory(path)
    else
      parse_file(path)
    end
    @result
  end

  def parse_directory(path)
    parse_file("#{path}/CMakeLists.txt")
  end

  def parse_file(path)
    reset(path)
    IO.readlines(path).each do |line|
      parse_line(line.strip)
    end
    set_error if !@current_token.nil?
    @result
  end

  def parse_line(line)
    return if line.empty?

    @current_token = CMakeParserToken.new if @current_token.nil?
    @current_token.add_line(line)
    parse_current_token if @current_token.is_valid
  end

  # -------------------
  # All code that follows is copied verbatim from the old version and needs to
  # be refactored
  # ------------------

  def parse_current_token
    startline = @current_token.content[0]
  
    if( startline.start_with?( "add_executable") )
      add_executable_target
    elsif( startline.start_with?("add_library") )
      add_library_target
    elsif(startline.start_with?("kde4_add_library"))
      add_kde_library_target
    elsif(startline.start_with?("kde4_add_plugin"))
      add_plugin_target
    elsif(startline.start_with?("kde4_add_executable"))
      add_kde_executable_target
    elsif(startline.start_with?("add_subdirectory"))
      add_subdirectory
    elsif(startline.start_with?("target_link_libraries"))
      add_link_libraries
    end
    add_variable if(startline =~ /^set[\s]*\(/)  # put here because of the regexp

    @current_token = nil
  end

  def parser_error(meth_str)
    puts "A parser error occurred while processing: '#{@result.filename}'"
    puts "current token content:"
    puts @current_token.content.join("\n")
    #exit -1
  end

  ##
  # extracts the first argument for a command (which is usually the name)
  # For example: set( SomeVar .... )
  def extract_name_for_command(str, command_name)
    r = str =~ /^(#{command_name}[\s]*\([\s]*([\w]*))/
    parser_error(command_name) if r.nil?
    return [ $1, $2 ]
  end

  def extract_value_list(str)
    str.strip!
    str.chop! if str.end_with? ")"
    words = str.split(/[\s]+/)
    lst = []
    words.each do |w|
      if w.start_with? "${"
        lst += get_variable_value(w)
      else
        lst << w
      end
    end
    #puts "--extract_value_list returns: #{lst.join(',')}"
    #puts "---list size= #{lst.size}"
    lst
  end

  def get_variable_value(identifier)
    identifier =~ /\$\{[\s]*([\w]+)/
    name = $1
    @result.variables.each do |var|
      return var.values if var.name == name
    end
    puts "value list for variable '#{name}' not found"
    return []
  end

  def add_variable
    #puts "--add_variable()"
    var = CMakeVariable.new

    # extract name
    str = @current_token.content_string
    match, var.name = extract_name_for_command(str, "set")
    
    # extract the list of values
    str = str[match.length..-1]
    var.values = extract_value_list(str)
    
    #puts "---add_variable #{var.name}"
    @result.variables << var
  end

  def add_subdirectory
    #puts "--add_subdirectory"
    match, name = extract_name_for_command(
        @current_token.content_string, "add_subdirectory")
    #puts "---add_subdir #{name}"
    @result.subdirectories << name
  end

  def add_executable_target
    #puts "--add_executable_target"
    target = CMakeTarget.new
    target.type = :executable

    # get the name
    str = @current_token.content_string
    match, name = extract_name_for_command(str, "add_executable")
    target.name = name
    str = str[match.length..-1]

    str = remove_options_from_string(str,
        %w[ WIN32 MACOSX_BUNDLE EXCLUDE_FROM_ALL ])

    # and get the list of sources
    target.sources = extract_value_list(str)

    @result.targets << target
  end

  def remove_options_from_string(str, options)
    options.each do |option|
      if str =~ /^([\s]*#{option}[\s]*)/
        str = str[$1.length..-1]
      end
    end
    str
  end
 
  def add_kde_executable_target
    #puts "--add_executable_target"
    target = CMakeTarget.new
    target.type = :executable

    # get the name
    str = @current_token.content_string
    match, name = extract_name_for_command(str, "kde4_add_executable")
    target.name = name
    str = str[match.length..-1]

    # and get the list of sources
    target.sources = extract_value_list(str)

    @result.targets << target
  end

  def add_library_target
    #puts "--add_library_target"
    libtarget = CMakeTarget.new
    libtarget.type = :library

    # get the name
    str = @current_token.content_string
    match, name = extract_name_for_command(str, "add_library")
    #puts "---add_library set name '#{name}'"
    libtarget.name = name
    str = str[match.length..-1]

    # get the optional library type
    if str =~ /^([\s]*(SHARED|STATIC|MODULE|)[\s]*)/i
      libtarget.libtype = $2.downcase.to_sym
      str = str[$1.length..-1]
    end
    # remove the optional EXCLUDE_FROM_ALL
    if str =~ /^([\s]*EXCLUDE_FROM_ALL[\s]*)/
      str = str[$1.length..-1]
    end
    # and the list of sources
    libtarget.sources = extract_value_list(str)

    @result.targets << libtarget
  end

  def add_kde_library_target
    #puts "--add_library_target"
    libtarget = CMakeTarget.new
    libtarget.type = :library

    # get the name
    str = @current_token.content_string
    match, name = extract_name_for_command(str, "kde4_add_library")
    #puts "---add_library set name '#{name}'"
    libtarget.name = name
    str = str[match.length..-1]

    # get the optional library type
    r = str =~ /^([\s]*(SHARED|STATIC|MODULE|)[\s]*)/i
    if !r.nil?
      libtarget.libtype = $2.downcase.to_sym
      str = str[$1.length..-1]
    end
    # and the list of sources
    libtarget.sources = extract_value_list(str)

    @result.targets << libtarget
  end

  def add_plugin_target
    #puts "--add_plugin_target"
    plugintarget = CMakeTarget.new
    plugintarget.type = :plugin

    # get the name
    str = @current_token.content_string
    match, name = extract_name_for_command(str, "kde4_add_plugin")
    plugintarget.name = name
    str = str[match.length..-1]

    # and the list of sources
    plugintarget.sources = extract_value_list(str)

    @result.targets <<  plugintarget
  end

  def add_link_libraries
    #puts "--add_link_libraries"
    str = @current_token.content_string
    match, name = extract_name_for_command(str, "target_link_libraries")

    str = str[match.length..-1]
    @result.link_libraries[name] = extract_value_list(str)
  end
end

