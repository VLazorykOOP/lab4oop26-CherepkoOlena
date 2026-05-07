//
// Created by acer_ on 07.05.2026.
//

#include "Task1.h"
#include <iostream>
#include <cmath>

using namespace std;

class Vector3D {
    private:
        double x, y, z;
        int State; // 0 - OK, 1 - Nullptr, 2 - Div/0, 3 - Bad Index

    public:
        static int objectCount;

    Vector3D() : x(0), y(0), z(0), State(0) {
        objectCount++;
    }

    Vector3D(double val) : x(val), y(val), z(val), State(0) {
        objectCount++;
    }

    Vector3D(double* arr) {
        if (arr == nullptr) {
            x = y = z = 0;
            State = 1; //NULL
            std::cout << "Error NULL" << std::endl;
        } else {
            x = arr[0];
            y = arr[1];
            z = arr[2];
            State = 0;
        }
        objectCount++;
    }

    ~Vector3D() {
        cout << "State when removed: " << State << endl;
        objectCount--;
    }

    int getState() const { return State; }

    Vector3D& operator++() {
        x += 1.0; y += 1.0; z += 1.0;
        return *this;
    }

    Vector3D operator++(int) {
        Vector3D temp = *this;
        ++(*this);
        return temp;
    }

    Vector3D& operator--() {
        x -= 1.0; y -= 1.0; z -= 1.0;
        return *this;
    }

    Vector3D operator--(int) {
        Vector3D temp = *this;
        --(*this);
        return temp;
    }

    bool operator!() const {
        return (x != 0 || y != 0 || z != 0);
    }

    // (перпендикулярний вектор)
    Vector3D operator~() const {
        double values[] = {-y, x, 0};
        return Vector3D(values);
    }

    Vector3D operator-() const {
        Vector3D res;
        res.x = -x; res.y = -y; res.z = -z;
        return res;
    }

    Vector3D& operator=(const Vector3D& other) {
        if (this != &other) {
            x = other.x; y = other.y; z = other.z; State = other.State;
        }
        return *this;
    }

    Vector3D& operator+=(const Vector3D& v) {
        x += v.x; y += v.y; z += v.z; return *this;
    }
    Vector3D& operator-=(const Vector3D& v) {
        x -= v.x; y -= v.y; z -= v.z; return *this;
    }
    Vector3D& operator*=(double val) {
        x *= val; y *= val; z *= val; return *this;
    }
    Vector3D& operator/=(double val) {
        if (val == 0) { State = 2; return *this; }
        x /= val;
        y /= val;
        z /= val;
        return *this;
    }
    Vector3D& operator&=(const Vector3D& v) { // Векторний добуток
        double nx = y * v.z - z * v.y;
        double ny = z * v.x - x * v.z;
        double nz = x * v.y - y * v.x;
        x = nx; y = ny; z = nz;
        return *this;
    }
    Vector3D& operator%=(int val) {
        if (val == 0) { State = 2; return *this; }
        x = (int)x % val; y = (int)y % val; z = (int)z % val;
        return *this;
    }

    Vector3D operator+(const Vector3D& v) const { return Vector3D(*this) += v; }
    Vector3D operator-(const Vector3D& v) const { return Vector3D(*this) -= v; }
    Vector3D operator*(double val) const { return Vector3D(*this) *= val; }
    Vector3D operator/(double val) {
        Vector3D res(*this); res /= val; return res;
    }
    Vector3D operator%(int val) {
        Vector3D res(*this); res %= val; return res;
    }

    friend ostream& operator<<(ostream& out, const Vector3D& v) {
        out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return out;
    }
    friend istream& operator>>(istream& in, Vector3D& v) {
        in >> v.x >> v.y >> v.z;
        return in;
    }

    bool operator==(const Vector3D& v) const { return x == v.x && y == v.y && z == v.z; }
    bool operator!=(const Vector3D& v) const { return !(*this == v); }

    bool operator>(const Vector3D& v) const { return x > v.x && y > v.y && z > v.z; }
    bool operator>=(const Vector3D& v) const { return x >= v.x && y >= v.y && z >= v.z; }
    bool operator<(const Vector3D& v) const { return x < v.x && y < v.y && z < v.z; }
    bool operator<=(const Vector3D& v) const { return x <= v.x && y <= v.y && z <= v.z; }


    double& operator[](int index) {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        State = 3;
        return z;
    }

};

int Vector3D::objectCount = 0;


void Task1() {
    cout << "Vector count: " << Vector3D::objectCount << endl;

    Vector3D v1;
    Vector3D v2(5.5);

    double arr[] = {1.0, 2.0, 3.0};
    Vector3D v3(arr);

    cout << "v1: " << v1 << "\nv2: " << v2 << "\nv3: " << v3 << endl;
    cout << "Vector count: " << Vector3D::objectCount << endl;

    // Тест операцій
    v1 = v2 + v3;
    cout << "v1 = v2 + v3: " << v1 << endl;

    v3++;
    cout << "v3 after ++: " << v3 << endl;

    v1 /= 0;
    cout << "division by 0: " << v1.getState() << endl;

    cout << "Indexation v3[1]: " << v3[1] << endl;
    v3[5] = 10; // Невірний індекс
    cout << "Error index: " << v3.getState() << endl;


    cout << "Vector count final: " << Vector3D::objectCount << endl;
}