#pragma once

#ifndef _MATH_H_
    #define _MATH_H_
    #include <math.h>
#endif // !_MATH_H_

#ifndef _ASSERT_H_
    #define _ASSERT_H_
    #include <assert.h>
#endif // !_ASSERT_H_

/*
 Vector3  ��ά������
 
 ��������������������ά�ȵ���ֵ��
 ʵ���������Ļ���������
 */
class Vector3 {
public:
    float x, y, z;
    Vector3() : x(0.0), y(0.0), z(0.0) {}
    Vector3(float x, float y, float z)
        : x(x), y(y), z(z) {}
    Vector3(float xyz)
        : x(xyz), y(xyz), z(xyz) {}
    ~Vector3() {}

    // ��������Ϊָ��ֵ
    void all(float d) {
        x = d;
        y = d;
        z = d;
    }

    Vector3& operator = (const Vector3& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    bool operator == (const Vector3& v) const {
        return x == v.x && y == v.y && z == v.z;
    }
    bool operator != (const Vector3& v) const {
        return !(*this == v);
    }

    // ȡ����
    Vector3 operator - () const {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator + (const Vector3& v) const {
        return Vector3(
            x + v.x,
            y + v.y,
            z + v.z
        );
    }
    Vector3& operator += (const Vector3& v) {
        *this = *this + v;
        return *this;
    }

    Vector3 operator - (const Vector3& v) const {
        return Vector3(-v + *this);
    }
    Vector3& operator -= (const Vector3& v) {
        *this = *this - v;
        return *this;
    }

    // ���� * ��
    Vector3 operator * (float d) const {
        return Vector3(x * d, y * d, z * d);
    }
    Vector3& operator *= (float d) {
        *this = *this * d;
        return *this;
    }
    // ���� / ��
    Vector3 operator / (float d) const {
        // if (d == 0.0) d = 1;
        float di = 1.0 / d;
        return *this * di;
    }
    Vector3& operator /= (float d) {
        *this = *this / d;
        return *this;
    }

    // �������
    float operator * (const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // ��ģ
    float length() {
        return sqrt(x * x + y * y + z * z);
    }

    // ��׼������
    void normalize() {
        float l = this->length();
        assert(l != 0.0);
        *this /= this->length();
    }
    
};

// �������
Vector3 v3Cross(const Vector3& v1, const Vector3& v2) {
    return Vector3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

// ��λ�˷�
Vector3 v3ElementwiseProduct(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

// ��������
float v3Distance(const Vector3& v1, const Vector3& v2) {
    float dx = v1.x - v2.x,
          dy = v1.y - v2.y,
          dz = v1.z - v2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}