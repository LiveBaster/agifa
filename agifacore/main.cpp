// Project AGIFA                                                              //
// Copyright © 2022 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       main.cpp                                                       //
// AUTHORS:    Victor Artyukhov, Timur Tukhvatullin                           //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#include <QCoreApplication>

#include <iostream>
#include <string>
#include <string.h>
#include "agifadef.h"
#include "agifalib_global.h"
#include "agifa_array.h"
#include "agifa_array_pointers.h"
#include "agifa_sensor.h"
#include "agifa_motor.h"
#include "agifa_node.h"
#include "agifa_system.h"

using namespace agifa_base;

int parrot_system( const char* filename )
{
    AgifaSystem sys1; // компонент "Ухо"
    AgifaSystem sys2; // компонент "Голосовой аппарат"

    // загружаем конфигурацию тела из xml-файла
    // ...

    // применяем загруженную конфигурацию тела для компонента "Ухо"
    AgifaSensor* pSensor1 = new AgifaSensor();
    sys1.AddSensor( pSensor1 );
    AgifaMotor* pMotor1 = new AgifaMotor();
    pMotor1->SetActionMin( 0 );
    pMotor1->SetActionMax( 26 ); // 26 маленьких букв латинского алфавита
    sys1.AddMotor( pMotor1 );

    // применяем загруженную конфигурацию тела для компонента "Голосовой аппарат"
    AgifaSensor* pSensor2 = new AgifaSensor();
    sys1.AddSensor( pSensor2 );
    AgifaMotor* pMotor2 = new AgifaMotor();
    pMotor2->SetActionMin( 0 );
    pMotor2->SetActionMax( 26 ); // 26 маленьких букв латинского алфавита
    sys1.AddMotor( pMotor2 );

    while( true )
    {
        // освобождаем дерево результатов для следующего цикла
        sys1.FreeTrees();
        sys2.FreeTrees();
        // добавляем начальный узел дерева результатов
        sys1.AddNode( new AgifaNode( 0 ) );
        sys2.AddNode( new AgifaNode( 0 ) );

        std::string input;
        std::cout << std::endl << "> ";
        std::getline( std::cin, input );

        if( input == "exit" )
            return 0;

        std::string output;

        for( size_t index = 0; index < input.size(); index++ )
        {
            pSensor1->SetResult( input[index] );
            result_t result = 0;

            AgifaNode* pNode1 = sys1.SearchNode( index );
            AgifaNode* pNode2 = sys2.SearchNode( index );
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
                    sys1.AddNode( new AgifaNode( index+1 ) );
                    sys2.AddNode( new AgifaNode( index+1 ) );
                    output += (char)pSensor1->GetResult();
                }
            }
        }
        std::cout << std::endl << output << std::endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    /*
    for (int arg = 1; arg < argc; arg++)
    {
        if (!strcmp(argv[arg], "-parrot"))
        {
            if (arg + 1 >= argc) return 1;

            return parrot_system(argv[arg + 1]);
        }
    }
    */
    // для отладки без файла конфигурации!!!
    parrot_system( "" );

    return 0;
}
