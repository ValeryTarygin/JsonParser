#include <iostream>
#include "JsonParser/json_parser.h"

using namespace json_parser;

int main()
{ 	
	CJsonParser parser;
	auto flag = parser.parse("test_json.json");	
	std::wcout << (flag ? parser.out() : L"file not found\n");	
}

