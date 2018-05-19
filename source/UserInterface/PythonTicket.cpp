/*********************************************************************
* date        : 2016.11.15
* file        : PythonTicket.cpp
* author      : VegaS
* version	  : 0.0.1
*/
#include "StdAfx.h"
#include "PythonApplication.h"
#include "Packet.h"
#include "PythonNetworkStream.h"
#include "PythonTicket.h"
#include "InstanceBase.h"
#include "Test.h"
#include "AbstractPlayer.h"

enum
{
	TICKET_MAX_LENGTH_TITLE = 32,
	TICKET_MAX_LENGTH_CONTENT = 450,
	TICKET_MAX_LENGTH_REPLY = 200,
	TICKET_MAX_LOGS_GENERAL = 200,
	TICKET_MAX_LOGS_FROM_REPLY = 40,
	TICKET_LOGS_PER_PAGE = 20,
	TICKET_MAX_PAGE_LOGS = 10,	
	TICKET_MAX_PAGE_LOGS_ADMIN = 500,
	TICKET_UNKNOWN_LOG = 999,
};

CPythonTicketLogs* CPythonTicketLogs::curInstance_A = NULL; 
CPythonTicketLogs::CPythonTicketLogs(void)
{}
CPythonTicketLogs::~CPythonTicketLogs(void)
{}

CPythonTicketLogsReply* CPythonTicketLogsReply::curInstance_B = NULL; 
CPythonTicketLogsReply::CPythonTicketLogsReply(void)
{}
CPythonTicketLogsReply::~CPythonTicketLogsReply(void)
{}

CPythonTicketLogs* CPythonTicketLogs::instance()
{
	if(!curInstance_A)
		curInstance_A = new CPythonTicketLogs();
	return curInstance_A;
}

CPythonTicketLogsReply* CPythonTicketLogsReply::instance()
{
	if(!curInstance_B)
		curInstance_B = new CPythonTicketLogsReply();
	return curInstance_B;
}

void CPythonTicketLogs::AddLogDetails(TPacketTicketLogsData p)
{
	m_vecData_A.clear();	

	for(int i = 0; i < TICKET_MAX_LOGS_GENERAL; i++)
	{
		TPacketTicketLogs mex = p.logs[i];
		m_vecData_A.push_back(mex);
	}
}
void CPythonTicketLogsReply::AddLogDetails(TPacketTicketLogsDataReply p)
{
	m_vecData_B.clear();

	for(int i = 0; i < TICKET_MAX_LOGS_FROM_REPLY; i++)
	{
		TPacketTicketLogsReply mex = p.logs[i];
		m_vecData_B.push_back(mex);
	}
}

TPacketTicketLogs CPythonTicketLogs::Request(int id)
{
	if(m_vecData_A.size() < id)
	{
		TPacketTicketLogs log;
		strncpy(log.ticked_id, "NULL", sizeof(log.ticked_id));					
		strncpy(log.title, "NULL", sizeof(log.title));				
		strncpy(log.content, "NULL", sizeof(log.content));		
		log.priority = 999;
		strncpy(log.create_date, "NULL", sizeof(log.create_date) - 1);
		log.status = 999;		
		return log;
	}
	return m_vecData_A[id];
}

TPacketTicketLogsReply CPythonTicketLogsReply::Request(int id)
{
	if(m_vecData_B.size() < id)
	{
		TPacketTicketLogsReply log;
		strncpy(log.reply_from, "NULL", sizeof(log.reply_from));					
		strncpy(log.reply_content, "NULL", sizeof(log.reply_content));						
		strncpy(log.reply_date, "NULL", sizeof(log.reply_date) - 1);	
		return log;
	}
	return m_vecData_B[id];
}

PyObject * ticketLoadLogs(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* dwRes = PyTuple_New(6);
	int id;

	if (!PyTuple_GetInteger(poArgs, 0, &id))
		return Py_BuildException();
	
	TPacketTicketLogs p = CPythonTicketLogs::instance()->Request(id);
	
	PyTuple_SetItem(dwRes, 0, Py_BuildValue("s", p.ticked_id));
	PyTuple_SetItem(dwRes, 1, Py_BuildValue("s", p.title));
	PyTuple_SetItem(dwRes, 2, Py_BuildValue("s", p.content));
	PyTuple_SetItem(dwRes, 3, Py_BuildValue("i", p.priority));
	PyTuple_SetItem(dwRes, 4, Py_BuildValue("s", p.create_date));
	PyTuple_SetItem(dwRes, 5, Py_BuildValue("i", p.status));
	return dwRes;
}

PyObject * ticketLoadLogsReply(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* dwRes = PyTuple_New(3);
	int id;

	if (!PyTuple_GetInteger(poArgs, 0, &id))
		return Py_BuildException();
	
	TPacketTicketLogsReply p = CPythonTicketLogsReply::instance()->Request(id);
	
	PyTuple_SetItem(dwRes, 0, Py_BuildValue("s", p.reply_from));
	PyTuple_SetItem(dwRes, 1, Py_BuildValue("s", p.reply_content));
	PyTuple_SetItem(dwRes, 2, Py_BuildValue("s", p.reply_date));
	return dwRes;
}

PyObject * ticketIsAdmin(PyObject * poSelf, PyObject * poArgs)
{
	static const char* currentName = CPythonPlayer::Instance().GetName();
	CInstanceBase * ch = CPythonPlayer::Instance().NEW_GetMainActorPtr();
	
	const char* arListMembers[] = {
		"x", "y", "z"
	};
	
	for(unsigned int i=0; i<_countof(arListMembers); i++){
		if ((!strcmp(arListMembers[i], currentName)) && ch->IsGameMaster()){
			return Py_BuildValue("i", TRUE);
		}
	}
	return Py_BuildValue("i", FALSE);
}

PyObject* netSendTicketPacketOpen(PyObject* poSelf, PyObject* poArgs)
{
	int szAction;
	int szMode;
	char* szTicketID;

	if (!PyTuple_GetInteger(poArgs, 0, &szAction))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 1, &szMode))
		return Py_BuildException();
	if (!PyTuple_GetString(poArgs, 2, &szTicketID))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendTicketPacketOpen(szAction, szMode, szTicketID);
	return Py_BuildNone();
}

PyObject* netSendTicketPacketCreate(PyObject* poSelf, PyObject* poArgs)
{
	char* szTitle;
	char* szContent;
	int szPriority;

	if (!PyTuple_GetString(poArgs, 0, &szTitle))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 1, &szContent))
		return Py_BuildException();
	
	if (!PyTuple_GetInteger(poArgs, 2, &szPriority))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendTicketPacketCreate(szTitle, szContent, szPriority);
	return Py_BuildNone();
}

PyObject* netSendTicketPacketReply(PyObject* poSelf, PyObject* poArgs)
{
	char* szTicketID;
	char* szReply;

	if (!PyTuple_GetString(poArgs, 0, &szTicketID))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 1, &szReply))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendTicketPacketReply(szTicketID, szReply);
	return Py_BuildNone();
}

PyObject* netSendTicketPacketAdmin(PyObject* poSelf, PyObject* poArgs)
{
	int szAction;
	char* szTicketID;
	char* szName;
	char* szReason;

	if (!PyTuple_GetInteger(poArgs, 0, &szAction))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 1, &szTicketID))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 2, &szName))
		return Py_BuildException();
	
	if (!PyTuple_GetString(poArgs, 3, &szReason))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendTicketPacketAdmin(szAction, szTicketID, szName, szReason);
	return Py_BuildNone();
}

PyObject* netSendTicketPacketAdminChangePage(PyObject* poSelf, PyObject* poArgs)
{
	int iStartPage;

	if (!PyTuple_GetInteger(poArgs, 0, &iStartPage))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendTicketPacketAdminChangePage(iStartPage);
	return Py_BuildNone();
}

void initTicket()
{
	static PyMethodDef s_methods[] = {
		{ "SendTicketPacketOpen",				netSendTicketPacketOpen,				METH_VARARGS },
		{ "SendTicketPacketCreate",				netSendTicketPacketCreate,				METH_VARARGS },
		{ "SendTicketPacketReply",				netSendTicketPacketReply,				METH_VARARGS },
		{ "SendTicketPacketAdmin",				netSendTicketPacketAdmin,				METH_VARARGS },
		{ "SendTicketPacketAdminChangePage",	netSendTicketPacketAdminChangePage,		METH_VARARGS },

		{ "GetLogByID",			ticketLoadLogs,				METH_VARARGS },
		{ "GetLogsReply",		ticketLoadLogsReply,		METH_VARARGS },
		{ "IsAdministrator",	ticketIsAdmin,				METH_VARARGS },
		{ NULL,						NULL,							NULL }
	};

	PyObject* poModule = Py_InitModule("ticket", s_methods);
	
	PyModule_AddIntConstant(poModule, "TICKET_MAX_LENGTH_TITLE",					TICKET_MAX_LENGTH_TITLE);
	PyModule_AddIntConstant(poModule, "TICKET_MAX_LENGTH_CONTENT",					TICKET_MAX_LENGTH_CONTENT);	
	PyModule_AddIntConstant(poModule, "TICKET_MAX_LENGTH_REPLY",					TICKET_MAX_LENGTH_REPLY);
	PyModule_AddIntConstant(poModule, "TICKET_MAX_LOGS_GENERAL",					TICKET_MAX_LOGS_GENERAL);	
	PyModule_AddIntConstant(poModule, "TICKET_MAX_LOGS_FROM_REPLY",					TICKET_MAX_LOGS_FROM_REPLY);	
	PyModule_AddIntConstant(poModule, "TICKET_LOGS_PER_PAGE",						TICKET_LOGS_PER_PAGE);	
	PyModule_AddIntConstant(poModule, "TICKET_MAX_PAGE_LOGS",						TICKET_MAX_PAGE_LOGS);
	PyModule_AddIntConstant(poModule, "TICKET_MAX_PAGE_LOGS_ADMIN",					TICKET_MAX_PAGE_LOGS_ADMIN);
	PyModule_AddIntConstant(poModule, "TICKET_UNKNOWN_LOG",							TICKET_UNKNOWN_LOG);	

}