// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_sensor.cpp                                               //
// AUTHORS:    Victor Artyukhov, Nikita Demerza                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include "agifa_sensor.h"

namespace agifa_base
{

AgifaSensor::AgifaSensor() :
    m_sensorId( EmptyId ),
    m_result( 0 )
{
}

AgifaSensor::AgifaSensor( id_t sensorId ) :
    m_sensorId( sensorId ),
    m_result( 0 )
{
}

AgifaSensor::~AgifaSensor()
{
}

int AgifaSensor::Compare( const AgifaLinkPointer* poi )
{
    AgifaSensor* p = (AgifaSensor*)poi;
    if( m_sensorId == p->m_sensorId )
        return 0 ;
    if( m_sensorId < p->m_sensorId )
        return -1;
    return 1;
}

AgifaLinkPointer* AgifaSensor::Duplicate() const
{
    return (new AgifaSensor())->Copy( this );
}

AgifaLinkPointer* AgifaSensor::Copy( const AgifaLinkPointer* poi )
{
    AgifaSensor* p = (AgifaSensor*)poi;
    m_sensorId = p->m_sensorId;
    return this;
}

}
