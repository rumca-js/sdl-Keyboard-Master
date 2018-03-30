/*
 * Utilities.cpp
 *
 *  Created on: 30 mar 2018
 *      Author: hunter
 */

#include <stdio.h>
#include <stdlib.h>

unsigned rand_min_max(unsigned min, unsigned max) {
	return min + (rand() % static_cast<int>(max - min + 1));
}
