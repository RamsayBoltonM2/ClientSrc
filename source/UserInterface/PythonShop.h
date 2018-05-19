#pragma once

#include "Packet.h"

/*
 *	상점 처리
 *
 *	2003-01-16 anoa	일차 완료
 *	2003-12-26 levites 수정
 *
 *	2012-10-29 rtsummit 새로운 화폐 출현 및 tab 기능 추가로 인한 shop 확장.
 *
 */
typedef enum
{
	SHOP_COIN_TYPE_GOLD, // DEFAULT VALUE
	SHOP_COIN_TYPE_SECONDARY_COIN,
} EShopCoinType;


#ifdef ENABLE_SHOPEX_SYSTEM_NEW
typedef enum
{
	SHOP_TYPE_GOLD,	// DEFULT VALUE
	SHOP_TYPE_CASH,	// account.cash
	SHOP_TYPE_COINS,	// account.coins
	SHOP_TYPE_ALIGN,	// player.alignment
	SHOP_TYPE_WARPOINT,	// player.warpoint
	SHOP_TYPE_10THEVENT,	// quest.10theventpoints
} EShopType;
#endif

class CPythonShop : public CSingleton<CPythonShop>
{
	public:
		CPythonShop(void);
		virtual ~CPythonShop(void);

		void Clear();

		void SetItemData(DWORD dwIndex, const TShopItemData & c_rShopItemData);
		BOOL GetItemData(DWORD dwIndex, const TShopItemData ** c_ppItemData);

		void SetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData & c_rShopItemData);
		BOOL GetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData ** c_ppItemData);

#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		void SetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData & c_rShopItemData);
		BOOL GetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData ** c_ppItemData);

		void SetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData & c_rShopItemData);
		BOOL GetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData ** c_ppItemData);
#endif

		void SetTabCount(BYTE bTabCount) { m_bTabCount = bTabCount; }
		BYTE GetTabCount() { return m_bTabCount; }

		void SetTabCoinType(BYTE tabIdx, BYTE coinType);
		BYTE GetTabCoinType(BYTE tabIdx);

		void SetTabName(BYTE tabIdx, const char* name);
		const char* GetTabName(BYTE tabIdx);

#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		void SetShopDisplayedCount(DWORD dwDisplayedCount);
		DWORD	GetShopDisplayedCount();
#endif

#ifdef ENABLE_SHOPEX_SYSTEM_NEW
		void SetShopName(const char* name);
		void SetPriceType(short price_type);
		const char* GetShopName();
		short GetPriceType();
#endif

		//BOOL GetSlotItemID(DWORD dwSlotPos, DWORD* pdwItemID);

#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		void Open(BOOL isPrivateShop, BOOL isMainPrivateShop, BOOL isOfflineShop);
#else
		void Open(BOOL isPrivateShop, BOOL isMainPrivateShop);	
#endif
		void Close();
		BOOL IsOpen();
		BOOL IsPrivateShop();
		BOOL IsMainPlayerPrivateShop();
#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		BOOL IsOfflineShop();
#endif
		void ClearPrivateShopStock();
		void AddPrivateShopItemStock(TItemPos ItemPos, BYTE byDisplayPos, DWORD dwPrice, DWORD dwPriceCheque);
		void DelPrivateShopItemStock(TItemPos ItemPos);
		int GetPrivateShopItemPrice(TItemPos ItemPos);
		int GetPrivateShopItemPriceCheque(TItemPos ItemPos);
		void BuildPrivateShop(const char * c_szName);
		
#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		void ClearOfflineShopStock();
		void AddOfflineShopItemStock(TItemPos ItemPos, BYTE byDisplayPos, DWORD dwPrice, DWORD dwPrice2, short sPriceType);
		void DelOfflineShopItemStock(TItemPos ItemPos);
		int	 GetOfflineShopItemPrice(TItemPos ItemPos);
		int	 GetOfflineShopItemPrice2(TItemPos ItemPos);
		int	 GetOfflineShopItemPriceType(TItemPos ItemPos);
		BYTE	GetOfflineShopItemStatus(TItemPos ItemPos);
		void BuildOfflineShop(const char * c_szName, BYTE bNpcVnum);
#endif

	protected:
		BOOL	CheckSlotIndex(DWORD dwIndex);

	protected:
		BOOL				m_isShoping;
		BOOL				m_isPrivateShop;
		BOOL				m_isMainPlayerPrivateShop;
		BOOL				m_isOfflineShop;

		struct ShopTab
		{
			ShopTab()
			{
				coinType = SHOP_COIN_TYPE_GOLD;
			}
			BYTE				coinType;
			std::string			name;
			TShopItemData		items[SHOP_HOST_ITEM_MAX_NUM];
		};

#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		struct OfflineShopTab
		{
			OfflineShopTab()
			{
				coinType = SHOP_COIN_TYPE_GOLD;
			}
			BYTE				coinType;
			std::string			name;
			TOfflineShopItemData items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
		};
		
		DWORD				m_dwDisplayedCount;
#endif

		BYTE m_bTabCount;
		ShopTab m_aShoptabs[SHOP_TAB_COUNT_MAX];
#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		OfflineShopTab m_aOfflineShoptabs[SHOP_TAB_COUNT_MAX];
#endif
#ifdef ENABLE_SHOPEX_SYSTEM_NEW
		std::string			shop_name;
		short				sPrice_type;
#endif
		typedef std::map<TItemPos, TShopItemTable2> TPrivateShopItemStock;
		TPrivateShopItemStock	m_PrivateShopItemStock;
		
#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		typedef std::map<TItemPos, TOfflineShopItemTable> TOfflineShopItemStock;
		TOfflineShopItemStock	m_OfflineShopItemStock;
#endif
};
