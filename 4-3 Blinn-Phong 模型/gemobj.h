#pragma once
#include "../vector3.h"

/**
 * GEMOBJ.H
 *
 * ���弸�ζ���
 * Last Edit: 2020/07/01
 */

/**
 * Surface  ���ζ���Ļ���
 *
 * ʵ����Blinn-Phong ģ��Ҫ��ı����������뾵�淴�䡣
 */
class Surface {
public:
    // ������������ɫ������������ֵ�ֱ��ӦRGBͨ��
    Vector3 diffuse;
    // ���ʾ��淴����ɫ������������ֵ�ֱ��ӦRGBͨ��
    Vector3 specular;
    // Phong ָ�����������ʹ����
    float phongExponent;

    Surface() {}
    ~Surface() {}

    virtual bool hit(const Vector3& ve,
        const Vector3& vd,
        float t1,
        float t2,
        float& rec) = 0;

    virtual Vector3 getNormal(Vector3) = 0;
};

// ����ʵ������������������ࣻ�������ζ���һ��ɿ������������ε�ƴ�ӡ�

/**
 * Triangle  ��������
 *
 * �̳���Surface �ࡣ
 */
class Triangle : public Surface {
public:
    //�����ε���������
    Vector3 p1, p2, p3;
    //��������ķ�����
    Vector3 normal;

    Triangle() {}
    /**
     * ����һ�������������뾵�淴��������Ρ�
     * �䷨�����ķ�������˳���йء�������˵��
     * ������ָ��������ͨ��p1, p2, p3����Ĵָ��ָ����Ϊ����������
     * 
     * @param p1,p2,p3 �����ε���������
     * @param diffuse ��������ɫ������������ֵ�ֱ��ӦRGBͨ��
     * @param specular ���淴����ɫ������������ֵ�ֱ��ӦRGBͨ��
     * @param phongExponent ���ʹ����
     */
    Triangle(const Vector3& p1,
             const Vector3& p2,
             const Vector3& p3,
             const Vector3& diffuse,
             const Vector3& specular,
             float          phongExponent
        ) : p1(p1), p2(p2), p3(p3) {
        this->diffuse = diffuse;
        this->specular = specular;
        this->phongExponent = phongExponent;
        this->normal = v3Cross(p2 - p1, p3 - p1);
        this->normal.normalize();
    }

    /**
     * �������εķ�������
     * �������ķ�������˳���йء�������˵��
     * ������ָ��������ͨ��p1, p2, p3����Ĵָ��ָ����Ϊ����������
     *
     * @param p ����һ�㣬Ĭ��Ϊ��ָ��
     */
    virtual Vector3 getNormal(const Vector3) {
        return normal;
    }

    /**
     * �жϹ������������Ƿ��ཻ��
     *
     * @param      //����ɱ�ʾΪve+t*vd
     * @param[in]  ve �����λ��
     * @param[in]  vd ���߷����ɽ���ָ�������
     * @param[in]  t1,t2 t�ķ�Χ��t1<t2
     * @param[out] rec �˱��������ཻʱt��ֵ
     *
     * @return bool �Ƿ��ཻ
     */
    virtual bool hit(const Vector3& ve,
        const Vector3& vd,
        float t1,
        float t2,
        float& rec) {
        //ʹ�ù������������󽻹�ʽ�жϣ�
        //Ϊ�����Ч��ʹ���˼����м������
        assert(t2 > t1);
        float a = p1.x - p2.x,
            b = p1.y - p2.y,
            c = p1.z - p2.z,
            d = p1.x - p3.x,
            e = p1.y - p3.y,
            f = p1.z - p3.z,
            g = vd.x,
            h = vd.y,
            i = vd.z,
            j = p1.x - ve.x,
            k = p1.y - ve.y,
            l = p1.z - ve.z;
        float ei_hf = e * i - h * f,
            gf_di = g * f - d * i,
            dh_eg = d * h - e * g,
            ak_jb = a * k - j * b,
            jc_al = j * c - a * l,
            bl_kc = b * l - k * c;
        float M = a * ei_hf + b * gf_di + c * dh_eg;

        rec = -(f * ak_jb + e * jc_al + d * bl_kc) / M;
        if (rec > t2 || rec < t1) {
            return false;
        }
        float beta = (j * ei_hf + k * gf_di + l * dh_eg) / M;
        if (beta < 0 || beta > 1) {
            return false;
        }
        float gamma = (i * ak_jb + h * jc_al + g * bl_kc) / M;
        if (gamma < 0 || gamma > 1 - beta) {
            return false;
        }
        return true;
    }
};

/**
 * Sphere  ����
 *
 * �̳���Surface �ࡣ
 */
class Sphere : public Surface {
public:
    //����
    Vector3 center;
    //�뾶
    float radius = 0;

    Sphere() {}
    /**
     * ����һ�������������뾵�淴������档
     *
     * @param center ����
     * @param radius �뾶
     * @param diffuse ��������ɫ������������ֵ�ֱ��ӦRGBͨ��
     * @param specular ���淴����ɫ������������ֵ�ֱ��ӦRGBͨ��
     * @param phongExponent ���ʹ����
     */
    Sphere(const Vector3& center,
        float radius,
        const Vector3& diffuse,
        const Vector3& specular,
        float          phongExponent
    ) : center(center), radius(radius) {
        this->diffuse = diffuse;
        this->specular = specular;
        this->phongExponent = phongExponent;
    }

    /**
     * ������ķ�������
     * �������ķ���������ָ�����档
     *
     * @param p ������һ��
     */
    virtual Vector3 getNormal(const Vector3 p) {
        Vector3 normal = p - center;
        normal.normalize();
        return normal;
    }

    /**
     * �жϹ����������Ƿ��ཻ��
     *
     * @param      //����ɱ�ʾΪve+t*vd
     * @param[in]  ve �����λ��
     * @param[in]  vd ���߷����ɽ���ָ�������
     * @param[in]  t1,t2 t�ķ�Χ��t1<t2
     * @param[out] rec �˱��������ཻʱt��ֵ
     *
     * @return bool �Ƿ��ཻ
     */
    virtual bool hit(const Vector3& ve,
        const Vector3& vd,
        float t1,
        float t2,
        float& rec) {
        assert(t2 > t1);
        //ʹ�ù����������󽻹�ʽ�жϣ�
        //Ϊ�����Ч��ʹ���˼����м������
        Vector3 e_c = ve - center;
        float d_e_c = vd * e_c;
        float d_d = vd * vd;
        float delta = d_e_c * d_e_c - d_d * (e_c * e_c - radius * radius);
        if (delta < 0) {
            return false;
        }
        rec = (-d_e_c - sqrt(delta)) / d_d;
        if (rec > t2 || rec < t1) {
            return false;
        }
        return true;
    }
};

/**
 * Light  ���Դ
 */
struct Light {
    // λ������
    Vector3 position;
    // ��ǿ������������ֵ�ֱ��ӦRGBͨ����
    // ��ǿ��С������޹ء�
    Vector3 intensity;
};