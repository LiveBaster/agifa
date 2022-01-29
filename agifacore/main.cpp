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
    AgifaSystem sys;

    // загружаем конфигурацию тела из xml-файла
    // ...

    // применяем загруженную конфигурацию тела
    AgifaSensor* pSensor = new AgifaSensor();
    sys.AddSensor( pSensor );
    AgifaMotor* pMotor = new AgifaMotor();
    pMotor->SetActionMin( 0 );
    pMotor->SetActionMax( 26 ); // 26 маленьких букв латинского алфавита
    sys.AddMotor( pMotor );

    while( true )
    {
        // освобождаем дерево результатов для следующего цикла
        sys.FreeTrees();
        // добавляем начальный узел дерева результатов
        sys.AddNode( new AgifaNode( 0 ) );

        std::string input;
        std::getline( std::cin, input );

        if( input == "exit" )
            return 0;

        std::string output;

        for( index_t index = 0; index < input.size(); index++ )
        {
            target_t target = input[index];
            result_t result = 0;

            AgifaNode* pNode = sys.SearchNode( index );
            if( pNode )
            {
                bool acceptorResult = false;
                do
                {
                    action_t action = pNode->SynthesisOfAction( *pMotor );
                    // преобразуем действие в букву и "озвучиваем" её
                    result = char(action)+'a';
                    acceptorResult = pNode->ActionAcceptor( target, result );
                } while( !acceptorResult );
                if( acceptorResult )
                {
                    sys.AddNode( new AgifaNode( index+1 ) );
                    output += (char)result;
                }
            }
        }
        std::cout << std::endl << output << std::endl;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    for (int arg = 1; arg < argc; arg++)
    {
        if (!strcmp(argv[arg], "-parrot"))
        {
            if (arg + 1 >= argc) return 1;

            return parrot_system(argv[arg + 1]);
        }
    }

    return 0;
}
