/*
 *  PolyPerlin.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/9/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Math

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"

#define SAMPLE_SIZE 1024

namespace Polycode {

class _PolyExport Perlin
{
public:

  Perlin(int octaves,Number freq,Number amp,int seed);


  Number Get(Number x,Number y)
  {
    Number vec[2];
    vec[0] = x;
    vec[1] = y;
    return perlin_noise_2D(vec);
  };

private:
  void init_perlin(int n,Number p);
  Number perlin_noise_2D(Number vec[2]);

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