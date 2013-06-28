#include <gtest/gtest.h>
#include "../inverted_list.h"
using namespace std;

bool operator == (const index_unit& lh, const index_unit& rh) {
	return lh.doc == rh.doc && lh.freq == rh.freq
		&& lh.pos_info_offset == rh.pos_info_offset;
}

class inverted_list_test1 : public testing::Test {
protected:
	inverted_list inv1, inv2;
	virtual void SetUp() {
		inv1.clear(); inv2.clear();
		inv1.set_file_name("inverted.dat");
		inv2.set_file_name("inverted.dat");
	}
	virtual void TearDown() {
		::remove("inverted.dat");
	}
};

TEST_F(inverted_list_test1, empty_test) {
	ASSERT_TRUE(inv1.write_to_disk());
	ASSERT_TRUE(inv2.load_from_disk());
	EXPECT_EQ(inv1, inv2);
}

TEST_F(inverted_list_test1, small_test) {
	vector<posting_list> v; index_unit u[4] = { {1, 1, 0}, {2, 2, 11}, {1, 1, 20}, {2, 2, 30} };
	inv1.new_posting_list(); inv1[0].push_back(u[0]);
	inv1.new_posting_list(); inv1[1].push_back(u[2]); inv1[1].push_back(u[3]);
	inv1[0].push_back(u[1]);
	EXPECT_EQ(2u, inv1.size());
	EXPECT_EQ(2u, inv1[0].size());
	EXPECT_EQ(2u, inv1[1].size());

	ASSERT_TRUE(inv1.write_to_disk());
	ASSERT_TRUE(inv2.load_from_disk());
	EXPECT_EQ(inv1, inv2);
}

TEST(inverted_list_test2, empty_filename) {
	inverted_list inv;
	EXPECT_FALSE(inv.write_to_disk());
	EXPECT_FALSE(inv.load_from_disk());
}
