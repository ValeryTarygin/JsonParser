#include "../JsonParser/json_parser.h"
#include <gtest/gtest.h>

using namespace json_parser;

class JsonParserTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		json = std::make_unique<CJsonParser>();
	}
	std::unique_ptr<CJsonParser> json;
};

TEST_F(JsonParserTest, TestOneKey) {
	json->parse("test_json_one_key.json");
	std::wstring expected(L"firstName: Petrov;");
	std::wstring resultString(json->out());
	auto cmp = wcscmp(expected.c_str(), resultString.c_str());
	ASSERT_TRUE(cmp == 0);
}

TEST_F(JsonParserTest, TestManyKeys) {
	CJsonParser json;
	json.parse("test_json_many_keys.json");
	std::wstring expected(L"address: streetAddress: street: Moscow sh ., 101;\nstreetAddress: apartment: apart .101;\naddress: city: Moscow;\n");
	std::wstring resultString(json.out());
	auto cmp = wcscmp(expected.c_str(), resultString.c_str());
	ASSERT_TRUE(cmp == 0);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
