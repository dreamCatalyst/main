#
#
#


class DirectoryHelper
  def self.files_filtered_by_extension(directory, extensions)
    re_string = ""
    extensions.each do |ext| re_string += "(\.#{ext}$)|" end
    re_string.chop!
    re = Regexp.new(re_string)

    @matched_files = []
    Dir.glob(directory + "/*").each do |filepath|
      @matched_files << filepath if filepath =~ re
    end
    return @matched_files
  end

  def self.get_user_home
    home_var = [ "HOME", "HOMEPATH"].detect do |h| ENV[h] end
    if home_var.nil?
      puts "Could not detect your home directory! Please contact me (the author)"
      return "."
    end
    return ENV[home_var]
  end

  # Creates the given path much like "mkdir -p" would do.
  # TODO: How would we do this on Windows?
  def self.mkdir_p(path)
    existing_path = ""
    path_components = path.split "/"

    if path.start_with? "/"
      path_components.shift
    else
      existing_path = path_components.shift
    end
    
    path_components.each do |p|
      existing_path += ("/" + p)
      Dir.mkdir existing_path unless File.directory?(existing_path)
    end
    true
  end
end

