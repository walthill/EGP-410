#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#include <queue>
#include "NodeRecord.h"

template
< class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
class PriorityQueue : public std::priority_queue<T, Container, Compare>
{
	private:
	public: 
		typedef typename
			std::priority_queue	< T, Container, Compare>::container_type::const_iterator const_iterator;

		const_iterator contains(const T &value) const
		{
			auto first = this->c.cbegin(); //container access
			auto last = this->c.cend();
			
			while (first != last)
			{
				if (*first == value) return first;
				++first;
			}

			return last;
		}

	/*	void find(const T &value) const
		{
			auto first = this->c.cbegin(); //container access
			auto last = this->c.cend();

			while (first != last)
			{
			}

			//return ;
		}
		*/
/*		const_iterator find(const Node &value) const
		{
			auto first = this->c.cbegin(); //container access
			auto last = this->c.cend();

			while (first != last)
			{
				if (*first == value) return first;
				++first;
			}

			return last;
		}
		*/

		const_iterator begin() const
		{
			auto first= this->c.cbegin();
			return first;
		}

		const_iterator end() const
		{
			auto last = this->c.cend();
			return last;
		}
			
		bool remove(const T& value) {
			auto it = std::find(this->c.begin(), this->c.end(), value);
			if (it != this->c.end()) {
				this->c.erase(it);
				std::make_heap(this->c.begin(), this->c.end(), this->comp);
				return true;
			}
			else {
				return false;
			}
		}

		/*const T back() const
		{
			T returnValue;



			return returnValue;
		}*/
//		bool operator ==(const NodeRecord& rhs) { return node == rhs.node; };

};

class W_Compare
{
	public: 
		bool operator() (const NodeRecord lhs, const NodeRecord rhs)
		{
			return lhs.costSoFar > rhs.costSoFar;
		}

};

class W_AStarCompare
{
	public:
		bool operator() (const NodeRecord lhs, const NodeRecord rhs)
		{
			return lhs.estimatedTotalCost > rhs.estimatedTotalCost;
		}
};

#endif // !PRIORITY_Q_H
