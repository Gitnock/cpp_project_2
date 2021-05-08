// Name:Enock lubega
// Seneca Student ID: 154192181
// Seneca email:elubega@myseneca.ca
// Date of completion:4/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
			//os << "MAGA TEST:" << (*this).getItemName() << std::endl;
		}
	}
	Workstation::Workstation(const std::string line) :Station::Station(line) {
	};
	bool Workstation::attemptToMoveOrder()
	{
		bool isMoved = false;
		if (!m_orders.empty() && m_orders.front().isItemFilled(getItemName())) {
			if (!m_pNextStation) {
				completed.push_back(std::move(m_orders.front()));
				m_orders.pop_front();
				isMoved = true;
			}
			else {
				*m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
				isMoved = true;
			}
			
		}
		//std::cout << "TEST: " << getQuantity() << std::endl;
		if (getQuantity() <= 0) {
			if (!m_pNextStation) {
				incomplete.push_back(std::move(m_orders.front()));
				m_orders.pop_front();
				isMoved = true;
			}
			else {
				*m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
				isMoved = true;
			}
		}

		return isMoved;
	}
	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		os << this->getItemName() << " --> ";
		if (m_pNextStation)
			os << m_pNextStation->getItemName();
		else {
			os << "End of Line";
		}
		os << std::endl;
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		// TODO: insert return statement here
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}