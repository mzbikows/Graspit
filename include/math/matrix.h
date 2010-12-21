//######################################################################
//
// GraspIt!
// Copyright (C) 2002-2009  Columbia University in the City of New York.
// All rights reserved.
//
// GraspIt! is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GraspIt! is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GraspIt!.  If not, see <http://www.gnu.org/licenses/>.
//
// Author(s): Matei T. Ciocarlie
//
// $Id: matrix.h,v 1.13.2.1 2009/07/23 21:17:55 cmatei Exp $
//
//######################################################################

#ifndef _matrix_h_
#define _matrix_h_

#include <assert.h>
#include <iostream>
#include <vector>
#include <list>

class transf;
class mat3;

//! A class for storing and performing operations on general 2-dimensional matrices
/*! The Matrix is a general 2-dimensional matrix, along with a (growing)
	number of operations that can be performed on it. The data itself is stored as
	a column-major array of doubles. The important design decisions are:

	A Matrix only holds doubles for now. At some point I hope to template the class 
	to hold	anything you might want.

	Many of the computations are done using LAPACK. This should be really fast,
	but also has problems. One of them is that it prevents using const correctly
	for all the operations and arguments that should be const.

	A Matrix's size is determined when it is constructed, and can never be changed
	afterwards. This is somewhat inflexible, but allows us to catch size 
	mismatches at run time. In debug mode, all operations first assert(...) the 
	correct matrix sizes.

	All Matrix copies are deep copies. This avoids lots of problem with consistency,
	but can also eat up memory and slow down operations. Be particularly careful 
	when using the copy constructor, or any functions that return instances of
	the Matrix class: all are done using deep copies.

	No operators have been implemented. Most operations that involve two or more
	matrices are external to this class, and rather than returning the result, they
	take in the result as an argument. This makes it somewhat easier to catch errors,
	but also make chaining of operations annoying.
*/
class Matrix{
private:
	int mRows, mCols;
	//! The actual data, in column-major format
	double *mData;
	//! Keeps track of row permutations that have been done
	int *mRowPermutations;
	//! Keeps track of column permutations that have been done
	int *mColPermutations;

	//! All the work that is common between all constructors
	void initialize(int m, int n);
	//! Copies the actual data from a column-major array in memory
	void setFromColMajor(const double *M);
	//! Copies the actual data from a row-major array in memory
	void setFromRowMajor(const double *M);
public:
	//! A matrix of the given size with unspecified contents
	Matrix(int m, int n);
	//! Copy constructor
	Matrix(const Matrix &M);
	//! A matrix of the given size, with contents initialized from an array in memory
	Matrix(const double *M, int m, int n, bool colMajor);
	virtual ~Matrix();

	inline double& elem(int m, int n);
	inline const double& elem(int m, int n) const;
	//! Returns a pointer to the actual data in memory
	double *getData(){return mData;}
	//! Returns a copy of the data as a column major vector of doubles
	void getData(std::vector<double> *data) const;
	//! The number of rows of this matrix
	int rows() const {return mRows;}
	//! The number of columns of this matrix
	int cols() const {return mCols;}
	Matrix getColumn(int c) const;
	Matrix getRow(int r) const;
	Matrix getSubMatrix(int startRow, int startCol, int rows, int cols) const;

	void setAllElements(double val);
	//! Copies a block of the matrix \a m into a block of this matrix
	void copySubBlock(int startRow, int startCol, int rows, int cols, 
				      const Matrix &m, int startMRow, int startMCol);
	//! Copies the entire matrix \a m into a sub-block of this matrix
	void copySubMatrix(int startRow, int startCol, const Matrix &m){
		copySubBlock(startRow, startCol, m.rows(), m.cols(), m, 0, 0);}
	//! Copies the entire matrix \a m to this matrix; sizes must be identical
	void copyMatrix(const Matrix &m){copySubMatrix(0, 0, m);}

	friend std::ostream& operator<<(std::ostream &os, const Matrix &m);
	void print(FILE *fp) const;//improve Mariusz ¯bikowski, mzbikows@gmail.com
	//void print(FILE *fp = stderr) const;

	//! Computes the rank of the matrix using SVD
	int rank() const;
	//! Computes the Frobenius norm of the matrix: sqrt(sum_of_all_squared_elems)
	double fnorm() const;
	//! The largest absolute value of any element in this matrix
	double absMax() const;
	//! The sum of all the elements in the matrix
	double elementSum() const;
	void swapRows(int r1, int r2);
	void swapCols(int c1, int c2);
	//! Transposes this matrix in place
	void transpose();
	//! Sets this matrix to identity. Not really used, use the static EYE instead
	void eye();
	//! Multiples the matrix by the scalar s
	void multiply(double s);

	//! Returns the transpose of this matrix; the original is unaffected
	Matrix transposed() const;

	//! An identity matrix of the given size
	static Matrix EYE(int m, int n);
	//! A negated identity matrix of the given size
	static Matrix NEGEYE(int m, int n);
	//! A mtrix of the given size filled with zeroes
	static Matrix ZEROES(int m, int n);
	//! A permutation matrix initialized from a permutation vector in memory
	static Matrix PERMUTATION(int n, int *jpvt);
	//! A 4x4 transform matrix that can be used to left-multiply a 4x1 homogeneous vector
	static Matrix TRANSFORM(const transf &t);
	//! A 3x3 rotation matrix that can be used to left-multiply a 3x1 vector
	static Matrix ROTATION(const mat3 &rot);
	//! A 2D 2x2 rotation matrix that can be used to left-multiply a 2x1 vector
	static Matrix ROTATION2D(double theta);
	//! Builds a block diagonal matrix from the matrices in the list
	static Matrix BLOCKDIAG(std::list<Matrix*> *blocks);
	//! Builds a block diagonal matrix from the two given matrices
	static Matrix BLOCKDIAG(const Matrix &M1, const Matrix &M2);
	//! Builds a block column matrix from the column matrices in the list
	static Matrix BLOCKCOLUMN(std::list<Matrix*> *blocks);
	//! Builds a block column matrix from the two given matrices
	static Matrix BLOCKCOLUMN(const Matrix &M1, const Matrix &M2);
	//! Builds a block row matrix from the row matrices in the list
	static Matrix BLOCKROW(std::list<Matrix*> *blocks);
	//! Builds a block row matrix from the two given matrices
	static Matrix BLOCKROW(const Matrix &M1, const Matrix &M2);
	//! Returns a vector filled with the max value that can be expressed as a double
	static Matrix MAX_VECTOR(int rows);
	//! Returns a vector filled with the min value that can be expressed as a double
	static Matrix MIN_VECTOR(int rows);

	//! Used for zero comparisons in all computations
	static const double EPS;
};

//! Performs M = L * R
void matrixMultiply(const Matrix &L, const Matrix &R, Matrix &M);
//! Performs M = L + R
void matrixAdd(const Matrix &L, const Matrix &R, Matrix &M);
//! Checks if two matrices are identical
bool matrixEqual(const Matrix &R, const Matrix &L);
//! Solves the system A*X=B with square A. X is overwritten on B. 
int triangularSolve(Matrix &A, Matrix &B);
//! Computes minimum norm solution of underdetermined system A*X=B with full-rank A.
int underDeterminedSolveSVD(Matrix &A, Matrix &B, Matrix &X);
//! Computes minimum norm solution of underdetermined system A*X=B even for rank-deficient A
int underDeterminedSolveQR(Matrix &A, Matrix &B, Matrix &X);
//! Computes a solution of an underdetermined system A*X = B using Moore-Penrose pseudo-inverse
int underDeterminedSolveMPInv(Matrix &A, Matrix &B, Matrix &X);
//! Computes the inverse of a square matrix
int matrixInverse(const Matrix &A, Matrix &AInv);
//! Solves a Quadratic Program
int QPSolver(const Matrix &Q, 
			 const Matrix &Eq, const Matrix &b,
			 const Matrix &InEq, const Matrix &ib,
			 const Matrix &lowerBounds, const Matrix &upperBounds,
			 Matrix &sol, double *objVal);
//! Solves a factorized Quadratic Program
int factorizedQPSolver(const Matrix &Qf, 
								  const Matrix &Eq, const Matrix &b,
								  const Matrix &InEq, const Matrix &ib,			
								  const Matrix &lowerBounds, const Matrix &upperBounds,
								  Matrix &sol, double *objVal);
//! A simple test to check that the QP solver works
void testQP();
//! Solves a linear program
int LPSolver(const Matrix &Q,
			 const Matrix &Eq, const Matrix &b,
			 const Matrix &InEq, const Matrix &ib,
			 const Matrix &lowerBounds, const Matrix &upperBounds,
			 Matrix &sol, double *objVal);
//! A simple test to check that the LP solver works
void testLP();

double&
Matrix::elem(int m, int n) 
{
	assert(m<mRows);
	assert(n<mCols);
	return mData[n*mRows + m];
}

const double&
Matrix::elem(int m, int n) const
{
	assert(m<mRows);
	assert(n<mCols);
	return mData[n*mRows + m];
}

#endif
