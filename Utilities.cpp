// Name:Enock lubega
// Seneca Student ID: 154192181
// Seneca email:elubega@myseneca.ca
// Date of completion:3/17/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
namespace sdds {
	char Utilities::m_delimiter = '\0';
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;

	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		
		std::string out;

		size_t end = str.find_first_of(m_delimiter, next_pos);

		
		if (next_pos < str.length()) {

			//handle after delimiter
			if (end == std::string::npos) {
				out = str.substr(next_pos);
				if(out.length()>getFieldWidth())
					setFieldWidth(out.length());
				more = false;
			}
			else {
				out = str.substr(next_pos, end - next_pos);
				if (out.length() > getFieldWidth())
					setFieldWidth(out.length());
				if (out.empty()) {
					more = false;
					throw "empty";
				}
				next_pos = end + 1;
				more = true;
			}
		}
		else {
			more = false;
		}
		return out;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;

	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}
