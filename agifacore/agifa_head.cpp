// Project AGIFA/Core                                                         //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifa_head.cpp                                                 //
// AUTHORS:    Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include <iostream>
#include <cstdio>

#include "agifa_head.h"

namespace agifa_core
{

AgifaHead::AgifaHead(QObject *parent) :
    QObject(parent),
    m_isRun( false ),
    m_pEar( nullptr ),
    m_pVoice( nullptr )
{
    InitHead();

    connect( &m_earThread, &QThread::started, m_pEar, &AgifaBrain::doWork );
    connect( &m_earThread, &QThread::finished, m_pEar, &AgifaBrain::exitWork );
    connect( m_pEar, &AgifaBrain::resultReady, this, &AgifaHead::handleResults );
    m_pEar->moveToThread( &m_earThread );
    m_earThread.start();

}

AgifaHead::~AgifaHead()
{
    if( m_pEar )
    {
        m_pEar->exitWork();
        m_earThread.quit();
        m_earThread.wait();
        m_pEar = nullptr;
    }
    if( m_pVoice )
    {
        m_pVoice->exitWork();
        m_voiceThread.quit();
        m_voiceThread.wait();
        m_pVoice = nullptr;
    }
}

void AgifaHead::InitHead()
{
    m_pEar = new AgifaBrain();
    m_pVoice = new AgifaBrain();
    // загружаем конфигурацию тела из xml-файла
    // ...

    // применяем загруженную конфигурацию тела для компонента "Ухо"
    AgifaSensor* pSensor1 = new AgifaSensor();
    m_pEar->GetSystem().AddSensor( pSensor1 );
    AgifaMotor* pMotor1 = new AgifaMotor();
    pMotor1->SetActionMin( 0 );
    pMotor1->SetActionMax( 26 ); // 26 маленьких букв латинского алфавита
    m_pEar->GetSystem().AddMotor( pMotor1 );

    // применяем загруженную конфигурацию тела для компонента "Голосовой аппарат"
    AgifaSensor* pSensor2 = new AgifaSensor();
    m_pVoice->GetSystem().AddSensor( pSensor2 );
    AgifaMotor* pMotor2 = new AgifaMotor();
    pMotor2->SetActionMin( 0 );
    pMotor2->SetActionMax( 26 ); // 26 маленьких букв латинского алфавита
    m_pVoice->GetSystem().AddMotor( pMotor2 );
}

void AgifaHead::Wait()
{
    int delay = 1;
    struct timespec ts = { delay/10, 1 };
    timespec remaining;
    nanosleep( &ts, &remaining );
}

void AgifaHead::run()
{
    m_isRun = true;

    std::cout << "AgifaHead::run1()\n";

    while( true )
    {
        // освобождаем дерево результатов для следующего цикла
//        m_sys1.FreeTrees();
//        m_sys2.FreeTrees();
        // добавляем начальный узел дерева результатов
//        m_sys1.AddNode( new AgifaNode( 0 ) );
//        m_sys2.AddNode( new AgifaNode( 0 ) );

        std::string input;
        std::cout << std::endl << "> ";
        std::getline( std::cin, input );

        if( input == "exit" )
            break;

        std::string output;

        for( size_t index = 0; index < input.size(); index++ )
        {
            if( m_pEar )
                m_pEar->SetNodeIndex( index );
            if( m_pVoice )
                m_pVoice->SetNodeIndex( index );
            if( m_pEar )
            {
                m_pEar->SetSensor( 0, input[index] );
                m_pEar->SetTarget( 0, input[index] );
            }
            bool acceptorResult = false;
            do
            {
                // ждём действие от Уха
                action_t earAction = 0;
                for( int i=0; i<100; i++ )
                {
                    if( m_pEar->GetMotor( 0, earAction ) )
                        break;
                    Wait();
                }
                // передаём действие от Уха на датчик Голосового аппарата
                if( m_pVoice )
                    m_pVoice->SetSensor( 0, earAction );
                // ждём действие от Голосового аппарата
                action_t voiceAction = 0;
                for( int i=0; i<100; i++ )
                {
                    if( m_pVoice && m_pVoice->GetMotor( 0, voiceAction ) )
                        break;
                    Wait();
                }
                // "озвучиваем" действие от Голосового аппарата и передаём Голос на датчик Уха
                result_t result = char(voiceAction)+'a';
                if( m_pEar )
                    m_pEar->SetSensor( 0, result );
            } while( !acceptorResult );
/*
            result_t result = 0;
            AgifaNode* pNode1 = m_sys1.SearchNode( index );
            AgifaNode* pNode2 = m_sys2.SearchNode( index );
            if( pNode1 && pNode2 )
            {
                target_t target1 = pSensor1->GetResult();
                bool acceptorResult1 = false;
                bool acceptorResult2_2 = false;
                do
                {
                    action_t action1 = pNode1->SynthesisOfAction( *pMotor1 );
                    pSensor2->SetResult( action1 );
                    target_t target2 = pSensor2->GetResult();
                    bool acceptorResult2_1 = false;
                    do
                    {
                        action_t action2 = pNode2->SynthesisOfAction( *pMotor2 );
                        // преобразуем действие в букву и "озвучиваем" её
                        result = char(action2)+'a';
                        pSensor1->SetResult( result );
                        // акцептер действия для компонента "Ухо"
                        acceptorResult1 = pNode1->ActionAcceptor( target1, pSensor1->GetResult() );
                        pSensor2->SetResult( action2 );
                        // акцептер действия для компонента "Голосовой аппарат"
                        acceptorResult2_1 = pNode2->ActionAcceptor( target2, pSensor2->GetResult() );
                        // синхронизирующий акцептер действия для компонентов "Голосовой аппарат" и "Ухо"
                        acceptorResult2_2 = pNode2->ActionAcceptor( target2, pSensor2->GetResult(), acceptorResult1 );
                    } while( !acceptorResult2_1 );
                } while( !acceptorResult1 && !acceptorResult2_2 );
                if( acceptorResult1 )
                {
                    m_sys1.AddNode( new AgifaNode( index+1 ) );
                    m_sys2.AddNode( new AgifaNode( index+1 ) );
                    output += (char)pSensor1->GetResult();
                }
            }
*/
        }
        std::cout << std::endl << output << std::endl;
    }

/*
    while( m_isRun )
    {
        if( getchar() == 'q' )
            // завершение программы
            break;
        int delay = 1;
        struct timespec ts = { delay/10, 1 };
        timespec remaining;
        nanosleep( &ts, &remaining );
    }
*/
    std::cout << "AgifaHead::run2()\n";

    emit finished();
}

void AgifaHead::handleResults( const QString& result )
{

    std::cout << "AgifaHead::handleResults()" << result.toStdString() << "\n";

}

}
