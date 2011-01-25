#
#
#


class DirectoryHelper
  def self.files_filtered_by_extension(directory, extensions)
    re_string = ""
    extensions.each do |ext| re_string += "(#{ext}$)|" end
    re_string.chop!
    re = Regexp.new(re_string)

    @matched_files = []
    Dir.glob(directory + "/*").each do |filepath|
      @matched_files << filepath if filepath =~ re
    end
    return @matched_files
  end
end

