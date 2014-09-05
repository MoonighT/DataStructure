#include <vector>
#include <map>
#include "cas.h"

class HPRecType
{
	HPRecType *pNext_;
	int active_;
	static HPRecType *pHead_;
	static int listLen_;

public:
	void *pHazard_; //can be used by the thread that acquired it
	static HPRecType* Head()
	{
		return pHead_;
	}
	//acquires one hazard pointer
	static HPRecType* Acquire() 
	{
		//try to use a retired HP record
		HPRecType *p = pHead_;
		for (; p; p = p->pNext_)
		{
			if (p->active_ ||
				!CAS(&p->active_, 0, 1))
				continue;
			//get one
			return p;
		}
		//increment the list length if no retured
		int oldLen;
		do{
			oldLen = listLen_;
		} while (!CAS(&listLen_, oldLen, oldLen + 1));

		//allocate a new one
		HPRecType *p = new HPRecType();
		HPRecType *old;
		p->active_ = 1;
		p->pNext_ = 0;
		//push it to the front
		do{
			old = pHead_;
			p->pNext_ = old;
		} while (!CAS(&pHead_, old, p));
		return p;
	}

	static void release(HPRecType *p)
	{
		p->pHazard_ = 0;
		p->active_ = 0;
	}
};

template <class K, class V>
vector<std::map<K, V> *> rlist;