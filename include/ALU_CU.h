#pragma once
#ifndef _ALU_CU_
#define _ALU_CU_

#include "../include/mySimpleComputer.h"
#include "../include/MyReadKey.h"


int CU();
int ALU(int command, int operand);
void CheckFlags(void);

static enum keys key;
#endif 
