/*
 * This file is part of Matrix.
 *
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <functional>


namespace linalg
{
template <typename T>
class Matrix
{
public:
    // Delete the default constructor. Matrix cannot be initialized empty.
    Matrix() = delete;

   /**
    *  @brief Constructor
    *
    * Constructs a Matrix object from a given Integer. The Matrix object 
    * is always a 2D entity. When initialized by an Integer, it forms the 
    * first row and first column of the Matrix object.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * 
    * linalg::Matrix A{1};
    * 
    * // outputs (1, 1)
    * std::cout << A.size();
    * 
    * 
    * @param mat - Integer value.
    * @return Initializes a Matrix object.
    */
    Matrix(const T mat)
        : m_matrix{1, std::vector<T>(1, mat)}
    {
    }

   /**
    * @brief Constructor
    *
    * Matrix object is always a 2D entity. When initialized by 1D vector, it forms the 
    * first row of the Matrix object.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * 
    * linalg::Matrix A{{1, 2, 3, 4}};
    * 
    * // outputs (1, 4)
    * std::cout << A.size();
    * 
    * 
    * @param mat - 1D STL vector.
    * @return Initializes a Matrix object.
    */
    Matrix(const std::vector<T>& mat)
        : m_matrix{1, mat}
    {
    }

   /**
    * @brief Constructor
    *
    * Constructs a Matrix object from a given 2D vector. Matrix object is 
    * always a 2D entity.
    * 
    * 
    * @example
    * 
    * #include <vector>
    * #include "Matrix.h"
    * 
    * std::vector<int> vec{{{1, 2}, {3, 4}}};
    * linalg::Matrix A{vec};
    * 
    * // outputs (2, 2)
    * std::cout << A.size();
    * 
    * 
    * @param mat - 2D STL vector.
    * @return Initializes a Matrix object.
    */
    Matrix(const std::vector<std::vector<T>>& mat)
        : m_matrix{mat}
    {
        for (int row=1; row<m_matrix.size(); row++)
        {
            if (m_matrix[row - 1].size() != m_matrix[row].size())
            {
                std::cout << m_matrix[row - 1].size() << ", " << m_matrix[row].size() << '\n';
                std::cerr << "Contructor - Matrix dimension do not match" << std::endl;
                std::abort();
            }
        }
    }

   /**
    * @brief Constructor
    *
    * Constructs a Matrix object of size equal to the given dimensions.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * 
    * linalg::Matrix A{3, 4};
    * linalg::Matrix B{3, 4, 2};
    * 
    * // outputs (3, 4)
    * std::cout << A.size();
    * // outputs (3, 4) with all elements initialized to 2.
    * std::cout << B.size();
    * 
    *
    * @param row - The number of rows of the Matrix object.
    * @param col - The number of columns of the Matrix object.
    * @param value - This will be the value of all the elements in the Matrix 
    *                object. Will default to 0.
    * @return Initializes a Matrix object.
    */
    Matrix(const size_t& row, const size_t& col, T value=0)
        : m_matrix{row, std::vector<T>(col, value)}
    {
    }

   /**
    * @brief Operator overload to multiply 1D or 2D matrices.
    *
    * Inputs are Matrix objects. The matrix can be a row or column vector or a 
    * 2D matrix. Dimensions for matrix multiplication are checked. Assertion
    * error is raised if dimensions do not match. Returns the result as a Matrix 
    * object.
    * 
    * This operation can also chain with other Matrix objects. The only 
    * requirement is matrix dimensions should match.
    * 
    * Dimension checking:
    * C(m, k) = A(m, n) * B(n, k)
    * 
    * The paranthesis demonstrate dimensions of the Matrix object. Here, n 
    * should be the same of A and B, i.e, the number of columns of the Matrix 
    * object on the left-hand side of the operator* and the number of rows of the 
    * Matrix object on the right-hand side of the operator* should the constant.
    *
    * 
    * @example
    * 
    * #include "Matrix.h"
    * 
    * linalg::Matrix A{{1, 2, 3}};
    * linalg::Matrix B{{1, 2, 3}};
    * B = B.transpose();
    * lingalg::Matrix C{A * B};
    * // -or-
    * std::cout << A * B;
    * 
    * 
    * @param lhs - The left-hand side of the operator should be a Matrix object.
    * @param rhs - The right-hand side of the operator should be a Matrix object.
    * @return Matrix multiplication after dimension checking as a Matrix object.
    */
    template <typename U>
    friend Matrix<U> operator* (const Matrix<U>& mat1, const Matrix<U>& mat2);

   /**
    * @brief Returns the transpose of the Matrix object.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * 
    * linalg::Matrix A{{1, 2, 3, 4}}; // size: (1, 4)
    * linalg::Matrix B{{{1, 2, 3}, {4, 5, 6}}}; // size: (2, 3)
    * A = A.transpose();
    * B = B.transpose();
    * // outputs (4, 1)
    * std::cout << A.size();
    * // outputs (3, 2)
    * std::cout << B.size();
    * 
    * 
    * @return The transpose of the Matrix object.
    */
    Matrix<T> transpose();

   /**
    * @brief Returns the size of the Matrix object in a Pair.
    * 
    * The first parameter is the number of rows and the second 
    * parameter is the number of columns.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * 
    * linalg::Matrix A{{{1, 2, 3}, {4, 5, 6}}}; // size: (2, 3)
    *
    * std::cout << A.size(); // Outputs (2, 3)
    * std::cout << A.size().first; // Outputs number of rows: 2
    * std::cout << A.size().second; // Outputs number of columns: 3
    * 
    * 
    * @return The size of the Matrix object as STL Pair.
    */
    std::pair<size_t, size_t> size();

   /**
    * @brief Output stream overload function for Matrix object.
    * This function adds support for string stream and prints Matrix 
    * object to the screen.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * linalg::Matrix A{{{1, 2, 3}, {4, 5, 6}}};
    * std::cout << A;
    * 
    * 
    * @return The output stream of the complete Matrix object.
    */
    template <typename U>
    friend std::ostream& operator<< (std::ostream& output, const Matrix<U>& mat);

   /**
    * @brief This function helps print the size of the Matrix object.
    * It pushes the size of the Matrix object in a output stream.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * linalg::Matrix A{{{1, 2, 3}, {4, 5, 6}}};
    * std::cout << A.size(); Output: (2, 3)
    * 
    * 
    * @return The output stream of the size of the Matrix object.
    */
    friend std::ostream& operator<< (std::ostream& output, const std::pair<size_t, size_t>& size);

   /**
    * @brief This function implements the comparison operator for 
    * the Matrix object. 
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * linalg::Matrix A{{{1, 2, 3}, {4, 5, 6}}};
    * linalg::Matrix B{{{1, 2, 3}, {4, 5, 6}}};
    * std::cout << A == B; // Output: 0 or true
    * 
    * 
    * @return True if all the elements are the same, False even if 
    * one element does not match.
    */
    template <typename U>
    friend bool operator== (const Matrix<U>& c1, const Matrix<U>& c2);

   /**
    * @brief Returns true if both Matrices are the same, false even 
    * if one element is not the same. This function helps in testing.
    * 
    * 
    * @example
    * 
    * #include "Matrix.h"
    * 
    * linalg::Matrix A{{{1, 2, 3}, {4, 5, 6}}};
    * linalg::Matrix B{{{1, 2, 3}, {4, 5, 6}}};
    * linalg::Matrix C{{1, 2, 3}};
    *
    * std::cout << isSame(A, B); // Output: 1 or true
    * std::cout << isSame(A, C); // Output: 0 or false
    * 
    * @param m1 - The first Matrix object to compare.
    * @param m2 - The second Matrix object to compare.
    * @return Whether the given Matrices are the same or not.
    */
    static bool isSame(const linalg::Matrix<T>& m1, const linalg::Matrix<T>& m2);

private:
    // The actual 2D Matrix.
    std::vector<std::vector<T>> m_matrix;
};

template <typename T>
Matrix<T> operator*(const Matrix<T>& mat1, const Matrix<T>& mat2)
{
    if (mat1.m_matrix[0].size() != mat2.m_matrix.size())
    {
        std::cerr << "Matrix dimension do not match" << std::endl;
        std::abort();
    }

    Matrix<T> res(mat1.m_matrix.size(), mat2.m_matrix[0].size());

    for (int i=0; i<res.m_matrix.size(); i++)
    {
        for (int k=0; k<mat1.m_matrix[0].size(); k++)
        {
            for (int j=0; j<res.m_matrix[i].size(); j++)
            {
                res.m_matrix[i][j] += mat1.m_matrix[i][k] * mat2.m_matrix[k][j];
            }
        }
    }

    return res;
}

// Original implementation of matrix multiplication. Tested to be 
// slower than the other implementation.
// Matrix operator* (const Matrix& mat1, const Matrix& mat2)
// {
//     assert(mat1.m_matrix[0].size() == mat2.m_matrix.size());
//     Matrix res(mat1.m_matrix.size(), mat2.m_matrix[0].size());

//     for (int i=0; i<res.m_matrix.size(); i++)
//     {
//         for (int j=0; j<res.m_matrix[i].size(); j++)
//         {
//             for (int k=0; k<mat1.m_matrix[0].size(); k++)
//             {
//                 res.m_matrix[i][j] += mat1.m_matrix[i][k] * mat2.m_matrix[k][j];
//             }
//         }
//     }

//     return res;
// }

// TODO: can this be done in-place
template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    // Initialize the output matrix.
    // Notice the dimensions are switched.
    Matrix<T> res(m_matrix[0].size(), m_matrix.size());

    for (int i=0; i<m_matrix.size(); i++)
    {
        for (int j=0; j<m_matrix[0].size(); j++)
        {
            res.m_matrix[j][i] = m_matrix[i][j];
        }
    }
    return res;
}

template <typename T>
std::pair<size_t, size_t> Matrix<T>::size()
{
    // row, col
    return std::make_pair(this->m_matrix.size(), this->m_matrix[0].size());
}

template <typename T>
std::ostream& operator<< (std::ostream& output, const Matrix<T>& mat)
{
    // Pushes the first (N-1) rows in the buffer.
    output << '[';
    for (int i=0; i<mat.m_matrix.size()-1; i++)
    {
        output << "[ ";
        for (int j=0; j<mat.m_matrix[i].size(); j++)
        {
            output << mat.m_matrix[i][j] << ' ';
        }
        output << "]";
        output << "\n ";
    }

    // Pushes the last row in the buffer.
    // This is done to print the matrix properly.
    // Otherwise, the last bracket is printed on the next line.
    for (int i=mat.m_matrix.size()-1; i<mat.m_matrix.size(); i++)
    {
        output << "[ ";
        for (int j=0; j<mat.m_matrix[i].size(); j++)
        {
            output << mat.m_matrix[i][j] << ' ';
        }
        output << "]";
    }
    output << ']';
    output << '\n';
    return output;
}

std::ostream& operator<< (std::ostream& output, const std::pair<size_t, size_t>& size)
{
    output << "(" << size.first << ", " << size.second << ")\n";
    return output;
}

template <typename T>
bool operator== (const Matrix<T>& m1, const Matrix<T>& m2)
{
    return (m1.m_matrix == m2.m_matrix);
}

template <typename T>
static bool isSame(const linalg::Matrix<T>& m1, const linalg::Matrix<T>& m2)
{
    return (m1 == m2);
}

}; // namespace linalg

#endif // MATRIX_H
