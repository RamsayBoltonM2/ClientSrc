#include "StdAfx.h"
#include "PythonNetworkStream.h"
//#include "PythonNetworkDatagram.h"
#include "AccountConnector.h"
#include "PythonGuild.h"
#include "Test.h"

#include "AbstractPlayer.h"

static std::string gs_stServerInfo;
extern BOOL gs_bEmpireLanuageEnable;
std::list<std::string> g_kList_strCommand;

PyObject* netGetBettingGuildWarValue(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();


	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.EXPORT_GetBettingGuildWarValue(szName));
}

PyObject* netSetServerInfo(PyObject* poSelf, PyObject* poArgs)
{
	char* szFileName;
	if (!PyTuple_GetString(poArgs, 0, &szFileName))
		return Py_BuildException();

	gs_stServerInfo=szFileName;
	return Py_BuildNone();
}

PyObject* netGetServerInfo(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("s", gs_stServerInfo.c_str());
}

PyObject* netPreserveServerCommand(PyObject* poSelf, PyObject* poArgs)
{
	char* szLine;
	if (!PyTuple_GetString(poArgs, 0, &szLine))
		return Py_BuildException();

	g_kList_strCommand.push_back(szLine);

	return Py_BuildNone();
}

PyObject* netGetPreservedServerCommand(PyObject* poSelf, PyObject* poArgs)
{
	if (g_kList_strCommand.empty())
		return Py_BuildValue("s", "");

	std::string strCommand = g_kList_strCommand.front();
	g_kList_strCommand.pop_front();

	return Py_BuildValue("s", strCommand.c_str());
}

PyObject* netStartGame(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.StartGame();

	return Py_BuildNone();
}

PyObject* netIsTest(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", __IS_TEST_SERVER_MODE__);
}

PyObject* netWarp(PyObject* poSelf, PyObject* poArgs)
{
	int nX;
	if (!PyTuple_GetInteger(poArgs, 0, &nX))
		return Py_BuildException();

	int nY;
	if (!PyTuple_GetInteger(poArgs, 1, &nY))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.Warp(nX, nY);

	return Py_BuildNone();
}

PyObject* netLoadInsultList(PyObject* poSelf, PyObject* poArgs)
{
	char* szFileName;
	if (!PyTuple_GetString(poArgs, 0, &szFileName))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.LoadInsultList(szFileName));
}

PyObject* netUploadMark(PyObject* poSelf, PyObject* poArgs)
{
	char* szFileName;
	if (!PyTuple_GetString(poArgs, 0, &szFileName))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.UploadMark(szFileName));
}

PyObject* netUploadSymbol(PyObject* poSelf, PyObject* poArgs)
{
	char* szFileName;
	if (!PyTuple_GetString(poArgs, 0, &szFileName))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.UploadSymbol(szFileName));
}

PyObject* netGetGuildID(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.GetGuildID());
}

PyObject* netGetEmpireID(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.GetEmpireID());
}

PyObject* netGetMainActorVID(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.GetMainActorVID());
}

PyObject* netGetMainActorRace(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.GetMainActorRace());
}

PyObject* netGetMainActorEmpire(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.GetMainActorEmpire());
}

PyObject* netGetMainActorSkillGroup(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.GetMainActorSkillGroup());
}

PyObject* netIsSelectedEmpire(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.IsSelectedEmpire());
}


PyObject* netGetAccountCharacterSlotDataInteger(PyObject* poSelf, PyObject* poArgs)
{
	int nIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &nIndex))
		return Py_BuildException();

	int nType;
	if (!PyTuple_GetInteger(poArgs, 1, &nType))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	UINT uResult=rkNetStream.GetAccountCharacterSlotDatau(nIndex, nType);
	return Py_BuildValue("i", uResult);
}

PyObject* netGetAccountCharacterSlotDataString(PyObject* poSelf, PyObject* poArgs)
{
	int nIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &nIndex))
		return Py_BuildException();

	int nType;
	if (!PyTuple_GetInteger(poArgs, 1, &nType))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("s", rkNetStream.GetAccountCharacterSlotDataz(nIndex, nType));
}

// SUPPORT_BGM
PyObject* netGetFieldMusicFileName(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("s", rkNetStream.GetFieldMusicFileName());
}

PyObject* netGetFieldMusicVolume(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("f", rkNetStream.GetFieldMusicVolume());
}
// END_OF_SUPPORT_BGM

PyObject* netSetPhaseWindow(PyObject* poSelf, PyObject* poArgs)
{
	int ePhaseWnd;
	if (!PyTuple_GetInteger(poArgs, 0, &ePhaseWnd))
		return Py_BuildException();

	PyObject* poPhaseWnd;
	if (!PyTuple_GetObject(poArgs, 1, &poPhaseWnd))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetPhaseWindow(ePhaseWnd, poPhaseWnd);
	return Py_BuildNone();
}

PyObject* netClearPhaseWindow(PyObject* poSelf, PyObject* poArgs)
{
	int ePhaseWnd;
	if (!PyTuple_GetInteger(poArgs, 0, &ePhaseWnd))
		return Py_BuildException();

	PyObject* poPhaseWnd;
	if (!PyTuple_GetObject(poArgs, 1, &poPhaseWnd))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.ClearPhaseWindow(ePhaseWnd, poPhaseWnd);
	return Py_BuildNone();
}

PyObject* netSetServerCommandParserWindow(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* poPhaseWnd;
	if (!PyTuple_GetObject(poArgs, 0, &poPhaseWnd))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetServerCommandParserWindow(poPhaseWnd);
	return Py_BuildNone();
}

PyObject* netSetAccountConnectorHandler(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* poPhaseWnd;
	if (!PyTuple_GetObject(poArgs, 0, &poPhaseWnd))
		return Py_BuildException();

	CAccountConnector & rkAccountConnector = CAccountConnector::Instance();
	rkAccountConnector.SetHandler(poPhaseWnd);
	return Py_BuildNone();
}

PyObject* netSetHandler(PyObject* poSelf, PyObject* poArgs)
{
	PyObject* poHandler;

	if (!PyTuple_GetObject(poArgs, 0, &poHandler))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetHandler(poHandler);
	return Py_BuildNone();
}

PyObject* netSetTCPRecvBufferSize(PyObject* poSelf, PyObject* poArgs)
{
	int bufSize;
	if (!PyTuple_GetInteger(poArgs, 0, &bufSize))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetRecvBufferSize(bufSize);
	return Py_BuildNone();
}

PyObject* netSetTCPSendBufferSize(PyObject* poSelf, PyObject* poArgs)
{
	int bufSize;
	if (!PyTuple_GetInteger(poArgs, 0, &bufSize))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetSendBufferSize(bufSize);
	return Py_BuildNone();
}

PyObject* netSetUDPRecvBufferSize(PyObject* poSelf, PyObject* poArgs)
{
	int bufSize;
	if (!PyTuple_GetInteger(poArgs, 0, &bufSize))
		return Py_BuildException();

	//CPythonNetworkDatagram::Instance().SetRecvBufferSize(bufSize);
	return Py_BuildNone();
}

PyObject* netSetMarkServer(PyObject* poSelf, PyObject* poArgs)
{
	char* szAddr;
	if (!PyTuple_GetString(poArgs, 0, &szAddr))
		return Py_BuildException();

	int port;
	if (!PyTuple_GetInteger(poArgs, 1, &port))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetMarkServer(szAddr, port);
	return Py_BuildNone();
}

PyObject* netConnectTCP(PyObject* poSelf, PyObject* poArgs)
{
	char* szAddr;
	if (!PyTuple_GetString(poArgs, 0, &szAddr))
		return Py_BuildException();

	int port;
	if (!PyTuple_GetInteger(poArgs, 1, &port))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.ConnectLoginServer(szAddr, port);
	return Py_BuildNone();
}

PyObject* netConnectUDP(PyObject* poSelf, PyObject* poArgs)
{
	char * c_szIP;
	if (!PyTuple_GetString(poArgs, 0, &c_szIP))
		return Py_BuildException();
	int iPort;
	if (!PyTuple_GetInteger(poArgs, 1, &iPort))
		return Py_BuildException();

	//CPythonNetworkDatagram::Instance().SetConnection(c_szIP, iPort);
	return Py_BuildNone();
}

PyObject* netConnectToAccountServer(PyObject* poSelf, PyObject* poArgs)
{
	char* addr;
	if (!PyTuple_GetString(poArgs, 0, &addr))
		return Py_BuildException();

	int port;
	if (!PyTuple_GetInteger(poArgs, 1, &port))
		return Py_BuildException();

	char* account_addr;
	if (!PyTuple_GetString(poArgs, 2, &account_addr))
		return Py_BuildException();

	int account_port;
	if (!PyTuple_GetInteger(poArgs, 3, &account_port))
		return Py_BuildException();

	CAccountConnector & rkAccountConnector = CAccountConnector::Instance();
	rkAccountConnector.Connect(addr, port, account_addr, account_port);
	return Py_BuildNone();
}

#ifdef ENABLE_VIEW_MOB_TARGET_SYSTEM
PyObject* netTargetInfoLoad(PyObject* poSelf, PyObject* poArgs)
{
	DWORD dwVID;

	if (!PyArg_ParseTuple(poArgs, "i", &dwVID))
	{
		return Py_BuildException();
	}
	if (dwVID < 0)
	{
		return Py_BuildNone();
	}

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendTargetInfoLoadPacket(dwVID);

	return Py_BuildNone();
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

PyObject* netSetLoginInfo(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	char* szPwd;
	if (!PyTuple_GetString(poArgs, 1, &szPwd))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	CAccountConnector & rkAccountConnector = CAccountConnector::Instance();
	rkNetStream.SetLoginInfo(szName, szPwd);
	rkAccountConnector.SetLoginInfo(szName, szPwd);
	return Py_BuildNone();
}

PyObject* netSetOfflinePhase(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetOffLinePhase();
	return Py_BuildNone();
}

PyObject* netSendSelectEmpirePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iEmpireIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iEmpireIndex))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendSelectEmpirePacket(iEmpireIndex);
	return Py_BuildNone();
}

PyObject* netSendLoginPacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	char* szPwd;
	if (!PyTuple_GetString(poArgs, 1, &szPwd))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendLoginPacket(szName, szPwd);
	return Py_BuildNone();
}

PyObject* netDirectEnter(PyObject* poSelf, PyObject* poArgs)
{
	int nChrSlot;
	if (!PyTuple_GetInteger(poArgs, 0, &nChrSlot))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.ConnectGameServer(nChrSlot);
	return Py_BuildNone();
}

PyObject* netSendSelectCharacterPacket(PyObject* poSelf, PyObject* poArgs)
{
	int Index;
	if (!PyTuple_GetInteger(poArgs, 0, &Index))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendSelectCharacterPacket((BYTE) Index);
	return Py_BuildNone();
}

PyObject* netSendChangeNamePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	char* szName;
	if (!PyTuple_GetString(poArgs, 1, &szName))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendChangeNamePacket((BYTE)iIndex, szName);
	return Py_BuildNone();
}

PyObject* netEnableChatInsultFilter(PyObject* poSelf, PyObject* poArgs)
{
	int nEnable;
	if (!PyTuple_GetInteger(poArgs, 0, &nEnable))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.EnableChatInsultFilter(nEnable ? true : false);
	return Py_BuildNone();
}

PyObject* netIsChatInsultIn(PyObject* poSelf, PyObject* poArgs)
{
	char* szMsg;
	if (!PyTuple_GetString(poArgs, 0, &szMsg))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.IsChatInsultIn(szMsg));
}


PyObject* netIsInsultIn(PyObject* poSelf, PyObject* poArgs)
{
	char* szMsg;
	if (!PyTuple_GetString(poArgs, 0, &szMsg))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.IsInsultIn(szMsg));
}

PyObject* netSendWhisperPacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	char* szLine;

	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 1, &szLine))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendWhisperPacket(szName, szLine);
	return Py_BuildNone();
}

PyObject* netSendMobileMessagePacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	char* szLine;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	if (!PyTuple_GetString(poArgs, 1, &szLine))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendMobileMessagePacket(szName, szLine);
	return Py_BuildNone();
}

PyObject* netSendCharacterPositionPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iPosition;
	if (!PyTuple_GetInteger(poArgs, 0, &iPosition))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendCharacterPositionPacket((BYTE) iPosition);
	return Py_BuildNone();
}

PyObject* netSendChatPacket(PyObject* poSelf, PyObject* poArgs)
{
	char* szLine;
	if (!PyTuple_GetString(poArgs, 0, &szLine))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
	{
		iType = CHAT_TYPE_TALKING;
	}

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendChatPacket(szLine, iType);
	return Py_BuildNone();
}

PyObject* netSendEmoticon(PyObject* poSelf, PyObject* poArgs)
{
	int eEmoticon;
	if (!PyTuple_GetInteger(poArgs, 0, &eEmoticon))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendEmoticon(eEmoticon);
	return Py_BuildNone();
}

PyObject* netSendCreateCharacterPacket(PyObject* poSelf, PyObject* poArgs)
{
	int index;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BuildException();

	char* name;
	if (!PyTuple_GetString(poArgs, 1, &name))
		return Py_BuildException();

	int job;
	if (!PyTuple_GetInteger(poArgs, 2, &job))
		return Py_BuildException();

	int shape;
	if (!PyTuple_GetInteger(poArgs, 3, &shape))
		return Py_BuildException();

	int stat1;
	if (!PyTuple_GetInteger(poArgs, 4, &stat1))
		return Py_BuildException();
	int stat2;
	if (!PyTuple_GetInteger(poArgs, 5, &stat2))
		return Py_BuildException();
	int stat3;
	if (!PyTuple_GetInteger(poArgs, 6, &stat3))
		return Py_BuildException();
	int stat4;
	if (!PyTuple_GetInteger(poArgs, 7, &stat4))
		return Py_BuildException();

	if (index<0 && index>3)
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendCreateCharacterPacket((BYTE) index, name, (BYTE) job, (BYTE) shape, stat1, stat2, stat3, stat4);
	return Py_BuildNone();
}

PyObject* netSendDestroyCharacterPacket(PyObject* poSelf, PyObject* poArgs)
{
	int index;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BuildException();

	char * szPrivateCode;
	if (!PyTuple_GetString(poArgs, 1, &szPrivateCode))
		return Py_BuildException();

	if (index<0 && index>3)
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendDestroyCharacterPacket((BYTE) index, szPrivateCode);
	return Py_BuildNone();
}

PyObject* netSendEnterGamePacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendEnterGame();
	return Py_BuildNone();
}

#ifdef ENABLE_INGAME_MASTER_BAN_SYSTEM
PyObject* netSendAdminBanManager(PyObject* poSelf, PyObject* poArgs)
{
	int action;
	if (!PyTuple_GetInteger(poArgs, 0, &action))
		return Py_BuildException();

	char * c_szUserName;
	if (!PyTuple_GetString(poArgs, 1, &c_szUserName))
		return Py_BuildException();
	
	char * c_szReason;
	if (!PyTuple_GetString(poArgs, 2, &c_szReason))
		return Py_BuildException();

	int duration;
	if (!PyTuple_GetInteger(poArgs, 3, &duration))
		return Py_BuildException();	
	
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendAdminBanManager(action, c_szUserName, c_szReason, duration);
	return Py_BuildNone();
}
#endif

PyObject* netOnClickPacket(PyObject* poSelf, PyObject* poArgs)
{
	int index;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendOnClickPacket(index);

	return Py_BuildNone();
}

PyObject* netSendItemUsePacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos Cell;
	switch (PyTuple_Size(poArgs))
	{
	case 1:
		if (!PyTuple_GetInteger(poArgs, 0, &Cell.cell))
			return Py_BuildException();
		break;
	case 2:
		if (!PyTuple_GetByte(poArgs, 0, &Cell.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &Cell.cell))
			return Py_BuildException();
		break;
	default:
		return Py_BuildException();
	}

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemUsePacket(Cell);
	return Py_BuildNone();
}

PyObject* netSendItemUseToItemPacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos SourceCell;
	TItemPos TargetCell;
	switch (PyTuple_Size(poArgs))
	{
	case 2:
		if (!PyTuple_GetInteger(poArgs, 0, &SourceCell.cell))
			return Py_BuildException();

		if (!PyTuple_GetInteger(poArgs, 1, &TargetCell.cell))
			return Py_BuildException();
		break;
	case 4:
		if (!PyTuple_GetByte(poArgs, 0, &SourceCell.window_type))
			return Py_BuildException();

		if (!PyTuple_GetInteger(poArgs, 1, &SourceCell.cell))
			return Py_BuildException();

		if (!PyTuple_GetByte(poArgs, 2, &TargetCell.window_type))
			return Py_BuildException();

		if (!PyTuple_GetInteger(poArgs, 3, &TargetCell.cell))
			return Py_BuildException();
		break;
	default:
		return Py_BuildException();
	}
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemUseToItemPacket(SourceCell, TargetCell);
	return Py_BuildNone();
}

PyObject* netSendItemDropPacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos Cell;
	switch (PyTuple_Size(poArgs))
	{
	case 1:
		if (!PyTuple_GetInteger(poArgs, 0, &Cell.cell))
			return Py_BuildException();
		break;
	case 2:
		if (!PyTuple_GetByte(poArgs, 0, &Cell.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &Cell.cell))
			return Py_BuildException();
		break;
	default:
		return Py_BuildException();
	}


	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemDropPacket(Cell, 0);
	return Py_BuildNone();
}

PyObject* netSendItemDestroyPacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos Cell;

	if (!PyTuple_GetInteger(poArgs, 0, &Cell.cell))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendItemDestroyPacket(Cell);
	return Py_BuildNone();
}

PyObject* netSendItemDropPacketNew(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos Cell;
	int count;
	switch (PyTuple_Size(poArgs))
	{
	case 2:
		if (!PyTuple_GetInteger(poArgs, 0, &Cell.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &count))
			return Py_BuildException();

		break;
	case 3:
		if (!PyTuple_GetByte(poArgs, 0, &Cell.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &Cell.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &count))
			return Py_BuildException();

		break;
	default:
		return Py_BuildException();
	}
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemDropPacketNew(Cell, 0, count);
	return Py_BuildNone();
}

PyObject* netSendElkDropPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iElk;
	if (!PyTuple_GetInteger(poArgs, 0, &iElk))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemDropPacket(TItemPos(RESERVED_WINDOW, 0), (DWORD) iElk);
	return Py_BuildNone();
}

PyObject* netSendGoldDropPacketNew(PyObject* poSelf, PyObject* poArgs)
{
	int iElk;
	if (!PyTuple_GetInteger(poArgs, 0, &iElk))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemDropPacketNew(TItemPos (RESERVED_WINDOW, 0), (DWORD) iElk, 0);
	return Py_BuildNone();
}

PyObject* netSendItemMovePacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos Cell;
	TItemPos ChangeCell;
	int num;

	switch (PyTuple_Size(poArgs))
	{
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &Cell.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &ChangeCell.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &num))
			return Py_BuildException();
		break;
	case 5:
		{
			if (!PyTuple_GetByte(poArgs, 0, &Cell.window_type))
				return Py_BuildException();
			if (!PyTuple_GetInteger(poArgs, 1, &Cell.cell))
				return Py_BuildException();
			if (!PyTuple_GetByte(poArgs, 2, &ChangeCell.window_type))
				return Py_BuildException();
			if (!PyTuple_GetInteger(poArgs, 3, &ChangeCell.cell))
				return Py_BuildException();
			if (!PyTuple_GetInteger(poArgs, 4, &num))
				return Py_BuildException();
		}
		break;
	default:
		return Py_BuildException();
	}

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemMovePacket(Cell, ChangeCell, (BYTE) num);
	return Py_BuildNone();
}

PyObject* netSendItemPickUpPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendItemPickUpPacket(vid);
	return Py_BuildNone();
}

PyObject* netSendGiveItemPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iTargetVID;
	TItemPos Cell;
	int iItemCount;
	switch (PyTuple_Size(poArgs))
	{
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &iTargetVID))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &Cell.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &iItemCount))
			return Py_BuildException();
		break;
	case 4:
		if (!PyTuple_GetInteger(poArgs, 0, &iTargetVID))
			return Py_BuildException();
		if (!PyTuple_GetByte(poArgs, 1, &Cell.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &Cell.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 3, &iItemCount))
			return Py_BuildException();
		break;
	default:
		break;
	}

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendGiveItemPacket(iTargetVID, Cell, iItemCount);
	return Py_BuildNone();
}

PyObject* netSendShopEndPacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendShopEndPacket();
	return Py_BuildNone();
}

PyObject* netSendShopBuyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 0, &iCount))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendShopBuyPacket(iCount);
	return Py_BuildNone();
}

PyObject* netSendShopSearchBuyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iVid;
	if (!PyTuple_GetInteger(poArgs, 0, &iVid))
		return Py_BuildException();
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 1, &iPos))
		return Py_BuildException();
	int iBuyType;
	if (!PyTuple_GetInteger(poArgs, 2, &iBuyType))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendShopSearchBuyPacket(iVid, iPos, iBuyType);
	return Py_BuildNone();
}

PyObject* netSendShopSearchFindPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iJob;
	if (!PyTuple_GetInteger(poArgs, 0, &iJob))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();
	int iSubType;
	if (!PyTuple_GetInteger(poArgs, 2, &iSubType))
		return Py_BuildException();
	int iMinLevel;
	if (!PyTuple_GetInteger(poArgs, 3, &iMinLevel))
		return Py_BuildException();
	int iMaxLevel;
	if (!PyTuple_GetInteger(poArgs, 4, &iMaxLevel))
		return Py_BuildException();
	int iMinRefine;
	if (!PyTuple_GetInteger(poArgs, 5, &iMinRefine))
		return Py_BuildException();
	int iMaxRefine;
	if (!PyTuple_GetInteger(poArgs, 6, &iMaxRefine))
		return Py_BuildException();
	int iMinPrice;
	if (!PyTuple_GetInteger(poArgs, 7, &iMinPrice))
		return Py_BuildException();
	int iMaxPrice;
	if (!PyTuple_GetInteger(poArgs, 8, &iMaxPrice))
		return Py_BuildException();
	int iMinCheque;
	if (!PyTuple_GetInteger(poArgs, 9, &iMinCheque))
		return Py_BuildException();
	int iMaxCheque;
	if (!PyTuple_GetInteger(poArgs, 10, &iMaxCheque))
		return Py_BuildException();
	char * pcItemName;
	if (!PyTuple_GetString(poArgs, 11, &pcItemName))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendShopSearchFindPacket(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice, iMinCheque, iMaxCheque, pcItemName);

	return Py_BuildNone();
}

PyObject* netSendShopSellPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotNumber))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendShopSellPacket(iSlotNumber);
	return Py_BuildNone();
}

PyObject* netSendShopSellPacketNew(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotNumber;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotNumber))
		return Py_BuildException();
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 1, &iCount))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendShopSellPacketNew(iSlotNumber, iCount);
	return Py_BuildNone();
}

#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
PyObject* netSendOfflineShopEndPacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendOfflineShopEndPacket();
	return Py_BuildNone();
}

PyObject* netSendOfflineShopBuyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 0, &iCount))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendOfflineShopBuyPacket(iCount);
	return Py_BuildNone();
}

PyObject * netSendRefreshOfflineShop(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRefreshOfflineShop();
	return Py_BuildNone();
}

PyObject * netSendAddOfflineShopItem(PyObject * poSelf, PyObject * poArgs)
{
	int bDisplayPos;
	int bPos;
	int iPrice;
	int	iPrice2;
	int iPriceType;
	BYTE bWindowType;

	if (!PyTuple_GetInteger(poArgs, 0, &bDisplayPos))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 1, &bPos))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 2, &iPrice))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 3, &iPrice2))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 4, &iPriceType))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 5, &bWindowType))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendAddOfflineShopItem(TItemPos(bWindowType, bDisplayPos), bPos, iPrice, iPrice2, iPriceType);
	return Py_BuildNone();
}

PyObject * netSendRemoveOfflineShopItem(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bPos))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRemoveOfflineShopItem(bPos);
	return Py_BuildNone();
}

PyObject * netSendDestroyOfflineShop(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendDestroyOfflineShop();
	return Py_BuildNone();
}

PyObject * netSendRefreshOfflineShopMoney(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRefreshOfflineShopMoney();
	return Py_BuildNone();
}

PyObject * netSendRefreshUnsoldItems(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRefreshUnsoldItems();
	return Py_BuildNone();
}

PyObject * netSendOfflineShopTakeItem(PyObject * poSelf, PyObject * poArgs)
{
	BYTE bDisplayPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bDisplayPos))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopTakeItem(bDisplayPos);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawMoney(PyObject * poSelf, PyObject * poArgs)
{
	int llMoney;
	if (!PyTuple_GetInteger(poArgs, 0, &llMoney))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawMoney(llMoney);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawBar1(PyObject * poSelf, PyObject * poArgs)
{
	int iBar;
	if (!PyTuple_GetInteger(poArgs, 0, &iBar))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawBar1(iBar);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawBar2(PyObject * poSelf, PyObject * poArgs)
{
	int iBar;
	if (!PyTuple_GetInteger(poArgs, 0, &iBar))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawBar2(iBar);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawBar3(PyObject * poSelf, PyObject * poArgs)
{
	int iBar;
	if (!PyTuple_GetInteger(poArgs, 0, &iBar))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawBar3(iBar);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawSoulStone(PyObject * poSelf, PyObject * poArgs)
{
	int iSoulStone;
	if (!PyTuple_GetInteger(poArgs, 0, &iSoulStone))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawSoulStone(iSoulStone);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawDragonScale(PyObject * poSelf, PyObject * poArgs)
{
	int iDragonScale;
	if (!PyTuple_GetInteger(poArgs, 0, &iDragonScale))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawDragonScale(iDragonScale);
	return Py_BuildNone();
}

PyObject * netSendOfflineShopWithdrawDragonClaw(PyObject * poSelf, PyObject * poArgs)
{
	int iDragonClaw;
	if (!PyTuple_GetInteger(poArgs, 0, &iDragonClaw))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawDragonClaw(iDragonClaw);
	return Py_BuildNone();
}

#ifdef ENABLE_GF_CHEQUE_SYSTEM
PyObject * netSendOfflineShopWithdrawCheque(PyObject * poSelf, PyObject * poArgs)
{
	int iCheque;
	if (!PyTuple_GetInteger(poArgs, 0, &iCheque))
		return Py_BuildException();

	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopWithdrawCheque(iCheque);
	return Py_BuildNone();
}
#endif

PyObject * netSendOfflineShopTeleport(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopTeleport();
	return Py_BuildNone();	
}

PyObject * netSendOfflineShopCheck(PyObject * poSelf, PyObject * poArgs)
{
	CPythonNetworkStream & rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopCheck();
	return Py_BuildNone();
}
#endif

PyObject* netSendExchangeStartPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendExchangeStartPacket(vid);
	return Py_BuildNone();
}

PyObject* netSendExchangeElkAddPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iElk;
	if (!PyTuple_GetInteger(poArgs, 0, &iElk))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendExchangeElkAddPacket(iElk);
	return Py_BuildNone();
}

#ifdef ENABLE_PARTY_MATCHING_SYSTEM
PyObject* netSendGroupMatchPacket(PyObject* poSelf, PyObject* poArgs)
{
	int index;
	if (!PyTuple_GetInteger(poArgs, 0, &index))
		return Py_BuildException();
	int ayar;
	if (!PyTuple_GetInteger(poArgs, 1, &ayar))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.GroupMatchh(index, ayar);
	return Py_BuildNone();
}
#endif

PyObject* netSendExchangeItemAddPacket(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bWindowType))
		return Py_BuildException();
	WORD wSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wSlotIndex))
		return Py_BuildException();
	int iDisplaySlotIndex;
	if (!PyTuple_GetInteger(poArgs, 2, &iDisplaySlotIndex))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendExchangeItemAddPacket(TItemPos(bWindowType, wSlotIndex), iDisplaySlotIndex);
	return Py_BuildNone();
}

PyObject* netSendExchangeItemDelPacket(PyObject* poSelf, PyObject* poArgs)
{
	int pos;
	if (!PyTuple_GetInteger(poArgs, 0, &pos))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendExchangeItemDelPacket((BYTE) pos);
	return Py_BuildNone();
}

PyObject* netSendExchangeAcceptPacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendExchangeAcceptPacket();
	return Py_BuildNone();
}

PyObject* netSendExchangeExitPacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendExchangeExitPacket();
	return Py_BuildNone();
}

#ifdef ENABLE_GF_CHEQUE_SYSTEM
PyObject* netSendExchangeChequeAddPacket(PyObject* poSelf, PyObject* poArgs)
{
	BYTE iCheque;
	if (!PyTuple_GetInteger(poArgs, 0, &iCheque))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SendExchangeChequeAddPacket(iCheque);
	return Py_BuildNone();
}
#endif

PyObject* netExitApplication(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.ExitApplication();
	return Py_BuildNone();
}

PyObject* netExitGame(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.ExitGame();
	return Py_BuildNone();
}

PyObject* netLogOutGame(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.LogOutGame();
	return Py_BuildNone();
}

PyObject* netDisconnect(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.SetOffLinePhase();
	rkNetStream.Disconnect();

	return Py_BuildNone();
}

PyObject* netIsConnect(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	return Py_BuildValue("i", rkNetStream.IsOnline());
}

PyObject* netToggleGameDebugInfo(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.ToggleGameDebugInfo();
	return Py_BuildNone();
}

PyObject* netRegisterEmoticonString(PyObject* poSelf, PyObject* poArgs)
{
	char * pcEmoticonString;
	if (!PyTuple_GetString(poArgs, 0, &pcEmoticonString))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream=CPythonNetworkStream::Instance();
	rkNetStream.RegisterEmoticonString(pcEmoticonString);
	return Py_BuildNone();
}

#ifdef ENABLE_GF_UPDATE_MESSENGER_SYSTEM
PyObject* netSendMessengerAddBlockByVIDPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendMessengerAddBlockByVIDPacket(vid);
	
	return Py_BuildNone();
}

PyObject* netSendMessengerAddBlockByNamePacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendMessengerAddBlockByNamePacket(szName);
	
	return Py_BuildNone();
}

PyObject* netSendMessengerBlockRemovePacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szKey;
	if (!PyTuple_GetString(poArgs, 0, &szKey))
		return Py_BuildException();
	char * szName;
	if (!PyTuple_GetString(poArgs, 1, &szName))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendMessengerRemoveBlockPacket(szKey, szName);
	
	return Py_BuildNone();
}
#endif

PyObject* netSendMessengerAddByVIDPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendMessengerAddByVIDPacket(vid);

	return Py_BuildNone();
}

PyObject* netSendMessengerAddByNamePacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendMessengerAddByNamePacket(szName);

	return Py_BuildNone();
}

PyObject* netSendMessengerRemovePacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szKey;
	if (!PyTuple_GetString(poArgs, 0, &szKey))
		return Py_BuildException();
	char * szName;
	if (!PyTuple_GetString(poArgs, 1, &szName))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendMessengerRemovePacket(szKey, szName);

	return Py_BuildNone();
}

PyObject* netSendPartyInvitePacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendPartyInvitePacket(vid);

	return Py_BuildNone();
}

PyObject* netSendPartyInviteAnswerPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();
	int answer;
	if (!PyTuple_GetInteger(poArgs, 1, &answer))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendPartyInviteAnswerPacket(vid, answer);

	return Py_BuildNone();
}

PyObject* netSendPartyExitPacket(PyObject* poSelf, PyObject* poArgs)
{
	IAbstractPlayer& rPlayer=IAbstractPlayer::GetSingleton();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();

	DWORD dwVID = rPlayer.GetMainCharacterIndex();
	DWORD dwPID;
	if (rPlayer.PartyMemberVIDToPID(dwVID, &dwPID))
		rns.SendPartyRemovePacket(dwPID);

	return Py_BuildNone();
}

PyObject* netSendPartyRemovePacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendPartyRemovePacket(vid);

	return Py_BuildNone();
}

PyObject* netSendPartySetStatePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVID))
		return Py_BuildException();
	int iState;
	if (!PyTuple_GetInteger(poArgs, 1, &iState))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 2, &iFlag))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendPartySetStatePacket(iVID, iState, iFlag);

	return Py_BuildNone();
}

PyObject* netSendPartyUseSkillPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSkillIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSkillIndex))
		return Py_BuildException();
	int iVID;
	if (!PyTuple_GetInteger(poArgs, 1, &iVID))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendPartyUseSkillPacket(iSkillIndex, iVID);

	return Py_BuildNone();
}

PyObject* netSendPartyParameterPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iMode;
	if (!PyTuple_GetInteger(poArgs, 0, &iMode))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendPartyParameterPacket(iMode);

	return Py_BuildNone();
}

PyObject* netSendSafeboxSaveMoneyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iMoney;
	if (!PyTuple_GetInteger(poArgs, 0, &iMoney))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendSafeBoxMoneyPacket(SAFEBOX_MONEY_STATE_SAVE, iMoney);

	return Py_BuildNone();
}

PyObject* netSendSafeboxWithdrawMoneyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iMoney;
	if (!PyTuple_GetInteger(poArgs, 0, &iMoney))
		return Py_BuildException();

	CPythonNetworkStream& rns = CPythonNetworkStream::Instance();
	rns.SendSafeBoxMoneyPacket(SAFEBOX_MONEY_STATE_WITHDRAW, iMoney);

	return Py_BuildNone();
}

PyObject* netSendSafeboxCheckinPacket(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos InventoryPos;
	int iSafeBoxPos;

	switch (PyTuple_Size(poArgs))
	{
	case 2:
		InventoryPos.window_type = INVENTORY;
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &iSafeBoxPos))
			return Py_BuildException();
		break;
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &iSafeBoxPos))
			return Py_BuildException();
		break;

	}

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendSafeBoxCheckinPacket(InventoryPos, iSafeBoxPos);

	return Py_BuildNone();
}

PyObject* netSendSafeboxCheckoutPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSafeBoxPos;
	TItemPos InventoryPos;

	switch (PyTuple_Size(poArgs))
	{
	case 2:
		if (!PyTuple_GetInteger(poArgs, 0, &iSafeBoxPos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		break;
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &iSafeBoxPos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &InventoryPos.cell))
			return Py_BuildException();
		break;
	default:
		break;
	}

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendSafeBoxCheckoutPacket(iSafeBoxPos, InventoryPos);

	return Py_BuildNone();
}

PyObject* netSendSafeboxItemMovePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSourcePos;
	if (!PyTuple_GetInteger(poArgs, 0, &iSourcePos))
		return Py_BuildException();
	int iTargetPos;
	if (!PyTuple_GetInteger(poArgs, 1, &iTargetPos))
		return Py_BuildException();
	int iCount;
	if (!PyTuple_GetInteger(poArgs, 2, &iCount))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendSafeBoxItemMovePacket(iSourcePos, iTargetPos, iCount);

	return Py_BuildNone();
}

PyObject* netSendMallCheckoutPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iMallPos;
	TItemPos InventoryPos;

	switch (PyTuple_Size(poArgs))
	{
	case 2:
		if (!PyTuple_GetInteger(poArgs, 0, &iMallPos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		break;
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &iMallPos))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 2, &InventoryPos.cell))
			return Py_BuildException();
		break;
	default:
		return Py_BuildException();
	}
	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendMallCheckoutPacket(iMallPos, InventoryPos);

	return Py_BuildNone();
}

PyObject* netSendAnswerMakeGuildPacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendAnswerMakeGuildPacket(szName);

	return Py_BuildNone();
}

PyObject* netSendQuestInputStringPacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szString;
	if (!PyTuple_GetString(poArgs, 0, &szString))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendQuestInputStringPacket(szString);

	return Py_BuildNone();
}

PyObject* netSendQuestConfirmPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iAnswer;
	if (!PyTuple_GetInteger(poArgs, 0, &iAnswer))
		return Py_BuildException();
	int iPID;
	if (!PyTuple_GetInteger(poArgs, 1, &iPID))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendQuestConfirmPacket(iAnswer, iPID);

	return Py_BuildNone();
}

PyObject* netSendGuildAddMemberPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVID))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildAddMemberPacket(iVID);

	return Py_BuildNone();
}

PyObject* netSendGuildRemoveMemberPacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szKey;
	if (!PyTuple_GetString(poArgs, 0, &szKey))
		return Py_BuildException();

	CPythonGuild::TGuildMemberData * pGuildMemberData;
	if (!CPythonGuild::Instance().GetMemberDataPtrByName(szKey, &pGuildMemberData))
	{
		TraceError("netSendGuildRemoveMemberPacket(szKey=%s) - Can't Find Guild Member\n", szKey);
		return Py_BuildNone();
	}

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildRemoveMemberPacket(pGuildMemberData->dwPID);

	return Py_BuildNone();
}

PyObject* netSendGuildChangeGradeNamePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iGradeNumber;
	if (!PyTuple_GetInteger(poArgs, 0, &iGradeNumber))
		return Py_BuildException();
	char * szGradeName;
	if (!PyTuple_GetString(poArgs, 1, &szGradeName))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildChangeGradeNamePacket(iGradeNumber, szGradeName);

	return Py_BuildNone();
}

PyObject* netSendGuildChangeGradeAuthorityPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iGradeNumber;
	if (!PyTuple_GetInteger(poArgs, 0, &iGradeNumber))
		return Py_BuildException();
	int iAuthority;
	if (!PyTuple_GetInteger(poArgs, 1, &iAuthority))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildChangeGradeAuthorityPacket(iGradeNumber, iAuthority);

	return Py_BuildNone();
}

PyObject* netSendGuildOfferPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iExperience;
	if (!PyTuple_GetInteger(poArgs, 0, &iExperience))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildOfferPacket(iExperience);

	return Py_BuildNone();
}

PyObject* netSnedGuildPostCommentPacket(PyObject* poSelf, PyObject* poArgs)
{
	char * szComment;
	if (!PyTuple_GetString(poArgs, 0, &szComment))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildPostCommentPacket(szComment);

	return Py_BuildNone();
}

PyObject* netSnedGuildDeleteCommentPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildDeleteCommentPacket(iIndex);

	return Py_BuildNone();
}

PyObject* netSendGuildRefreshCommentsPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iHightestIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iHightestIndex))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildRefreshCommentsPacket(iHightestIndex);

	return Py_BuildNone();
}

PyObject* netSendGuildChangeMemberGradePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iPID;
	if (!PyTuple_GetInteger(poArgs, 0, &iPID))
		return Py_BuildException();
	int iGradeNumber;
	if (!PyTuple_GetInteger(poArgs, 1, &iGradeNumber))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildChangeMemberGradePacket(iPID, iGradeNumber);

	return Py_BuildNone();
}

PyObject* netSendGuildUseSkillPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSkillID;
	if (!PyTuple_GetInteger(poArgs, 0, &iSkillID))
		return Py_BuildException();
	int iTargetVID;
	if (!PyTuple_GetInteger(poArgs, 1, &iTargetVID))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildUseSkillPacket(iSkillID, iTargetVID);

	return Py_BuildNone();
}

PyObject* netSendGuildChangeMemberGeneralPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iPID;
	if (!PyTuple_GetInteger(poArgs, 0, &iPID))
		return Py_BuildException();
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 1, &iFlag))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildChangeMemberGeneralPacket(iPID, iFlag);

	return Py_BuildNone();
}

PyObject* netSendGuildInviteAnswerPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iGuildID;
	if (!PyTuple_GetInteger(poArgs, 0, &iGuildID))
		return Py_BuildException();
	int iAnswer;
	if (!PyTuple_GetInteger(poArgs, 1, &iAnswer))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildInviteAnswerPacket(iGuildID, iAnswer);

	return Py_BuildNone();
}

PyObject* netSendGuildChargeGSPPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iGSP;
	if (!PyTuple_GetInteger(poArgs, 0, &iGSP))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildChargeGSPPacket(iGSP);

	return Py_BuildNone();
}

PyObject* netSendGuildDepositMoneyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iGSP;
	if (!PyTuple_GetInteger(poArgs, 0, &iGSP))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildDepositMoneyPacket(iGSP);

	return Py_BuildNone();
}

PyObject* netSendGuildWithdrawMoneyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iGSP;
	if (!PyTuple_GetInteger(poArgs, 0, &iGSP))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendGuildWithdrawMoneyPacket(iGSP);

	return Py_BuildNone();
}

PyObject* netSendRequestRefineInfoPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();

//	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
//	rns.SendRequestRefineInfoPacket(iSlotIndex);
	assert(!"netSendRequestRefineInfoPacket - This function is not used anymore");

	return Py_BuildNone();
}

PyObject* netSendRefinePacket(PyObject* poSelf, PyObject* poArgs)
{
	int iSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();
#ifdef ENABLE_REFINE_WINDOW_EXTEND_SYSTEM
	int lLow;
	if (!PyTuple_GetInteger(poArgs, 2, &lLow))
		return Py_BuildException();
	
	int lMedium;
	if (!PyTuple_GetInteger(poArgs, 3, &lMedium))
		return Py_BuildException();

	int lExtra;
	if (!PyTuple_GetInteger(poArgs, 4, &lExtra))
		return Py_BuildException();
	
	int lTotal;
	if (!PyTuple_GetInteger(poArgs, 5, &lTotal))
		return Py_BuildException();
#endif

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
#ifdef ENABLE_REFINE_WINDOW_EXTEND_SYSTEM
	rns.SendRefinePacket(iSlotIndex, iType, lLow, lMedium, lExtra, lTotal);
#else
	rns.SendRefinePacket(iSlotIndex, iType);	
#endif

	return Py_BuildNone();
}

PyObject* netSendSelectItemPacket(PyObject* poSelf, PyObject* poArgs)
{
	int iItemPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemPos))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.SendSelectItemPacket(iItemPos);

	return Py_BuildNone();
}

PyObject* netSetPacketSequenceMode(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	CAccountConnector & rkAccountConnector = CAccountConnector::Instance();
	rns.SetPacketSequenceMode(true);
	rkAccountConnector.SetPacketSequenceMode(true);

	return Py_BuildNone();
}

PyObject* netSetEmpireLanguageMode(PyObject* poSelf, PyObject* poArgs)
{
	int iMode;
	if (!PyTuple_GetInteger(poArgs, 0, &iMode))
		return Py_BuildException();

	//CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	gs_bEmpireLanuageEnable = iMode;

	return Py_BuildNone();
}

PyObject* netSetSkillGroupFake(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	CPythonNetworkStream& rns=CPythonNetworkStream::Instance();
	rns.__TEST_SetSkillGroupFake(iIndex);

	return Py_BuildNone();
}

#include "GuildMarkUploader.h"
#include "GuildMarkDownloader.h"

PyObject* netSendGuildSymbol(PyObject* poSelf, PyObject* poArgs)
{
	char * szIP;
	if (!PyTuple_GetString(poArgs, 0, &szIP))
		return Py_BuildException();
	int iPort;
	if (!PyTuple_GetInteger(poArgs, 1, &iPort))
		return Py_BuildException();
	char * szFileName;
	if (!PyTuple_GetString(poArgs, 2, &szFileName))
		return Py_BuildException();
	int iGuildID;
	if (!PyTuple_GetInteger(poArgs, 3, &iGuildID))
		return Py_BuildException();

	CNetworkAddress kAddress;
	kAddress.Set(szIP, iPort);

	UINT uiError;

	CGuildMarkUploader& rkGuildMarkUploader=CGuildMarkUploader::Instance();
	if (!rkGuildMarkUploader.ConnectToSendSymbol(kAddress, 0, 0, iGuildID, szFileName, &uiError))
	{
		assert(!"Failed connecting to send symbol");
	}

	return Py_BuildNone();
}

PyObject* netDisconnectUploader(PyObject* poSelf, PyObject* poArgs)
{
	CGuildMarkUploader& rkGuildMarkUploader=CGuildMarkUploader::Instance();
	rkGuildMarkUploader.Disconnect();
	return Py_BuildNone();
}

PyObject* netRecvGuildSymbol(PyObject* poSelf, PyObject* poArgs)
{
	char * szIP;
	if (!PyTuple_GetString(poArgs, 0, &szIP))
		return Py_BuildException();
	int iPort;
	if (!PyTuple_GetInteger(poArgs, 1, &iPort))
		return Py_BuildException();
	int iGuildID;
	if (!PyTuple_GetInteger(poArgs, 2, &iGuildID))
		return Py_BuildException();

	CNetworkAddress kAddress;
	kAddress.Set(szIP, iPort);

	std::vector<DWORD> kVec_dwGuildID;
	kVec_dwGuildID.clear();
	kVec_dwGuildID.push_back(iGuildID);

	CGuildMarkDownloader& rkGuildMarkDownloader=CGuildMarkDownloader::Instance();
	if (!rkGuildMarkDownloader.ConnectToRecvSymbol(kAddress, 0, 0, kVec_dwGuildID))
	{
		assert(!"Failed connecting to recv symbol");
	}

	return Py_BuildNone();
}

PyObject* netRegisterErrorLog(PyObject* poSelf, PyObject* poArgs)
{
	char * szLog;
	if (!PyTuple_GetString(poArgs, 0, &szLog))
		return Py_BuildException();

	return Py_BuildNone();
}

#ifdef ENABLE_PRIVATESHOPSEARCH_SYSTEM_NOVA
PyObject* netSendPrivateShopSearchInfo(PyObject* poSelf, PyObject* poArgs)
{
	int iJob;
	if (!PyTuple_GetInteger(poArgs, 0, &iJob))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();
	int iSubType;
	if (!PyTuple_GetInteger(poArgs, 2, &iSubType))
		return Py_BuildException();
	int iMinLevel;
	if (!PyTuple_GetInteger(poArgs, 3, &iMinLevel))
		return Py_BuildException();
	int iMaxLevel;
	if (!PyTuple_GetInteger(poArgs, 4, &iMaxLevel))
		return Py_BuildException();
	int iMinRefine;
	if (!PyTuple_GetInteger(poArgs, 5, &iMinRefine))
		return Py_BuildException();
	int iMaxRefine;
	if (!PyTuple_GetInteger(poArgs, 6, &iMaxRefine))
		return Py_BuildException();
	int iMinPrice;
	if (!PyTuple_GetInteger(poArgs, 7, &iMinPrice))
		return Py_BuildException();
	int iMaxPrice;
	if (!PyTuple_GetInteger(poArgs, 8, &iMaxPrice))
		return Py_BuildException();
	int iMinCheque;
	if (!PyTuple_GetInteger(poArgs, 9, &iMinCheque))
		return Py_BuildException();
	int iMaxCheque;
	if (!PyTuple_GetInteger(poArgs, 10, &iMaxCheque))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendPrivateShopSearchInfo(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice, iMinCheque, iMaxCheque);

	return Py_BuildNone();
}

PyObject* netSendPrivateShopSearchInfoSub(PyObject* poSelf, PyObject* poArgs)
{
	int iJob;
	if (!PyTuple_GetInteger(poArgs, 0, &iJob))
		return Py_BuildException();
	int iType;
	if (!PyTuple_GetInteger(poArgs, 1, &iType))
		return Py_BuildException();
	int iSubType;
	if (!PyTuple_GetInteger(poArgs, 2, &iSubType))
		return Py_BuildException();
	int iMinLevel;
	if (!PyTuple_GetInteger(poArgs, 3, &iMinLevel))
		return Py_BuildException();
	int iMaxLevel;
	if (!PyTuple_GetInteger(poArgs, 4, &iMaxLevel))
		return Py_BuildException();
	int iMinRefine;
	if (!PyTuple_GetInteger(poArgs, 5, &iMinRefine))
		return Py_BuildException();
	int iMaxRefine;
	if (!PyTuple_GetInteger(poArgs, 6, &iMaxRefine))
		return Py_BuildException();
	int iMinPrice;
	if (!PyTuple_GetInteger(poArgs, 7, &iMinPrice))
		return Py_BuildException();
	int iMaxPrice;
	if (!PyTuple_GetInteger(poArgs, 8, &iMaxPrice))
		return Py_BuildException();
	char * pcItemName;
	if (!PyTuple_GetString(poArgs, 9, &pcItemName))
		return Py_BuildException();
	int iMinCheque;
	if (!PyTuple_GetInteger(poArgs, 10, &iMinCheque))
		return Py_BuildException();
	int iMaxCheque;
	if (!PyTuple_GetInteger(poArgs, 11, &iMaxCheque))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendPrivateShopSearchInfoSub(iJob, iType, iSubType, iMinLevel, iMaxLevel, iMinRefine, iMaxRefine, iMinPrice, iMaxPrice, pcItemName, iMinCheque, iMaxCheque);

	return Py_BuildNone();
}

PyObject* netSendPrivateShopSerchBuyItem(PyObject* poSelf, PyObject* poArgs)
{
	int iShopVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iShopVID))
		return Py_BuildException();
	int iItemPos;
	if (!PyTuple_GetInteger(poArgs, 1, &iItemPos))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendPrivateShopSerchBuyItem(iShopVID, iItemPos);
	return Py_BuildNone();
}
#endif

void initnet()
{
	static PyMethodDef s_methods[] =
	{
		{ "GetBettingGuildWarValue",			netGetBettingGuildWarValue,				METH_VARARGS },
		{ "EnableChatInsultFilter",				netEnableChatInsultFilter,				METH_VARARGS },
		{ "SetServerInfo",						netSetServerInfo,						METH_VARARGS },
		{ "GetServerInfo",						netGetServerInfo,						METH_VARARGS },
		{ "PreserveServerCommand",				netPreserveServerCommand,				METH_VARARGS },
		{ "GetPreservedServerCommand",			netGetPreservedServerCommand,			METH_VARARGS },

		{ "StartGame",							netStartGame,							METH_VARARGS },
		{ "Warp",								netWarp,								METH_VARARGS },
		{ "IsTest",								netIsTest,								METH_VARARGS },
		{ "SetMarkServer",						netSetMarkServer,						METH_VARARGS },
		{ "IsChatInsultIn",						netIsChatInsultIn,						METH_VARARGS },
		{ "IsInsultIn",							netIsInsultIn,							METH_VARARGS },
		{ "LoadInsultList",						netLoadInsultList,						METH_VARARGS },
		{ "UploadMark",							netUploadMark,							METH_VARARGS },
		{ "UploadSymbol",						netUploadSymbol,						METH_VARARGS },
		{ "GetGuildID",							netGetGuildID,							METH_VARARGS },
		{ "GetEmpireID",						netGetEmpireID,							METH_VARARGS },
		{ "GetMainActorVID",					netGetMainActorVID,						METH_VARARGS },
		{ "GetMainActorRace",					netGetMainActorRace,					METH_VARARGS },
		{ "GetMainActorEmpire",					netGetMainActorEmpire,					METH_VARARGS },
		{ "GetMainActorSkillGroup",				netGetMainActorSkillGroup,				METH_VARARGS },
		{ "GetAccountCharacterSlotDataInteger",	netGetAccountCharacterSlotDataInteger,	METH_VARARGS },
		{ "GetAccountCharacterSlotDataString",	netGetAccountCharacterSlotDataString,	METH_VARARGS },

		// FIELD_MUSIC
		{ "GetFieldMusicFileName",				netGetFieldMusicFileName,				METH_VARARGS },
		{ "GetFieldMusicVolume",				netGetFieldMusicVolume,					METH_VARARGS },
		// END_OF_FIELD_MUSIC

		{ "ToggleGameDebugInfo",				netToggleGameDebugInfo,					METH_VARARGS },
		{ "SetLoginInfo",						netSetLoginInfo,						METH_VARARGS },
		{ "SetPhaseWindow",						netSetPhaseWindow,						METH_VARARGS },
		{ "ClearPhaseWindow",					netClearPhaseWindow,					METH_VARARGS },
		{ "SetServerCommandParserWindow",		netSetServerCommandParserWindow,		METH_VARARGS },
		{ "SetAccountConnectorHandler",			netSetAccountConnectorHandler,			METH_VARARGS },
		{ "SetHandler",							netSetHandler,							METH_VARARGS },
		{ "SetTCPRecvBufferSize",				netSetTCPRecvBufferSize,				METH_VARARGS },
		{ "SetTCPSendBufferSize",				netSetTCPSendBufferSize,				METH_VARARGS },
		{ "SetUDPRecvBufferSize",				netSetUDPRecvBufferSize,				METH_VARARGS },
		{ "DirectEnter",						netDirectEnter,							METH_VARARGS },

		{ "LogOutGame",							netLogOutGame,							METH_VARARGS },
		{ "ExitGame",							netExitGame,							METH_VARARGS },
		{ "ExitApplication",					netExitApplication,						METH_VARARGS },
		{ "ConnectTCP",							netConnectTCP,							METH_VARARGS },
		{ "ConnectUDP",							netConnectUDP,							METH_VARARGS },
		{ "ConnectToAccountServer",				netConnectToAccountServer,				METH_VARARGS },
#ifdef ENABLE_VIEW_MOB_TARGET_SYSTEM
		{ "SendTargetInfoLoad",					netTargetInfoLoad,						METH_VARARGS },
#endif
		{ "SendLoginPacket",					netSendLoginPacket,						METH_VARARGS },
		{ "SendSelectEmpirePacket",				netSendSelectEmpirePacket,				METH_VARARGS },
		{ "SendSelectCharacterPacket",			netSendSelectCharacterPacket,			METH_VARARGS },
		{ "SendChangeNamePacket",				netSendChangeNamePacket,				METH_VARARGS },
		{ "SendCreateCharacterPacket",			netSendCreateCharacterPacket,			METH_VARARGS },
		{ "SendDestroyCharacterPacket",			netSendDestroyCharacterPacket,			METH_VARARGS },
		{ "SendEnterGamePacket",				netSendEnterGamePacket,					METH_VARARGS },

		{ "SendItemUsePacket",					netSendItemUsePacket,					METH_VARARGS },
		{ "SendItemUseToItemPacket",			netSendItemUseToItemPacket,				METH_VARARGS },
		{ "SendItemDropPacket",					netSendItemDropPacket,					METH_VARARGS },
		{ "SendItemDropPacketNew",				netSendItemDropPacketNew,				METH_VARARGS },

		{ "SendItemDestroyPacket", netSendItemDestroyPacket, METH_VARARGS },

		{ "SendElkDropPacket",					netSendElkDropPacket,					METH_VARARGS },
		{ "SendGoldDropPacketNew",				netSendGoldDropPacketNew,				METH_VARARGS },
		{ "SendItemMovePacket",					netSendItemMovePacket,					METH_VARARGS },
		{ "SendItemPickUpPacket",				netSendItemPickUpPacket,				METH_VARARGS },
		{ "SendGiveItemPacket",					netSendGiveItemPacket,					METH_VARARGS },

		{ "SetOfflinePhase",					netSetOfflinePhase,						METH_VARARGS },
		{ "Disconnect",							netDisconnect,							METH_VARARGS },
		{ "IsConnect",							netIsConnect,							METH_VARARGS },

		{ "SendChatPacket",						netSendChatPacket,						METH_VARARGS },
		{ "SendEmoticon",						netSendEmoticon,						METH_VARARGS },
		{ "SendWhisperPacket",					netSendWhisperPacket,					METH_VARARGS },
		{ "SendMobileMessagePacket",			netSendMobileMessagePacket,				METH_VARARGS },

		{ "SendCharacterPositionPacket",		netSendCharacterPositionPacket,			METH_VARARGS },
#ifdef ENABLE_INGAME_MASTER_BAN_SYSTEM
		{ "SendAdminBanManagerPacket",				netSendAdminBanManager,					METH_VARARGS },
#endif

		{ "SendShopEndPacket",					netSendShopEndPacket,					METH_VARARGS },
		{ "SendShopBuyPacket",					netSendShopBuyPacket,					METH_VARARGS },
		{ "SendShopSearchBuyPacket",			netSendShopSearchBuyPacket,				METH_VARARGS },
		{ "SendShopSearchFindPacket",			netSendShopSearchFindPacket,			METH_VARARGS },
		{ "SendShopSellPacket",					netSendShopSellPacket,					METH_VARARGS },
		{ "SendShopSellPacketNew",				netSendShopSellPacketNew,				METH_VARARGS },

		{ "SendExchangeStartPacket",			netSendExchangeStartPacket,				METH_VARARGS },
		#ifdef ENABLE_PARTY_MATCHING_SYSTEM
		{ "SendGroupMatch",						netSendGroupMatchPacket,				METH_VARARGS },
		#endif
		{ "SendExchangeItemAddPacket",			netSendExchangeItemAddPacket,			METH_VARARGS },
		{ "SendExchangeItemDelPacket",			netSendExchangeItemDelPacket,			METH_VARARGS },
		{ "SendExchangeElkAddPacket",			netSendExchangeElkAddPacket,			METH_VARARGS },
		{ "SendExchangeAcceptPacket",			netSendExchangeAcceptPacket,			METH_VARARGS },
		{ "SendExchangeExitPacket",				netSendExchangeExitPacket,				METH_VARARGS },
#ifdef ENABLE_GF_CHEQUE_SYSTEM
		{ "SendExchangeChequeAddPacket",		netSendExchangeChequeAddPacket,			METH_VARARGS },
#endif

#ifdef ENABLE_OFFLINESHOP_SYSTEM_SK
		{ "SendOfflineShopEndPacket",			netSendOfflineShopEndPacket,			METH_VARARGS },
		{ "SendOfflineShopBuyPacket",			netSendOfflineShopBuyPacket,			METH_VARARGS },
		{ "SendAddOfflineShopItem",				netSendAddOfflineShopItem,				METH_VARARGS },
		{ "SendRemoveOfflineShopItem",			netSendRemoveOfflineShopItem,			METH_VARARGS },
		{ "SendDestroyOfflineShop",				netSendDestroyOfflineShop,				METH_VARARGS },
		{ "SendRefreshOfflineShop",				netSendRefreshOfflineShop,				METH_VARARGS },
		{ "SendRefreshOfflineShopMoney",		netSendRefreshOfflineShopMoney,			METH_VARARGS },
		{ "SendRefreshUnsoldItems",				netSendRefreshUnsoldItems,				METH_VARARGS },
		{ "SendOfflineShopWithdrawMoney",		netSendOfflineShopWithdrawMoney,		METH_VARARGS },
		{ "SendOfflineShopWithdrawBar1",		netSendOfflineShopWithdrawBar1,			METH_VARARGS },
		{ "SendOfflineShopWithdrawBar2",		netSendOfflineShopWithdrawBar2,			METH_VARARGS },
		{ "SendOfflineShopWithdrawBar3",		netSendOfflineShopWithdrawBar3,			METH_VARARGS },
		{ "SendOfflineShopWithdrawSoulStone",	netSendOfflineShopWithdrawSoulStone,	METH_VARARGS },
		{ "SendOfflineShopWithdrawDragonScale",	netSendOfflineShopWithdrawDragonScale,	METH_VARARGS },
		{ "SendOfflineShopWithdrawDragonClaw",	netSendOfflineShopWithdrawDragonClaw,	METH_VARARGS },
#ifdef ENABLE_GF_CHEQUE_SYSTEM
		{ "SendOfflineShopWithdrawCheque",		netSendOfflineShopWithdrawCheque,		METH_VARARGS },
#endif
		{ "SendOfflineShopTakeItem",			netSendOfflineShopTakeItem,				METH_VARARGS },
		{ "SendOfflineShopTeleportPacket",		netSendOfflineShopTeleport,				METH_VARARGS },
		{ "SendOfflineShopCheck",				netSendOfflineShopCheck,				METH_VARARGS },
#endif

		{ "SendOnClickPacket",					netOnClickPacket,						METH_VARARGS },
		
		// Emoticon String
		{ "RegisterEmoticonString",				netRegisterEmoticonString,				METH_VARARGS },

		// Messenger
		{ "SendMessengerAddByVIDPacket",		netSendMessengerAddByVIDPacket,			METH_VARARGS },
		{ "SendMessengerAddByNamePacket",		netSendMessengerAddByNamePacket,		METH_VARARGS },
		{ "SendMessengerRemovePacket",			netSendMessengerRemovePacket,			METH_VARARGS },
		
		#ifdef ENABLE_GF_UPDATE_MESSENGER_SYSTEM
		{ "SendMessengerAddBlockByVIDPacket",		netSendMessengerAddBlockByVIDPacket,			METH_VARARGS },
		{ "SendMessengerAddBlockByNamePacket",		netSendMessengerAddBlockByNamePacket,			METH_VARARGS },
		{ "SendMessengerRemoveBlockPacket",			netSendMessengerBlockRemovePacket,				METH_VARARGS },
		#endif

		// Party
		{ "SendPartyInvitePacket",				netSendPartyInvitePacket,				METH_VARARGS },
		{ "SendPartyInviteAnswerPacket",		netSendPartyInviteAnswerPacket,			METH_VARARGS },
		{ "SendPartyExitPacket",				netSendPartyExitPacket,					METH_VARARGS },
		{ "SendPartyRemovePacket",				netSendPartyRemovePacket,				METH_VARARGS },
		{ "SendPartySetStatePacket",			netSendPartySetStatePacket,				METH_VARARGS },
		{ "SendPartyUseSkillPacket",			netSendPartyUseSkillPacket,				METH_VARARGS },
		{ "SendPartyParameterPacket",			netSendPartyParameterPacket,			METH_VARARGS },

		// Safebox
		{ "SendSafeboxSaveMoneyPacket",			netSendSafeboxSaveMoneyPacket,			METH_VARARGS },
		{ "SendSafeboxWithdrawMoneyPacket",		netSendSafeboxWithdrawMoneyPacket,		METH_VARARGS },
		{ "SendSafeboxCheckinPacket",			netSendSafeboxCheckinPacket,			METH_VARARGS },
		{ "SendSafeboxCheckoutPacket",			netSendSafeboxCheckoutPacket,			METH_VARARGS },
		{ "SendSafeboxItemMovePacket",			netSendSafeboxItemMovePacket,			METH_VARARGS },

		// Mall
		{ "SendMallCheckoutPacket",				netSendMallCheckoutPacket,				METH_VARARGS },

		// Guild
		{ "SendAnswerMakeGuildPacket",				netSendAnswerMakeGuildPacket,				METH_VARARGS },
		{ "SendQuestInputStringPacket",				netSendQuestInputStringPacket,				METH_VARARGS },
		{ "SendQuestConfirmPacket",					netSendQuestConfirmPacket,					METH_VARARGS },
		{ "SendGuildAddMemberPacket",				netSendGuildAddMemberPacket,				METH_VARARGS },
		{ "SendGuildRemoveMemberPacket",			netSendGuildRemoveMemberPacket,				METH_VARARGS },
		{ "SendGuildChangeGradeNamePacket",			netSendGuildChangeGradeNamePacket,			METH_VARARGS },
		{ "SendGuildChangeGradeAuthorityPacket",	netSendGuildChangeGradeAuthorityPacket,		METH_VARARGS },
		{ "SendGuildOfferPacket",					netSendGuildOfferPacket,					METH_VARARGS },
		{ "SendGuildPostCommentPacket",				netSnedGuildPostCommentPacket,				METH_VARARGS },
		{ "SendGuildDeleteCommentPacket",			netSnedGuildDeleteCommentPacket,			METH_VARARGS },
		{ "SendGuildRefreshCommentsPacket",			netSendGuildRefreshCommentsPacket,			METH_VARARGS },
		{ "SendGuildChangeMemberGradePacket",		netSendGuildChangeMemberGradePacket,		METH_VARARGS },
		{ "SendGuildUseSkillPacket",				netSendGuildUseSkillPacket,					METH_VARARGS },
		{ "SendGuildChangeMemberGeneralPacket",		netSendGuildChangeMemberGeneralPacket,		METH_VARARGS },
		{ "SendGuildInviteAnswerPacket",			netSendGuildInviteAnswerPacket,				METH_VARARGS },
		{ "SendGuildChargeGSPPacket",				netSendGuildChargeGSPPacket,				METH_VARARGS },
		{ "SendGuildDepositMoneyPacket",			netSendGuildDepositMoneyPacket,				METH_VARARGS },
		{ "SendGuildWithdrawMoneyPacket",			netSendGuildWithdrawMoneyPacket,			METH_VARARGS },

		// Refine
		{ "SendRequestRefineInfoPacket",			netSendRequestRefineInfoPacket,				METH_VARARGS },
		{ "SendRefinePacket",						netSendRefinePacket,						METH_VARARGS },
		{ "SendSelectItemPacket",					netSendSelectItemPacket,					METH_VARARGS },

		// SYSTEM
		{ "SetPacketSequenceMode",					netSetPacketSequenceMode,					METH_VARARGS },
		{ "SetEmpireLanguageMode",					netSetEmpireLanguageMode,					METH_VARARGS },

		// For Test
		{ "SetSkillGroupFake",						netSetSkillGroupFake,						METH_VARARGS },

		// Guild Symbol
		{ "SendGuildSymbol",						netSendGuildSymbol,							METH_VARARGS },
		{ "DisconnectUploader",						netDisconnectUploader,						METH_VARARGS },
		{ "RecvGuildSymbol",						netRecvGuildSymbol,							METH_VARARGS },

		// Log
		{ "RegisterErrorLog",						netRegisterErrorLog,						METH_VARARGS },

#ifdef ENABLE_PRIVATESHOPSEARCH_SYSTEM_NOVA
		{ "SendPrivateShopSearchInfo",				netSendPrivateShopSearchInfo,				METH_VARARGS },
		{ "SendPrivateShopSearchInfoSub",			netSendPrivateShopSearchInfoSub,			METH_VARARGS },
		{ "SendPrivateShopSerchBuyItem",			netSendPrivateShopSerchBuyItem,				METH_VARARGS },
#endif

		{ NULL,										NULL,										NULL },
	};

	PyObject* poModule = Py_InitModule("net", s_methods);

	PyModule_AddIntConstant(poModule, "ERROR_NONE", CPythonNetworkStream::ERROR_NONE);
	PyModule_AddIntConstant(poModule, "ERROR_CONNECT_MARK_SERVER", CPythonNetworkStream::ERROR_CONNECT_MARK_SERVER);
	PyModule_AddIntConstant(poModule, "ERROR_LOAD_MARK", CPythonNetworkStream::ERROR_LOAD_MARK);
	PyModule_AddIntConstant(poModule, "ERROR_MARK_WIDTH", CPythonNetworkStream::ERROR_MARK_WIDTH);
	PyModule_AddIntConstant(poModule, "ERROR_MARK_HEIGHT", CPythonNetworkStream::ERROR_MARK_HEIGHT);

	// MARK_BUG_FIX
	PyModule_AddIntConstant(poModule, "ERROR_MARK_UPLOAD_NEED_RECONNECT", CPythonNetworkStream::ERROR_MARK_UPLOAD_NEED_RECONNECT);
	PyModule_AddIntConstant(poModule, "ERROR_MARK_CHECK_NEED_RECONNECT", CPythonNetworkStream::ERROR_MARK_CHECK_NEED_RECONNECT);
	// END_OF_MARK_BUG_FIX

	PyModule_AddIntConstant(poModule, "PHASE_WINDOW_LOGIN", CPythonNetworkStream::PHASE_WINDOW_LOGIN);
	PyModule_AddIntConstant(poModule, "PHASE_WINDOW_SELECT", CPythonNetworkStream::PHASE_WINDOW_SELECT);
	PyModule_AddIntConstant(poModule, "PHASE_WINDOW_CREATE", CPythonNetworkStream::PHASE_WINDOW_CREATE);
	PyModule_AddIntConstant(poModule, "PHASE_WINDOW_LOAD", CPythonNetworkStream::PHASE_WINDOW_LOAD);
	PyModule_AddIntConstant(poModule, "PHASE_WINDOW_GAME", CPythonNetworkStream::PHASE_WINDOW_GAME);
	PyModule_AddIntConstant(poModule, "PHASE_WINDOW_EMPIRE", CPythonNetworkStream::PHASE_WINDOW_EMPIRE);
	PyModule_AddIntConstant(poModule, "PHASE_WINDOW_LOGO", CPythonNetworkStream::PHASE_WINDOW_LOGO);

	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_ID", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_ID);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_NAME", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_NAME);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_RACE", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_RACE);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_LEVEL", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_LEVEL);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_STR", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_STR);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_DEX", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_DEX);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_INT", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_INT);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_HTH", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_HTH);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_PLAYTIME", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_PLAYTIME);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_FORM", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_FORM);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_ADDR", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_ADDR);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_PORT", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_PORT);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_GUILD_ID", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_GUILD_ID);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_GUILD_NAME", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_GUILD_NAME);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_CHANGE_NAME_FLAG", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_CHANGE_NAME_FLAG);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_HAIR", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_HAIR);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_ACCE", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_ACCE);
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_WARPOINT", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_WARPOINT);

	PyModule_AddIntConstant(poModule, "SERVER_COMMAND_LOG_OUT",	CPythonNetworkStream::SERVER_COMMAND_LOG_OUT);
	PyModule_AddIntConstant(poModule, "SERVER_COMMAND_RETURN_TO_SELECT_CHARACTER",	CPythonNetworkStream::SERVER_COMMAND_RETURN_TO_SELECT_CHARACTER);
	PyModule_AddIntConstant(poModule, "SERVER_COMMAND_QUIT",	CPythonNetworkStream::SERVER_COMMAND_QUIT);

	PyModule_AddIntConstant(poModule, "EMPIRE_A", 1);
	PyModule_AddIntConstant(poModule, "EMPIRE_B", 2);
	PyModule_AddIntConstant(poModule, "EMPIRE_C", 3);
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_REFINE_FAIL", DS_SUB_HEADER_REFINE_FAIL);
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_REFINE_FAIL_MAX_REFINE", DS_SUB_HEADER_REFINE_FAIL_MAX_REFINE);
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_REFINE_FAIL_INVALID_MATERIAL", DS_SUB_HEADER_REFINE_FAIL_INVALID_MATERIAL);
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MONEY", DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MONEY);
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MATERIAL", DS_SUB_HEADER_REFINE_FAIL_NOT_ENOUGH_MATERIAL);
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_REFINE_FAIL_TOO_MUCH_MATERIAL", DS_SUB_HEADER_REFINE_FAIL_TOO_MUCH_MATERIAL);
	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_REFINE_SUCCEED", DS_SUB_HEADER_REFINE_SUCCEED);
}
