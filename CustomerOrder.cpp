// Name:Enock lubega
// Seneca Student ID: 154192181
// Seneca email:elubega@myseneca.ca
// Date of completion:3/23/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "CustomerOrder.h"
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder()
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
	}
	CustomerOrder::CustomerOrder(const std::string& line)
	{
		Utilities util;
		size_t pos = 0u;
		bool isMore = true;
		std::string item = "";

		m_name = util.extractToken(line, pos, isMore);
		m_product = util.extractToken(line, pos, isMore);

		m_cntItem = std::count(line.begin(), line.end(), util.getDelimiter()) - 1;
		
		this->m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {

			item = util.extractToken(line, pos, isMore);
			m_lstItem[i] = new Item(item);
		}

		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder&)
	{
		throw std::string("Cannot make copies.");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& that) noexcept
	{
		*this = std::move(that);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& that) noexcept
	{
		if (this != &that) {
			m_lstItem = that.m_lstItem;
			m_name = that.m_name;
			m_product = that.m_product;
			m_cntItem = that.m_cntItem;
			that.m_lstItem = nullptr;
			that.m_name = "";
			that.m_cntItem = 0u;
			that.m_product = "";
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	bool CustomerOrder::isFilled() const
	{
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
				isFilled = false;
		}
		return isFilled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool isGood = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (m_lstItem[i]->m_isFilled == false)
					isGood = false;
			}
		}
		return isGood;

	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			//os << "MAGA TEST:" << station.getItemName() << std::endl;
			if (station.getItemName() == m_lstItem[i]->m_itemName)
			{
				
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", "
						<< m_product << " [" << station.getItemName() << "]" << std::endl;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", "
						<< m_product << " [" << station.getItemName() << "]" << std::endl;
				}
			}
		}

	}
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::right << std::setw(6)<< std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setw(16) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) 
				os << "FILLED";
			else os << "TO BE FILLED";

			os << std::endl;
		}

	}
}