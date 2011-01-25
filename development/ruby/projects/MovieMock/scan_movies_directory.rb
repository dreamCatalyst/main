#
#
#

require 'directory_helper'


class MovieFileDescriptor
  attr_accessor :name, :year, :directory, :video_files

  def initialize(path)
    if(File.directory?(path))
      initialize_w_directory(path)
    else
      initialize_w_file(path)
    end
  end

  def has_subtitle
    true  # TODO  implement this less silly
  end

  private
  def initialize_w_file(file)
    if file =~ /^(.+)\/([^\/]+)$/
      @directory = $1
      filename = $2
      if filename =~ /(.+) - ([\d]+)\....$/
        @name = $1
        @year = $2
      else
        @name = filename
        @year = 0
      end
    else
      puts "Provided file-path is unexpected: '#{file}'"
      @directory = ""
      @name = file
      @year = 0
    end
    @video_files = [ file ]
  end

  def initialize_w_directory(dir)
    @directory = dir
    if dir =~ /\/?([^\/]+) - ([\d]+)$/
      @name = $1
      @year = $2
    else
      puts "Directory '#{dir}' doesn't match the naming convention!"
      @name = dir
      @year = 0
    end
    @video_files = get_video_files_in_dir
  end

  def get_video_files_in_dir
    Dir.glob(@directory + "/*.avi")  # for now
  end

end

class MyMoviesDirectoryParser
  attr_accessor :base_directory

  def initialize
    @base_directory = "/mnt/TERRA2/Movies"
  end

  def get_movie_list
    @movie_list = []
    Dir.glob(@base_directory + "/*").sort.each do |entry|
      entry_fn = File.basename(entry)
      next if entry_fn == "." or entry_fn == ".."
      add_directory(entry)
    end
    return @movie_list
  end

  private
  def add_directory(dirname)
    return if File.basename(dirname).size == 1  # Skip the marker-directories A, B, C etc TODO which this apparently does NOT accomplish
    return add_collection_directory(dirname) if dirname =~ /Collection/
    @movie_list << MovieFileDescriptor.new(dirname)
  end

  def add_collection_directory(dirname)
    video_files = DirectoryHelper.files_filtered_by_extension(dirname, "avi")
    if(video_files.size > 0)
      video_files.each do |video_file|
        @movie_list << MovieFileDescriptor.new(video_file)
      end
    else
      Dir.glob(dirname + "/*").each do |entry|
        next if entry == "." or entry == ".."
        if File.directory?(entry)
          @movie_list << MovieFileDescriptor.new(entry)
        end
      end
    end
  end

end

