#ifndef _AX_OBJECT_
#define _AX_OBJECT_

#include "axEvent.h"

typedef unsigned long axID;

class axObject
{
public:
	axObject() :_id(IncrementGlobalIdCount())
	{
	}

	void AddConnection(axEventFct fct) const;

	inline axID GetID() const
	{
		return _id;
	}

private:
	axID _id;
	
	static axID _global_id_count;

	static axID IncrementGlobalIdCount()
	{
		return ++_global_id_count;
	}
};

#endif // _AX_OBJECT_ 
