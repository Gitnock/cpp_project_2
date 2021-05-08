// Name:Enock lubega
// Seneca Student ID: 154192181
// Seneca email:elubega@myseneca.ca
// Date of completion:3/16/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <iomanip>
namespace sdds {
	class Station
	{
		size_t mStationId;
		std::string mItemName;
		std::string mDesc;
		size_t mSerial;
		size_t mQuantity;

		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string line);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}
#endif // !SDDS_STATION_H

