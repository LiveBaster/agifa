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

    // возвращает количество узлов в m_trees
    index_t GetTreesCount() const { return m_trees.GetCount(); }

    // добавить новый узел ДР в m_trees. Возвращает true, если узел успешно добавлен.
    bool AddNode( AgifaNode* pNode );
    // найти узел ДР в m_trees. Возвращает nullptr, если не находит.
    AgifaNode* SearchNode( id_t nodeId );
    // удаляет узел ДР из m_trees и освобождает память за ним
    bool RemoveNode( id_t nodeId );

    // добавить новый датчик в m_sensors. Возвращает true, если датчик успешно добавлен.
    bool AddSensor( AgifaSensor* pSensor );
    // найти датчик в m_sensors. Возвращает nullptr, если не находит.
    AgifaSensor* SearchSensor( id_t sensorId );
    // удаляет сенсор из m_sensors и освобождает память за ним
    bool RemoveSensor( id_t sensorId );

    // добавить новый мотор в m_motors. Возвращает true, если мотор успешно добавлен.
    bool AddMotor( AgifaMotor* pMotor );
    // найти мотор в m_motors. Возвращает nullptr, если не находит.
    AgifaMotor* SearchMotor( id_t motorId );
    // удаляет мотор из m_motors и освобождает память за ним
    bool RemoveMotor( id_t motorId );
};

}

#endif
