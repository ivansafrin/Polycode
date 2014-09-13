/*
Copyright (C) 2014 by Joachim Meyer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once
#include "PolyGlobals.h"
#include "PolyString.h"
#include "PolyResource.h"

namespace Polycode {
	class ObjectEntry;
	
	class _PolyExport Prop : public PolyBase {
	public:
		Prop(const String& name, const int type = Prop::PROP_STRING);
		Prop(ObjectEntry *entry);
		~Prop();

		Prop *loadPropFromEntry(ObjectEntry* entry);


		int type;

		String name;
		int value;

		std::vector<Prop*> children;

		static const int PROP_VECTOR3 = 0;
		static const int PROP_VECTOR2 = 1;
		static const int PROP_SLIDER = 2;
		static const int PROP_BUTTON = 3;
		static const int PROP_NUMBER = 4;
		static const int PROP_TARGET_BINDING = 5;
		static const int PROP_RENDER_TARGET = 6;
		static const int PROP_SHADER_PASS = 7;
		static const int PROP_REMOVABLE_STRING = 8;
		static const int PROP_LAYER = 9;
		static const int PROP_CUSTOM = 10;
		static const int PROP_STRING = 11;
		static const int PROP_COLOR = 12;
		static const int PROP_COMBO = 13;
		static const int PROP_BOOL = 14;
		static const int PROP_SOUND = 15;
		static const int PROP_BEZIER_RGBA_CURVE = 16;
		static const int PROP_BEZIER_CURVE = 17;
		static const int PROP_MATERIAL = 18;
		static const int PROP_MATERIAL_PREVIEW = 19;
		static const int PROP_TEXTURE = 20;
		static const int PROP_SCENE_SPRITE = 21;
		static const int PROP_SCENE_ENTITY_INSTANCE = 22;
	};

	class _PolyExport Plugin : public Resource {
		public:
			Plugin(const String& name);
			Plugin(ObjectEntry *entry);
			~Plugin();
		
			Plugin* loadPluginFromEntry(ObjectEntry *entry);

			void addProp(Prop* prop);
			void setProp(Prop* prop);

			void removeProp(Prop* prop);
			void removeProp(const String& propName);

			std::vector<Prop*> getProps() const;
			unsigned int getNumProps() const;

			unsigned int pluginType;

			static const unsigned int PLUGIN_ENTITY = 0;

			String ext;
			//ObjectEntry *sheetEntry;

		protected:
			std::vector<Prop*> props;
	};
}