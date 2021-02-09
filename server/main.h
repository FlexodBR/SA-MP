/*

	SA:MP Multiplayer Modification
	Copyright 2004-2005 SA:MP Team

	file:
		main.h
	desc:
		Main header file for the whole project.
		Should be included by all *.cpp files.

*/

#ifndef SAMPSRV_MAIN_H
#define SAMPSRV_MAIN_H

#pragma warning(disable:4786)
#pragma warning(disable:4996)
#pragma warning(disable:4244)

// -------
// DEFINES
// -------

//#define RAKRCON

#define MAX_FILTER_SCRIPTS		16

#define DEFAULT_MAX_PLAYERS		32
#define DEFAULT_LISTEN_PORT		8192
#define DEFAULT_RCON_PORT		8193
#define DEFAULT_RCON_MAXUSERS	8
#define DEFAULT_RCON_PASSWORD	"changeme"
// ------------
// OS SPECIFICS
// ------------

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#define SLEEP(x) { Sleep(x); }

	#include <windows.h>
	#include <tchar.h>
	#include <mmsystem.h>
	#include <malloc.h>
	#include <shellapi.h>
	#include <time.h>
	#include <Shlwapi.h>
#else
	#define SLEEP(x) { usleep(x * 1000); }
	#define MAX_PATH 260

	#include <dlfcn.h>
	#include <unistd.h>
	#include <sys/time.h>
	#include <sys/times.h>
	#include <signal.h>
	#include <sys/types.h>
	#include <sys/sysinfo.h>
	#include <dirent.h>

	typedef int SOCKET;

	#ifndef stricmp
		#define stricmp strcasecmp
	#endif
#endif


// --------
// SETTINGS DEF
typedef struct _SERVER_SETTINGS {
	int  iMaxPlayers;
	int  iPort;
	char szBindIp[64];
} SERVER_SETTINGS;

// --------
// INCLUDES
// --------

// Regular crap
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

// Std
#include <map>
#include <string>
#include <vector>
#include <sstream>

// Raknet
#include <raknet/RakServer.h>
#include <raknet/BitStream.h>
#include <raknet/PacketEnumerations.h>
#include <raknet/SAMPRPC.h>
#include <raknet/DS_Map.h>

// amx
#include <amx/amx.h>

// SQLite3
#include <sqlite/sqlite3.h>

// SHA2-256
#include <sha2/sha256.h>

// Shared stuffs
#include "shared.h"

// Animations
#include "animations.h"

// SA:MP
#include "variable.h"
#include "system.h"
#include "console.h"
#include "httpclient.h"
#include "threadedhttp.h"
#include "scrtimers.h"
#include "gamemodes.h"
#include "filterscripts.h"
#include "netrpc.h"
#include "playertextdrawpool.h"
#include "player.h"
#include "playerpool.h"
#include "vehicle.h"
#include "vehiclepool.h"
#include "pickuppool.h"
#include "object.h"
#include "objectpool.h"
#include "menu.h"
#include "menupool.h"
#include "textdrawpool.h"
#include "gangzonepool.h"
#include "actor.h"
#include "actorpool.h"
#include "netgame.h"
#include "plugins.h"
//#include "rcon.h"
#include "runutil.h"
#include "scrcore.h"

// ---------
// EXTERNALS
// ---------

extern CConsole* pConsole;
extern CNetGame* pNetGame;
extern CPlugins* pPlugins;

/*#ifdef RAKRCON
extern CRcon *pRcon;
#endif*/

extern BYTE byteRconUser;
extern bool bRconSocketReply;
extern bool g_bDBLogging;
extern bool g_bDBLogQueries;
extern bool bGameModeFinished;
extern bool	bQuitApp;
extern unsigned int _uiRndSrvChallenge;
extern float g_fStreamDistance;
extern int g_iStreamRate;
extern bool bQueryLogging;
extern int iSleepTime;

// -------------------
// FUNCTION PROTOTYPES
// -------------------

void logprintf(char* format, ...);
void flogprintf(char* format, ...);
void LoadLogFile();
bool RCONPasswordValid();

#ifdef LINUX
void SignalHandler(int sig);
long GetTickCount();
char* strlwr(char* str);
#endif

#endif // SAMPSRV_MAIN_H
