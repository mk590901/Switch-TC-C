//	File Switch_resetHelper.h automatically generated at 2024-12-23 08:21:34

#ifndef Switch_resetHelper_H
#define Switch_resetHelper_H

#include "core.h"

//	Transfer functions

	//void switchEntry(void* data);
	//void switchInit(void* data);
	void offEntry(void* data);
	void offReset(void* data);
	//void offExit(void* data);
	void offTurn(void* data);
	void onEntry(void* data);
	//void onExit(void* data);
	void onTurn(void* data);

	void create_helper(QHsmHelper* helper);

#endif	//	Switch_resetHelper_H

