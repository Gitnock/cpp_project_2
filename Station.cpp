// Name:Enock lubega
// Seneca Student ID: 154192181
// Seneca email:elubega@myseneca.ca
// Date of completion:3/16/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Station.h"
#include "Utilities.h"


namespace sdds {
	size_t Station::id_generator = 0;
	size_t Station::m_widthField = 0;

	Station::Station(const std::string line)
	{
		Utilities util;
		size_t pos = 0u;
		bool isMore = true;

		mItemName = util.extractToken(line, pos, isMore);
		mSerial = stoi(util.extractToken(line, pos, isMore));
		mQuantity = stoi(util.extractToken(line, pos, isMore));

		if (mItemName.length() > m_widthField) {
			m_widthField = mItemName.length();
			util.setFieldWidth(m_widthField);
		}

		mDesc = util.extractToken(line, pos, isMore);

		mStationId = ++id_generator;

		

	}
	const std::string& Station::getItemName() const
	{
		return mItemName;
	}
	size_t Station::getNextSerialNumber()
	{
		return mSerial++;
	}
	size_t Station::getQuantity() const
	{
		return mQuantity;
	}
	void Station::updateQuantity()
	{
		if (getQuantity() > 0)
			--mQuantity;
	}
	void Station::display(std::ostream& os, bool full) const
	{
		if (full) {
			os << "[" << std::setfill('0') << std::right << std::setw(3) << mStationId << "]" << " Item: " << std::left << std::setfill(' ');
			os << std::setw(m_widthField) << getItemName() << " [" << std::setfill('0');
			os << std::setw(6) << std::right << mSerial << "] " << "Quantity: " << std::left << std::setfill(' ');
			os << std::setw(m_widthField) << getQuantity() << " Description: " << mDesc;

		}
		else {

			os << "[" << std::setfill('0') << std::setw(3) << mStationId << "]"<< " Item: " << std::left << std::setfill(' ') << std::setw(m_widthField) << mItemName
				<< " [" << std::setfill('0') << std::setw(6) << std::right << mSerial << "]";

		}
		os << std::endl;

	}
}