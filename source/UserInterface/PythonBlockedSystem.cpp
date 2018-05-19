#include "StdAfx.h"

#ifdef ENABLE_CANBLOCK_PLAYER_SYSTEM
#include "PythonBlockedSystem.h"
#include "PythonNetworkStream.h"

CPythonBlockedSystem::CPythonBlockedSystem()
{
	Clear();
}

CPythonBlockedSystem::~CPythonBlockedSystem()
{
	Clear();
}

bool CPythonBlockedSystem::isBlocked(const char * charName)
{
	return std::find(m_vecBlockList.begin(), m_vecBlockList.end(), charName) != m_vecBlockList.end();
}

void CPythonBlockedSystem::Clear()
{
	m_vecBlockList.clear();
}

void CPythonBlockedSystem::Add(const char * charName)
{
	if (!isBlocked(charName))
		m_vecBlockList.push_back(charName);
}

void CPythonBlockedSystem::Remove(const char * charName)
{
	if (isBlocked(charName))
		m_vecBlockList.erase(std::remove(m_vecBlockList.begin(), m_vecBlockList.end(), charName), m_vecBlockList.end());
}

const char * CPythonBlockedSystem::Get(int iIndex) const
{
	if (iIndex >= BLOCKSYSTEM_MAX_PLAYERS)
		return "";
	
	size_t vecSize = m_vecBlockList.size();
	if (iIndex >= vecSize)
		return "";
	
	return m_vecBlockList[iIndex].c_str();
}

PyObject * GetBlockedSystem(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BadArgument();
	
	return Py_BuildValue("s", CPythonBlockedSystem::Instance().Get(iIndex));
}

PyObject * SendBlockSystem(PyObject * poSelf, PyObject * poArgs)
{
	bool bAdd;
	if (!PyTuple_GetBoolean(poArgs, 0, &bAdd))
		return Py_BadArgument();
	
	char * charName;
	if (!PyTuple_GetString(poArgs, 1, &charName))
		return Py_BadArgument();
	
	if ((strlen(charName) > 0))
	{
		if ((CPythonBlockedSystem::Instance().isBlocked(charName)) && (!bAdd))
		{
			CPythonNetworkStream & rkNetStream = CPythonNetworkStream::Instance();
			rkNetStream.SendBlockSystemPacket(bAdd, charName);
		}
		else if ((!CPythonBlockedSystem::Instance().isBlocked(charName)) && (bAdd))
		{
			CPythonNetworkStream & rkNetStream = CPythonNetworkStream::Instance();
			rkNetStream.SendBlockSystemPacket(bAdd, charName);
		}
	}
	
	return Py_BuildNone();
}

PyObject * BlockSystemIsBlocked(PyObject * poSelf, PyObject * poArgs)
{
	char * charName;
	if (!PyTuple_GetString(poArgs, 0, &charName))
		return Py_BadArgument();
	
	if ((strlen(charName) > 0))
	{
		if (CPythonBlockedSystem::Instance().isBlocked(charName))
			return Py_BuildValue("b", true);
			
	}
	
	return Py_BuildValue("b", false);
}

void initBlockedSystem()
{
	static PyMethodDef functions[] = {
										{"Get", GetBlockedSystem, METH_VARARGS},
										{"Send", SendBlockSystem, METH_VARARGS},
										{"isBlocked", BlockSystemIsBlocked, METH_VARARGS},
										{NULL, NULL, NULL},
	};
	
	PyObject* pModule = Py_InitModule("blocksystem", functions);
	PyModule_AddIntConstant(pModule, "MAX_PLAYERS", BLOCKSYSTEM_MAX_PLAYERS);
}
#endif
