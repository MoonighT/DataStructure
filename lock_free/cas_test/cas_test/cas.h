

template <class T>
bool CAS(T* addr, T expected, T value)
{
	if (*addr == expected){
		*addr = value;
		return true;
	}
	return false;
}