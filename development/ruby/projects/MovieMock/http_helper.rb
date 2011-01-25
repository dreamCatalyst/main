#
#
#

require 'open-uri'

class HttpHelper
  def self.perform_download(url, dest)
    open(url) do |source_file|
      open(dest, "w") do |dest_file|
        dest_file << source_file.read(source_file.size)
      end
    end
  end
end

# don't you just love it when stuff is just easy -insert sigh of relief-

