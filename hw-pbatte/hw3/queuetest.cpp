#include "queueint.h"
#include "gtest/gtest.h"

class QueueIntTest : public testing::Test {
protected:

	QueueIntTest() {
		// You can do set-up work for each test here.
	}

	virtual ~QueueIntTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {

		q1.push(1);
		q1.push(2);
		q1.push(3);
		q1.push(4);
		q2.push(5);
		q2.push(6);
		q2.push(7);
		q2.push(8);
		q3.push(9);
		q3.push(10);
		q3.push(11);
		q3.push(12);
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	//Objects declared here can be used by all tests in the test case.

	QueueInt q1;
	QueueInt q2;
	QueueInt q3;
};

TEST_F(QueueIntTest, PushNominal) 
{
	EXPECT_EQ(4, q1.size());
	EXPECT_EQ(4, q2.size());
	EXPECT_EQ(4, q3.size());
}

TEST_F(QueueIntTest, PopNominal)
{
	for(int i = 0; i < 4; i++)
	{
		EXPECT_EQ(i+1, q1.front());
		q1.pop();

	}
	EXPECT_EQ(0, q1.size());
	EXPECT_EQ(true, q1.empty());
}

TEST_F(QueueIntTest, FrontNominal)
{
	EXPECT_EQ(5, q2.front());
}

TEST_F(QueueIntTest, ConcatenateNominal)
{
	q1.concatenate(q2);
	EXPECT_EQ(8, q1.size());
	EXPECT_EQ(0, q2.size());
	q1.pop();
	q1.pop();
	q1.pop();
	q1.pop();
	EXPECT_EQ(5, q1.front());
}