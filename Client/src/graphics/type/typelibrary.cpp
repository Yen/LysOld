#include "typelibrary.hpp"

#include <exception>

namespace lys
{

	TypeLibrary &TypeLibrary::instance()
	{
		static TypeLibrary instance;
		return instance;
	}

	TypeLibrary::TypeLibrary()
	{
		if (FT_Init_FreeType(&_library) != 0)
		{
			throw std::exception("Error initializing TypeLibrary");
		}
	}

	TypeLibrary::~TypeLibrary()
	{
		FT_Done_FreeType(_library);
	}

}