// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_node.h                                                   //
// AUTHORS:    Victor Artyukhov, Nikita Demerza                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_NODE_H )
#define __AGIFA_NODE_H

#include "agifadef.h"
#include "agifalib_global.h"
#include "agifa_array.h"
#include "agifa_array_pointers.h"
#include "agifa_motor.h"

namespace agifa_base
{

class AGIFALIB_EXPORT AgifaNode : public AgifaLinkPointer
// узел дерева результатов
{
protected:
    // идентификатор узла
    id_t m_nodeId;
    // достигнутый результат
    result_t m_result;
    // действие, выполняемое исполнительным устройством
    action_t m_action;
    // родительские узлы
    AgifaArray<id_t> m_parentNodes;
    // дочерние узлы
    AgifaArray<id_t> m_childNodes;
public:
    AgifaNode();
    AgifaNode( id_t nodeId );
    virtual ~AgifaNode();

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );

    id_t GetNodeId() const { return m_nodeId; }
    void SetNodeId( id_t nodeId ) { m_nodeId = nodeId; }

    // акцептор действия
    bool ActionAcceptor( target_t target, result_t result );
    // синтезирует очередное новое действие (ориентировочно-исследовательская реакция)
    action_t SynthesisOfAction( AgifaMotor& motor );
};

}

#endif
