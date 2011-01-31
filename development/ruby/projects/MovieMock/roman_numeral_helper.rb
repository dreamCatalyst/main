#
#
#

class RomanNumeralHelper
  # Let's keep it simple for now
  SimpleValues = %w{ i ii iii iv v vi vii viii ix x xi xii }
  def self.is_valid_numeral(str)
    SimpleValues.include?(str.downcase)
  end
end
