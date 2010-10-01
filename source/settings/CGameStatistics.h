#ifndef _GAME_STATISTICS_H_
#define _GAME_STATISTICS_H_

#include <string>
#include <stdio.h>
#include <gctypes.h>
#include <vector>
#include "usbloader/disc.h"

typedef struct _Stats
{
    char id[7];
    u8 FavoriteRank;
    u8 LockStatus;
    u8 PlayCount;
} GameStatus;

class CGameStatistics
{
    public:
        //!Constructor
        CGameStatistics();
        //!Destructor
        ~CGameStatistics();
        //!Load
        bool Load(const char * path);
        //!Save
        bool Save();
        //!AddGame
        bool AddGame(const GameStatus & NewGame);
        //!Reset
        bool RemoveAll();
        //!Overload for removing one game out of the list
        bool Remove(const char * id);
        bool Remove(const u8 * id) { return Remove((const char *) id); };
        bool Remove(const struct discHdr * game) { if(!game) return false; else return Remove(game->id); };
        //!Overloads for set playcount
        void SetPlayCount(const char * id, int count);
        void SetPlayCount(const u8 * id, int count) { SetPlayCount((const char *) id, count); };
        void SetPlayCount(const struct discHdr * game, int count) { if(!game) return; SetPlayCount(game->id, count); };
        //!Overloads for get playcount
        int GetPlayCount(const char * id);
        int GetPlayCount(const u8 * id) { return GetPlayCount((const char *) id); };
        int GetPlayCount(const struct discHdr * game) { if(!game) return 0; else return GetPlayCount(game->id); };
        //!Overloads for set FavoriteRank
        void SetFavoriteRank(const char * id, int rank);
        void SetFavoriteRank(const u8 * id, int rank) { SetFavoriteRank((const char *) id, rank); };
        void SetFavoriteRank(const struct discHdr * game, int rank) { if(!game) return; SetFavoriteRank(game->id, rank); };
        //!Overloads for get FavoriteRank
        int GetFavoriteRank(const char * id);
        int GetFavoriteRank(const u8 * id) { return GetFavoriteRank((const char *) id); };
        int GetFavoriteRank(const struct discHdr * game) { if(!game) return 0; else return GetFavoriteRank(game->id); };
        //!Overloads for set LockStatus
        void SetLockStatus(const char * id, int lock);
        void SetLockStatus(const u8 * id, int lock) { SetLockStatus((const char *) id, lock); };
        void SetLockStatus(const struct discHdr * game, int lock) { if(!game) return; SetLockStatus(game->id, lock); };
        //!Overloads for get LockStatus
        int GetLockStatus(const char * id);
        int GetLockStatus(const u8 * id) { return GetLockStatus((const char *) id); };
        int GetLockStatus(const struct discHdr * game) { if(!game) return 0; else return GetLockStatus(game->id); };
        //!Get GameStatus
        GameStatus * GetGameStatus(const char * id);
        //!Overload
        GameStatus * GetGameStatus(const u8 * id) { return GetGameStatus((const char *) id); };
        //!Overload
        GameStatus * GetGameStatus(const struct discHdr * game) { if(!game) return NULL; else return GetGameStatus(game->id); };

    protected:
        bool ReadGameID(const char * src, char * GameID, int size);
        bool SetSetting(GameStatus & game, char *name, char *value);

        void ParseLine(char *line);
        void TrimLine(char *dest, const char *src, int size);
        std::string ConfigPath;
        std::vector<GameStatus> GameList;
};

extern CGameStatistics GameStatistics;

#endif