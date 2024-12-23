//	File Switch_resetHelper.c automatically generated at 2024-12-23 08:21:33

#include "Switch_resetHelper.h"
//	Transfer functions

//void switchEntry(void* data) {
//}

//void switchInit(void* data) {
//}

void offEntry(void* data) {
	printf("OFF\n");
}

void offReset(void* data) {
	printf("@RESET\n");
}

//void offExit(void* data) {
//}

void offTurn(void* data) {
	printf("OFF: TURN\n");
}

void onEntry(void* data) {
	printf("ON\n");
}

//void onExit(void* data) {
//}

void onTurn(void* data) {
	printf("ON: TURN\n");
}

void create_helper(QHsmHelper* helper) {
	void (*switch_init_functions[])(void*) = {
		//switchEntry,
		//switchInit,
		offEntry
	};
	insert(helper, "switch", "init", compose_threaded_code_executor("off", switch_init_functions, ARRAY_SIZE(switch_init_functions)));

	void (*off_reset_functions[])(void*) = {
		offReset,
		//offExit,
		//switchInit,
		offEntry
	};
	insert(helper, "off", "RESET", compose_threaded_code_executor("off", off_reset_functions, ARRAY_SIZE(off_reset_functions)));

	void (*off_turn_functions[])(void*) = {
		offTurn,
		onEntry
	};
	insert(helper, "off", "TURN", compose_threaded_code_executor("on", off_turn_functions, ARRAY_SIZE(off_turn_functions)));

	void (*on_reset_functions[])(void*) = {
		offReset,
		//onExit,
		//offExit,
		//switchInit,
		offEntry
	};
	insert(helper, "on", "RESET", compose_threaded_code_executor("off", on_reset_functions, ARRAY_SIZE(on_reset_functions)));

	void (*on_turn_functions[])(void*) = {
		onTurn,
		//onExit,
		//offExit,
		//switchInit,
		offEntry
	};
	insert(helper, "on", "TURN", compose_threaded_code_executor("off", on_turn_functions, ARRAY_SIZE(on_turn_functions)));

}
