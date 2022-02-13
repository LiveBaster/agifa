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
    // текущее состояние мотора
    action_t m_action;
    // минимально возможное состояние мотора
    action_t m_actionMin;
    // максимально возможное состояние мотора
    action_t m_actionMax;
    // направление движения мотора
    int m_direction;
    // индикатор изменения значения состояния мотора
    bool m_actionChanged;
public:
    AgifaMotor();
    AgifaMotor( id_t motorId, action_t actionMin, action_t actionMax );
    virtual ~AgifaMotor();

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );

    id_t GetMotorId() const { return m_motorId; }
    void SetMotorId( id_t motorId ) { m_motorId = motorId; }

    action_t GetAction() const { return m_action; }
    void SetAction( action_t action ) { m_action = action; }

    action_t GetActionMin() const { return m_actionMin; }
    void SetActionMin( action_t actionMin ) { m_actionMin = actionMin; }

    action_t GetActionMax() const { return m_actionMax; }
    void SetActionMax( action_t actionMax ) { m_actionMax = actionMax; }

    // синтезирует очередное новое действие (ориентировочно-исследовательская реакция)
    action_t SynthesisOfAction();

    void SetActionChanged( bool fl ) { m_actionChanged = fl; }
    bool IsActionChanged() const { return m_actionChanged; }
};

}

#endif
