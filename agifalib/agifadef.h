// Project AGIFA                                                              //
// Copyright © 2021 Victor Artyukhov. All Rights Reserved.                    //
//                                                                            //
// FILE:       agifadef.h                                                     //
// AUTHOR:     Victor Artyukhov                                               //
//                                                                            //
// For license and copyright information please follow this link:             //
// https://github.com/LiveBaster/agifa/blob/main/LICENSE                      //

#if !defined( __AGIFADEF_H )
#define __AGIFADEF_H

#include <stdlib.h>
#include <stdint.h>

namespace agifa_base
{

typedef int64_t index_t;
typedef index_t id_t;
typedef int64_t count_t;

typedef int64_t result_t; // тип данных для текущего результата
typedef result_t target_t; // тип данных для требуемого результата
typedef result_t deviation_t; // тип данных для отклонения от требуемого результата
typedef result_t action_t; // тип данных для действия

const index_t IndexEmpty = -1;
const index_t AddCount   = 50;

#define MAXSTR 1024

enum param_t
// типы параметров компонента
{
	WantParam = 0,		// параметр потребности
	SensorParam = 1,	// параметр датчика
	MotorParam  = 2		// параметр мотора
};

}

#endif
