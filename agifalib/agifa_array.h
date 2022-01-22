// Project AGIFA                                                              //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_array.h                                                  //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFA_ARRAY_H )
#define __AGIFA_ARRAY_H

#include "agifadef.h"
#include <cstring>

namespace agifa_base
{

const index_t AddMaxCount   = 5;

//--- Class AgifaArray ---------------------------------------------------------

template <class T>
class AgifaArray
{
protected:
    T* m_list;
    index_t m_count;
    index_t m_maxCount;
public:
    AgifaArray();
    AgifaArray( index_t maxCount );
    AgifaArray( const AgifaArray<T>& );
    ~AgifaArray();

    void Free();
    void FullFree();
    void FastFree();
    // отсоединение списка от головы
    void FreeHead();

    T& operator []( index_t i );
    T operator []( index_t i ) const;
    AgifaArray<T>& operator = ( const AgifaArray<T>& );
    template<T> friend bool operator == ( const AgifaArray<T>& aItem1, const AgifaArray<T>& aItem2 );
    template<T> friend bool operator != ( const AgifaArray<T>& aItem1, const AgifaArray<T>& aItem2 );

    bool IsNull() const;
    index_t GetCount() const;
    void SetMaxCount( index_t count );

    void AtInsert( index_t index, T aItem );
    // добавить в начало списка
    void InsertStart( T aItem );
    // добавить в конец списка
    void InsertEnd( T aItem );
    // добавить, используя сортировку
    index_t Insert( T aItem );

    // удалить элемент списка (без освобождения памяти)
    void AtRemove( index_t index );
    // удалить элемент списка (без освобождения памяти)
    bool Remove( T aItem );

    bool Search( T aItem, index_t& index ) const;
    index_t GetIndex( const T aItem ) const;
};

template <class T>
inline
AgifaArray<T>::AgifaArray() :
    m_list( 0 )
{
    m_count = m_maxCount = 0;
}

template <class T>
inline
AgifaArray<T>::AgifaArray( index_t maxCount ) :
    m_list( 0 )
{
    m_count = m_maxCount = 0;
    SetMaxCount( maxCount );
}

template <class T>
inline
AgifaArray<T>::AgifaArray( const AgifaArray<T>& aItem ) :
    m_list( 0 ),
    m_count( 0 ),
    m_maxCount( 0 )
{
    T* lst = aItem.m_list;
    if( lst ) {
        index_t cnt = aItem.m_count;
        for( index_t i=0; i<cnt; i++ )
            AtInsert( i, *lst++ );
    }
}

template <class T>
inline
AgifaArray<T>::~AgifaArray()
{
    Free();
}

template <class T>
inline
void AgifaArray<T>::Free()
{
    if( m_list ) {
        ::free( m_list );
        m_list = 0;
    }
    m_count = m_maxCount = 0;
}

template <class T>
inline
void AgifaArray<T>::FullFree()
{
    if( m_list ) {
        for( index_t i=m_count-1; i>=0; i-- )
            delete *(m_list+i);
        ::free( m_list );
        m_list = 0;
    }
    m_count = m_maxCount = 0;
}

template <class T>
inline
void AgifaArray<T>::FastFree()
{
    m_count = 0;
}

template <class T>
inline
void AgifaArray<T>::FreeHead()
{
    m_list = 0;
    m_count = m_maxCount = 0;
}

template <class T>
inline
T AgifaArray<T>::operator []( index_t i ) const
{
    if( i >= 0 && i < m_count )
        return *(m_list+i);
}

template <class T>
inline
T& AgifaArray<T>::operator []( index_t i )
{
    if( i >= 0 && i < m_count )
        return *(m_list+i);
}

template <class T>
AgifaArray<T>& AgifaArray<T>::operator = ( const AgifaArray<T>& aItem )
{
    Free();
    T* lst = aItem.m_list;
    if( lst ) {
        index_t cnt = aItem.m_count;
        for( index_t i=0; i<cnt; i++ )
            AtInsert( i, *lst++ );
    }
    return *this;
}

template <class T>
bool operator == ( const AgifaArray<T>& aItem1, const AgifaArray<T>& aItem2 )
{
    if( aItem1.m_count != aItem2.m_count )
        return false;
    for( index_t i=0; i<aItem1.m_count; i++ ) {
        if( aItem1[i] != aItem2[i] )
            return false;
    }
    return true;
}

template <class T>
bool operator != ( const AgifaArray<T>& aItem1, const AgifaArray<T>& aItem2 )
{
    if( aItem1.m_count != aItem2.m_count )
        return true;
    for( index_t i=0; i<aItem1.m_count; i++ ) {
        if( aItem1[i] != aItem2[i] )
            return true;
    }
    return false;
}

template <class T>
inline
bool AgifaArray<T>::IsNull() const
{
    return m_count ? false : true;
}

template <class T>
inline
index_t AgifaArray<T>::GetCount() const
{
    return m_count;
}

template <class T>
void AgifaArray<T>::SetMaxCount( index_t count )
{
    if( count <= m_maxCount )
        return;
    T* p;
    if( m_list == 0 )
        p = (T*)::malloc( size_t(count*sizeof( T )) );
    else
        p = (T*)::realloc( m_list, size_t(count*sizeof( T )) );
    if( p ) {
        m_list = p;
        memset( p+m_maxCount, 0, size_t(count-m_maxCount)*sizeof( T ) );
        m_maxCount = count;
    }
}

template <class T>
void AgifaArray<T>::AtInsert( index_t index, T aItem )
{
    if( m_count == m_maxCount )
        SetMaxCount( m_maxCount+m_count/2+AddMaxCount );
    T* poi = m_list+index;
    if( index < m_count )
        std::memmove( poi+1, poi, size_t(m_count-index)*sizeof( T ) );
    m_count ++;
    *poi = aItem;
}

template <class T>
inline
void AgifaArray<T>::InsertStart( T aItem )
{
    AtInsert( 0, aItem );
}

template <class T>
inline
void AgifaArray<T>::InsertEnd( T aItem )
{
    AtInsert( m_count, aItem );
}

template <class T>
inline
index_t AgifaArray<T>::Insert( T aItem )
{
    index_t i;
    if( Search( aItem, i ) == false )
        AtInsert( i, aItem );
    return i;
}

template <class T>
inline
void AgifaArray<T>::AtRemove( index_t ind )
{
    if( m_count > 0 && ind >= 0 && ind < m_count ) {
        m_count-- ;
        memmove( m_list+ind, m_list+ind+1, size_t((m_count-ind)*sizeof( T )) );
    }
}

template <class T>
bool AgifaArray<T>::Remove( T aItem )
{
    T* lst = m_list;
    for( index_t i=0; i<m_count; i++ )
        if( *(lst++) == aItem ) {
            AtRemove( i );
            return true;
        }
    return false;
}

template <class T>
bool AgifaArray<T>::Search( T aItem, index_t& index/*, index_t beginIndex*/ ) const
{
    index_t i;
    T item;
    T* lst = m_list;
    index_t l = 0;
    index_t h = m_count-1;
    while( l <= h ) {
        if( (item = *(lst+(i = (l+h)>>1))) < aItem )
            l = i+1;
        else {
            h = i-1;
            if( item == aItem ) {
                index = i;
                return true;
            }
        }
    }
    index = l;
    return false;
}

template <class T>
index_t AgifaArray<T>::GetIndex( const T aItem ) const
{
    T* lst = m_list;
    for( index_t i=0; i<m_count; i++ )
        if( *(lst+i) == aItem )
            return i;
    return index_t( -1 );
}

}

#endif
