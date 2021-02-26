#pragma once

/*

SA:MP Multiplayer Modification
Copyright 2004-2005 SA:MP Team

Version: $Id: textdrawpool.h,v 1.3 2008-02-15 07:20:36 kyecvs Exp $

*/

//----------------------------------------------------

class CTextDrawPool
{
private:
	bool m_bSlotState[MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS];

public:
	CTextDrawPool();
	~CTextDrawPool();

	CTextDraw* m_pTextDraw[MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS];

	CTextDraw * New(WORD wText, TEXT_DRAW_TRANSMIT *TextDrawTransmit, PCHAR szText);
	void Delete(WORD wText);
	void Draw();

	CTextDraw * GetAt(WORD wText) {
		if (wText >= MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS) return NULL;
		if (!m_bSlotState[wText]) return NULL;
		return m_pTextDraw[wText];
	};
};

//----------------------------------------------------
