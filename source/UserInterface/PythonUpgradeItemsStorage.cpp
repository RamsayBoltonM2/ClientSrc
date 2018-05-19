#include "StdAfx.h"
#include "PythonUpgradeItemsStorage.h"
#include "PythonPlayer.h"
#include "PythonApplication.h"

void CPythonUpgradeItemsStorage::SetItemData(DWORD dwSlotIndex, const TItemData & rItemData)
{
	if (dwSlotIndex >= m_ItemInstanceVector.size())
	{
		TraceError("CPythonUpgradeItemsStorage::SetItemData(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return;
	}

	m_ItemInstanceVector[dwSlotIndex] = rItemData;
}

void CPythonUpgradeItemsStorage::OpenUpgradeItemsStorage()
{
	m_ItemInstanceVector.clear();
	m_ItemInstanceVector.resize(UPGRADE_ITEMS_STORAGE_TOTAL_SIZE);

	for (DWORD i = 0; i < m_ItemInstanceVector.size(); ++i)
	{
		TItemData & rInstance = m_ItemInstanceVector[i];
		ZeroMemory(&rInstance, sizeof(rInstance));
	}
}

void CPythonUpgradeItemsStorage::ClearVector()
{
	m_ItemInstanceVector.clear();
}

void CPythonUpgradeItemsStorage::DelItemData(DWORD dwSlotIndex)
{
	if (dwSlotIndex >= m_ItemInstanceVector.size())
	{
		TraceError("CPythonUpgradeItemsStorage::DelItemData(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return;
	}

	TItemData & rInstance = m_ItemInstanceVector[dwSlotIndex];
	ZeroMemory(&rInstance, sizeof(rInstance));
}

int CPythonUpgradeItemsStorage::GetCurrentUpgradeItemsStorageSize()
{
	return m_ItemInstanceVector.size();
}

BOOL CPythonUpgradeItemsStorage::GetSlotItemID(DWORD dwSlotIndex, DWORD* pdwItemID)
{
	if (dwSlotIndex >= m_ItemInstanceVector.size())
	{
		TraceError("CPythonUpgradeItemsStorage::GetSlotItemID(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return FALSE;
	}

	*pdwItemID = m_ItemInstanceVector[dwSlotIndex].vnum;

	return TRUE;
}

BOOL CPythonUpgradeItemsStorage::GetItemDataPtr(DWORD dwSlotIndex, TItemData ** ppInstance)
{
	if (dwSlotIndex >= m_ItemInstanceVector.size())
	{
		TraceError("CPythonUpgradeItemsStorage::GetItemData(dwSlotIndex=%d) - Strange slot index", dwSlotIndex);
		return FALSE;
	}

	*ppInstance = &m_ItemInstanceVector[dwSlotIndex];

	return TRUE;
}

CPythonUpgradeItemsStorage::CPythonUpgradeItemsStorage()
{
	m_ItemInstanceVector.clear();
	m_ItemInstanceVector.resize(UPGRADE_ITEMS_STORAGE_TOTAL_SIZE);

	for (DWORD i = 0; i < m_ItemInstanceVector.size(); ++i)
	{
		TItemData & rInstance = m_ItemInstanceVector[i];
		ZeroMemory(&rInstance, sizeof(rInstance));
	}
}

CPythonUpgradeItemsStorage::~CPythonUpgradeItemsStorage()
{
}

PyObject * upgradeStorageGetCurrentUpgradeItemsStorageSize(PyObject * poSelf, PyObject * poArgs)
{
	return Py_BuildValue("i", CPythonUpgradeItemsStorage::Instance().GetCurrentUpgradeItemsStorageSize());
}

PyObject * uppStorageClearVector(PyObject * poSelf, PyObject * poArgs)
{
	CPythonUpgradeItemsStorage::Instance().ClearVector();
	return Py_BuildValue("i", 1);
}

PyObject * upgradeStorageGetItemID(PyObject * poSelf, PyObject * poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData * pInstance;
	if (!CPythonUpgradeItemsStorage::Instance().GetItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->vnum);
}

PyObject * upgradeStorageGetItemCount(PyObject * poSelf, PyObject * poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData * pInstance;
	if (!CPythonUpgradeItemsStorage::Instance().GetItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->count);
}

PyObject * upgradeStorageGetItemFlags(PyObject * poSelf, PyObject * poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData * pInstance;
	if (!CPythonUpgradeItemsStorage::Instance().GetItemDataPtr(ipos, &pInstance))
		return Py_BuildException();

	return Py_BuildValue("i", pInstance->flags);
}

PyObject * upgradeStorageGetItemMetinSocket(PyObject * poSelf, PyObject * poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BadArgument();
	int iSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iSocketIndex))
		return Py_BadArgument();

	if (iSocketIndex >= ITEM_SOCKET_SLOT_MAX_NUM)
		return Py_BuildException();

	TItemData * pItemData;
	if (!CPythonUpgradeItemsStorage::Instance().GetItemDataPtr(iSlotIndex, &pItemData))
		return Py_BuildException();

	return Py_BuildValue("i", pItemData->alSockets[iSocketIndex]);
}

PyObject * upgradeStorageGetItemAttribute(PyObject * poSelf, PyObject * poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		TItemData * pItemData;
		if (CPythonUpgradeItemsStorage::Instance().GetItemDataPtr(iSlotIndex, &pItemData))
			return Py_BuildValue("ii", pItemData->aAttr[iAttrSlotIndex].bType, pItemData->aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject * uppStorageGetItemLink(PyObject * poSelf, PyObject * poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData * pPlayerItem;
	CPythonUpgradeItemsStorage::Instance().GetItemDataPtr(ipos, &pPlayerItem);
	CItemData * pItemData = NULL;
	char buf[1024];

	if (pPlayerItem && CItemManager::Instance().GetItemDataPointer(pPlayerItem->vnum, &pItemData))
	{
		char itemlink[256];
		int len;
		bool isAttr = false;

#ifdef ENABLE_CHANGE_LOOK_SYSTEM
		len = snprintf(itemlink, sizeof(itemlink), "item:%x|%d:%x:%x:%x:%x",
#else
		len = snprintf(itemlink, sizeof(itemlink), "item:%x:%x:%x:%x:%x",
#endif

#ifdef ENABLE_CHANGE_LOOK_SYSTEM
			pPlayerItem->vnum, 0, pPlayerItem->flags,
#else
			pPlayerItem->vnum, pPlayerItem->flags,
#endif
			pPlayerItem->alSockets[0], pPlayerItem->alSockets[1], pPlayerItem->alSockets[2]);

		for (int i = 0; i < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++i)
		{
			// if (pPlayerItem->aAttr[i].bType != 0) // @fixme009 (this line must be commented)
			{
				len += snprintf(itemlink + len, sizeof(itemlink)-len, ":%x:%d",
				pPlayerItem->aAttr[i].bType, pPlayerItem->aAttr[i].sValue);
				isAttr = true;
			}
		}

		if (GetDefaultCodePage() == CP_ARABIC) {
			if (isAttr)
				snprintf(buf, sizeof(buf), " |h|r[%s]|cffffc700|H%s|h", pItemData->GetName(), itemlink);
			else
				snprintf(buf, sizeof(buf), " |h|r[%s]|cfff1e6c0|H%s|h", pItemData->GetName(), itemlink);
		}
		else {
			if (isAttr)
				snprintf(buf, sizeof(buf), "|cffffc700|H%s|h[%s]|h|r", itemlink, pItemData->GetName());
			else
				snprintf(buf, sizeof(buf), "|cfff1e6c0|H%s|h[%s]|h|r", itemlink, pItemData->GetName());
		}
	}
	else
		buf[0] = '\0';

	return Py_BuildValue("s", buf);
}

void initupgradeStorage()
{
	static PyMethodDef s_methods[] =
	{
		// Upgrade Items Storage
		{ "GetCurrentUpgradeItemsStorageSize", upgradeStorageGetCurrentUpgradeItemsStorageSize, METH_VARARGS },
		{ "GetItemID", upgradeStorageGetItemID, METH_VARARGS },
		{ "GetItemCount", upgradeStorageGetItemCount, METH_VARARGS },
		{ "GetItemFlags", upgradeStorageGetItemFlags, METH_VARARGS },
		{ "GetItemMetinSocket", upgradeStorageGetItemMetinSocket, METH_VARARGS },
		{ "GetItemAttribute", upgradeStorageGetItemAttribute, METH_VARARGS },
		{ "GetItemLink", uppStorageGetItemLink, METH_VARARGS },
		{ "ClearVector", uppStorageClearVector, METH_VARARGS },

		{ NULL, NULL, NULL },
	};

	PyObject * poModule = Py_InitModule("upgradeStorage", s_methods);
	PyModule_AddIntConstant(poModule, "UPGRADE_ITEMS_STORAGE_SLOT_X_COUNT", CPythonUpgradeItemsStorage::UPGRADE_ITEMS_STORAGE_SLOT_X_COUNT);
	PyModule_AddIntConstant(poModule, "UPGRADE_ITEMS_STORAGE_SLOT_Y_COUNT", CPythonUpgradeItemsStorage::UPGRADE_ITEMS_STORAGE_SLOT_Y_COUNT);
	PyModule_AddIntConstant(poModule, "UPGRADE_ITEMS_STORAGE_PAGE_SIZE", CPythonUpgradeItemsStorage::UPGRADE_ITEMS_STORAGE_PAGE_SIZE);
	PyModule_AddIntConstant(poModule, "UPGRADE_ITEMS_STORAGE_TAB_COUNT", CPythonUpgradeItemsStorage::UPGRADE_ITEMS_STORAGE_TAB_COUNT);
}
