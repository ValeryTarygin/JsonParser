#include "json_parser.h"
#include <fstream>
#include <string>
#include <iterator>
#include "../Composite/composite_leaf.h"

namespace json_parser
{
	CJsonParser::CJsonParser()
		: is_key_(true)
		, is_array_values_(false)
		, is_whole_word_(true)
	{
	}

	bool CJsonParser::parse(const char* nameFile)
	{
		using iterator_string = std::istream_iterator<std::wstring, wchar_t>;

		std::wifstream file(nameFile);		

		if(!file.is_open())
			return false;
			
		iterator_string itFirst{ file };
		iterator_string end;

		json_composite_ = std::make_shared<CCompositeValues>();
		auto tempComposite = json_composite_;

		for (auto it = itFirst; it != end; ++it)
		{
			if(isStringHasSymbol(*it, symbols_constants::kOpeningBrace))
				is_key_ = true;
			else if(isStringHasSymbol(*it, symbols_constants::kClosingBrace))
			{
				tempComposite = tempComposite->getParent();
				is_key_ = true;
			}
			else if(isStringHasSymbol(*it, symbols_constants::kOpeningSquareBracket))
				is_array_values_ = true;
			else if(isStringHasSymbol(*it, symbols_constants::kClosingSquareBracket))
				is_array_values_ = false;
			else if (isWordComplete ( *it ))
				addWordToComposite(tempComposite);
		}
		
		return true;
	}

	bool CJsonParser::isStringHasSymbol ( std::wstring _string, const wchar_t _symbol )
	{
		return _string.find_first_of ( _symbol ) != std::wstring::npos;
	}

	bool CJsonParser::isWordComplete ( std::wstring _string )
	{
		auto appendToString = [] ( std::wstring& srcString, std::wstring tailString ) {
			srcString.append ( L" " );
			srcString.append ( tailString );
		};

		const auto posBegin = _string.find_first_of ( L"\"" );
		const auto posEnd = _string.find_last_of ( L"\"" );

		if (posBegin != std::wstring::npos && posBegin != posEnd)
			value_ = _string.substr ( posBegin + 1, posEnd - posBegin - 1 );
		else if (posBegin != std::wstring::npos)
		{
			if (is_whole_word_)
				value_ = _string.substr ( posBegin + 1, _string.length () - 1 );
			else
				appendToString ( value_, _string.substr ( 0, posEnd ) );

			is_whole_word_ = !is_whole_word_;
		}
		else
			appendToString ( value_, _string );

		return	is_whole_word_;
	}

	void CJsonParser::addWordToComposite(CompositePtr& _root)
	{
		if(is_key_)
		{
			_root = _root->addItem(std::make_shared<CCompositeValues>(value_));
			is_key_ = false;
		}
		else
		{
			_root = _root->addItem(std::make_shared<CCompositeLeaf>(value_));
			if(!is_array_values_)
			{
				_root = _root->getParent();
				is_key_ = true;
			}
		}
	}

	std::wstring CJsonParser::out()
	{
		 return json_composite_->out ();
	}
}
