#include <iostream>
#include <map>
#include <mutex>
#include <chrono>
#include "HPRecType.h"

template <class K, class V>
class WRRMMap
{
	std::map<K, V>* pMap_;
public:
	WRRMMap(){
		pMap_ = new map<K, V>();
	}

public:
	V Lookup(const K& k)
	{
		// no lock
		return (*pMap_)[k];
	}

	void Update(const K& k,
		const V& v)
	{
		std::map<K, V>* pNew = 0;
		std::map<K, V>* pOld;
		do {
			pOld = pMap_;
			delete pNew;
			pNew = new map<K, V>(*pOld);
			(*pNew)[k] = v;
		} while (!CAS(&pMap_, pOld, pNew));
		//std::chrono::milliseconds dura(200);
		//std::this_thread::sleep_for(dura);
		delete pOld;
	}

private:
	static void Retire(map<K, V> *pold){
		rlist.push_back(pold);
		if (rlist.size() > 10){
			Scan(HPRecType::Head());
		}
	}

};







template <class K, class V>
class WRRMMap_Lock {
	std::mutex mtx_;

	std::map<K, V> map_;

public:

	V Lookup(const K& k) {
		std::lock_guard<std::mutex> lock(mtx_);
		return map_[k];
	}

	void Update(const K& k,
		const V& v) {
		std::lock_guard<std::mutex> lock(mtx_);
		map_[k] = v;
	}
};