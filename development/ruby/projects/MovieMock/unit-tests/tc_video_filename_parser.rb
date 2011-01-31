#
#
#


require 'test/unit'
require 'video_filename_parser'


class TestVideoFilenameParser < Test::Unit::TestCase
  Expectations = {
    "Family.Guy.S09E21.Its.a.Trap.DVDRip.XviD-REWARD.avi" =>
      { :name => "Family Guy",
        :season => 9,
        :episode => 21,
        :title => "Its a Trap",
        :release_group => "REWARD"
      },
    "Stargate Atlantis S01E03 - Hide and Seek.avi" =>
      { :name => "Stargate Atlantis",
        :season => 1,
        :episode => 3,
        :title => "Hide and Seek"
      },
    "Doctor.Who.2005.S05E01.The.Eleventh.Hour.HDTV.XviD-FoV.[VTV].avi" =>
      { :name => "Doctor Who 2005",
        :season => 5,
        :episode => 1,
        :title => "The Eleventh Hour",
        :release_group => "FoV [VTV]"
      },
    "Lie.to.Me.S03E01.HDTV.XviD-LOL.[VTV].avi" =>
      { :name => "Lie to Me",
        :season => 3,
        :episode => 1,
        :release_group => "LOL [VTV]"
      },
    "V.2009.S02E03.Laid.Bare.HDTV.XviD-FQM.avi" =>
      { :name => "V 2009",
        :season => 2,
        :episode => 3,
        :title => "Laid Bare",
        :release_group => "FQM"
      },
    "b5.122-amc.avi" =>
      { :name => "B5",
        :season => 1,
        :episode => 22,
        :release_group => "amc"
      },
    "Babylon5.1x00.The_Gathering.REPACK.DVDRip.XviD-DKi.avi" =>
      { :name => "Babylon5",
        :season => 1,
        :episode => 0,
        :title => "The Gathering",
        :release_group => "DKi"
      },
    "Battlestar Galactica - 4x02 - Six of One.avi" =>
      { :name => "Battlestar Galactica",
        :season => 4,
        :episode => 2,
        :title => "Six of One"
      },
    "the.big.bang.theory.s03e01.hdtv.xvid-notv.avi" =>
      { :name => "The Big Bang Theory",
        :season => 3,
        :episode => 1,
        :release_group => "notv"
      },
    "the_new_adventures_of_old_christine-S01E01-Pilot.avi" =>
      { :name => "The New Adventures of Old Christine",
        :season => 1,
        :episode => 1,
        :title => "Pilot"
      },
    "Spartacus.Gods.of.the.Arena.Pt.I.720p.HDTV.X264-DIMENSION.mkv" =>
      { :name => "Spartacus Gods of the Arena Pt I",
        :release_group => "DIMENSION"
      },
    "Spartacus.Gods.of.the.Arena.Pt.II.720p.HDTV.X264-CTU.mkv" =>
      { :name => "Spartacus Gods of the Arena Pt II",
        :release_group => "CTU"
      },
    "Spartacus.Gods.of.the.Arena.Pt.I.HDTV.XviD-SYS.avi" =>
      { :name => "Spartacus Gods of the Arena Pt I",
        :release_group => "SYS"
      },
    "Supernatural.S06E07.HDTV.XviD-2HD.avi" =>
      { :name => "Supernatural",
        :season => 6,
        :episode => 7
      },
    "Fringe.S03E05.720p.HDTV.X264-DIMENSION.mkv" =>
      { :name => "Fringe",
        :season => 3,
        :episode => 5,
        :release_group => "DIMENSION"
      },
    "Star Trek TNG - 2x03 - Elementary, Dear Data.avi" =>
      { :name => "Star Trek Tng",
        :season => 2,
        :episode => 3,
        :title => "Elementary, Dear Data"
      }
  }

  @@parser = VideoFilenameParser.new
  @@results = {}
  @@test_count = 0
  Expectations.each do |filename, expected_hash|
    # get the results
    @@results[filename] = @@parser.parse(filename)

    # create tests dynamically one for each key that is expected
    @@key_count = 0
    expected_hash.each do |key,val|

key_test_fun_str = <<EOS
  def test_#{@@test_count}_akey_#{@@key_count}
    assert_equal( #{val.class == String ? ('"' + val + '"') : val },
        @@results["#{filename}"][:#{key}],
        "Filename: '#{filename}' key: #{key}" )
  end
EOS
      eval key_test_fun_str
      @@key_count += 1
    end

    # and create one testing the hash_equality
gen_test_fun_str = <<EOS
  def test_#{@@test_count}_generic
    assert_equal( Expectations["#{filename}"], @@results["#{filename}"],
          "Filename: '#{filename}'" )
  end
EOS
    eval gen_test_fun_str
    @@test_count += 1
  end

end

