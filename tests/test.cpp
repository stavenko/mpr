#include <gtest/gtest.h>

TEST(gtestWorks, firstTest){
  ASSERT_EQ(50,0) << "50 is not equal to 0.0";
}



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
