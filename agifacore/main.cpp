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

    sys.AddSensor( new AgifaSensor() );
    sys.AddMotor( new AgifaMotor() );

    while (true)
    {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") return 0;

        std::string output;

        for (index_t index = 0; index < input.size(); index++)
        {
            if( index >= sys.GetTreesCount() )
                sys.AddNode( new AgifaNode() );

            target_t target = input[index];
            result_t result = 0;

            AgifaNode* pNode = sys.SearchNode( index );
            if( pNode )
            {
                while (!pNode->ActionAcceptor(target, result))
                {
                    action_t action = pNode->SynthesisOfAction();
                    result+=action;
                }
            }

            output+=(char) result;
        }

        std::cout << output << std::endl;
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
