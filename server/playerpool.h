/*

	SA:MP Multiplayer Modification
	Copyright 2004-2005 SA:MP Team

	file:
		playerpool.h
	desc:
		Player pool handling header file.

    Version: $Id: playerpool.h,v 1.12 2006/04/09 09:54:46 kyeman Exp $

*/

#ifndef SAMPSRV_PLAYERPOOL_H
#define SAMPSRV_PLAYERPOOL_H

//----------------------------------------------------

class CPlayerPool
{
private:
	
	bool	m_bPlayerSlotState[MAX_PLAYERS];
	CPlayer *m_pPlayers[MAX_PLAYERS];
	//CHAR	m_szPlayerName[MAX_PLAYERS][MAX_PLAYER_NAME+1];
	//int 	m_iPlayerScore[MAX_PLAYERS];
	//int	m_iPlayerMoney[MAX_PLAYERS];
	//bool	m_bIsAnAdmin[MAX_PLAYERS];
	//BYTE	m_byteVirtualWorld[MAX_PLAYERS];
	int		m_iPlayerCount;
	int		m_iLastPlayerId;

public:
	
	CPlayerPool();
	~CPlayerPool();

	bool Process(float fElapsedTime);
	bool New(BYTE bytePlayerID, PCHAR szPlayerName, char* szVersion);
	bool Delete(BYTE bytePlayerID, BYTE byteReason);
		
	// Retrieve a player
	CPlayer* GetAt(int iPlayerID) {
		return (iPlayerID >= 0 && iPlayerID < MAX_PLAYERS) ? m_pPlayers[iPlayerID] : nullptr;
	};

	// Find out if the slot is inuse.
	bool GetSlotState(int iPlayerID) {
		return (iPlayerID >= 0 && iPlayerID < MAX_PLAYERS) ? m_bPlayerSlotState[iPlayerID] : false;
	};

	/*PCHAR GetPlayerName(BYTE bytePlayerID) {
		if(bytePlayerID >= MAX_PLAYERS) { return NULL; }
		return m_szPlayerName[bytePlayerID];
	};

	int GetPlayerScore(BYTE bytePlayerID) {
		if(bytePlayerID >= MAX_PLAYERS) { return 0; }
		return m_iPlayerScore[bytePlayerID];
	};

	void SetPlayerScore(BYTE bytePlayerID, int iScore) {
		if(bytePlayerID >= MAX_PLAYERS) return;
		m_iPlayerScore[bytePlayerID] = iScore;
	};

	void SetPlayerName(BYTE bytePlayerID, PCHAR szName) {
		strcpy(m_szPlayerName[bytePlayerID], szName);
	}

	int GetPlayerMoney(BYTE bytePlayerID) {
		if(bytePlayerID >= MAX_PLAYERS) { return 0; }
		return m_iPlayerMoney[bytePlayerID];
	};

	void SetPlayerMoney(BYTE bytePlayerID, int iMoney) {
		if(bytePlayerID >= MAX_PLAYERS) return;
		m_iPlayerMoney[bytePlayerID] = iMoney;
	};*/

	/*void ResetPlayerScoresAndMoney() {
		//memset(&m_iPlayerScore[0],0,sizeof(int) * MAX_PLAYERS);
		//memset(&m_iPlayerMoney[0],0,sizeof(int) * MAX_PLAYERS);	
		//memset(&m_byteVirtualWorld[0],0,sizeof(BYTE) * MAX_PLAYERS);	
	};
	
	void SetPlayerVirtualWorld(BYTE bytePlayerID, BYTE byteVirtualWorld);
	
	BYTE GetPlayerVirtualWorld(BYTE bytePlayerID) {
		if (bytePlayerID >= MAX_PLAYERS) { return 0; }
		return m_byteVirtualWorld[bytePlayerID];		
	};*/

	/*void SetAdmin(unsigned int iPlayerId, bool bToggle) { m_bIsAnAdmin[iPlayerId] = bToggle; }
	void SetAdmin(BYTE bytePlayerID) { m_bIsAnAdmin[bytePlayerID] = true; };
	bool IsAdmin(BYTE bytePlayerID) { return m_bIsAnAdmin[bytePlayerID]; };*/

	void InitPlayersForPlayer(BYTE bytePlayerID);
	void InitSpawnsForPlayer(BYTE bytePlayerID);

	BYTE GetKillType(BYTE byteWhoKilled, BYTE byteWhoDied);

	float GetDistanceFromPlayerToPlayer(BYTE bytePlayer1, BYTE bytePlayer2);
	float GetDistanceSquaredFromPlayerToPlayer(BYTE bytePlayer1, BYTE bytePlayer2);
	bool  IsNickInUse(PCHAR szNick);

	int GetPlayerCount() { return m_iPlayerCount; };

	void DestroyActorForPlayers(unsigned short usActorID);

	void DeactivateAll();
	int GetLastPlayerId() const { return m_iLastPlayerId; }
	
	char* GetAnimNameByIndex(int iIndex) {
		if (iIndex > 1812 || iIndex < 1) return (char*)0;
		return (char*)g_szAnimNames[iIndex];
	};
};

//----------------------------------------------------

#endif