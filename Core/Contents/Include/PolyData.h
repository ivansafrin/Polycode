

#include "PolyGlobals.h"
#include "PolyString.h"
#include "OSBasics.h"

namespace Polycode {

	class _PolyExport Data {
		public:
			Data();
			~Data();
		
		void loadFromFile(String fileName);
		String getAsString(int encoding);
		void setFromString(String str, int encoding);
		bool saveToFile(String fileName);
		char *getData() { return data; }
				
		protected:

			long dataSize;
			char *data;
		
	};

}