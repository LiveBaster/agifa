// Project AGIFA                                                              //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_array_pointers.h                                         //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_ARRAY_POINTERS_H )
#define __AGIFA_ARRAY_POINTERS_H

#include "agifadef.h"
#include <cstring>
#include "agifalib_global.h"

namespace agifa_base
{

const index_t AddMaxCountArrayPointer = 5;

//--- Class AgifaLinkPointer ---------------------------------------------------

class AGIFALIB_EXPORT AgifaLinkPointer
{
public:
    AgifaLinkPointer() {}
    virtual ~AgifaLinkPointer();

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );
};

//--- Class AgifaArrayPointers -------------------------------------------------

const unsigned char
    flpDuplicates   = 0x01, // позволяет иметь одинаковые элементы
    flpFreeHead     = 0x02; // освобождает только голову списка

class AGIFALIB_EXPORT AgifaArrayPointers : public AgifaLinkPointer
{
public:
    AgifaLinkPointer** m_pList;
    index_t m_count;    // размер списка
    index_t m_maxCount; // максимальный размер списка
    unsigned char m_flags;
public:
    AgifaArrayPointers();
    AgifaArrayPointers( unsigned char fl );
    virtual ~AgifaArrayPointers();

    void Free();
    void FastFree();
    void FreeHead(); // освободить список без удаления элементов

    virtual int Compare( const AgifaLinkPointer* poi );
    virtual AgifaLinkPointer* Duplicate() const;
    virtual AgifaLinkPointer* Copy( const AgifaLinkPointer* poi );

    const AgifaLinkPointer& operator []( index_t i ) const;
    AgifaLinkPointer& operator []( index_t i );

    void SetDuplicates( unsigned char fl = true );
    void SetFreeHead( unsigned char fl = true );
    bool IsNull() const;
    index_t GetCount() const;
    void SetMaxCount( index_t count );

    void AtInsert( index_t index, AgifaLinkPointer* p );
    index_t InsertStart( AgifaLinkPointer* p );     // добавить в начало списка
    index_t InsertEnd( AgifaLinkPointer* p );       // добавить в конец списка
    index_t Insert( AgifaLinkPointer* p );          // добавить, используя сортировку

    AgifaLinkPointer* AtRemove( index_t index );    // удалить элемент списка (без освобождения памяти)
    AgifaLinkPointer* Remove( AgifaLinkPointer* p );// удалить элемент списка (без освобождения памяти)

    const AgifaLinkPointer*	GetLast() const;
    AgifaLinkPointer* GetLast();
    const AgifaLinkPointer*	GetFirst() const;
    AgifaLinkPointer* GetFirst();
    const AgifaLinkPointer*	Prev( const AgifaLinkPointer* p ) const;
    AgifaLinkPointer* Prev( AgifaLinkPointer* p );
    const AgifaLinkPointer*	Next( const AgifaLinkPointer* p ) const;
    AgifaLinkPointer* Next( AgifaLinkPointer* p );
    bool Search( const AgifaLinkPointer* aItem, index_t& index, index_t beginIndex = 0 ) const;
    index_t GetIndex( const AgifaLinkPointer* aItem ) const;
protected:
    AgifaArrayPointers( const AgifaArrayPointers& ) {}
    AgifaArrayPointers& operator = ( const AgifaArrayPointers& ) { return *this; }
};

inline
AgifaArrayPointers::AgifaArrayPointers() :
    m_pList( 0 ),
    m_count( 0 ),
    m_maxCount( 0 ),
    m_flags( 0 )
{
}

inline
AgifaArrayPointers::AgifaArrayPointers( unsigned char fl ) :
    m_pList( 0 ),
    m_count( 0 ),
    m_maxCount( 0 ),
    m_flags( fl )
{
}

inline
void AgifaArrayPointers::Free()
{
    if( m_pList != 0 && (m_flags & flpFreeHead) == 0 )
        for( index_t i=m_count-1; i>=0; i-- )
            delete *(m_pList+i);
    FreeHead();
}

inline
void AgifaArrayPointers::FastFree()
{
    if( m_pList && (m_flags & flpFreeHead) == 0 )
        for( index_t i=m_count-1; i>=0; i-- )
            delete *(m_pList+i);
    m_count = 0;
}

inline
void AgifaArrayPointers::FreeHead()
{
    if( m_pList != 0 )
        ::free( m_pList );
    m_pList = 0;
    m_count = 0;
    m_maxCount = 0;
}

inline
const AgifaLinkPointer& AgifaArrayPointers::operator []( index_t i ) const
{
    if( i >= 0 && i < m_count )
        return **(m_pList+i);
    static AgifaLinkPointer empty;
    return empty;
}

inline
AgifaLinkPointer& AgifaArrayPointers::operator []( index_t i )
{
    if( i >= 0 && i < m_count )
        return **(m_pList+i);
    static AgifaLinkPointer empty;
    return empty;
}

inline
void AgifaArrayPointers::SetDuplicates( unsigned char fl )
{
    if( fl )
        m_flags |= flpDuplicates;
    else
        m_flags &= ~flpDuplicates;
}

inline
void AgifaArrayPointers::SetFreeHead( unsigned char fl )
{
    if( fl )
        m_flags |= flpFreeHead;
    else
        m_flags &= ~flpFreeHead;
}

inline
bool AgifaArrayPointers::IsNull() const
{
    return m_count ? false : true;
}

inline
index_t AgifaArrayPointers::GetCount() const
{
    return m_count;
}

inline
index_t AgifaArrayPointers::InsertStart( AgifaLinkPointer* p )
{
    AtInsert( 0, p );
    return 0;
}

inline
index_t AgifaArrayPointers::InsertEnd( AgifaLinkPointer* p )
{
    AtInsert( m_count, p );
    return m_count-1;
}

inline
index_t AgifaArrayPointers::Insert( AgifaLinkPointer* p )
// добавить, используя сортировку
{
    index_t i;
    if( Search( p, i ) == 0 || (m_flags & flpDuplicates) )
        AtInsert( i, p );
    else
    if( (m_flags & flpFreeHead) == 0 )
        delete p;
    return i;
}

inline
AgifaLinkPointer* AgifaArrayPointers::AtRemove( index_t index )
// удалить элемент списка (без освобождения памяти)
{
    if( index >= 0 && index < m_count ) {
        AgifaLinkPointer* p = *(m_pList+index);
        m_count --;
        if( m_count > 0 )
            memmove( m_pList+index, m_pList+index+1, size_t(m_count-index)*sizeof( AgifaLinkPointer* ) );
        return p;
    }
    return nullptr;
}

inline
const AgifaLinkPointer* AgifaArrayPointers::GetLast() const
{
    return m_count ? *(m_pList+m_count-1): 0;
}

inline
AgifaLinkPointer* AgifaArrayPointers::GetLast()
{
    return m_count ? *(m_pList+m_count-1): 0;
}

inline
const AgifaLinkPointer* AgifaArrayPointers::GetFirst() const
{
    return m_count ? *m_pList : 0;
}

inline
AgifaLinkPointer* AgifaArrayPointers::GetFirst()
{
    return m_count ? *m_pList : 0;
}

//--- Class AgifaArrayTemp -----------------------------------------------------

template <class T>
class AgifaArrayTemp : public AgifaArrayPointers
{
public:
    AgifaArrayTemp() : AgifaArrayPointers() {}
    AgifaArrayTemp( char fl ) : AgifaArrayPointers( fl ) {}

    const T& operator []( index_t i ) const { return (const T&)AgifaArrayPointers::operator []( i ); }
    T& operator []( index_t i ) { return (T&)AgifaArrayPointers::operator []( i ); }

    // удалить элемент списка (без освобождения памяти)
    T* AtRemove( index_t index ) { return (T*)AgifaArrayPointers::AtRemove( index ); }
    // удалить элемент списка (без освобождения памяти)
    T* Remove( T* p ) { return (T*)AgifaArrayPointers::Remove( (AgifaLinkPointer*)p ); }

    const T* GetLast() const { return GetCount() ? &(*this)[ GetCount()-1 ]: 0; }
    T* GetLast() { return (T*)(GetCount() ? &(*this)[ GetCount()-1 ]: 0); }
    const T* GetFirst() const { return (const T*)(GetCount() ? &(*this)[ 0 ] : 0); }
    T* GetFirst() { return (T*)(GetCount() ? &(*this)[ 0 ] : 0); }
    const T* Prev( const T* p ) const { return (const T*)AgifaArrayPointers::Prev( (const AgifaLinkPointer*)p ); }
    T* Prev( T* p ) { return (T*)AgifaArrayPointers::Prev( (AgifaLinkPointer*)p ); }
    const T* Next( const T* p ) const { return (const T*)AgifaArrayPointers::Next( (const AgifaLinkPointer*)p ); }
    T* Next( T* p ) { return (T*)AgifaArrayPointers::Next( (AgifaLinkPointer*)p ); }
    index_t GetIndex( const T* aItem ) const { return AgifaArrayPointers::GetIndex( (const AgifaLinkPointer*)aItem ); }

protected:
    AgifaArrayTemp( const AgifaArrayTemp& ) {}
    AgifaArrayTemp& operator = ( const AgifaArrayTemp& ) { return *this; }
};

}

#endif
