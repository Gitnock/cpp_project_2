// Name:Enock lubega
// Seneca Student ID: 154192181
// Seneca email:elubega@myseneca.ca
// Date of completion:4/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"

namespace sdds {
	LineManager::LineManager(const std::string& fileName, const std::vector<Workstation*>& stations)
	{
		Utilities util;
		size_t pos = 0u;
		bool isMore = true, isFirst = true;
		util.setDelimiter('|');

		std::string line, cWS, nWS;
		std::ifstream file(fileName);

		std::vector<Workstation*> left;
		std::vector<Workstation*> right;

		if (!file)
			throw std::string("Unable to open [") + fileName + "] file.";
		while (std::getline(file, line)) {
			pos = 0u;
			cWS = util.extractToken(line, pos, isMore);
			std::for_each(stations.begin(), stations.end(), [&](Workstation* ws) {
				if (cWS == ws->getItemName()) {
					activeLine.push_back(ws);
					left.push_back(std::move(ws));
					if (isMore) {
						nWS = util.extractToken(line, pos, isMore);
						std::for_each(stations.begin(), stations.end(), [&](Workstation* wsN) {
							if (nWS == wsN->getItemName()) {
								ws->setNextStation(wsN);
								right.push_back(std::move(wsN));
							}

						});
						
					}
					
				}
			});
		}
		
		std::for_each(left.begin(), left.end(), [&](Workstation* c) {
			isFirst = true;

			std::for_each(right.begin(), right.end(), [&](Workstation* n) {
				
				if (c->getItemName() == n->getItemName()) {
					//std::cout << "TEST: " << n->getItemName() << std::endl;
					isFirst = false;
				}

			});
			if (isFirst) {

				m_firstStation = std::move(c);
				//std::cout << "TEST: " << m_firstStation->getItemName() << std::endl;
			}

		});
		/*for (size_t i = 0; i < first.size(); i++)
		{	
			std::cout << "TEST: " << first[i]->getItemName() << std::endl;
		}*/
		
		m_cntCustomerOrder = pending.size();
		

	}
	void LineManager::linkStations()
	{
		size_t size = activeLine.size();
		activeLine.clear();

		activeLine.push_back(std::move(m_firstStation));
		for (size_t i = 0; i < size-1; i++)
		{
			activeLine.push_back(std::move(activeLine[i]->getNextStation()));
		}
		
	}
	bool LineManager::run(std::ostream& os)
	{
		static size_t count = 0;
		os << "Line Manager Iteration: " << ++count<< std::endl;
		if (!pending.empty()) {
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}
		for (auto&& i : activeLine) {
			i->fill(os);
		}
		for (auto&& i : activeLine) {
			i->attemptToMoveOrder();
		}
		return completed.size() == m_cntCustomerOrder;
	}
	void LineManager::display(std::ostream& os) const
	{
		std::for_each(activeLine.begin(), activeLine.end(), [&](auto i) {
			i->display(os);
			});
	}
}