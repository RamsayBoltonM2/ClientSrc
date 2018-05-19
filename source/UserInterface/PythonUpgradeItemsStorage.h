#pragma once

class CPythonUpgradeItemsStorage : public CSingleton < CPythonUpgradeItemsStorage >
{
public:
	enum
	{
		UPGRADE_ITEMS_STORAGE_SLOT_X_COUNT = 5,
		UPGRADE_ITEMS_STORAGE_SLOT_Y_COUNT = 9,
		UPGRADE_ITEMS_STORAGE_PAGE_SIZE = UPGRADE_ITEMS_STORAGE_SLOT_X_COUNT * UPGRADE_ITEMS_STORAGE_SLOT_Y_COUNT,
		UPGRADE_ITEMS_STORAGE_TAB_COUNT = 2,
		UPGRADE_ITEMS_STORAGE_TOTAL_SIZE = UPGRADE_ITEMS_STORAGE_TAB_COUNT * UPGRADE_ITEMS_STORAGE_PAGE_SIZE,
	};
	typedef std::vector<TItemData> TItemInstanceVector;

public:
	CPythonUpgradeItemsStorage();
	virtual ~CPythonUpgradeItemsStorage();

	void SetItemData(DWORD dwSlotIndex, const TItemData & rItemData);
	void DelItemData(DWORD dwSlotIndex);

	BOOL GetSlotItemID(DWORD dwSlotIndex, DWORD* pdwItemID);

	void ClearVector();
	void OpenUpgradeItemsStorage();

	int GetCurrentUpgradeItemsStorageSize();
	BOOL GetItemDataPtr(DWORD dwSlotIndex, TItemData ** ppInstance);

protected:
	TItemInstanceVector m_ItemInstanceVector;
};
