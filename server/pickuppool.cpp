/*

	SA:MP Multiplayer Modification
	Copyright 2004-2005 SA:MP Team

    Version: $Id: pickuppool.cpp,v 1.5 2006/05/07 15:35:32 kyeman Exp $

*/

#include "main.h"

//----------------------------------------------------

int CPickupPool::New(int iModel, int iType, float fX, float fY, float fZ, BYTE staticp, int iVirtualWorld)
{
	if (m_iPickupCount >= MAX_PICKUPS) return -1;

	for (int i = 0; i < MAX_PICKUPS; i++)
	{
		if (!m_bActive[i])
		{
			m_Pickups[i].iModel = iModel;
			m_Pickups[i].iType = iType;
			m_Pickups[i].fX = fX;
			m_Pickups[i].fY = fY;	
			m_Pickups[i].fZ = fZ;
			m_iVirtualWorld[i] = iVirtualWorld;
			if (staticp)
			{
				// Static, can't be destroyed
				m_bActive[i] = -1;
			}
			else
			{
				// Dynamic, can be destroyed
				m_bActive[i] = 1;
			}
			m_iPickupCount++;
			
			// Broadcast to existing players:
			// No longer needed. Handled by streaming..
			/*RakNet::BitStream bsPickup;
			bsPickup.Write(i);
			bsPickup.Write((PCHAR)&m_Pickups[i], sizeof (PICKUP));
			pNetGame->GetRakServer()->RPC(RPC_Pickup, &bsPickup, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, true, false);*/
			
			ProcessLastID();
			return i;
		}
	}
	return -1;
}

int CPickupPool::Destroy(int iPickup)
{
	if (iPickup >= 0 && iPickup < MAX_PICKUPS && m_bActive[iPickup] == 1 && pNetGame->GetPlayerPool())
	{
		// Destroying the given pickup for all player who has that pickup streamed in
		for (BYTE i = 0; i < MAX_PLAYERS; i++) {
			CPlayer* pPlayer = pNetGame->GetPlayerPool()->GetAt(i);
			if (pPlayer && pPlayer->IsPickupStreamedIn(iPickup)) {
				StreamOut(iPickup, i); // a.k.a. destroy it...
			}
		}
		m_bActive[iPickup] = 0;
		m_iPickupCount--;
		/*RakNet::BitStream bsPickup;
		bsPickup.Write(iPickup);
		pNetGame->GetRakServer()->RPC(RPC_DestroyPickup, &bsPickup, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, true, false);*/
		ProcessLastID();
		return 1;
		
	}
	return 0;
}

void CPickupPool::ProcessLastID()
{
	m_sLastPickupID = -1;
	for (int i = 0; i < MAX_PICKUPS; i++) {
		if (m_bActive[i])
			m_sLastPickupID = i;
	}
}

//----------------------------------------------------

// No longer needed, since handled by internal streaming (TODO)
void CPickupPool::InitForPlayer(BYTE bytePlayerID)
{	
	/*RakNet::BitStream *pbsPickup;

	int x=0;

	pbsPickup = new RakNet::BitStream();

	while(x != MAX_PICKUPS)
	{
		if (m_bActive[x])
		{
			pbsPickup->Write(x);
			pbsPickup->Write((PCHAR)&m_Pickups[x], sizeof (PICKUP));
		
			pNetGame->GetRakServer()->RPC(RPC_Pickup,pbsPickup,HIGH_PRIORITY,RELIABLE,
				0,pNetGame->GetRakServer()->GetPlayerIDFromIndex(bytePlayerID),false,false);

			pbsPickup->Reset();
		}

		x++;
	}

	delete pbsPickup;*/
}

bool CPickupPool::IsValid(int iPickupId)
{
	if (0 <= iPickupId && iPickupId <= MAX_PICKUPS && m_bActive[iPickupId] != 0)
		return true;

	return false;
}

bool CPickupPool::IsStatic(int iPickupId)
{
	if (0 <= iPickupId && iPickupId <= MAX_PICKUPS && m_bActive[iPickupId] == -1)
		return true;

	return false;
}

void CPickupPool::StreamIn(int iPickupID, BYTE bytePlayerID)
{
	if (IsValid(iPickupID)) {
		RakNet::BitStream bsPickup;
		bsPickup.Write(iPickupID);
		bsPickup.Write((PCHAR)&m_Pickups[iPickupID], sizeof(PICKUP));
		pNetGame->SendToPlayer(bytePlayerID, RPC_Pickup, &bsPickup);
	}
}

void CPickupPool::StreamOut(int iPickupID, BYTE bytePlayerID)
{
	if (IsValid(iPickupID)) {
		RakNet::BitStream bsPickup;	
		bsPickup.Write(iPickupID);
		pNetGame->SendToPlayer(bytePlayerID, RPC_DestroyPickup, &bsPickup);
	}
}

int CPickupPool::GetVirtualWorld(int iPickupID)
{
	return m_iVirtualWorld[iPickupID];
}
