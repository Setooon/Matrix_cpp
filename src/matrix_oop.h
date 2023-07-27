#pragma once
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

class Matrix {
  int rows_, cols_;
  double **matrix_;
  std::string err[5] = {"different matrix dimensions",
                        "the matrix is not square", "matrix determinant is 0",
                        "index is out of range",
                        "the number of columns of the first matrix does not"};

 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix &o);
  Matrix(Matrix &&o);
  Matrix(int rows, int cols, std::vector<double> arr);
  ~Matrix();
  Matrix operator+(const Matrix &o);
  Matrix operator-(const Matrix &o);
  Matrix operator*(const Matrix &o);
  Matrix operator*(double a);
  Matrix &operator*=(const Matrix &o);
  Matrix &operator*=(double a);
  Matrix &operator+=(const Matrix &o);
  Matrix &operator-=(const Matrix &o);
  bool operator==(const Matrix &o);
  Matrix &operator=(const Matrix &o);
  double &operator()(int row, int col);
  bool eq_matrix(const Matrix &o);
  void SumMatrix(const Matrix &o);
  bool EqMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();
  void _minor(int row, int col);
  void allocate() {
    matrix_ = new double *[rows_];
    matrix_[0] = new double[rows_ * cols_];
    for (int i = 1; i < rows_; i++) {
      matrix_[i] = matrix_[i - 1] + cols_;
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = 0;
      }
    }
  }
  void deallocate() {
    if (matrix_) {
      delete[] matrix_[0];
      delete[] matrix_;
    }
  }
  bool isnz(const Matrix &o) { return (cols_ > 0 && rows_ > 0); }
  bool eq(const Matrix &o) { return (cols_ == o.cols_ && rows_ == o.rows_); }
  int Getrows_() { return rows_; }
  void Setrows_(int a);
  int Getcols_() { return cols_; }
  void Setcols_(int a);
};
