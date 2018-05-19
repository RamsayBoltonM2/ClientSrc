#pragma once
#include "Packet.h"

class CPythonManagerBank
{
	public:
		CPythonManagerBank(void);
		~CPythonManagerBank(void);
		void Append(TPacketCGBank p);
		TAccountBank BINARY_LoadLogs_Account(int);
		static CPythonManagerBank* instance();
	private:
		std::vector<TAccountBank> BankInformations;
		static CPythonManagerBank * curAccountBank;
};

