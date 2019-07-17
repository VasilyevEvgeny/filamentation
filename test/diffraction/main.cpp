//
// Created by vasilyev on 17.07.2019.
//

#include "gtest/gtest.h"
#include "test_diffraction.h"

int main() {

    TestDiffraction test_diffraction = TestDiffraction();

    int a = test_diffraction.get_a();

    EXPECT_EQ(a, 6) << "Different numbers!";

    return 0;
}
