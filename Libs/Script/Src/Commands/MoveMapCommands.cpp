/*
 * Copyright (C) 2010-2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
Name: mm_commandscript
%Complete: 100
Comment: All mm related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MoveMap.h"       // for mmap manager
#include "PathFinder.h"    // for mmap commands
#include "Chat.h"

class mm_commandscript : public CommandScript
{
public:
    mm_commandscript() : CommandScript("mm_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand mmCommandTable[] =
        {
            { "path",           SEC_GAMEMASTER,     false, &HandleMmapPathCommand,            "", NULL },
            { "loc",            SEC_GAMEMASTER,     false, &HandleMmapLocCommand,             "", NULL },
            { "loadedtiles",    SEC_GAMEMASTER,     false, &HandleMmapLoadedTilesCommand,     "", NULL },
            { "stats",          SEC_GAMEMASTER,     false, &HandleMmapStatsCommand,           "", NULL },
            { "testarea",       SEC_GAMEMASTER,     false, &HandleMmapTestArea,               "", NULL },
            { "",               SEC_ADMINISTRATOR,  false, &HandleMmap,                       "", NULL },
            { NULL,             0,                  false, NULL,                              "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "mmap",           SEC_GAMEMASTER,     false, NULL,                     "", mmCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    static bool HandleMmapPathCommand(ChatHandler* handler, const char* args)
    {
        if (!MMAP::MMapFactory::createOrGetMMapManager()->GetNavMesh(handler->GetSession()->GetPlayer()->GetMapId()))
        {
            handler->PSendSysMessage("NavMesh not loaded for current map.");
            return true;
        }

        handler->PSendSysMessage("mmap path:");

        // units
        Player* player = handler->GetSession()->GetPlayer();
        Unit* target = handler->getSelectedUnit();
        if (!player || !target)
        {
            handler->PSendSysMessage("Invalid target/source selection.");
            return true;
        }

        char* para = strtok((char*)args, " ");

        bool useStraightPath = false;
        if (para && strcmp(para, "true") == 0)
            useStraightPath = true;

        // unit locations
        float x, y, z;
        player->GetPosition(x, y, z);

        // path
        PathFinder path(target, x, y, z);
        path.setUseStrightPath(useStraightPath);

        PointPath pointPath = path.getFullPath();

        handler->PSendSysMessage("%s's path to %s:", target->GetName(), player->GetName());
        handler->PSendSysMessage("Building %s", useStraightPath ? "StraightPath" : "SmoothPath");
        handler->PSendSysMessage("length %i type %u", pointPath.size(), path.getPathType());

        PathNode start = path.getStartPosition();
        PathNode next = path.getNextPosition();
        PathNode end = path.getEndPosition();
        PathNode actualEnd = path.getActualEndPosition();

        handler->PSendSysMessage("start      (%.3f, %.3f, %.3f)", start.x, start.y, start.z);
        handler->PSendSysMessage("next       (%.3f, %.3f, %.3f)", next.x, next.y, next.z);
        handler->PSendSysMessage("end        (%.3f, %.3f, %.3f)", end.x, end.y, end.z);
        handler->PSendSysMessage("actual end (%.3f, %.3f, %.3f)", actualEnd.x, actualEnd.y, actualEnd.z);

        if (!player->isGameMaster())
            handler->PSendSysMessage("Enable GM mode to see the path points.");

        // this entry visible only to GM's with "gm on"
        static const uint32 WAYPOINT_NPC_ENTRY = 1;
        Creature* wp = NULL;
        for (uint32 i = 0; i < pointPath.size(); ++i)
        {
            wp = player->SummonCreature(WAYPOINT_NPC_ENTRY, pointPath[i].x, pointPath[i].y, pointPath[i].z, 0, TEMPSUMMON_TIMED_DESPAWN, 9000);
            // TODO: make creature not sink/fall
        }

        return true;
    }

    static bool HandleMmapLocCommand(ChatHandler* handler, const char* args)
    {
        handler->PSendSysMessage("mmap tileloc:");

        // grid tile location
        Player* player = handler->GetSession()->GetPlayer();

        float gx = 32 - player->GetPositionX() / SIZE_OF_GRIDS;
        float gy = 32 - player->GetPositionY() / SIZE_OF_GRIDS;

        handler->PSendSysMessage("%03u%02i%02i.mmtile", player->GetMapId(), gy, gx);
        handler->PSendSysMessage("gridloc [%i,%i]", gx, gy);

        // calculate navmesh tile location
        const dtNavMesh* navmesh = MMAP::MMapFactory::createOrGetMMapManager()->GetNavMesh(player->GetMapId());
        const dtNavMeshQuery* navmeshquery = MMAP::MMapFactory::createOrGetMMapManager()->GetNavMeshQuery(player->GetMapId(), player->GetInstanceId());
        if (!navmesh || !navmeshquery)
        {
            handler->PSendSysMessage("NavMesh not loaded for current map.");
            return true;
        }

        const float* min = navmesh->getParams()->orig;

        float x, y, z;
        player->GetPosition(x, y, z);
        float location[VERTEX_SIZE] = {y, z, x};
        float extents[VERTEX_SIZE] = {3.0f, 5.0f, 3.0f};

        float tilex = (y - min[0] / SIZE_OF_GRIDS);
        float tiley = (x - min[2] / SIZE_OF_GRIDS);

        handler->PSendSysMessage("Calc   [%02i,%02i]", tilex, tiley);

        // navmesh poly -> navmesh tile location
        dtQueryFilter filter = dtQueryFilter();
        dtPolyRef polyRef = INVALID_POLYREF;
        navmeshquery->findNearestPoly(location, extents, &filter, &polyRef, NULL);

        if (polyRef == INVALID_POLYREF)
            handler->PSendSysMessage("Dt     [??,??] (invalid poly, probably no tile loaded)");
        else
        {
            const dtMeshTile* tile;
            const dtPoly* poly;
            navmesh->getTileAndPolyByRef(polyRef, &tile, &poly);
            if (tile)
                handler->PSendSysMessage("Dt     [%02i,%02i]", tile->header->x, tile->header->y);
            else
                handler->PSendSysMessage("Dt     [??,??] (no tile loaded)");
        }

        return true;
    }

    static bool HandleMmapLoadedTilesCommand(ChatHandler* handler, const char* args)
    {
        uint32 mapid = handler->GetSession()->GetPlayer()->GetMapId();

        const dtNavMesh* navmesh = MMAP::MMapFactory::createOrGetMMapManager()->GetNavMesh(mapid);
        const dtNavMeshQuery* navmeshquery = MMAP::MMapFactory::createOrGetMMapManager()->GetNavMeshQuery(mapid, handler->GetSession()->GetPlayer()->GetInstanceId());
        if (!navmesh || !navmeshquery)
        {
            handler->PSendSysMessage("NavMesh not loaded for current map.");
            return true;
        }

        handler->PSendSysMessage("mmap loadedtiles:");

        for (int32 i = 0; i < navmesh->getMaxTiles(); ++i)
        {
            const dtMeshTile* tile = navmesh->getTile(i);
            if (!tile || !tile->header)
                continue;

            handler->PSendSysMessage("[%02i,%02i]", tile->header->x, tile->header->y);
        }

        return true;
    }

    static bool HandleMmapStatsCommand(ChatHandler* handler, const char* args)
    {
        handler->PSendSysMessage("mmap stats:");
        handler->PSendSysMessage("  global mmap pathfinding is %sabled", sWorld->getBoolConfig(CONFIG_BOOL_MMAP_ENABLED) ? "en" : "dis");

        MMAP::MMapManager *manager = MMAP::MMapFactory::createOrGetMMapManager();
        handler->PSendSysMessage(" %u maps loaded with %u tiles overall", manager->getLoadedMapsCount(), manager->getLoadedTilesCount());

        const dtNavMesh* navmesh = manager->GetNavMesh(handler->GetSession()->GetPlayer()->GetMapId());
        if (!navmesh)
        {
            handler->PSendSysMessage("NavMesh not loaded for current map.");
            return true;
        }

        uint32 tileCount = 0;
        uint32 nodeCount = 0;
        uint32 polyCount = 0;
        uint32 vertCount = 0;
        uint32 triCount = 0;
        uint32 triVertCount = 0;
        uint32 dataSize = 0;
        for (int32 i = 0; i < navmesh->getMaxTiles(); ++i)
        {
            const dtMeshTile* tile = navmesh->getTile(i);
            if (!tile || !tile->header)
                continue;

            tileCount ++;
            nodeCount += tile->header->bvNodeCount;
            polyCount += tile->header->polyCount;
            vertCount += tile->header->vertCount;
            triCount += tile->header->detailTriCount;
            triVertCount += tile->header->detailVertCount;
            dataSize += tile->dataSize;
        }

        handler->PSendSysMessage("Navmesh stats on current map:");
        handler->PSendSysMessage(" %u tiles loaded", tileCount);
        handler->PSendSysMessage(" %u BVTree nodes", nodeCount);
        handler->PSendSysMessage(" %u polygons (%u vertices)", polyCount, vertCount);
        handler->PSendSysMessage(" %u triangles (%u vertices)", triCount, triVertCount);
        handler->PSendSysMessage(" %.2f MB of data (not including pointers)", ((float)dataSize / sizeof(unsigned char)) / 1048576);

        return true;
    }

    static bool HandleMmap(ChatHandler* handler, const char* args)
    {
        bool on = sWorld->getBoolConfig(CONFIG_BOOL_MMAP_ENABLED);
        if (on)
            handler->SendSysMessage("WORLD: mmaps are now ENABLED (individual map settings still in effect)");
        else
            handler->SendSysMessage("WORLD: mmaps are now DISABLED");

        handler->PSendSysMessage("mmaps are %sabled", on ? "en" : "dis");

        return true;
    }

    static bool HandleMmapTestArea(ChatHandler* handler, const char* args)
    {
        float radius = 40.0f;
        handler->ExtractFloat((char**)&args, radius);

        CellPair pair(Strawberry::ComputeCellPair(handler->GetSession()->GetPlayer()->GetPositionX(), handler->GetSession()->GetPlayer()->GetPositionY()));
        Cell cell(pair);
        cell.SetNoCreate();

        std::list<Creature*> creatureList;
        Creature* const creature = handler->getSelectedCreature();

        Strawberry::AnyUnitInObjectRangeCheck go_check(handler->GetSession()->GetPlayer(), radius);
        Strawberry::CreatureListSearcher<Strawberry::AnyUnitInObjectRangeCheck> go_search(creature, creatureList, go_check);
        TypeContainerVisitor<Strawberry::CreatureListSearcher<Strawberry::AnyUnitInObjectRangeCheck>, GridTypeMapContainer> go_visit(go_search);

        // Get Creatures
        cell.Visit(pair, go_visit, *(handler->GetSession()->GetPlayer()->GetMap()), *(handler->GetSession()->GetPlayer()), radius);

        if (!creatureList.empty())
        {
            handler->PSendSysMessage("Found %i Creatures.", creatureList.size());

            uint32 paths = 0;
            uint32 uStartTime = getMSTime();

            float gx,gy,gz;
            handler->GetSession()->GetPlayer()->GetPosition(gx,gy,gz);
            for (std::list<Creature*>::iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
            {
                PathFinder((*itr), gx, gy, gz);
                ++paths;
            }

            uint32 uPathLoadTime = getMSTimeDiff(uStartTime, getMSTime());
            handler->PSendSysMessage("Generated %i paths in %i ms", paths, uPathLoadTime);
        }
        else
            handler->PSendSysMessage("No creatures in %f yard range.", radius);

        return true;
    }
};

void AddSC_mm_commandscript()
{
    new mm_commandscript();
}
