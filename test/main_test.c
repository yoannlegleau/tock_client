//
// Created by adzer on 24/01/2022.

//

/*
set(SDL2_image_INCLUDE_DIR C:/lib/CUnitLocal/CUnitLocal/include)
set(SDL2_image_LIB_DIR C:/Users/adzer/Downloads/CUnitLocal/CUnitLocal/lib/mingw)
include_directories(${SDL2_image_INCLUDE_DIR})
link_directories(${SDL2_image_LIB_DIR})

target_link_libraries(${PROJECT_NAME} cunit cunit)
 */

#include "CUnit/CUnit.h"

int max (int i1, int i2);

void test_max(void)
{
    CU_ASSERT (maxi(0,2)== 2);
    CU_ASSERT (maxi(0,-2)== 0);
    CU_ASSERT (maxi(2,2) == 2);
}
