#
#
#

require 'roman_numeral_helper'
require 'pp'

class VideoFilenameParser
  def parse(filename)
    return {} if(filename.nil? or filename.empty?)
    fn = filename.gsub(/\.|_|-/, ' ')
    fn = remove_resolution_fields(fn)
    @filename_fields = fn.split(" ")
    @filename_fields.pop  # pop the extension
    @result = { }
    parse_components
    return @result
  end

  private
  def remove_resolution_fields(fn)
    fn.gsub(/480p|720p|1080p|x264|H264/i, " ")
  end

  def parse_components
    find_and_set_season_episode_fields
    parse_name
    parse_title
    parse_release_group
  end

  SeasonEp_Regexps = [
    /s([\d]+)e([\d]+)/i,
    /([\d])+x([\d]+)/i,
    /(\d)(\d\d)/
  ]

  ##
  # Currently supported formats are:
  # * s00e00
  # * s0e00
  # * 0x00
  # * 000
  def find_and_set_season_episode_fields
    @season_ep_field_pos = nil
    SeasonEp_Regexps.each do |re|
      @filename_fields.each_with_index do |fn_field, idx|
        if fn_field =~ re
          @season_ep_field_pos = idx
          @result[:season] = $1.to_i
          @result[:episode] = $2.to_i
          break
        end
      end
      break unless @season_ep_field_pos.nil?
    end
    @season_ep_field_pos
  end
  

  def parse_name
    if @season_ep_field_pos.nil?
      # set name to start until either release_group or end_thingie is matched
      name = get_title_or_name_string(0)
      unless name.nil?
        @result[:name] = beautify_name(name)
      end
    else
      #puts "Parsing name @sef_pos=#{@season_ep_field_pos}"
      #pp @filename_fields
      @result[:name] = beautify_name(@filename_fields[0...@season_ep_field_pos])
    end
  end

  NoCapWords = %w{ the a of to }
  def beautify_name(name_fields)
    if(name_fields.class == String)
      name_fields = name_fields.split(" ")
    end

    if(name_fields.size == 1)
      return name_fields[0].capitalize
    end
    first = name_fields.shift.capitalize
    capped = name_fields.map do |f| 
      if NoCapWords.include?(f)
        f.downcase
      elsif RomanNumeralHelper.is_valid_numeral(f)
        f.upcase
      else 
        f.capitalize
      end
    end
    return first + " " + capped.join(" ")
  end

  def parse_title
    return if @season_ep_field_pos.nil?
    start = @season_ep_field_pos + 1
    title = get_title_or_name_string(start)
    unless title.nil?
      @result[:title] = title
    end
  end

  AdditionalTitleEndMarkers =
    %w{ hdtv xvid dvdrip pdtv ws repack }

  def get_title_or_name_string(start = 0)
    str = ""
    @filename_fields[start..-1].each do |field|
      if AdditionalTitleEndMarkers.include?(field.downcase) or
          ReleaseGroups.include?(field.downcase)
        break
      else
        str += field + " "
      end
    end

    return (str == "") ? nil : str.chop
 end

  ReleaseGroups =
    %w{ dimension ctu sys notv dki fqm lol [vtv] reward amc fov }
  def parse_release_group
    num_fields_to_parse = 4
    if(@filename_fields.size < num_fields_to_parse)
      num_fields_to_parse = @filename_fields.size
    end

    rls_group = ""
    @filename_fields[(-1*num_fields_to_parse)..-1].each do |field|
      rls_group += field + " " if ReleaseGroups.include? field.downcase
    end
    if(rls_group != "")
      @result[:release_group] = rls_group.chop
    end
  end
end


