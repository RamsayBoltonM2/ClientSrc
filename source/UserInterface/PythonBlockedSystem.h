#pragma once

#ifdef ENABLE_CANBLOCK_PLAYER_SYSTEM
#include "Packet.h"

class CPythonBlockedSystem : public CSingleton<CPythonBlockedSystem>
{
	public:
		CPythonBlockedSystem();
		virtual ~CPythonBlockedSystem();
		
		void	Clear();
		void	Add(const char * charName);
		void	Remove(const char * charName);
		bool	isBlocked(const char * charName);
		const char *	Get(int iIndex) const;
	
	protected:
		std::vector<std::string>	m_vecBlockList;
};
#endif
