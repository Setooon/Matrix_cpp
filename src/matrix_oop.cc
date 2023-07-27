#include "matrix_oop.h"

Matrix::Matrix() {
  rows_ = 3;
  cols_ = 3;
  allocate();
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) { allocate(); }

Matrix::Matrix(const Matrix &o) : rows_(o.rows_), cols_(o.cols_) {
  allocate();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
}

Matrix::Matrix(int rows, int cols, std::vector<double> arr)
    : rows_(rows), cols_(cols) {
  allocate();
  int k = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = arr[k++];
    }
  }
}

Matrix::Matrix(Matrix &&o)
    : matrix_(o.matrix_), rows_(o.rows_), cols_(o.cols_) {
  o.matrix_ = NULL;
  o.rows_ = 0;
  o.cols_ = 0;
}

Matrix::~Matrix() {
  if (matrix_) {
    deallocate();
    cols_ = 0;
    rows_ = 0;
  }
}

bool Matrix::EqMatrix(const Matrix &o) {
  bool res = false;
  if (eq(o)) {
    res = true;
    for (int i = 0; i < rows_ && res; i++) {
      for (int j = 0; j < cols_ && res; j++) {
        if (std::fabs(matrix_[i][j] - o.matrix_[i][j]) > 1e-7) {
          res = false;
        }
      }
    }
  }
  return res;
}

void Matrix::SumMatrix(const Matrix &o) {
  if (eq(o)) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += o.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument(err[0]);
  }
}

void Matrix::SubMatrix(const Matrix &o) {
  if (eq(o)) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= o.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument(err[0]);
  }
}

void Matrix::MulNumber(const double num) {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (matrix_ && isnz(*this) && isnz(other) && cols_ == other.rows_ &&
      rows_ == other.cols_) {
    Matrix tmpB = other, tmp_res = *this;
    tmp_res.Setcols_(rows_);
    tmpB = tmpB.Transpose();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < rows_; j++) {
        tmp_res.matrix_[i][j] = 0;
        for (int k = 0; k < cols_; k++) {
          tmp_res.matrix_[i][j] += (matrix_[i][k] * tmpB.matrix_[j][k]);
        }
      }
    }
    *this = tmp_res;
  } else {
    throw std::invalid_argument(err[4]);
  }
}

Matrix Matrix::Transpose() {
  Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}

Matrix Matrix::CalcComplements() {
  Matrix tmp(cols_, rows_), matrix_minor;
  if (rows_ == cols_) {
    if (rows_ == 1) {
      matrix_[0][0] = 1.0;
    } else {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          matrix_minor = *this;
          matrix_minor._minor(i, j);
          tmp.matrix_[i][j] = pow(-1, i + j) * matrix_minor.Determinant();
        }
      }
    }
  } else {
    throw std::invalid_argument(err[1]);
  }
  return tmp;
}

double Matrix::Determinant() {
  int inv = 1;
  double res = 0.0, tmp = 0.0;
  if (rows_ == cols_) {
    if (rows_ == 1) {
      res = matrix_[0][0];
    } else if (rows_ == 2) {
      res = (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
    } else {
      Matrix matrix_minor = *this;
      for (int i = 0; i < cols_; i++) {
        matrix_minor = *this;
        matrix_minor._minor(i, 0);
        res = res + inv * matrix_[i][0] * matrix_minor.Determinant();
        inv = -inv;
      }
    }
  } else {
    throw std::invalid_argument(err[1]);
  }
  return res;
}

Matrix Matrix::InverseMatrix() {
  Matrix tmp(rows_, cols_);
  if (cols_ > 0 && isnz(*this) && isnz(tmp)) {
    double res_determ = this->Determinant();
    if (fabs(res_determ) >= 1e-7) {
      tmp = this->CalcComplements();
      tmp = tmp.Transpose();
      tmp.MulNumber(1.0 / res_determ);
    } else {
      throw std::invalid_argument(err[2]);
    }
  }
  return tmp;
}

void Matrix::_minor(int row, int col) {
  for (int i = 0; i < cols_ - 1; i++) {
    for (int j = 0; j < cols_ - 1; j++) {
      if (i >= row && j >= col) {
        matrix_[i][j] = matrix_[i + 1][j + 1];
      } else if (i >= row) {
        matrix_[i][j] = matrix_[i + 1][j];
      } else if (j >= col) {
        matrix_[i][j] = matrix_[i][j + 1];
      } else {
        matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  this->Setcols_(cols_ - 1);
  this->Setrows_(rows_ - 1);
}

bool Matrix::operator==(const Matrix &o) { return EqMatrix(o); }
Matrix &Matrix::operator*=(const Matrix &o) {
  MulMatrix(o);
  return *this;
}
Matrix &Matrix::operator*=(double a) {
  MulNumber(a);
  return *this;
}
Matrix &Matrix::operator+=(const Matrix &o) {
  SumMatrix(o);
  return *this;
}
Matrix &Matrix::operator-=(const Matrix &o) {
  SubMatrix(o);
  return *this;
}
Matrix Matrix::operator+(const Matrix &o) {
  Matrix res = *this;
  res.SumMatrix(o);
  return res;
}
Matrix Matrix::operator-(const Matrix &o) {
  Matrix res = *this;
  res.SubMatrix(o);
  return res;
}
Matrix Matrix::operator*(const Matrix &o) {
  Matrix res = *this;
  res.MulMatrix(o);
  return res;
}
Matrix Matrix::operator*(double o) {
  Matrix res = *this;
  res.MulNumber(o);
  return res;
}

Matrix &Matrix::operator=(const Matrix &o) {
  if (this != &o) {
    if (matrix_) {
      deallocate();
    }
    rows_ = o.rows_;
    cols_ = o.cols_;
    allocate();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = o.matrix_[i][j];
      }
    }
  }
  return *this;
}
double &Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range(err[3]);
  }
  return matrix_[row][col];
}

void Matrix::Setcols_(int a) {
  if (a != Getcols_()) {
    Matrix tmp = *this;
    deallocate();
    tmp.cols_ = tmp.cols_ > a ? a : tmp.cols_;
    cols_ = a;
    allocate();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < tmp.cols_; j++) {
        matrix_[i][j] = tmp.matrix_[i][j];
      }
    }
  }
}
void Matrix::Setrows_(int a) {
  if (a != Getrows_()) {
    Matrix tmp = *this;
    deallocate();
    tmp.rows_ = tmp.rows_ > a ? a : tmp.rows_;
    rows_ = a;
    allocate();
    for (int i = 0; i < tmp.rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = tmp.matrix_[i][j];
      }
    }
  }
}
