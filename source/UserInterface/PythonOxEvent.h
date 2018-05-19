/*********************************************************************
* date        : 2017.01.14
* file        : PythonOxEvent.h
* author      : VegaS
* version	  : 0.0.1
*/
#pragma once
#include "Packet.h"

enum
{
	MAX_ROWS = 4,
	MAX_RANGE = 5,
	EMPTY_DATA = 999,
	EMPTY_VALUE = 0,
	ITEM_MAX_COUNT = 200,
	
	LOGIN = 0,	
	OPEN_EVENT = 1,
	CLOSE_GATES = 2,
	CLOSE_EVENT = 3,
	REWARD_PLAYERS = 4,
	ASK_QUESTION = 5,
	FORCE_CLOSE_EVENT = 6,
	CLEAR_REWARD = 7,
	
	APPEND_WINNERS = 6,
	APPEND_WINDOW = 7,
	APPEND_REFRESH = 8,
	
	EMPTY_VNUM = 0,
	EMPTY_COUNT = 0,
	
	NEED_SIZE = 1,
	CLEAR_DATA = 0,
	REFRESH_DATA = 3,
};

class CPythonOxEvent
{
	public:
		CPythonOxEvent(void);
		~CPythonOxEvent(void);
		void Initialize(TPacketCGOxEventData p);
		TPacketCGOxEvent Request(int);
		static CPythonOxEvent* instance();
	private:
		std::vector<TPacketCGOxEvent> m_vecData;
		static CPythonOxEvent * curInstance;
};