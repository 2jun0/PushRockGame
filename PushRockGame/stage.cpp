﻿#include "stage.h"

const int STAGE_COUNT = 4;
const string STAGES[] = {
//"1 1 1 1 1 1 1 1 1 1 \n\
// 1 4 4 0 0 0 0 0 0 1 \n\
// 1 0 0 0 0 2 0 0 0 1 \n\
// 1 0 0 0 2 0 0 0 0 1 \n\
// 1 0 0 0 0 0 0 0 0 1 \n\
// 1 0 0 0 0 0 0 0 3 1 \n\
// 1 1 1 1 1 1 1 1 1 1",

"1 1 1 1 1 1 1 1 \n\
 1 1 1 4 1 1 1 1 \n\
 1 1 1 0 1 1 1 1 \n\
 1 1 1 2 0 2 4 1 \n\
 1 4 0 2 3 1 1 1 \n\
 1 1 1 1 2 1 1 1 \n\
 1 1 1 1 4 1 1 1 \n\
 1 1 1 1 1 1 1 1",

//"1 1 1 1 1 \n\
// 1 1 2 1 1 \n\
// 1 2 3 2 1 \n\
// 1 1 2 4 1 \n\
// 1 1 1 1 1",

"1 1 1 1 1 1 \n\
 1 1 0 0 1 1 \n\
 1 0 3 2 1 1 \n\
 1 1 2 0 0 1 \n\
 1 1 0 0 0 1 \n\
 1 4 0 0 0 1 \n\
 1 0 0 0 4 1 \n\
 1 1 1 1 1 1",

"1 1 1 1 1 1 1 1 \n\
 1 1 1 4 4 1 1 1 \n\
 1 1 1 0 4 1 1 1 \n\
 1 1 0 0 2 4 1 1 \n\
 1 1 0 2 0 0 1 1 \n\
 1 0 0 0 2 2 0 1 \n\
 1 0 0 3 0 0 0 1 \n\
 1 1 1 1 1 1 1 1",

"1 1 1 1 1 1 \n\
 1 1 0 0 1 1 \n\
 1 0 3 2 1 1 \n\
 1 1 2 0 0 1 \n\
 1 1 0 2 0 1 \n\
 1 4 2 0 0 1 \n\
 1 4 4 0 4 1 \n\
 1 1 1 1 1 1"
};
