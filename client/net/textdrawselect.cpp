
#include "../main.h"

CTextDrawSelect::CTextDrawSelect()
{
	m_pSelectID = -1;
	m_pSelectColor = 0;
	m_pIsActive = false;

	int x=0;
	while (x != MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS) {
		m_pTextDraw[x] = NULL;
		x++;
	}
}

CTextDrawSelect::~CTextDrawSelect()
{
	if (m_pIsActive) {
		m_pSelectID = -1;
		m_pSelectColor = 0;
		m_pIsActive = false;

		int x=0;
		while (x != MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS) {
			SAFE_DELETE(m_pTextDraw[x]);
			x++;
		}
	}
}

void CTextDrawSelect::Enable(DWORD dwHoveredColor)
{
	m_pIsActive = true;
	m_pSelectID = -1;
	m_pSelectColor = (((dwHoveredColor << 16) | dwHoveredColor & 0xFF00) << 8) |
		(((dwHoveredColor >> 16) | dwHoveredColor & 0xFF0000) >> 8);
}

void CTextDrawSelect::Disable()
{
	if (m_pIsActive)
	{
		pGame->DisableCamera(false);
		pGame->DisplayHud(true);

		pCursor->m_ucShowForTextDraw = false;

		m_pSelectID = -1;
		m_pSelectColor = 0;
		m_pIsActive = false;

		int x = 0;
		CTextDrawPool* pTextDrawPool = pNetGame->GetTextDrawPool();
		while (x != MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS) {
			if (pTextDrawPool->GetAt(x) && m_pTextDraw[x]) {
				m_pTextDraw[x]->m_bSelect = 0;
				m_pTextDraw[x]->m_dwSelectColor = 0;
			}
			x++;
		}

		//SendNotification();
	}
}

void CTextDrawSelect::SendNotification()
{
	RakNet::BitStream bsSend;

	bsSend.Write(m_pSelectID);

	pNetGame->Send(RPC_ClickTextDraw, &bsSend);
}

void CTextDrawSelect::Process()
{
	if (m_pIsActive)
	{
		CTextDrawPool* pTextDrawPool = pNetGame->GetTextDrawPool();

		if (pTextDrawPool)
		{
			POINT Point;

			GetCursorPos(&Point);
			ScreenToClient(pGame->GetMainWindowHwnd(), &Point);

			int x=0;
			while (x != MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS) {
				if (pTextDrawPool->GetAt(x)) {
					CTextDraw* pTextDraw = pTextDrawPool->m_pTextDraw[x];
					if (pTextDraw && pTextDraw->m_TextDrawData.byteSelectable)
					{
						m_pTextDraw[x] = pTextDraw;
						m_pSelectID = -1;

						pGame->DisableCamera(true);
						pGame->DisplayHud(false);

						pCursor->m_ucShowForTextDraw = true;

						m_pTextDraw[x]->m_bSelect = 0;
						m_pTextDraw[x]->m_dwSelectColor = 0;

						if (PtInRect(&pTextDraw->m_rArea, Point))
						{
							if (GetAsyncKeyState(VK_LBUTTON))
							{
								m_pSelectID = x;
								SendNotification();
								m_pSelectColor = 0;
								m_pSelectID = -1;
								m_pTextDraw[x]->m_bSelect = 0;
								m_pTextDraw[x]->m_dwSelectColor = 0;
								return;
							}

							m_pTextDraw[x]->m_bSelect = 1;
							m_pTextDraw[x]->m_dwSelectColor = m_pSelectColor;
						}
					}
				}
				x++;
			}
		}
	}
}