#pragma once

#include "../Composite/composite_values.h"

/**
namespace json_parser
@brief namespace json parser
*/
namespace json_parser
{
	/**
	namespace symbols_constants
	@brief namespace for constants symbols
	*/
	namespace symbols_constants
	{
		constexpr wchar_t kOpeningBrace = L'{';
		constexpr wchar_t kClosingBrace = L'}';
		constexpr wchar_t kOpeningSquareBracket = L'[';
		constexpr wchar_t kClosingSquareBracket = L']';
	}

	/**
	@brief class for simple parsing json
	*/
	class CJsonParser
	{
		CompositePtr json_composite_;
		bool is_key_;
		bool is_array_values_;
		bool is_whole_word_;
		std::wstring value_;

	public:
		CJsonParser ();	

	public:
		/**
		@brief parsing json file
		@detailed this function does parsing json file and keeps result in composite pattern
		@param name json file
		@return success flag
		*/
		bool parse(const char* nameFile);
		/**
		@brief get result of parsing
		@return result string
		*/
		std::wstring out();	

	private:
		bool isStringHasSymbol(std::wstring _string, const wchar_t _symbol);
		bool isWordComplete(std::wstring _string);
		void addWordToComposite(CompositePtr& _root);
	};
}

