

#include "PolyGlobals.h"
#include "PolyString.h"
#include "tinyxml.h"

namespace Polycode {

	class _PolyExport ObjectEntry {
	public:
		
		ObjectEntry() { type = ObjectEntry::CONTAINER_ENTRY; }
		
		int type;
		String name;
		
		Number NumberVal;
		int intVal;
		String stringVal;
		bool boolVal;		
		int length;
		
		ObjectEntry *addChild(String name) {
			ObjectEntry *entry = new ObjectEntry();
			entry->type = ObjectEntry::CONTAINER_ENTRY;			
			entry->name = name;
			children.push_back(entry);
			length = children.size();
			return entry;
		}
		
		
		ObjectEntry *addChild(String name, Number val) {
			ObjectEntry *entry = new ObjectEntry();
			entry->type = ObjectEntry::FLOAT_ENTRY;			
			entry->NumberVal = val;
			entry->name = name;
			children.push_back(entry);
			length = children.size();			
			return entry;			
		}

		ObjectEntry *addChild(String name, int val) {
			ObjectEntry *entry = new ObjectEntry();
			entry->type = ObjectEntry::INT_ENTRY;
			entry->intVal = val;
			entry->name = name;
			children.push_back(entry);	
			length = children.size();			
			return entry;			
		}

		ObjectEntry *addChild(String name, String val) {
			ObjectEntry *entry = new ObjectEntry();
			entry->type = ObjectEntry::STRING_ENTRY;
			entry->stringVal = val;
			entry->name = name;
			children.push_back(entry);
			length = children.size();			
			return entry;			
		}		
		
		ObjectEntry *addChild(String name, bool val) {
			ObjectEntry *entry = new ObjectEntry();
			entry->type = ObjectEntry::BOOL_ENTRY;			
			entry->boolVal = val;
			entry->name = name;
			children.push_back(entry);
			length = children.size();			
			return entry;			
		}
		
		
		static const int FLOAT_ENTRY = 0;		
		static const int INT_ENTRY = 1;
		static const int BOOL_ENTRY = 2;
		static const int ARRAY_ENTRY = 3;
		static const int STRING_ENTRY = 4;	
		static const int CONTAINER_ENTRY = 5;	
		
		inline ObjectEntry *operator [] ( int index) { return children[index];}
		inline ObjectEntry *operator [] ( String key) { for(int i=0; i < children.size(); i++) { if(children[i]->name == key) { return children[i]; } } return NULL; }		
		
		vector<ObjectEntry*> children;		
	};
	
	class _PolyExport Object {
	public:
		Object();
		~Object();
		
		bool loadFromXML(String fileName);
		void saveToXML(String fileName);
		void createFromXMLElement(TiXmlElement *element, ObjectEntry *entry);
		TiXmlElement *createElementFromObjectEntry(ObjectEntry *entry);
		
		ObjectEntry root;
		
	};
	
}