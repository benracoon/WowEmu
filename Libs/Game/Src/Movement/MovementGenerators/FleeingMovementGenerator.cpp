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
#include "CreatureAI.h"
#include "MapManager.h"
#include "FleeingMovementGenerator.h"
#include "DestinationHolderImp.h"
#include "ObjectAccessor.h"
#include "PathFinder.h"

#define MIN_QUIET_DISTANCE 28.0f
#define MAX_QUIET_DISTANCE 43.0f

template<class T>
void FleeingMovementGenerator<T>::_setTargetLocation(T &owner)
{
    if (!&owner)
        return;

    if (owner.HasUnitState(UNIT_STAT_ROOT | UNIT_STAT_STUNNED))
        return;

    float x, y, z;
    if (!_getPoint(owner, x, y, z))
        return;

    owner.AddUnitState(UNIT_STAT_FLEEING | UNIT_STAT_ROAMING);
    Traveller<T> traveller(owner);
    
    PathFinder path(&owner, x, y, z);
    path.setPathLengthLimit(30.0f);

    if (path.getPathType() & PATHFIND_NOPATH)
    {
        i_nextCheckTime.Reset(urand(1000, 1500));
        return;
    }

    PointPath pointPath = path.getFullPath();

    float speed = traveller.Speed() * 0.001f; // in ms
    uint32 traveltime = uint32(pointPath.GetTotalLength() / speed);
    uint32 flags = (owner.GetTypeId() == TYPEID_UNIT) ? ((Creature*)&owner)->GetUnitMovementFlags() : SPLINEFLAG_WALKING;
    owner.SendMonsterMoveByPath(pointPath, 1, std::min<uint32>(pointPath.size(), 5), flags, traveltime);

    PathNode p = pointPath[std::min<uint32>(pointPath.size()-1, 4)];
    owner.UpdateGroundPositionZ(p.x, p.y, p.z);

    i_destinationHolder.SetDestination(traveller, p.x, p.y, p.z, false);
    i_nextCheckTime.Reset(traveltime + urand(800, 1500));
}

template<class T>
bool FleeingMovementGenerator<T>::_getPoint(T &owner, float &x, float &y, float &z)
{
    if(!&owner)
        return false;

    float dist_from_caster, angle_to_caster;
    if(Unit *fright = ObjectAccessor::GetUnit(owner, i_frightGUID))
    {
        dist_from_caster = fright->GetDistance(&owner);
        if(dist_from_caster > 0.2f)
            angle_to_caster = fright->GetAngle(&owner);
        else
            angle_to_caster = frand(0, 2*M_PI_F);
    }
    else
    {
        dist_from_caster = 0.0f;
        angle_to_caster = frand(0, 2*M_PI_F);
    }

    float dist, angle;
    if(dist_from_caster < MIN_QUIET_DISTANCE)
    {
        dist = frand(0.4f, 1.3f)*(MIN_QUIET_DISTANCE - dist_from_caster);
        angle = angle_to_caster + frand(-M_PI_F/8, M_PI_F/8);
    }
    else if(dist_from_caster > MAX_QUIET_DISTANCE)
    {
        dist = frand(0.4f, 1.0f)*(MAX_QUIET_DISTANCE - MIN_QUIET_DISTANCE);
        angle = -angle_to_caster + frand(-M_PI_F/4, M_PI_F/4);
    }
    else    // we are inside quiet range
    {
        dist = frand(0.6f, 1.2f)*(MAX_QUIET_DISTANCE - MIN_QUIET_DISTANCE);
        angle = frand(0, 2*M_PI_F);
    }

    float curr_x, curr_y, curr_z;
    owner.GetPosition(curr_x, curr_y, curr_z);

    x = curr_x + dist*cos(angle);
    y = curr_y + dist*sin(angle);
    z = curr_z;

    owner.UpdateGroundPositionZ(x, y, z);

    return true;
}

template<class T>
void FleeingMovementGenerator<T>::Initialize(T &owner)
{
    if (!&owner)
        return;

    owner.CastStop();
    owner.AddUnitState(UNIT_STAT_FLEEING | UNIT_STAT_ROAMING);
    owner.SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);

    if(owner.GetTypeId() == TYPEID_UNIT)
    {
        ((Creature*)&owner)->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
        ((Creature*)&owner)->SetUInt64Value(UNIT_FIELD_TARGET, 0);
    }

    _setTargetLocation(owner);
}

template<class T>
void
FleeingMovementGenerator<T>::Finalize(T &owner)
{
    owner.RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);
    owner.ClearUnitState(UNIT_STAT_FLEEING | UNIT_STAT_ROAMING);
    owner.ClearUnitState(UNIT_STAT_MOVE);

    if (owner.GetTypeId() == TYPEID_UNIT && owner.getVictim())
        owner.SetUInt64Value(UNIT_FIELD_TARGET, owner.getVictim()->GetGUID());
}

template<class T>
void FleeingMovementGenerator<T>::Interrupt(T &owner)
{
    // flee state still applied while movegen disabled
    owner.ClearUnitState(UNIT_STAT_FLEEING);
}

template<class T>
void
FleeingMovementGenerator<T>::Reset(T &owner)
{
    Initialize(owner);
}

template<class T>
bool
FleeingMovementGenerator<T>::Update(T &owner, const uint32 & time_diff)
{
    if (!&owner || !owner.isAlive())
        return false;
    if (owner.HasUnitState(UNIT_STAT_ROOT | UNIT_STAT_STUNNED))
        return true;

    Traveller<T> traveller(owner);

    i_nextCheckTime.Update(time_diff);

    if ((owner.IsStopped() && !i_destinationHolder.HasArrived()) || !i_destinationHolder.HasDestination())
    {
        _setTargetLocation(owner);
        return true;
    }

    if (i_destinationHolder.UpdateTraveller(traveller, time_diff))
    {
        i_destinationHolder.ResetUpdate(100);
        if (i_nextCheckTime.Passed() && i_destinationHolder.HasArrived())
        {
            _setTargetLocation(owner);
            return true;
        }
    }
    return true;
}

template<>
bool FleeingMovementGenerator<Creature>::GetDestination(float &x, float &y, float &z) const
{
    if (i_destinationHolder.HasArrived())
        return false;

    i_destinationHolder.GetDestination(x, y, z);
    return true;
}

template<>
bool FleeingMovementGenerator<Player>::GetDestination(float & /*x*/, float & /*y*/, float & /*z*/) const
{
    return false;
}

template void FleeingMovementGenerator<Player>::Initialize(Player &);
template void FleeingMovementGenerator<Creature>::Initialize(Creature &);
template bool FleeingMovementGenerator<Player>::_getPoint(Player &, float &, float &, float &);
template bool FleeingMovementGenerator<Creature>::_getPoint(Creature &, float &, float &, float &);
template void FleeingMovementGenerator<Player>::_setTargetLocation(Player &);
template void FleeingMovementGenerator<Creature>::_setTargetLocation(Creature &);
template void FleeingMovementGenerator<Player>::Interrupt(Player &);
template void FleeingMovementGenerator<Creature>::Interrupt(Creature &);
template void FleeingMovementGenerator<Player>::Finalize(Player &);
template void FleeingMovementGenerator<Creature>::Finalize(Creature &);
template void FleeingMovementGenerator<Player>::Reset(Player &);
template void FleeingMovementGenerator<Creature>::Reset(Creature &);
template bool FleeingMovementGenerator<Player>::Update(Player &, const uint32 &);
template bool FleeingMovementGenerator<Creature>::Update(Creature &, const uint32 &);

void TimedFleeingMovementGenerator::Finalize(Unit &owner)
{
    owner.RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);
    owner.ClearUnitState(UNIT_STAT_FLEEING | UNIT_STAT_ROAMING);
    if (Unit* victim = owner.getVictim())
    {
        if (owner.isAlive())
        {
            owner.AttackStop();
            owner.ToCreature()->AI()->AttackStart(victim);
        }
    }
}

bool TimedFleeingMovementGenerator::Update(Unit & owner, const uint32 & time_diff)
{
    if (!owner.isAlive())
        return false;

    if (owner.HasUnitState(UNIT_STAT_ROOT | UNIT_STAT_STUNNED))
        return true;

    i_totalFleeTime.Update(time_diff);
    if (i_totalFleeTime.Passed())
        return false;

    // This calls grant-parent Update method hiden by FleeingMovementGenerator::Update(Creature &, const uint32 &) version
    // This is done instead of casting Unit& to Creature& and call parent method, then we can use Unit directly
    return MovementGeneratorMedium< Creature, FleeingMovementGenerator<Creature> >::Update(owner, time_diff);
}

