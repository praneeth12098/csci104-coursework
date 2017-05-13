#include "llistint.h"
#include "gtest/gtest.h"

class LListIntTest : public testing::Test {
protected:

	LListIntTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LListIntTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		list1.push_back(1);
		list1.push_back(2);
		list1.push_back(3);
		list1.push_back(4);
		list2.push_back(5);
		list2.push_back(6);
		list2.push_back(7);
		list2.push_back(8);
		list3.push_back(9);
		list3.push_back(10);
		list3.push_back(11);
		list3.push_back(12);
		list4.push_back(13);
		list4.push_back(14);
		list4.push_back(15);
		list4.push_back(16);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	LListInt list1;
	LListInt list2;
	LListInt list3;
	LListInt list4;
	LListInt elist;
};

TEST_F(LListIntTest, Push_BackNominal) 
{
	EXPECT_EQ(4, list1.size());
	EXPECT_EQ(4, list2.size());
	EXPECT_EQ(4, list3.size());
}

TEST_F(LListIntTest, AddOperatorNominal)
{
	list1 += list2;
	EXPECT_EQ(8, list1.size());
	EXPECT_EQ(0, list2.size());
	EXPECT_EQ(5, list1.get(4));
}

TEST_F(LListIntTest, AddOperatorBoundary)
{
	list1 += list3 += list4;
	EXPECT_EQ(12, list1.size());
	EXPECT_EQ(0, list3.size());
	EXPECT_EQ(0, list4.size());
	list1 += list1;
	EXPECT_EQ(12, list1.size());
}

TEST_F(LListIntTest, AddOperatorBoundaryOffNominal)
{
	elist += list1;
	EXPECT_EQ(4, elist.size());
}

TEST_F(LListIntTest, EqualsOperatorNominal)
{
	EXPECT_EQ(0, elist.size());
	EXPECT_EQ(4, list1.size());
	elist = list1;
	EXPECT_EQ(4, elist.size());
	EXPECT_EQ(2, elist.get(1));
}

TEST_F(LListIntTest, EqualsOperatorBoundary)
{
	list1 = elist;
	EXPECT_EQ(4, list1.size());

}

TEST_F(LListIntTest, CopyConstructorNominal)
{
	LListInt list5(list1);
	EXPECT_EQ(4, list5.size());
	EXPECT_EQ(1, list5.get(0));
}

TEST_F(LListIntTest, coutNominal)
{
	for(int i = 0; i < 20; i++)
	{
		list1.push_back(i);
	}
	cout<<list1;
}