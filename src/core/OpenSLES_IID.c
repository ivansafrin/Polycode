/*
 * Copyright (c) 2007-2009 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and /or associated documentation files (the "Materials "), to
 * deal in the Materials without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Materials, and to permit persons to whom the Materials are
 * furnished to do so, subject to 
 * the following conditions: 
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Materials. 
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS IN THE
 * MATERIALS.
 *
 * OpenSLES_IID.c - OpenSL ES version 1.0
 *
 */

/****************************************************************************/
/* NOTE: This file is a standard OpenSL ES file and should not be           */
/* modified in any way.                                                     */
/****************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif




#include "OpenSLES.h" /* SL Header */

/*****************************************************************************/
/* Interface IDs                                                             */
/*****************************************************************************/

static const struct SLInterfaceID_ SL_IID_NULL_ = { 0xec7178ec, 0xe5e1, 0x4432, 0xa3f4, { 0x46, 0x57, 0xe6, 0x79, 0x52, 0x10 } };
const SLInterfaceID SL_IID_NULL = &SL_IID_NULL_;

static const struct SLInterfaceID_ SL_IID_AUDIOIODEVICECAPABILITIES_ = { 0xb2564dc0, 0xddd3, 0x11db, 0xbd62, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_AUDIOIODEVICECAPABILITIES = &SL_IID_AUDIOIODEVICECAPABILITIES_;

static const struct SLInterfaceID_ SL_IID_LED_ = { 0x2cc1cd80, 0xddd6, 0x11db, 0x807e, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_LED = &SL_IID_LED_;

static const struct SLInterfaceID_ SL_IID_VIBRA_ = { 0x169a8d60, 0xdddd, 0x11db, 0x923d, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_VIBRA = &SL_IID_VIBRA_;

static const struct SLInterfaceID_ SL_IID_METADATAEXTRACTION_ = { 0xaa5b1f80, 0xddd6, 0x11db, 0xac8e, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_METADATAEXTRACTION = &SL_IID_METADATAEXTRACTION_;

static const struct SLInterfaceID_ SL_IID_METADATATRAVERSAL_ = { 0xc43662c0, 0xddd6, 0x11db, 0xa7ab, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_METADATATRAVERSAL = &SL_IID_METADATATRAVERSAL_;

static const struct SLInterfaceID_ SL_IID_DYNAMICSOURCE_ = { 0xc55cc100, 0x038b, 0x11dc, 0xbb45, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_DYNAMICSOURCE = &SL_IID_DYNAMICSOURCE_;

static const struct SLInterfaceID_ SL_IID_OUTPUTMIX_ = { 0x97750f60, 0xddd7, 0x11db, 0x92b1, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_OUTPUTMIX = &SL_IID_OUTPUTMIX_;

static const struct SLInterfaceID_ SL_IID_PLAY_ = { 0xef0bd9c0, 0xddd7, 0x11db, 0xbf49, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_PLAY = &SL_IID_PLAY_;

static const struct SLInterfaceID_ SL_IID_PREFETCHSTATUS_ = { 0x2a41ee80, 0xddd8, 0x11db, 0xa41f, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_PREFETCHSTATUS = &SL_IID_PREFETCHSTATUS_;

static const struct SLInterfaceID_ SL_IID_PLAYBACKRATE_ = { 0x2e3b2a40, 0xddda, 0x11db, 0xa349, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_PLAYBACKRATE = &SL_IID_PLAYBACKRATE_;

static const struct SLInterfaceID_ SL_IID_SEEK_ = { 0xd43135a0, 0xdddc, 0x11db, 0xb458, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_SEEK = &SL_IID_SEEK_;

static const struct SLInterfaceID_ SL_IID_RECORD_ = { 0xc5657aa0, 0xdddb, 0x11db, 0x82f7, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_RECORD = &SL_IID_RECORD_;

static const struct SLInterfaceID_ SL_IID_EQUALIZER_ = { 0x0bed4300, 0xddd6, 0x11db, 0x8f34, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_EQUALIZER = &SL_IID_EQUALIZER_;

static const struct SLInterfaceID_ SL_IID_VOLUME_ = { 0x09e8ede0, 0xddde, 0x11db, 0xb4f6, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_VOLUME = &SL_IID_VOLUME_;

static const struct SLInterfaceID_ SL_IID_DEVICEVOLUME_ = { 0xe1634760, 0xf3e2, 0x11db, 0x9ca9, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_DEVICEVOLUME = &SL_IID_DEVICEVOLUME_;

static const struct SLInterfaceID_ SL_IID_OBJECT_ = { 0x79216360, 0xddd7, 0x11db, 0xac16, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_OBJECT = &SL_IID_OBJECT_;

static const struct SLInterfaceID_ SL_IID_BUFFERQUEUE_ = { 0x2bc99cc0, 0xddd4, 0x11db, 0x8d99, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_BUFFERQUEUE = &SL_IID_BUFFERQUEUE_;

static const struct SLInterfaceID_ SL_IID_PRESETREVERB_ = { 0x47382d60, 0xddd8, 0x11db, 0xbf3a, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_PRESETREVERB = &SL_IID_PRESETREVERB_;

static const struct SLInterfaceID_ SL_IID_ENVIRONMENTALREVERB_ = { 0xc2e5d5f0, 0x94bd, 0x4763, 0x9cac, { 0x4e, 0x23, 0x4d, 0x6, 0x83, 0x9e } };
const SLInterfaceID SL_IID_ENVIRONMENTALREVERB = &SL_IID_ENVIRONMENTALREVERB_;

static const struct SLInterfaceID_ SL_IID_EFFECTSEND_ = { 0x56e7d200, 0xddd4, 0x11db, 0xaefb, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_EFFECTSEND = &SL_IID_EFFECTSEND_;

static const struct SLInterfaceID_ SL_IID_3DGROUPING_ = { 0xebe844e0, 0xddd2, 0x11db, 0xb510, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_3DGROUPING = &SL_IID_3DGROUPING_;

static const struct SLInterfaceID_ SL_IID_3DCOMMIT_ = { 0x3564ad80, 0xdd0f, 0x11db, 0x9e19, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_3DCOMMIT = &SL_IID_3DCOMMIT_;

static const struct SLInterfaceID_ SL_IID_3DLOCATION_ = { 0x2b878020, 0xddd3, 0x11db, 0x8a01, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_3DLOCATION = &SL_IID_3DLOCATION_;

static const struct SLInterfaceID_ SL_IID_3DDOPPLER_ = { 0xb45c9a80, 0xddd2, 0x11db, 0xb028, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_3DDOPPLER = &SL_IID_3DDOPPLER_;

static const struct SLInterfaceID_ SL_IID_3DSOURCE_ = { 0x70bc7b00, 0xddd3, 0x11db, 0xa873, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_3DSOURCE = &SL_IID_3DSOURCE_;

static const struct SLInterfaceID_ SL_IID_3DMACROSCOPIC_ = { 0x5089aec0, 0xddd3, 0x11db, 0x9ad3, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_3DMACROSCOPIC = &SL_IID_3DMACROSCOPIC_;

static const struct SLInterfaceID_ SL_IID_MUTESOLO_ = { 0x5a28ebe0, 0xddd7, 0x11db, 0x8220, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_MUTESOLO = &SL_IID_MUTESOLO_;

static const struct SLInterfaceID_ SL_IID_DYNAMICINTERFACEMANAGEMENT_ = { 0x63936540, 0xf775, 0x11db, 0x9cc4, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_DYNAMICINTERFACEMANAGEMENT = &SL_IID_DYNAMICINTERFACEMANAGEMENT_;

static const struct SLInterfaceID_ SL_IID_MIDIMESSAGE_ = { 0xddf4a820, 0xddd6, 0x11db, 0xb174, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_MIDIMESSAGE = &SL_IID_MIDIMESSAGE_;

static const struct SLInterfaceID_ SL_IID_MIDITEMPO_ = { 0x1f347400, 0xddd7, 0x11db, 0xa7ce, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_MIDITEMPO = &SL_IID_MIDITEMPO_;

static const struct SLInterfaceID_ SL_IID_MIDIMUTESOLO_ = { 0x039eaf80, 0xddd7, 0x11db, 0x9a02, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_MIDIMUTESOLO = &SL_IID_MIDIMUTESOLO_;

static const struct SLInterfaceID_ SL_IID_MIDITIME_ = { 0x3da51de0, 0xddd7, 0x11db, 0xaf70, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_MIDITIME = &SL_IID_MIDITIME_;

static const struct SLInterfaceID_ SL_IID_AUDIODECODERCAPABILITIES_ = { 0x3fe5a3a0, 0xfcc6, 0x11db, 0x94ac, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_AUDIODECODERCAPABILITIES = &SL_IID_AUDIODECODERCAPABILITIES_;

static const struct SLInterfaceID_ SL_IID_AUDIOENCODER_ = { 0xd7d5af7a, 0x351c, 0x41a6, 0x94ec, { 0x1a, 0xc9, 0x5c, 0x71, 0x82, 0x2c } };
const SLInterfaceID SL_IID_AUDIOENCODER = &SL_IID_AUDIOENCODER_;

static const struct SLInterfaceID_ SL_IID_AUDIOENCODERCAPABILITIES_ = { 0x0f52a340, 0xfcd1, 0x11db, 0xa993, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_AUDIOENCODERCAPABILITIES = &SL_IID_AUDIOENCODERCAPABILITIES_;

static const struct SLInterfaceID_ SL_IID_BASSBOOST_ = { 0x0634f220, 0xddd4, 0x11db, 0xa0fc, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_BASSBOOST = &SL_IID_BASSBOOST_;

static const struct SLInterfaceID_ SL_IID_PITCH_ = { 0xc7e8ee00, 0xddd7, 0x11db, 0xa42c, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_PITCH = &SL_IID_PITCH_;

static const struct SLInterfaceID_ SL_IID_RATEPITCH_ = { 0x61b62e60, 0xddda, 0x11db, 0x9eb8, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_RATEPITCH = &SL_IID_RATEPITCH_;

static const struct SLInterfaceID_ SL_IID_VIRTUALIZER_ = { 0x37cc2c00, 0xdddd, 0x11db, 0x8577, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_VIRTUALIZER = &SL_IID_VIRTUALIZER_;

static const struct SLInterfaceID_ SL_IID_VISUALIZATION_ = { 0xe46b26a0, 0xdddd, 0x11db, 0x8afd, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_VISUALIZATION = &SL_IID_VISUALIZATION_;

static const struct SLInterfaceID_ SL_IID_ENGINE_ = { 0x8d97c260, 0xddd4, 0x11db, 0x958f, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_ENGINE = &SL_IID_ENGINE_;

static const struct SLInterfaceID_ SL_IID_ENGINECAPABILITIES_ = { 0x8320d0a0, 0xddd5, 0x11db, 0xa1b1, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_ENGINECAPABILITIES = &SL_IID_ENGINECAPABILITIES_;

static const struct SLInterfaceID_ SL_IID_THREADSYNC_ = { 0xf6ac6b40, 0xdddc, 0x11db, 0xa62e, { 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b } };
const SLInterfaceID SL_IID_THREADSYNC = &SL_IID_THREADSYNC_;


#ifdef __cplusplus
} /* extern "C" */
#endif

