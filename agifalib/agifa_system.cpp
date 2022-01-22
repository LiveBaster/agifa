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

}
