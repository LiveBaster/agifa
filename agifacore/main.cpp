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

using namespace afiga_base;

int parrot_system(const char * filename) {
	AgifaSystem sys;
	
	sys.m_sensors.InsertEnd(new AgifaSensor); // Чтение информации о датчиках
	sys.m_motors.InsertEnd(new AgifaMotor); // Чтение информации о моторах
	
    while (true)
	{
		std::string input;
		std::getline(std::cin, input);
		
		if (input == "exit") return 0;
		
		std::string output;
		
		for (index_t index = 0; index < input.size(); index++)
		{
			if (index >= sys.m_trees.GetCount()) sys.m_trees.InsertEnd(new AgifaNode);
			
			target_t target = (target) input[index];
			result_t result = 0;
			
			while (!sys.m_trees[index].ActionAcceptor(target, result))
			{
				action_t action = sys.m_trees[index].SynthesisOfAction();
				result+=action;
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
