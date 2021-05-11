// Project AGIFA                                                              //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_array_pointers.cpp                                       //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include "agifa_array_pointers.h"

namespace agifa_base
{

//--- Class AgifaLinkPointer ---------------------------------------------------

AgifaLinkPointer::~AgifaLinkPointer()
{
}

int AgifaLinkPointer::Compare( const AgifaLinkPointer* )
{
    return 0;
}

AgifaLinkPointer* AgifaLinkPointer::Duplicate() const
{
    return (new AgifaLinkPointer())->Copy( this );
}

AgifaLinkPointer* AgifaLinkPointer::Copy( const AgifaLinkPointer* )
{
    return this;
}

//--- Class AgifaArrayPointers -------------------------------------------------

AgifaArrayPointers::~AgifaArrayPointers()
{
    Free();
}

int AgifaArrayPointers::Compare( const AgifaLinkPointer* poi )
{
    AgifaArrayPointers* p = (AgifaArrayPointers*)poi;
    if( GetCount() != p->GetCount() )
        return -1;
    for( index_t i=0; i<GetCount(); i++ ) {
        if( (*this)[i].Compare( &(*p)[i] ) )
            return -1;
    }
    return 0;
}

AgifaLinkPointer* AgifaArrayPointers::Duplicate() const
{
    return (new AgifaArrayPointers())->Copy( this );
}

AgifaLinkPointer* AgifaArrayPointers::Copy( const AgifaLinkPointer* poi )
{
    Free();
    AgifaArrayPointers* p = (AgifaArrayPointers*)poi;
    m_flags = p->m_flags;
    AgifaLinkPointer** lst = p->m_pList;
    if( lst ) {
        index_t cnt = p->m_count;
        SetMaxCount( cnt );
        if( (m_flags & flpFreeHead) == 0 ) {
            for( index_t i=0; i<cnt; i++ )
                AtInsert( i, (*lst++)->Duplicate() );
        }
        else {
            for( index_t i=0; i<cnt; i++ )
                AtInsert( i, *lst++ );
        }
    }
    return this;
}

void AgifaArrayPointers::SetMaxCount( index_t count )
{
    if( count <= m_maxCount )
        return;
    AgifaLinkPointer** p = m_pList;
    if( p == 0 )
        p = (AgifaLinkPointer**)::malloc( size_t(count*sizeof( AgifaLinkPointer* )) );
    else
        p = (AgifaLinkPointer**)::realloc( p, size_t(count*sizeof( AgifaLinkPointer* )) );
    if( p ) {
        m_pList = p;
        m_maxCount = count;
    }
}

void AgifaArrayPointers::AtInsert( index_t index, AgifaLinkPointer* aItem )
{
    if( m_count == m_maxCount )
        SetMaxCount( m_maxCount+m_count/2+AddMaxCountArrayPointer );
    AgifaLinkPointer** poi = m_pList+index;
    if( index < m_count )
        memmove( poi+1, poi, size_t(m_count-index)*sizeof( AgifaLinkPointer* ) );
    m_count ++;
    *poi = aItem;
}

AgifaLinkPointer* AgifaArrayPointers::Remove( AgifaLinkPointer* p )
// удалить элемент списка (без освобождения памяти)
{
    index_t ind;
    if( Search( p, ind ) ) {
        if( &(*this)[ ind ] == p )
            return AtRemove( ind );
    }
    for( index_t i=ind+1; i<m_count; i++ ) {
        AgifaLinkPointer* pp = &(*this)[i];
        if( pp->Compare( p ) != 0 )
            break;
        if( pp == p )
            return AtRemove( i );
    }
    for( index_t i=ind-1; i>=0; i-- ) {
        AgifaLinkPointer* pp = &(*this)[i];
        if( pp->Compare( p ) != 0 )
            break;
        if( pp == p )
            return AtRemove( i );
    }
    return 0;
}

const AgifaLinkPointer* AgifaArrayPointers::Prev( const AgifaLinkPointer* p ) const
{
    AgifaLinkPointer** lst = m_pList;
    for( index_t i=0; i<m_count; i++ )
        if( *(lst+i) == p )
            return i>0 ? *(lst+i-1) : 0;
    return 0;
}

AgifaLinkPointer* AgifaArrayPointers::Prev( AgifaLinkPointer* p )
{
    AgifaLinkPointer** lst = m_pList;
    for( index_t i=0; i<m_count; i++ )
        if( *(lst+i) == p )
            return i>0 ? *(lst+i-1) : 0;
    return 0;
}

const AgifaLinkPointer* AgifaArrayPointers::Next( const AgifaLinkPointer* p ) const
{
    AgifaLinkPointer** lst = m_pList;
    for( index_t i=0; i<m_count; i++ )
        if( *(lst+i) == p )
            return i<m_count-1 ? *(lst+i+1) : 0;
    return 0;
}

AgifaLinkPointer* AgifaArrayPointers::Next( AgifaLinkPointer* p )
{
    AgifaLinkPointer** lst = m_pList;
    for( index_t i=0; i<m_count; i++ )
        if( *(lst+i) == p )
            return i<m_count-1 ? *(lst+i+1) : 0;
    return 0;
}

bool AgifaArrayPointers::Search( const AgifaLinkPointer* aItem, index_t& index, index_t beginIndex ) const
{
    index_t i;
    AgifaLinkPointer** lst = m_pList;
    index_t l = beginIndex;
    index_t h = m_count-1;
    while( l <= h ) {
        int c;
        if( (c = (*(lst+(i = ((l+h)>>1))))->Compare( aItem )) < 0 )
            l = i+1;
        else {
            h = i-1;
            if( c == 0 ) {
                index = i;
                return true;
            }
        }
    }
    index = l;
    return false;
}

index_t AgifaArrayPointers::GetIndex( const AgifaLinkPointer* aItem ) const
{
    AgifaLinkPointer** lst = m_pList;
    for( index_t i=0; i<m_count; i++ )
        if( *(lst+i) == aItem )
            return i;
    return index_t( -1 );
}

}
