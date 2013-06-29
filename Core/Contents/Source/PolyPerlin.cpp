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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "PolyPerlin.h"

using namespace Polycode;

#define B SAMPLE_SIZE
#define BM (SAMPLE_SIZE-1)

#define N 0x1000
#define NP 12   /* 2^N */
#define NM 0xfff

#define s_curve(t) ( t * t * (3.0f - 2.0f * t) )
#define lerp(t, a, b) ( a + t * (b - a) )

#define setup(i,b0,b1,r0,r1)\
	t = vec[i] + N;\
	b0 = ((int)t) & BM;\
	b1 = (b0+1) & BM;\
	r0 = t - (int)t;\
	r1 = r0 - 1.0f;

Number Perlin::noise1(Number arg)
{
	int bx0, bx1;
	Number rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;

	if (mStart) {
		srand(mSeed);
		mStart = false;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);

	sx = s_curve(rx0);

	u = rx0 * g1[ p[ bx0 ] ];
	v = rx1 * g1[ p[ bx1 ] ];

	return lerp(sx, u, v);
}

Number Perlin::noise2(Number vec[2])
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	Number rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	int i, j;

	if (mStart) {
		srand(mSeed);
		mStart = false;
		init();
	}

	setup(0,bx0,bx1,rx0,rx1);
	setup(1,by0,by1,ry0,ry1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

	q = g2[b00];
	u = at2(rx0,ry0);
	q = g2[b10];
	v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[b01];
	u = at2(rx0,ry1);
	q = g2[b11];
	v = at2(rx1,ry1);
	b = lerp(sx, u, v);

#undef at2

	return lerp(sy, a, b);
}

Number Perlin::noise3(Number vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	Number rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	int i, j;

	if (mStart) {
		srand(mSeed);
		mStart = false;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

#undef at3

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
}

void Perlin::normalize2(Number v[2])
{
	Number s;

	s = (Number)sqrt(v[0] * v[0] + v[1] * v[1]);
	s = 1.0f/s;
	v[0] = v[0] * s;
	v[1] = v[1] * s;
}

void Perlin::normalize3(Number v[3])
{
	Number s;

	s = (Number)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	s = 1.0f/s;

	v[0] = v[0] * s;
	v[1] = v[1] * s;
	v[2] = v[2] * s;
}

void Perlin::init(void)
{
	int i, j, k;

	for (i = 0 ; i < B ; i++) {
		p[i] = i;
		g1[i] = (Number)((rand() % (B + B)) - B) / B;
		for (j = 0 ; j < 2 ; j++)
			g2[i][j] = (Number)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);
		for (j = 0 ; j < 3 ; j++)
			g3[i][j] = (Number)((rand() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}

	while (--i) {
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}

	for (i = 0 ; i < B + 2 ; i++) {
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0 ; j < 2 ; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0 ; j < 3 ; j++)
			g3[B + i][j] = g3[i][j];
	}

}


Number Perlin::perlin_noise_2D(Number vec[2])
{
	int terms    = mOctaves;
	Number result = 0.0f;
	Number amp = mAmplitude;

	vec[0]*=mFrequency;
	vec[1]*=mFrequency;

	for( int i=0; i<terms; i++ ) {
		result += noise2(vec)*amp;
		vec[0] *= 2.0f;
		vec[1] *= 2.0f;
		amp*=0.5f;
	}


	return result;
}

Number Perlin::perlin_noise_3D(Number vec[3])
{
	int terms    = mOctaves;
	Number result = 0.0f;
	Number amp = mAmplitude;

	vec[0]*=mFrequency;
	vec[1]*=mFrequency;
	vec[2]*=mFrequency;

	for( int i=0; i<terms; i++ ) {
		result += noise3(vec)*amp;
		vec[0] *= 2.0f;
		vec[1] *= 2.0f;
		vec[2] *= 2.0f;
		amp*=0.5f;
	}


	return result;
}



Perlin::Perlin(int octaves,Number freq,Number amp,int seed)
{
	mOctaves = octaves;
	mFrequency = freq;
	mAmplitude = amp;
	mSeed = seed;
	mStart = true;
}
