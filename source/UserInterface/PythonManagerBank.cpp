#include "StdAfx.h"
#include "PythonApplication.h"
#include "Packet.h"
#include "PythonNetworkStream.h"
#include "PythonManagerBank.h"

CPythonManagerBank* CPythonManagerBank::curAccountBank = NULL; 
CPythonManagerBank::CPythonManagerBank(void)
{}
CPythonManagerBank::~CPythonManagerBank(void)
{}

CPythonManagerBank* CPythonManagerBank::instance()
{
	if(!curAccountBank)
		curAccountBank = new CPythonManagerBank();
	return curAccountBank;
}

void CPythonManagerBank::Append(TPacketCGBank p)
{
	BankInformations.clear();
#define MAX_LOGS 1000	
	for(int i = 0; i < MAX_LOGS; i++){
		TAccountBank mex = p.logs[i];
		BankInformations.push_back(mex);
	}
}

TAccountBank CPythonManagerBank::BINARY_LoadLogs_Account(int id)
{
	if(BankInformations.size() < id)
	{
		TAccountBank log;
		log.user_action = 999;
		log.user_money = 0;
		strncpy(log.user_datetime, "0000-00-00 00:00:00", sizeof(log.user_datetime) -1);
		strncpy(log.user_ip, "-", sizeof(log.user_ip));
		strncpy(log.user_recvmoney, "-", sizeof(log.user_recvmoney));
		return log;
	}
	return BankInformations[id];
}

PyObject * bankLoadLogs(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* res = PyTuple_New(5);
	int id;

	if (!PyTuple_GetInteger(poArgs, 0, &id))
		return Py_BuildException();
	
	TAccountBank p = CPythonManagerBank::instance()->BINARY_LoadLogs_Account(id);
	
	PyTuple_SetItem(res, 0, Py_BuildValue("i", p.user_action));
	PyTuple_SetItem(res, 1, Py_BuildValue("i", p.user_money));
	PyTuple_SetItem(res, 2, Py_BuildValue("s", p.user_datetime));
	PyTuple_SetItem(res, 3, Py_BuildValue("s", p.user_ip));
	PyTuple_SetItem(res, 4, Py_BuildValue("s", p.user_recvmoney));
	return res;
}

void initBankManager()
{
	static PyMethodDef s_methods[] = {
		{ "Append",			bankLoadLogs,				METH_VARARGS },
		{ NULL,						NULL,							NULL },
	};

	PyObject* poModule = Py_InitModule("managerBankLogs", s_methods);
}
