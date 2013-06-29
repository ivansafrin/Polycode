/*
Copyright (C) 2011 by Ivan Safrin

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
#include "PolyString.h"
#include "PolyGlobals.h"

#define SAMPLE_SIZE 1024

namespace Polycode {

/**
* 2D Perlin noise.
*/ 
class _PolyExport Perlin : public PolyBase 
{
	public:

		/**
		* Constructs perlin noise.
		* @param octaves Number of noise octaves.
		* @param freq Noise frequency.
		* @param amp Noise amplitude.
		* @param seed Noise seed.
		*/
		Perlin(int octaves,Number freq,Number amp,int seed);


		Number Get2DTiledX(Number x, Number y, Number t) {
			return ( (t - x) * Get2D(x, y) + (x) * Get2D(x - t, y) ) / (t);
		}

		/**
		* Returns noise value at the specified coordinate.
		* @param x Horizontal coordinate.
		* @param y Vertical coordinate.	
		*/ 

		Number Get(Number x,Number y) {
			return Get2D(x,y);
		};

		Number Get2D(Number x,Number y) {
			Number vec[2];
			vec[0] = x;
			vec[1] = y;
			return perlin_noise_2D(vec);
		};

		Number Get3D(Number x,Number y, Number z) {
			Number vec[3];
			vec[0] = x;
			vec[1] = y;
			vec[2] = z;
			return perlin_noise_3D(vec);
		};


	protected:
		void init_perlin(int n,Number p);
		Number perlin_noise_2D(Number vec[2]);
		Number perlin_noise_3D(Number vec[2]);
		
		Number noise1(Number arg);
		Number noise2(Number vec[2]);
		Number noise3(Number vec[3]);
		void normalize2(Number v[2]);
		void normalize3(Number v[3]);
		void init(void);

		int   mOctaves;
		Number mFrequency;
		Number mAmplitude;
		int   mSeed;

		int p[SAMPLE_SIZE + SAMPLE_SIZE + 2];
		Number g3[SAMPLE_SIZE + SAMPLE_SIZE + 2][3];
		Number g2[SAMPLE_SIZE + SAMPLE_SIZE + 2][2];
		Number g1[SAMPLE_SIZE + SAMPLE_SIZE + 2];
		bool  mStart;

};

}
