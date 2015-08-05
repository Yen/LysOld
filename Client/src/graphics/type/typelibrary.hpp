#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace lys
{

	class TypeLibrary
	{
	private:
		friend class TypeFace;
	private:
		FT_Library _library;
	public:
		static TypeLibrary &instance();
	public:
		TypeLibrary();
		~TypeLibrary();
	};

}