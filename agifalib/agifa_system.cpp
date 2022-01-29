// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_system.cpp                                               //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include "agifa_system.h"

namespace agifa_base
{

AgifaSystem::AgifaSystem() :
    m_systemId( EmptyId )
{
}

AgifaSystem::~AgifaSystem()
{
}

int AgifaSystem::Compare( const AgifaLinkPointer* poi )
{
    AgifaSystem* p = (AgifaSystem*)poi;
    if( m_systemId == p->m_systemId )
        return 0 ;
    if( m_systemId < p->m_systemId )
        return -1;
    return 1;
}

AgifaLinkPointer* AgifaSystem::Duplicate() const
{
    return (new AgifaSystem())->Copy( this );
}

AgifaLinkPointer* AgifaSystem::Copy( const AgifaLinkPointer* poi )
{
    AgifaSystem* p = (AgifaSystem*)poi;
    m_systemId = p->m_systemId;
    m_trees.Copy( poi );
    m_sensors.Copy( poi );
    m_motors.Copy( poi );
    return this;
}

void AgifaSystem::FreeTrees()
{
    m_trees.Free();
}

bool AgifaSystem::AddNode( AgifaNode* pNode )
{
    pNode->SetNodeId( m_trees.InsertEnd( pNode ) );
    return true;
}

AgifaNode* AgifaSystem::SearchNode( id_t nodeId )
{
    AgifaNode item( nodeId );
    index_t index = EmptyIndex;
    if( m_trees.Search( &item, index ) )
        return &m_trees[index];
    return nullptr;
}

bool AgifaSystem::RemoveNode( id_t nodeId )
{
    AgifaNode item( nodeId );
    index_t index = EmptyIndex;
    if( m_trees.Search( &item, index ) ) {
        delete m_trees.AtRemove( index );
        return true;
    }
    return false;
}

bool AgifaSystem::AddSensor( AgifaSensor* pSensor )
{
    pSensor->SetSensorId( m_sensors.InsertEnd( pSensor ) );
    return true;
}

AgifaSensor* AgifaSystem::SearchSensor( id_t sensorId )
{
    AgifaSensor item( sensorId );
    index_t index = EmptyIndex;
    if( m_sensors.Search( &item, index ) )
        return &m_sensors[index];
    return nullptr;
}

bool AgifaSystem::RemoveSensor( id_t sensorId )
{
    AgifaSensor item( sensorId );
    index_t index = EmptyIndex;
    if( m_sensors.Search( &item, index ) ) {
        delete m_sensors.AtRemove( index );
        return true;
    }
    return false;
}

bool AgifaSystem::AddMotor( AgifaMotor* pMotor )
{
    pMotor->SetMotorId( m_motors.InsertEnd( pMotor ) );
    return true;
}

AgifaMotor* AgifaSystem::SearchMotor( id_t motorId )
{
    AgifaMotor item( motorId, 0, 0 );
    index_t index = EmptyIndex;
    if( m_motors.Search( &item, index ) )
        return &m_motors[index];
    return nullptr;
}

bool AgifaSystem::RemoveMotor( id_t motorId )
{
    AgifaNode item( motorId );
    index_t index = EmptyIndex;
    if( m_motors.Search( &item, index ) ) {
        delete m_motors.AtRemove( index );
        return true;
    }
    return false;
}

}
