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

#include "Creature.h"
#include "MapManager.h"
#include "OpcodeHandler.h"
#include "ConfusedMovementGenerator.h"
#include "DestinationHolderImp.h"
#include "VMapFactory.h"
#include "PathFinder.h"

#ifdef MAP_BASED_RAND_GEN
#define rand_norm() unit.rand_norm()
#define urand(a,b) unit.urand(a,b)
#endif

template<class T>
void ConfusedMovementGenerator<T>::Initialize(T &unit)
{
    // set initial position
    unit.GetPosition(i_x, i_y, i_z);

    unit.SetUInt64Value(UNIT_FIELD_TARGET, 0);
    unit.SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit.CastStop();
    unit.StopMoving();
    unit.RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
    unit.AddUnitState(UNIT_STAT_CONFUSED);
}

template<class T>
void ConfusedMovementGenerator<T>::Interrupt(T &unit)
{
    // confused state still applied while movegen disabled
    unit.ClearUnitState(UNIT_STAT_CONFUSED);
}

template<class T>
void ConfusedMovementGenerator<T>::Reset(T &unit)
{
    i_nextMoveTime.Reset(0);
    i_destinationHolder.ResetUpdate();
    unit.StopMoving();
}

template<class T>
bool
ConfusedMovementGenerator<T>::Update(T &unit, const uint32 &diff)
{
    if (!&unit)
        return true;

    if (unit.HasUnitState(UNIT_STAT_ROOT | UNIT_STAT_STUNNED | UNIT_STAT_DISTRACTED))
        return true;

    if (i_nextMoveTime.Passed())
    {
        // currently moving, update location
        Traveller<T> traveller(unit);
        if (i_destinationHolder.UpdateTraveller(traveller, diff))
        {
            if (i_destinationHolder.HasArrived())
            {
                // arrived, stop and wait a bit
                unit.ClearUnitState(UNIT_STAT_MOVE);

                i_nextMoveTime.Reset(urand(800, 1500));
            }
        }
    }
    else
    {
        // waiting for next move
        i_nextMoveTime.Update(diff);
        if (i_nextMoveTime.Passed())
        {
            // start moving
            float x = i_x + 10.0f*(rand_norm_f() - 0.5f);
            float y = i_y + 10.0f*(rand_norm_f() - 0.5f);
            float z = i_z;

            unit.UpdateGroundPositionZ(x, y, z);
            
            Traveller<T> traveller(unit);
            PathFinder path(&unit, x, y, z);
            path.setPathLengthLimit(30.0f);
            if (path.getPathType() & PATHFIND_NOPATH)
            {
                i_nextMoveTime.Reset(urand(800, 1000));
                return true;
            }

            PointPath pointPath = path.getFullPath();

            float speed = traveller.Speed() * 0.001f; // in ms
            uint32 traveltime = uint32(pointPath.GetTotalLength() / speed);
            uint32 flags = (unit.GetTypeId() == TYPEID_UNIT) ? ((Creature*)&unit)->GetUnitMovementFlags() : SPLINEFLAG_WALKING;
            unit.SendMonsterMoveByPath(pointPath, 1, std::min<uint32>(pointPath.size(), 5), flags, traveltime);

            PathNode p = pointPath[std::min<uint32>(pointPath.size()-1, 4)];
            // we do not really need it with mmaps active
            unit.UpdateGroundPositionZ(p.x, p.y, p.z);
            i_destinationHolder.SetDestination(traveller, p.x, p.y, p.z, false);
        }
    }
    return true;
}

template<class T>
void
ConfusedMovementGenerator<T>::Finalize(T &unit)
{
    unit.RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit.ClearUnitState(UNIT_STAT_CONFUSED);
    unit.StopMoving();

    if (unit.GetTypeId() == TYPEID_UNIT && unit.getVictim())
        unit.SetUInt64Value(UNIT_FIELD_TARGET, unit.getVictim()->GetGUID());
}

template void ConfusedMovementGenerator<Player>::Initialize(Player &player);
template void ConfusedMovementGenerator<Creature>::Initialize(Creature &creature);
template void ConfusedMovementGenerator<Player>::Interrupt(Player &player);
template void ConfusedMovementGenerator<Creature>::Interrupt(Creature &creature);
template void ConfusedMovementGenerator<Player>::Finalize(Player &player);
template void ConfusedMovementGenerator<Creature>::Finalize(Creature &creature);
template void ConfusedMovementGenerator<Player>::Reset(Player &player);
template void ConfusedMovementGenerator<Creature>::Reset(Creature &creature);
template bool ConfusedMovementGenerator<Player>::Update(Player &player, const uint32 &diff);
template bool ConfusedMovementGenerator<Creature>::Update(Creature &creature, const uint32 &diff);


