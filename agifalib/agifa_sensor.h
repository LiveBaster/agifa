// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_sensor.h                                                 //
// AUTHORS:    Victor Artyukhov, Nikita Demerza                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_SENSOR_H )
#define __AGIFA_SENSOR_H

#include "agifadef.h"
#include "agifalib_global.h"
#include "agifa_array.h"
#include "agifa_array_pointers.h"

namespace agifa_base
{

class AGIFALIB_EXPORT AgifaSensor : public AgifaLinkPointer
// датчик
{
protected:
    // идентификатор датчика
    id_t m_sensorId;
    // текущее состояние датчика
    result_t m_result;
public:
    AgifaSensor();
    AgifaSensor( id_t sensorId );
    virtual ~AgifaSensor();

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );

    id_t GetSensorId() const { return m_sensorId; }
    void SetSensorId( id_t sensorId ) { m_sensorId = sensorId; }

    result_t GetResult() const { return m_result; }
    void SetResult( result_t result ) { m_result = result; }
};

}

#endif
