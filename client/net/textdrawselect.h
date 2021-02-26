
#pragma once

class CTextDrawSelect
{
private:
    int m_pSelectID;
    bool m_pIsActive;
    DWORD m_pSelectColor;

    CTextDraw* m_pTextDraw[MAX_TEXT_DRAWS + MAX_PLAYER_TEXT_DRAWS];

public:
	CTextDrawSelect();
	~CTextDrawSelect();

    void Enable(DWORD dwHoveredColor);
    void Disable();
    void SendNotification();
    void Process();
};