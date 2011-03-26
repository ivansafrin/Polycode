/*
 *  PolyMatrix4.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/26/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Math
 
#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyVector3.h"
#include <string.h>

namespace Polycode {

	class Vector3;
	
	class _PolyExport Matrix4 {
	
		public:
			Matrix4();


        inline Matrix4(
            Number m00, Number m01, Number m02, Number m03,
            Number m10, Number m11, Number m12, Number m13,
            Number m20, Number m21, Number m22, Number m23,
            Number m30, Number m31, Number m32, Number m33 )
        {
            m[0][0] = m00;
            m[0][1] = m01;
            m[0][2] = m02;
            m[0][3] = m03;
            m[1][0] = m10;
            m[1][1] = m11;
            m[1][2] = m12;
            m[1][3] = m13;
            m[2][0] = m20;
            m[2][1] = m21;
            m[2][2] = m22;
            m[2][3] = m23;
            m[3][0] = m30;
            m[3][1] = m31;
            m[3][2] = m32;
            m[3][3] = m33;
        }

			
			Matrix4(Number *m);
			~Matrix4();
			
			void init();
			
			union {
				Number m[4][4];
				Number ml[16];
			};
			
			inline void identity() {
				memset(ml, 0, sizeof(Number)*16);
				ml[0] = 1;
				ml[5] = 1;
				ml[10] = 1;
				ml[15] = 1;		
			}
		
			
			inline Vector3 rotateVector(const Vector3 &v2) {
				return Vector3(v2.x*m[0][0] + v2.y*m[1][0] + v2.z*m[2][0],
								v2.x*m[0][1] + v2.y*m[1][1] + v2.z*m[2][1],
								v2.x*m[0][2] + v2.y*m[1][2] + v2.z*m[2][2]);
			}
			
			inline Vector3 getPosition() {
				Vector3 pos;
				pos.x = m[3][0];
				pos.y = m[3][1];
				pos.z = m[3][2];
				return pos;
			}
			/*
			void setTransform(Vector3 pos, Vector3 scale, Quaternion rot) {
			
			}
	*/
			inline Vector3 operator * ( const Vector3 &v2 ) const
			{
				return Vector3(v2.x*m[0][0] + v2.y*m[1][0] + v2.z*m[2][0] + m[3][0],
								v2.x*m[0][1] + v2.y*m[1][1] + v2.z*m[2][1] + m[3][1],
								v2.x*m[0][2] + v2.y*m[1][2] + v2.z*m[2][2] + m[3][2]);
			}			
			
			inline Number* operator [] ( int row ) { return m[row];}

			inline void setPosition(Number x, Number y, Number z) {
				m[3][0] = x;
				m[3][1] = y;
				m[3][2] = z;
			}
		
			inline void setScale(Vector3 scale) {
				m[0][0] = scale.x;
				m[1][1] = scale.y;
				m[2][2] = scale.z;
			}

			inline void getEulerAngles(Number *ax, Number *ay, Number *az) {
				Number angle_x, angle_y, angle_z,tr_x,tr_y,C;
				
				angle_y = asin(m[0][2]);
				
				C = cosf(angle_y);
				angle_y *= TODEGREES;
				
				if(fabsf(C) > 0.005) {
					tr_x      =  m[2][2] / C; // 10 
					tr_y      = -m[1][2]  / C; // 6
					angle_x  = atan2f( tr_y, tr_x ) * TODEGREES;
					tr_x      =  m[0][0] / C; // 0
					tr_y      = -m[0][1] / C; // 1
					angle_z  = atan2f( tr_y, tr_x ) * TODEGREES;
				} else {
					angle_x  = 0;
					tr_x      =  m[1][1];
					tr_y      =  m[1][0];
					angle_z  = atan2f( tr_y, tr_x ) * TODEGREES;
				}					
				
				if (angle_x < 0) angle_x += 360;
				if (angle_y < 0) angle_y += 360;
				if (angle_z < 0) angle_z += 360;
				
				*ax = -fabs(angle_x);
				*ay = fabs(angle_y);
				*az = fabs(angle_z);

			}

			inline Matrix4 operator + ( const Matrix4 &m2 ) const {
				Matrix4 r;
				
				r.m[0][0] = m[0][0] + m2.m[0][0];
				r.m[0][1] = m[0][1] + m2.m[0][1];
				r.m[0][2] = m[0][2] + m2.m[0][2];
				r.m[0][3] = m[0][3] + m2.m[0][3];
				
				r.m[1][0] = m[1][0] + m2.m[1][0];
				r.m[1][1] = m[1][1] + m2.m[1][1];
				r.m[1][2] = m[1][2] + m2.m[1][2];
				r.m[1][3] = m[1][3] + m2.m[1][3];

				r.m[2][0] = m[2][0] + m2.m[2][0];
				r.m[2][1] = m[2][1] + m2.m[2][1];
				r.m[2][2] = m[2][2] + m2.m[2][2];
				r.m[2][3] = m[2][3] + m2.m[2][3];
				
				r.m[3][0] = m[3][0] + m2.m[3][0];
				r.m[3][1] = m[3][1] + m2.m[3][1];
				r.m[3][2] = m[3][2] + m2.m[3][2];
				r.m[3][3] = m[3][3] + m2.m[3][3];
				
				return r;
			}
			
			Matrix4 inverse();
			Matrix4 inverseAffine();
	
			inline Matrix4 operator * (const Matrix4 &m2) const {
           Matrix4 r;
            r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
            r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
            r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
            r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

            r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
            r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
            r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
            r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

            r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
            r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
            r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
            r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

            r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
            r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
            r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
            r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

            return r;

					}
		protected:
		
	};
}	