// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_motor.h                                                  //
// AUTHORS:    Victor Artyukhov, Nikita Demerza                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_MOTOR_H )
#define __AGIFA_MOTOR_H

#include "agifadef.h"
#include "agifalib_global.h"
#include "agifa_array.h"
#include "agifa_array_pointers.h"

namespace agifa_base
{

class AGIFALIB_EXPORT AgifaMotor : public AgifaLinkPointer
// мотор
{
protected:
    // идентификатор мотора
    id_t m_motorId;
    action_t m_action;
    action_t m_actionMin;
    action_t m_actionMax;
public:
    AgifaMotor();
    virtual ~AgifaMotor();

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );
};

}

#endif
