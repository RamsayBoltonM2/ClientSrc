/*********************************************************************
* date        : 2017.01.14
* file        : PythonOxEvent.cpp
* author      : VegaS
* version	  : 0.0.1
*/
#include "StdAfx.h"
#include "PythonApplication.h"
#include "Packet.h"
#include "PythonNetworkStream.h"
#include "PythonOxEvent.h"
#include "InstanceBase.h"
#include "Test.h"
#include "AbstractPlayer.h"

CPythonOxEvent* CPythonOxEvent::curInstance = NULL; 
CPythonOxEvent::CPythonOxEvent(void)
{}
CPythonOxEvent::~CPythonOxEvent(void)
{}

CPythonOxEvent* CPythonOxEvent::instance()
{
	if(!curInstance)
		curInstance = new CPythonOxEvent();
	return curInstance;
}

void CPythonOxEvent::Initialize(TPacketCGOxEventData packet)
{
	m_vecData.clear();	

	for(int i = 0; i < MAX_RANGE; i++)
	{
		TPacketCGOxEvent iter = packet.tempInfo[i];
		m_vecData.push_back(iter);
	}
}

TPacketCGOxEvent CPythonOxEvent::Request(int pid)
{
	if(m_vecData.size() < pid)
	{
		TPacketCGOxEvent packet;
		strncpy(packet.name, "", sizeof(packet.name));
		packet.level = EMPTY_DATA;	
		strncpy(packet.guild, "", sizeof(packet.guild));
		packet.empire = EMPTY_DATA;	
		packet.job = EMPTY_DATA;	
		packet.correct_answers = EMPTY_DATA;
		packet.job = EMPTY_DATA;	
		return packet;
	}
	return m_vecData[pid];
}

PyObject * AppendInformationsPacket(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* row = PyTuple_New(7);
	int pid;

	if (!PyTuple_GetInteger(poArgs, 0, &pid))
		return Py_BuildException();
	
	TPacketCGOxEvent packet = CPythonOxEvent::instance()->Request(pid);
	
	PyTuple_SetItem(row, 0, Py_BuildValue("s", packet.name));
	PyTuple_SetItem(row, 1, Py_BuildValue("i", packet.level));
	PyTuple_SetItem(row, 2, Py_BuildValue("s", packet.guild));
	PyTuple_SetItem(row, 3, Py_BuildValue("i", packet.empire));
	PyTuple_SetItem(row, 4, Py_BuildValue("i", packet.job));
	PyTuple_SetItem(row, 5, Py_BuildValue("s", packet.date));
	PyTuple_SetItem(row, 6, Py_BuildValue("i", packet.correct_answers));
	return row;
}

PyObject* SendOxEventManagerPacket(PyObject* poSelf, PyObject* poArgs)
{
	int type;
	char* c_szPassword;
	int vnum;
	int count;

	if (!PyTuple_GetInteger(poArgs, 0, &type))
		return Py_BuildException();
	
	if (!PyTuple_GetString(poArgs, 1, &c_szPassword))
		return Py_BuildException();
	
	if (!PyTuple_GetInteger(poArgs, 2, &vnum))
		return Py_BuildException();
	
	if (!PyTuple_GetInteger(poArgs, 3, &count))
		return Py_BuildException();	

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendOxEventManagerPacket(type, c_szPassword, vnum, count);
	return Py_BuildNone();
}

void initOxEvent()
{
	static PyMethodDef s_methods[] = {
		{ "GetWinners",		AppendInformationsPacket,		METH_VARARGS },
		{ "Manager",		SendOxEventManagerPacket,		METH_VARARGS },
		{ NULL,						NULL,							NULL }
	};

	PyObject* poModule = Py_InitModule("oxevent", s_methods);
	
	PyModule_AddIntConstant(poModule, "LOGIN",				LOGIN);
	PyModule_AddIntConstant(poModule, "OPEN_EVENT",			OPEN_EVENT);		
	PyModule_AddIntConstant(poModule, "CLOSE_GATES",		CLOSE_GATES);		
	PyModule_AddIntConstant(poModule, "CLOSE_EVENT",		CLOSE_EVENT);		
	PyModule_AddIntConstant(poModule, "REWARD_PLAYERS",		REWARD_PLAYERS);	
	PyModule_AddIntConstant(poModule, "ASK_QUESTION",		ASK_QUESTION);
	PyModule_AddIntConstant(poModule, "FORCE_CLOSE_EVENT",	FORCE_CLOSE_EVENT);
	PyModule_AddIntConstant(poModule, "CLEAR_REWARD",		CLEAR_REWARD);		
	
	PyModule_AddIntConstant(poModule, "APPEND_WINNERS",		APPEND_WINNERS);
	PyModule_AddIntConstant(poModule, "APPEND_WINDOW",		APPEND_WINDOW);
	PyModule_AddIntConstant(poModule, "APPEND_REFRESH",		APPEND_REFRESH);
	
	PyModule_AddIntConstant(poModule, "EMPTY_VALUE",		EMPTY_VALUE);
	PyModule_AddStringConstant(poModule, "EMPTY_PASSWORD",	"");
	PyModule_AddStringConstant(poModule, "NOT_STACKABLE",	"1");

	PyModule_AddIntConstant(poModule, "EMPTY_DATA",			EMPTY_DATA);	
	PyModule_AddIntConstant(poModule, "MAX_RANGE",			MAX_RANGE);	
	PyModule_AddIntConstant(poModule, "MAX_ROWS",			MAX_ROWS);	
	
	PyModule_AddIntConstant(poModule, "ITEM_MAX_COUNT",		ITEM_MAX_COUNT);	
	
	PyModule_AddIntConstant(poModule, "EMPTY_VNUM",			EMPTY_VNUM);	
	PyModule_AddIntConstant(poModule, "EMPTY_COUNT",		EMPTY_COUNT);
	PyModule_AddIntConstant(poModule, "NEED_SIZE",			NEED_SIZE);
	PyModule_AddIntConstant(poModule, "CLEAR_DATA",			CLEAR_DATA);
	PyModule_AddIntConstant(poModule, "REFRESH_DATA",		REFRESH_DATA);
}