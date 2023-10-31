// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <chrono>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        pMem = nullptr;
        if (size == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (size > MAX_VECTOR_SIZE)
            throw length_error("The size of the vector must be less than MAX_VECTOR_SIZE");
        pMem = new T[size]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s){  
      pMem = nullptr;
      if (sz == 0)
          throw out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE)
          throw length_error("The size of the vector must be less than MAX_VECTOR_SIZE")
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
    TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      if (v.pMem == nullptr)
          this->pMem = nullptr;
      else {
          this->pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
  }
    TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->pMem = nullptr;
      swap(*this, v);
  }
    ~TDynamicVector()
  {
      if (pMem != nullptr)
          delete[]pMem;
      sz = 0;
      pMem = nullptr;
  }
    TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      this->sz = v.sz;
      if (v.pMem == nullptr)
          this->pMem = nullptr;
      else {
          this->pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
      return *this;
  }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
  {
      return pMem[ind];
  }
    const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
    // индексация с контролем
    T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz)
          throw out_of_range("Vector size should be greater than zero");
      return pMem[ind];
  }
    const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
          throw out_of_range("Vector size should be greater than zero");
      return pMem[ind];
  }

    // сравнение
     bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz)
          return false;
      for (int i = 0; i < sz; i++)
          if (this->pMem[i] != v.pMem[i])
              return false;
      return true;
  }
    bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !this->operator==(v);
  }

    // скалярные операции
    TDynamicVector operator+(T val)
  {
      TDynamicVector temp(this->sz);
      if (pMem != nullptr) {
          for (int i = 0; i < sz; i++) {
              temp.pMem[i] = this->pMem[i] + val;
          }
      }
      return temp;
  }
    TDynamicVector operator-(T val)
  {
      TDynamicVector temp(this->sz);
      if (pMem != nullptr) {
          for (int i = 0; i < sz; i++) {
              temp.pMem[i] = this->pMem[i] - val;
          }
      }
      return temp;
  }
    TDynamicVector operator*(T val)
  {
      TDynamicVector temp(this->sz);
      if (pMem != nullptr) {
          for (int i = 0; i < sz; i++) {
              temp.pMem[i] = this->pMem[i] * val;
          }
      }
      return temp;
  }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz != v.sz)
          throw   exception("Вектора различного размера");
      TDynamicVector temp(this->sz);
      for (int i = 0; i < this->sz; i++)
          temp.pMem[i] = this->pMem[i] + v.pMem[i];
      return temp;
  }
    TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.sz)
          throw exception("Вектора различного размера");
      TDynamicVector temp(this->sz);
      for (int i = 0; i < this->sz; i++)
          temp.pMem[i] = this->pMem[i] - v.pMem[i];
      return temp;
  }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (this->sz != v.sz)
          throw exception("Вектора различного размера");
      T temp{};
      for (int i = 0; i < this->sz; i++)
          temp += pMem[i] * v[i];
      return temp;
  }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz == 0)
          throw out_of_range("Matrix size should be greater than zero");
      if (sz > MAX_MATRIX_SIZE)
          throw length_error("The size of the matrix must be less than MAX_MATRIX_SIZE");
      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(sz);
  }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz)
          return false;
      for (int i = 0; i < m.sz; i++) {
          if (pMem[i] != m.pMem[i])
              return false;
      }
      return true;
  }
    bool operator!=(const TDynamicMatrix& m) const noexcept {
      return !this->operator==(m);
  }
    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix temp(*this);
      for (int i = 0; i < sz; i++)
          temp.pMem[i] = temp.pMem[i] * val;
      return temp;
  }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (this->sz != v.size())
          throw exception("Различные линейные размеры вектора  и матрицы");
      TDynamicVector<T> temp(sz);
      for (int i = 0; i < sz; i++) {
          temp[i] = this->pMem[i] * v;
      }
      return temp;
  }



    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw exception("Матрицы различного размера");
      TDynamicMatrix temp(sz);
      for (int i = 0; i < sz; i++) {
          temp[i] = pMem[i] + m[i];
      }
      return temp;
  }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw   exception("Матрицы различного размера");
      TDynamicMatrix temp(sz);
      for (int i = 0; i < sz; i++) {
          temp[i] = pMem[i] - m[i];
      }
      return temp;
  }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw   exception("Матрицы различного размера");
      TDynamicMatrix temp(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              for (int k = 0; k < sz; k++)
                  temp[i][j] += this->pMem[i][k] * m.pMem[k][j];
          }
      }
      return temp;
  }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++) {
              istr >> v[i][j];
          }
      }
      return istr;
  }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++) {
              ostr << v[i][j] << " ";
          }
          ostr << endl;
      }
      return ostr;
  }


    size_t size() const noexcept { return sz; }

    //Индексация
    T& at(size_t ind1, size_t ind2)
  {
      if (ind1 < 0 || ind1 >= sz || ind2 < 0 || ind2 >= sz)
          throw out_of_range("Vector size should be greater than zero");
      return pMem[ind1][ind2];
  }
    const T& at(size_t ind) const
  {
      if (ind1 < 0 || ind1 >= sz || ind2 < 0 || ind2 >= sz)
          throw out_of_range("Vector size should be greater than zero");
      return pMem[ind1][ind2];
  }


 
};


#endif



class Timer {
private:
    chrono::time_point<chrono::steady_clock> start, end;
public:
    Timer() {
        start = chrono::high_resolution_clock::now();
    }
    void set() {
        end = chrono::high_resolution_clock::now();
        chrono::duration<float> dur = end - start;
        cout << "Время: " << dur.count() << " secund" << endl;
    }
};
