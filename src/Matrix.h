#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <numeric>
#include <array>

template<std::size_t N, typename T>
class Vector : public std::array<T, N>
{
public:
    Vector(T value = T()) {
        this->fill(value);
    }

    Vector(const std::initializer_list<T> &l) : Vector() {
        std::copy(l.begin(), l.end(), this->begin());
    }

    T length() {
        return std::sqrt(std::accumulate(this->begin(), this->end(), 0, [](T sum, T e){return sum + e*e;}));
    }

    const Vector<N,T>& operator+=(const Vector<N,T>& right) {
        *this = *this + right;
        return *this;
    }

    const Vector<N,T>& operator-=(const Vector<N,T>& right) {
        *this = *this - right;
        return *this;
    }

    const Vector<N,T>& operator*=(const T right) {
        *this = *this * right;
        return *this;
    }

    const Vector<N,T>& operator/=(const T right) {
        *this = *this / right;
        return *this;
    }

    friend Vector<N,T> operator+(const Vector<N,T>& left, const Vector<N,T>& right) {
        Vector<N,T> result;
        std::transform(left.begin(), left.end(), right.begin(), result.begin(), std::plus<T>());
        return result;
    }

    friend Vector<N,T> operator-(const Vector<N,T>& left, const Vector<N,T>& right) {
        Vector<N,T> result;
        std::transform(left.begin(), left.end(), right.begin(), result.begin(), std::minus<T>());
        return result;
    }

    friend Vector<N,T> operator*(const Vector<N,T>& left, const T right) {
        Vector<N,T> result = left;
        std::transform(left.begin(), left.end(), result.begin(), std::bind1st(std::multiplies<T>(), right));
        return result;
    }

    friend Vector<N,T> operator/(const Vector<N,T>& left, const T right) {
        Vector<N,T> result;
        std::transform(left.begin(), left.end(), result.begin(), std::bind2nd(std::divides<T>(), right));
        return result;
    }
};

template<std::size_t N, std::size_t M, typename T>
class Matrix : public Vector<N,Vector<M,T>>
{
public:
    Matrix(T value = T()) : Vector<N,Vector<M,T>>(Vector<M,T>(value)) {}

    Matrix(const std::initializer_list<std::initializer_list<T>> ll) : Matrix() {
        std::copy(ll.begin(), ll.end(), this->begin());
    }

    friend Vector<N,T> operator*(const Matrix<N,M,T>& left, const Vector<M,T>& right) {
        Vector<N,T> result;
        for (std::size_t i = 0; i < N; i++)
            for (std::size_t j = 0; j < M; j++)
                result[i] += left[i][j] * right[j];
        return result;
    }

    Matrix<N, M, T> transpose() {
        Matrix<N, M, T> result;
        for (std::size_t i = 0; i < N; i++)
            for (std::size_t j = 0; j < M; j++)
                result[i][j] = (*this)[j][i];
        return result;
    }

};

using Vector3D = Vector<3,double>;
using Matrix3x3D = Matrix<3,3,double>;
