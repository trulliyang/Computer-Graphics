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
 Vector2  ��ά������

 ��������������������ά�ȵ���ֵ��
 ʵ���������Ļ���������
 */
class Vector2 {
public:
    float x, y;
    Vector2() : x(0.0), y(0.0) {}
    Vector2(float x, float y)
        : x(x), y(y) {}
    Vector2(float xy)
        : x(xy), y(xy) {}
    ~Vector2() {}

    // ��������Ϊָ��ֵ
    void all(float d) {
        x = d;
        y = d;
    }

    Vector2& operator = (const Vector2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    bool operator == (const Vector2& v) const {
        return x == v.x && y == v.y;
    }
    bool operator != (const Vector2& v) const {
        return !(*this == v);
    }

    // ȡ����
    Vector2 operator - () const {
        return Vector2(-x, -y);
    }

    Vector2 operator + (const Vector2& v) const {
        return Vector2(
            x + v.x,
            y + v.y
        );
    }
    Vector2& operator += (const Vector2& v) {
        *this = *this + v;
        return *this;
    }

    Vector2 operator - (const Vector2& v) const {
        return Vector2(-v + *this);
    }
    Vector2& operator -= (const Vector2& v) {
        *this = *this - v;
        return *this;
    }

    // ���� * ��
    Vector2 operator * (float d) const {
        return Vector2(x * d, y * d);
    }
    Vector2& operator *= (float d) {
        *this = *this * d;
        return *this;
    }
    // ���� / ��
    Vector2 operator / (float d) const {
        // if (d == 0.0) d = 1;
        float di = 1.0 / d;
        return *this * di;
    }
    Vector2& operator /= (float d) {
        *this = *this / d;
        return *this;
    }

    // �������
    float operator * (const Vector2& v) const {
        return x * v.x + y * v.y;
    }

    // ��ģ
    float length() {
        return sqrt(x * x + y * y);
    }

    // ��׼������
    void normalize() {
        float l = this->length();
        assert(l != 0.0);
        *this /= this->length();
    }

};

// �������
float v2Cross(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.y - v2.x *v1.y;
}

// ��λ�˷�
Vector2 v2ElementwiseProduct(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1.x * v2.x, v1.y * v2.y);
}

// ��������
float v2Distance(const Vector2& v1, const Vector2& v2) {
    float dx = v1.x - v2.x,
        dy = v1.y - v2.y;
    return sqrt(dx * dx + dy * dy);
}