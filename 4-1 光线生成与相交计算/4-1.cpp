#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include <graphics.h>
#endif // !_GRAPHICS_H_

#ifndef _CONIO_H_
#define _CONIO_H_
#include <conio.h>
#endif // !_CONIO_H_

#include "../vector3.h"

/*
 * 4    ����׷��
 * 4-1  �����������ཻ����
 *
 * ��ʾ����׷�ٵĻ���ԭ��
 * ����������˳�����ɹ��ߡ������뼸��ͼ���ཻ���жϡ�
 *
 * ���л�����Windows��Visual Studio 2019
 * EasyX ͼ�ο�汾��20200520��beta��
 *
 * ****  �����������Ӧ���볢�������豸��  ****
 * ****  �����ֱ��������ȷ������Github�����������Ľ��������������ȷ��װEasyXͼ�ο⡣  ****
 *
 * Last Edit: 2020/06/24
 */

//���ζ���ĸ���
class Surface {
public:
    //����������ϵ��������������ֵ�ֱ��ӦRGBͨ��
    Vector3 diffuse;

    Surface() {}
    ~Surface() {}

    virtual bool hit(const Vector3& ve,
        const Vector3& vd,
        float t1,
        float t2,
        float& rec) = 0;
};

// ����ʵ������������������ࣻ�������ζ���һ��ɿ������������ε�ƴ�ӡ�

//��������
class Triangle : public Surface {
public:
    //�����ε���������
    Vector3 p1, p2, p3;

    Triangle() {}
    Triangle(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 diffuse) 
    : p1(p1), p2(p2), p3(p3) {
        this->diffuse = diffuse;
    }

    /*
     �жϹ������������Ƿ��ཻ��

     @param //���߿ɱ�ʾΪve+t*vd
     @param Vector3& ve �����λ��
     @param Vector3& vd ���߷����ɽ���ָ�������
     @param float t1, t2 t�ķ�Χ
     @param float& rec �ô˱��������ཻʱt��ֵ

     @return bool �Ƿ��ཻ
     */
    virtual bool hit(const Vector3& ve,
        const Vector3& vd,
        float t1,
        float t2,
        float& rec) {
        //ʹ�ù������������󽻹�ʽ�ж�(�μ�������İ�79ҳ)��
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

        rec = (f * ak_jb + e * jc_al + d * bl_kc) / M;
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

/*
 initFullscreen  ��ʼ��ȫ����ͼ����

 ***  ��Щ������ͼ��ѧ�޹�  ***
 */
void initFullscreen() {
    int rW = GetSystemMetrics(SM_CXSCREEN); // ��Ļ��� ����
    int rH = GetSystemMetrics(SM_CYSCREEN); // ��Ļ�߶� ����
    initgraph(rW, rH);
    HWND hwnd = GetHWnd();// EasyX�⺯������ȡ���ھ��
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE,
        (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);
}


int main() {
    initFullscreen();
    Vector3 o(0, 0, 0),
            a(100, 0, 0),
            b(0, 100, 0),
            c(0, 0, 100),
            color(0.25, 0.5, 0.25);
    Triangle* s[4] = {
        new Triangle(o, a, b, Vector3(0.75, 0.75, 0.5)),
        new Triangle(o, b, c, Vector3(0.75, 0.75, 0.5)),
        new Triangle(o, c, a, Vector3(0.75, 0.75, 0.5)),
        new Triangle(a, b, c, Vector3(0.75, 0.75, 0.5))
    };
    Vector3 e(175, -35, 35);
    Vector3 e_to_ScreenCenter(-165, 0, 0);  // �������ָ����Ļ���ĵ�����������Ļ��ֱ��
    DWORD* pImg = GetImageBuffer(0); // EasyX�⺯������ȡ�����Դ�ָ��
    int rW = GetSystemMetrics(SM_CXSCREEN); // ��Ļ��� ����
    int rH = GetSystemMetrics(SM_CYSCREEN); // ��Ļ�߶� ����

    // ������Ļ����ϵ�Ļ�
    Vector3 z(0, 0, 1);
    Vector3 w_axis, h_axis;
    Vector3 n = e_to_ScreenCenter;
    n.normalize();
    if (n == z || n == -z) {
        w_axis = Vector3(1, 0, 0);
    }
    else {
        w_axis = v3Cross(n, z);
    }
    h_axis = v3Cross(n, w_axis);

    for (int h = 0; h < rH; h++) {
        for (int w = 0; w < rW; w++) {
            int index = w + h * rW;

            // ��һ�������ɹ��ߡ�
            // �ؼ�����������ߵķ���d��
            // d == ����λ�� - e
            // |����λ�� == ��Ļ���� + ƫ��
            // ||��Ļ���� == e + e_to_ScreenCenter
            // ||ƫ�� == ��Ļ���� * ��Ļ����ϵ�Ļ�
            // ���ϣ�d == e_to_ScreenCenter + ƫ��
            Vector3 bia = w_axis * (w - rW/2) 
                + h_axis * (h - rH/2);
            Vector3 d = -(e_to_ScreenCenter + bia);
            if (bia.length() == 0.0) {
                int i = 0;
            }

            // �ڶ������жϹ��߻��еļ��ζ���
            float t = 10000000000;
            float temp;
            Surface* hitObj = nullptr;
            for (Surface* o : s) {
                if (o->hit(e, d, 0, t, temp)) {
                    if (t > temp) {
                        t = temp;
                        hitObj = o;
                    }
                }
            }

            // ���������ڸ�������ʾ���ζ������ɫ��
            if (hitObj != nullptr) {
                pImg[index] = RGB(
                    (int)(hitObj->diffuse.z * 255),
                    (int)(hitObj->diffuse.y * 255),
                    (int)(hitObj->diffuse.x * 255)
                );
                
            }
            else {
                pImg[index] = RGB(64,64,64);
            }
        }
    }

    _getch();
    delete s[0], s[1], s[2], s[3];
    s[0] = s[1] = s[2] = s[3] = nullptr;
    return 0;
}