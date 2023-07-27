#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(default_constructor_test, test1) {
  Matrix arr;
  ASSERT_DOUBLE_EQ(arr.Getrows_(), 3);
  ASSERT_DOUBLE_EQ(arr.Getcols_(), 3);
}

TEST(parameter_constructor_test, test1) {
  Matrix m1(1, 1), m3(3, 3);

  ASSERT_DOUBLE_EQ(m1.Getrows_(), 1);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 1);
  ASSERT_DOUBLE_EQ(m3.Getrows_(), 3);
  ASSERT_DOUBLE_EQ(m3.Getcols_(), 3);
}

TEST(initializer_list_constructor, test1) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr);
  ASSERT_DOUBLE_EQ(m1.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(copy_constructor, test1) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr);
  Matrix m2(m1);

  ASSERT_DOUBLE_EQ(m2.Getrows_(), m1.Getrows_());
  ASSERT_DOUBLE_EQ(m2.Getcols_(), m1.Getcols_());

  for (int i = 0; i < m2.Getrows_(); i++)
    for (int j = 0; j < m2.Getcols_(); j++)
      ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}

TEST(copy_constructor, test2) {
  std::vector<double> arr = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, arr);
  Matrix m2(m1);

  ASSERT_DOUBLE_EQ(m2.Getrows_(), m1.Getrows_());
  ASSERT_DOUBLE_EQ(m2.Getcols_(), m1.Getcols_());

  for (int i = 0; i < m2.Getrows_(); i++)
    for (int j = 0; j < m2.Getcols_(); j++)
      ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}

TEST(move_constructor, test1) {
  std::vector<double> arr = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, arr);
  Matrix m2(m1);

  ASSERT_DOUBLE_EQ(m2.Getrows_(), 3);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 3);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m2.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m2.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(EqMatrix, test1) {
  std::vector<double> arr = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, arr), m2(3, 3, arr);

  ASSERT_EQ(m1.EqMatrix(m2), 1);
}

TEST(SumMatrix, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  std::vector<double> arr2 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, arr1), m2(3, 3, arr2);

  m1.SumMatrix(m2);
  for (int i = 0; i < m2.Getrows_(); i++)
    for (int j = 0; j < m2.Getcols_(); j++)
      ASSERT_DOUBLE_EQ(m1(i, j), 2 * m2(i, j));
}

TEST(SubMatrix, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  std::vector<double> arr2 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, arr1), m2(3, 3, arr2);

  m1.SubMatrix(m2);
  for (int i = 0; i < m2.Getrows_(); i++) {
    for (int j = 0; j < m2.Getcols_(); j++) {
      ASSERT_DOUBLE_EQ(0, m1(i, j));
    }
  }
}

TEST(Assignment, test1) {
  Matrix m1(3, 3), m2(2, 2);

  m2 = m1;
  ASSERT_DOUBLE_EQ(m2.Getrows_(), 3);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 3);
}

TEST(MulNumber, test1) {
  std::vector<double> arr = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, arr);
  m1.MulNumber(3.);
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k * 3.);
}

TEST(MulMatrix, test1) {
  std::vector<double> arr = {10, 16, 9, 16};
  std::vector<double> arr1 = {1, 2, 3, 4, 1, 2};
  std::vector<double> arr2 = {1, 2, 3, 4, 1, 2};
  Matrix m1(2, 3, arr1), m2(3, 2, arr2);

  m1.MulMatrix(m2);
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(MulMatrix, test2) {
  std::vector<double> arr = {18, 16, 7, 14, 17, 14, 19, 10, 17};
  std::vector<double> arr1 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  std::vector<double> arr2 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, arr1), m2(3, 3, arr2);

  m1.MulMatrix(m2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), m2.Getcols_());
  ASSERT_DOUBLE_EQ(m1.Getrows_(), 3);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(Transpose, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr = {1, 3, 2, 4};
  Matrix m1(2, 2, arr1), m2;
  m2 = m1.Transpose();
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(OPER11, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  Matrix m1(2, 2, arr1);
  ASSERT_DOUBLE_EQ(m1(1, 0), 3);
}

TEST(CalcComplements, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr = {4, -3, -2, 1};
  Matrix m1(2, 2, arr1), m2;

  m2 = m1.CalcComplements();
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(CalcComplements, test2) {
  std::vector<double> arr1 = {11, 8, 9, 6, 5, 4, 3, 2, 1};
  std::vector<double> arr = {-3, 6, -3, 10, -16, 2, -13, 10, 7};
  Matrix m1(3, 3, arr1), m2;

  m2 = m1.CalcComplements();
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(InverseMatrix, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr = {-2, 1, 1.5, -0.5};
  Matrix m1(2, 2, arr1), m2;

  m2 = m1.InverseMatrix();
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(InverseMatrix, test2) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr = {-2, 1, 1.5, -0.5};
  Matrix m1(2, 2, arr1), m2;

  m2 = m1.InverseMatrix();
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(Determinant, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 10};
  Matrix m1(3, 3, arr1), m2;

  ASSERT_DOUBLE_EQ(m1.Determinant(), -3);
}

TEST(Determinant, test2) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  Matrix m1(2, 2, arr1), m2;

  ASSERT_DOUBLE_EQ(m1.Determinant(), -2);
}

TEST(CopyOperator, test1) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr), m2;
  m2 = m1;

  ASSERT_DOUBLE_EQ(m2.Getrows_(), m1.Getrows_());
  ASSERT_DOUBLE_EQ(m2.Getcols_(), m1.Getcols_());

  for (int i = 0; i < m2.Getrows_(); i++)
    for (int j = 0; j < m2.Getcols_(); j++)
      ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}

TEST(MoveOperator, test1) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr), m2;
  m2 = std::move(m1);

  ASSERT_DOUBLE_EQ(m2.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 2);
  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m2.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m2.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(plusequalop, test1) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr);
  m1 += m1;

  ASSERT_DOUBLE_EQ(m1.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k * 2);
}

TEST(minequalop, test1) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr);
  m1 -= m1;

  ASSERT_DOUBLE_EQ(m1.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), 0);
}

TEST(mulequalop, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr = {7, 10, 15, 22};
  Matrix m1(2, 2, arr1);
  m1 *= m1;

  ASSERT_DOUBLE_EQ(m1.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(mulequalop, test2) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr);
  m1 *= 2;

  ASSERT_DOUBLE_EQ(m1.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m1.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m1.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k * 2);
}

TEST(isequalop, test3) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  Matrix m1(2, 2, arr1), m2(2, 2, arr1);

  ASSERT_DOUBLE_EQ(m1.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 2);
  ASSERT_EQ(m1 == m2, 1);
}

TEST(plusop, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr2 = {5, 6, 7, 8};
  std::vector<double> ans = {6, 8, 10, 12};
  Matrix m1(2, 2, arr1), m2(2, 2, arr2), m3(2, 2);
  m3 = m2 + m1;

  ASSERT_DOUBLE_EQ(m3.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m3.Getcols_(), 2);
  int i = 0, j = 0;
  for (auto k = ans.begin(); k != ans.end(); k++,
            i = (j + 1) == m3.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m3.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m3(i, j), *k);
}

TEST(sub, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr2 = {5, 6, 7, 8};
  std::vector<double> ans = {6, 8, 10, 12};
  Matrix m1(2, 2, arr1), m2(2, 2, arr2), m3(2, 2);
  m3 = m1 + m2;
  ASSERT_DOUBLE_EQ(m2.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 2);
  int i = 0, j = 0;
  for (auto k = ans.begin(); k != ans.end(); k++,
            i = (j + 1) == m2.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m2.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m3(i, j), *k);
}

TEST(minop, test1) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr), m2;
  m2 = m1 - m1;

  ASSERT_DOUBLE_EQ(m2.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m2.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m2.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), 0);
}

TEST(mulop, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr = {7, 10, 15, 22};
  Matrix m1(2, 2, arr1), m2;
  m2 = m1 * m1;

  ASSERT_DOUBLE_EQ(m2.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m2.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m2.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(mulop, test2) {
  std::vector<double> arr = {1, 2, 3, 4};
  Matrix m1(2, 2, arr), m2;
  m2 = m1 * 3.0;
  ASSERT_DOUBLE_EQ(m2.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 2);

  int i = 0, j = 0;
  for (auto k = arr.begin(); k != arr.end(); k++,
            i = (j + 1) == m2.Getcols_() ? (i + 1) : i,
            j = (j + 1) == m2.Getcols_() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k * 3);
}

TEST(Getters, test1) {
  Matrix m1(2, 2), m2(3, 1);

  ASSERT_DOUBLE_EQ(m2.Getrows_(), 3);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 1);
  ASSERT_DOUBLE_EQ(m1.Getrows_(), 2);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 2);
}

TEST(Setters_, test1) {
  std::vector<double> arr1 = {1, 2, 3, 4};
  std::vector<double> arr2 = {5, 6, 7, 8};
  Matrix m1(2, 2, arr1), m2(2, 2, arr2);
  m1.Setcols_(3);
  m1.Setrows_(3);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 3);
  ASSERT_DOUBLE_EQ(m1.Getcols_(), 3);
  m2.Setrows_(1);
  m2.Setcols_(1);
  ASSERT_DOUBLE_EQ(m2.Getrows_(), 1);
  ASSERT_DOUBLE_EQ(m2.Getcols_(), 1);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
