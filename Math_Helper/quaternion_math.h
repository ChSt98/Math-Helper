#ifndef _QUATERNION_MATH_H_
#define _QUATERNION_MATH_H_


#include <Arduino.h>

#include "vector_math.h"


#ifndef PI
#define PI 3.1415926541f
#endif

#ifndef DEGREES
#define DEGREES 180.0f/PI
#endif




class Quaternion {
    public:
    
        float w;
        float x;
        float y;
        float z;

        bool valid = true;
        
        Quaternion() {
            w = 0.0f;
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        Quaternion(Vector axis, float angle) {

            angle /= 2.0f;
            float sa = sinf(angle);
            
            w = cosf(angle);
            x = axis.x*sa;
            y = axis.y*sa;
            z = axis.z*sa;

        }
        
        Quaternion(float nw, float nx, float ny, float nz) {
            w = nw;
            x = nx;
            y = ny;
            z = nz;
        }

        Quaternion(float nx, float ny, float nz) {
            w = 0.0f;
            x = nx;
            y = ny;
            z = nz;
        }


        Quaternion getConjugate() {
            return Quaternion(w, -x, -y, -z);
        }

        
        float getMagnitude() {

            float m = w*w + x*x + y*y + z*z;

            m = sqrtf(m);
            
            if (m == m) { // Check for NAN event
                
            } else valid = false;

            return m;

        }

        
        void normalize(bool sign = false) {

            float m = getMagnitude();

            if (valid) {

                if (sign) m = -m;
                
                w /= m;
                x /= m;
                y /= m;
                z /= m;

            }

            if (w==w && x==x && y==y && z==z) return; //Check for NAN event

            valid = false;

        }
        
        Quaternion copy() {
            return Quaternion(w, x, y, z);
        }

        Quaternion operator + (Quaternion b) {
            return Quaternion(w + b.w, x + b.x, y + b.y, z + b.z);
        }

        Quaternion operator - (Quaternion b) {
            return Quaternion(w - b.w, x - b.x, y - b.y, z - b.z);
        }

        Quaternion operator - (void) {
            return Quaternion(-w, -x, -y, -z);
        }

        Quaternion operator * (float c) {
            return Quaternion(w*c, x*c, y*c, z*c);
        }

        Quaternion operator / (float c) {
            return Quaternion(w/c, x/c, y/c, z/c);
        }

        void operator *= (float c) {
            w *= c;
            x *= c;
            y *= c;
            z *= c;
        }

        void operator += (Quaternion b) {
            w += b.w;
            x += b.x;
            y += b.y;
            z += b.z;
        }

        Quaternion operator * (Quaternion q) {
            return Quaternion(
                w*q.w - x*q.x - y*q.y - z*q.z,  // new w
                w*q.x + x*q.w + y*q.z - z*q.y,  // new x
                w*q.y - x*q.z + y*q.w + z*q.x,  // new y
                w*q.z + x*q.y - y*q.x + z*q.w); // new z
        }

};


#endif /* _HELPER_3DMATH_H_ */