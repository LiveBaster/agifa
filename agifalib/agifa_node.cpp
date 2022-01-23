// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_node.cpp                                                 //
// AUTHORS:    Victor Artyukhov, Nikita Demerza                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include "agifa_node.h"

namespace agifa_base
{

AgifaNode::AgifaNode() :
    m_nodeId( EmptyId ),
    m_result( 0 ),
    m_action( 0 )
{
}

AgifaNode::~AgifaNode()
{
}

int AgifaNode::Compare( const AgifaLinkPointer* poi )
{
    AgifaNode* p = (AgifaNode*)poi;
    if( m_nodeId == p->m_nodeId )
        return 0 ;
    if( m_nodeId < p->m_nodeId )
        return -1;
    return 1;
}

AgifaLinkPointer* AgifaNode::Duplicate() const
{
    return (new AgifaNode())->Copy( this );
}

AgifaLinkPointer* AgifaNode::Copy( const AgifaLinkPointer* poi )
{
    AgifaNode* p = (AgifaNode*)poi;
    m_nodeId = p->m_nodeId;
    m_result = p->m_result;
    m_action = p->m_action;
    m_parentNodes = p->m_parentNodes;
    m_childNodes = p->m_childNodes;
    return this;
}

bool AgifaNode::ActionAcceptor( target_t target, result_t result )
{
    if( target == result ) {
        return true;
    }
    return false;
}

action_t AgifaNode::SynthesisOfAction(target_t target, result_t result )
{
    if(target<result){
         return result-1
    }
    return result+1
}

}
