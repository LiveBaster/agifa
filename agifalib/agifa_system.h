// Project AGIFA                                                              //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_system.h                                                 //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_SYSTEM_H )
#define __AGIFA_SYSTEM_H

#include "agifadef.h"
#include "agifalib_global.h"
#include "agifa_array.h"
#include "agifa_array_pointers.h"
#include "agifa_sensor.h"
#include "agifa_motor.h"
#include "agifa_node.h"

namespace agifa_base
{

class AGIFALIB_EXPORT AgifaSystem : public AgifaLinkPointer
// система взаимосодействующих компонентов
{
protected:
    // идентификатор системы
    id_t m_systemId;
    // деревья результатов
    AgifaArrayTemp<AgifaNode> m_trees;
    // датчики
    AgifaArrayTemp<AgifaSensor> m_sensors;
    // моторы
    AgifaArrayTemp<AgifaMotor> m_motors;
public:
    AgifaSystem();
    virtual ~AgifaSystem();

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );
};

}

#endif
