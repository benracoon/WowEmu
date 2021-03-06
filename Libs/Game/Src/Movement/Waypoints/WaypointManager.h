/*
 * Copyright (C) 2010-2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
 *
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef STRAWBERRY_WAYPOINTMANAGER_H
#define STRAWBERRY_WAYPOINTMANAGER_H

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <vector>

struct WaypointData
{
    uint32 id;
    float x,y,z;
    bool run;
    uint32 delay;
    uint32 event_id;
    uint8 event_chance;

};

typedef std::vector<WaypointData*> WaypointPath;
typedef UNORDERED_MAP<uint32, WaypointPath> WaypointPathContainer;

class WaypointStore
{
    friend class ACE_Singleton<WaypointStore, ACE_Null_Mutex>;

    public:
        WaypointStore();
        ~WaypointStore();

        // Null Mutex is OK because WaypointMgr is initialized in the World thread before World is initialized
        static WaypointStore* instance() { return ACE_Singleton<WaypointStore, ACE_Null_Mutex>::instance(); }

        // Attempts to reload a single path from database
        void UpdatePath(uint32 id);

        // Loads all paths from database, should only run on startup
        void Load();

        // Returns the path from a given id
        WaypointPath const* GetPath(uint32 id) const
        {
            WaypointPathContainer::const_iterator itr = _waypointStore.find(id);
            if (itr != _waypointStore.end())
                return &itr->second;

            return NULL;
        }

        inline uint32 GetRecordsCount() const { return records; }

        private:
            uint32  records;
            WaypointPathContainer _waypointStore;
};

#define sWaypointMgr WaypointStore::instance()

#endif

