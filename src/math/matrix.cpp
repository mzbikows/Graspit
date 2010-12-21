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
// $Id: matrix.cpp,v 1.19.2.1 2009/07/23 21:18:09 cmatei Exp $
//
//######################################################################

#include "math/matrix.h"

#include <limits>
#include <math.h>

#ifdef MKL
#include "mkl_wrappers.h"
#else
#include "lapack_wrappers.h"
#endif

//for printing
#include "maxdet.h"

#include "matvec3D.h"

//#define GRASPITDBG
#include "debug.h"

//Quadratic Program solvers
#ifdef MOSEK_QP
#include "mosek_qp.h"
#endif

const double Matrix::EPS = 1.0e-7;

void Matrix::initialize(int m, int n)
{
	mRows = m;
	mCols = n;
	if (mRows>0 && mCols>0) {
		try {
			mData = new double[mRows*mCols];
		} catch(std::bad_alloc) {
			DBGA("Not enough memory for dense matrix of size " << 
				  mRows << " by " << mCols);
			assert(0);
			mData = NULL;
		}
		mRowPermutations = new int[mRows];
		mColPermutations = new int[mCols];
	} else {
		mRows = mCols = 0;
		mData = NULL;
		mRowPermutations = mColPermutations = NULL;
	}
}

Matrix::Matrix(int m, int n)
{
	initialize(m,n);
	for (int i=0; i<mRows; i++) {
		mRowPermutations[i] = i;
	}
	for (int i=0; i<mCols; i++) {
		mColPermutations[i] = i;
	}
}
Matrix::Matrix(const Matrix &M)
{
	initialize(M.rows(), M.cols());
	if (mRows) {
		memcpy(mData, M.mData, mRows*mCols*sizeof(double));
		memcpy(mRowPermutations, M.mRowPermutations, mRows*sizeof(int));
		memcpy(mColPermutations, M.mColPermutations, mCols*sizeof(int));
	}
}

Matrix::Matrix(const double *M, int m, int n, bool colMajor)
{
	initialize(m,n);
	if (colMajor) {
		setFromColMajor(M);
	} else {
		setFromRowMajor(M);
	}
	for (int i=0; i<mRows; i++) {
		mRowPermutations[i] = i;
	}
	for (int i=0; i<mCols; i++) {
		mColPermutations[i] = i;
	}
}

Matrix::~Matrix()
{
	if (mRows) {
		delete [] mData;
		delete [] mRowPermutations;
		delete [] mColPermutations;
	}
}

Matrix 
Matrix::EYE(int m, int n)
{
	assert( m>0 && n>0 );
	Matrix I(m,n);
	I.setAllElements(0.0);
	for(int i=0; i<std::min(m,n); i++) {
		I.elem(i,i) = 1.0;
	}
	return I;
}

Matrix 
Matrix::NEGEYE(int m, int n)
{
	assert( m>0 && n>0 );
	Matrix NI(m,n);
	NI.setAllElements(0.0);
	for(int i=0; i<std::min(m,n); i++) {
		NI.elem(i,i) = -1.0;
	}
	return NI;
}

Matrix 
Matrix::ZEROES(int m, int n)
{
	assert( m>0 && n>0 );
	Matrix Z(m,n);
	Z.setAllElements(0.0);
	return Z;
}

Matrix 
Matrix::PERMUTATION(int n, int *jpvt)
{
	assert(n>0);
	Matrix P(n,n);
	P.setAllElements(0.0);
	for (int c=0; c<n; c++) {
		assert (jpvt[c] > 0 && jpvt[c] <= n);
		P.elem(c, jpvt[c]-1) = 1.0;
	}
	return P;
}

Matrix
Matrix::ROTATION(const mat3 &rot)
{
	Matrix R(3,3);
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			R.elem(i,j) = rot.element(j,i);
		}
	}
	return R;
}

Matrix 
Matrix::BLOCKCOLUMN(std::list<Matrix*> *blocks)
{
	int numRows = 0;
	std::list<Matrix*>::iterator it;
	int numCols = 0;
	for(it=blocks->begin(); it!=blocks->end(); it++) {
		numRows += (*it)->rows();
		if ( (*it)->rows() ) {
			if (numCols == 0) {
				numCols = (*it)->cols();
			} else {
				assert((*it)->cols() == numCols);
			}
		}
	}
	if (!numRows) return Matrix(0, 0);
	Matrix C(numRows, numCols);
	numRows  = 0;
	for(it=blocks->begin(); it!=blocks->end(); it++) {
		if (!(*it)->rows()) continue;
		C.copySubMatrix(numRows, 0, *(*it));
		numRows += (*it)->rows();
	}
	return C;
}

Matrix 
Matrix::BLOCKCOLUMN(const Matrix &M1, const Matrix &M2)
{
	assert(M1.cols() == M2.cols());
	Matrix M(M1.rows() + M2.rows(), M1.cols());
	M.copySubMatrix(0, 0, M1);
	M.copySubMatrix(M1.rows(), 0, M2);
	return M;
}


Matrix 
Matrix::BLOCKROW(std::list<Matrix*> *blocks)
{
	int numCols = 0;
	std::list<Matrix*>::iterator it;
	int numRows = 0;
	for(it=blocks->begin(); it!=blocks->end(); it++) {
		numCols += (*it)->cols();
		if ( (*it)->cols() ) {
			if (numRows == 0) {
				numRows = (*it)->rows();
			} else {
				assert((*it)->rows() == numRows);
			}
		}
	}
	if (!numCols) return Matrix(0, 0);
	Matrix C(numRows, numCols);
	numCols  = 0;
	for(it=blocks->begin(); it!=blocks->end(); it++) {
		if (!(*it)->cols()) continue;
		C.copySubMatrix(0, numCols, *(*it));
		numCols += (*it)->cols();
	}
	return C;
}

Matrix 
Matrix::BLOCKROW(const Matrix &M1, const Matrix &M2)
{
	assert(M1.rows() == M2.rows());
	Matrix M(M1.rows(), M1.cols() + M2.cols());
	M.copySubMatrix(0, 0, M1);
	M.copySubMatrix(0, M1.cols(), M2);
	return M;
}

Matrix 
Matrix::BLOCKDIAG(std::list<Matrix*> *blocks)
{
	int numRows=0, numCols=0;
	std::list<Matrix*>::iterator it;
	for(it=blocks->begin(); it!=blocks->end(); it++) {
		numRows += (*it)->rows();
		numCols += (*it)->cols();
	}
	if (!numRows || !numCols) return Matrix(numRows, numCols);
	Matrix B(ZEROES(numRows, numCols));
	numRows = numCols = 0;
	for(it=blocks->begin(); it!=blocks->end(); it++) {
		if (!(*it)->rows() || !(*it)->cols()) continue;
		B.copySubMatrix(numRows, numCols, *(*it));
		numRows += (*it)->rows();
		numCols += (*it)->cols();
	}
	return B;
}

Matrix 
Matrix::BLOCKDIAG(const Matrix &M1, const Matrix &M2)
{
	Matrix M( ZEROES(M1.rows() + M2.rows(), M1.cols() + M2.cols()) );
	M.copySubMatrix(0, 0, M1);
	M.copySubMatrix(M1.rows(), M1.cols(), M2);
	return M;
}

Matrix 
Matrix::MAX_VECTOR(int rows)
{
	Matrix v(rows, 1);
	v.setAllElements(std::numeric_limits<double>::max());
	return v;
}

Matrix 
Matrix::MIN_VECTOR(int rows)
{
	Matrix v(rows, 1);
	v.setAllElements(std::numeric_limits<double>::min());
	return v;
}

/*!
	| cos(theta) -sin(theta) |
	| sin(theta)  cos(theta) |
*/
Matrix 
Matrix::ROTATION2D(double theta)
{
	Matrix R(2,2);
	R.elem(0,0) = cos(theta); R.elem(0,1) = -sin(theta);
	R.elem(1,0) = sin(theta); R.elem(1,1) =  cos(theta);
	return R;
}

void 
Matrix::setFromColMajor(const double *M)
{
	assert(mRows);
	memcpy(mData, M, mRows*mCols*sizeof(double));
}

void 
Matrix::setFromRowMajor(const double *M)
{
	assert(mRows);
	for(int row = 0; row<mRows; row++) {
		for(int col = 0; col<mCols; col++) {
			elem(row, col) = M[row*mCols + col];
		}
	}
}

void 
Matrix::getData(std::vector<double> *data) const
{
	data->resize(mRows * mCols, 0.0);
	memcpy( &((*data)[0]), mData, mRows*mCols*sizeof(double) );
}

int
Matrix::rank() const
{
	int size = std::min(mRows, mCols); 
	double *sv = new double[size];
	int lwork = 5 * std::max(mRows, mCols);
	double *work = new double[lwork];
	int info;
	//idiotic LAPACK destroys the content of the query matrix so we have
	//to copy it first. At least we can make this const now
	double *data = new double[mRows*mCols];
	memcpy(data, mData, mRows*mCols*sizeof(double));
	dgesvd("N", "N", mRows, mCols, data, mRows, sv, 
		   NULL, 1, NULL, 1, work, lwork, &info);
	if (info) {
		DBGA("Rank computation failed with info " << info);
	}
	int rank = 0;
	for (int i=0; i<size; i++) {
		//DBGA("SV " << i << ": " << sv[i]);
		if ( sv[i] > EPS ) rank++;
	}
	delete [] sv;
	delete [] work;
	delete [] data;
	return rank;
}

double
Matrix::fnorm() const
{
	double norm = 0.0;
	for (int r=0; r<mRows; r++) {
		for(int c=0; c<mCols; c++) {
			norm += elem(r,c) * elem(r,c);
		}
	}
	return sqrt(norm);
}

double
Matrix::absMax() const
{
	double max = fabs(elem(0,0));
	double m;
	for (int r=0; r<mRows; r++) {
		for(int c=0; c<mCols; c++) {
			m = fabs(elem(r,c));
			if (m>max) max = m;
		}
	}
	return max;
}

double
Matrix::elementSum() const
{
	double sum=0.0;
	for (int r=0; r<mRows; r++) {
		for(int c=0; c<mCols; c++) {
			sum += elem(r,c);
		}
	}
	return sum;
}

Matrix
Matrix::getColumn(int c) const
{
	assert(c<mCols);
	double *colPointer = mData + c * mRows;
	return Matrix(colPointer, mRows, 1, true);
}

Matrix
Matrix::getRow(int r) const
{
	assert(r<mRows);
	Matrix row(1, mCols);
	for(int i=0; i<mCols; i++) {
		row.elem(0,i) = elem(r,i);
	}
	return row;
}

Matrix 
Matrix::getSubMatrix(int startRow, int startCol, int rows, int cols) const
{
	assert(rows>0 && cols>0);
	assert(startRow+rows <= mRows && startCol+cols <= mCols);
	Matrix M(rows, cols);
	M.copySubBlock(0, 0, rows, cols, *this, startRow, startCol);
	return M;
}

void Matrix::setAllElements(double val) {
	//will be done with blas soon
	for(int row = 0; row<mRows; row++) {
		for(int col = 0; col<mCols; col++) {
			elem(row, col) = val;
		}
	}
}

void Matrix::copySubBlock(int startRow, int startCol, int rows, int cols, 
					      const Matrix &m, int startMRow, int startMCol)
{
	assert(startMRow + rows <= m.rows());
	assert(startMCol + cols <= m.cols());
	assert(startRow + rows <= mRows);
	assert(startCol + cols <= mCols);
	for (int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			elem(startRow+r, startCol+c) = m.elem(startMRow+r, startMCol+c);
		}
	}
}


std::ostream &
operator<<(std::ostream &os, const Matrix &m)
{
	for (int row = 0; row<m.mRows; row++) {
		for(int col = 0; col<m.mCols; col++) {
			os << m.elem(row, col) << " ";
		}
		os << std::endl;
	}
	return os;
}

void Matrix::print(FILE *fp) const 
{
	disp_mat(fp, mData, mRows, mCols, 0);
}

void
Matrix::swapCols(int c1, int c2) 
{
	for (int r=0; r<mRows; r++) {
		std::swap( elem(r,c1), elem(r,c2) );
	}
	std::swap(mColPermutations[c1], mColPermutations[c2]);
}

void
Matrix::swapRows(int r1, int r2) 
{
	for (int c=0; c<mCols; c++) {
		std::swap( elem(r1,c), elem(r2,c) );
	}
	std::swap(mRowPermutations[r1], mRowPermutations[r2]);
}

void
Matrix::transpose()
{
	//for now we don't do it in place
	assert(mRows);
	std::swap(mRows, mCols);
	//idiot programmer forgot about permutations
	std::swap(mRowPermutations, mColPermutations);
	double *oldData = mData;
	mData = new double[mRows * mCols];
	for (int r=0; r<mRows; r++) {
		for (int c=0; c<mCols; c++) {
			elem(r,c) = oldData[r*mCols + c];
		}
	}
	delete [] oldData;
}

void 
Matrix::eye()
{
	for (int r=0; r<mRows; r++) {
		for (int c=0; c<mCols; c++) {
			if (r==c) {
				elem(r,c) = 1.0;
			} else {
				elem(r,c) = 0.0;
			}
		}
	}
}

void
Matrix::multiply(double s)
{
	for (int r=0; r<mRows; r++) {
		for (int c=0; c<mCols; c++) {
			elem(r,c) *= s;
		}
	}
}

Matrix Matrix::transposed() const
{
	Matrix t(*this);
	t.transpose();
	return t;
}

void 
matrixMultiply(const Matrix &L, const Matrix &R, Matrix &M)
{
	assert( L.cols() == R.rows() );
	assert( L.rows() == M.rows() );
	assert( R.cols() == M.cols() );
	assert( L.cols() );
	/*
    //WARNING: Lapack does not use const-correctness
    //You will need to make temporary copies in memory to use the Lapack version
	double *tmpData = new double[M.rows() * M.cols()];
	dgemm("N", "N", L.rows(), R.cols(), L.cols(),
		1.0, L.getData(), L.rows(),
		R.getData(), R.rows(),
		0.0, tmpData, M.rows());
	memcpy(M.getData(), tmpData, M.rows() * M.cols() * sizeof(double));
	delete [] tmpData;
	*/
	//LAPACK IS NOT THREAD-SAFE!!!
	//Explicit version here. If not using threads, just use Lapack version above.
	for (int i=0; i<M.rows(); i++) {
		for (int j=0; j<M.cols(); j++) {
			double m = 0;
			for (int k=0; k<L.cols(); k++) {
				m += L.elem(i,k) * R.elem(k,j);
			}
			M.elem(i,j) = m;
		}
	}
}

void
matrixAdd(const Matrix &L, const Matrix &R, Matrix &M)
{
	assert( L.rows()==R.rows() && L.rows()==M.rows() );
	assert( L.cols()==R.cols() && L.cols()==M.cols() );
	for (int r=0; r<L.rows(); r++) {
		for(int c=0; c<L.cols(); c++) {
			M.elem(r,c) = L.elem(r,c) + R.elem(r,c);
		}
	}
}

bool 
matrixEqual(const Matrix &R, const Matrix &L)
{
	assert (R.rows() == L.rows() && R.cols() == L.cols());
	Matrix minL(L);
	minL.multiply(-1.0);
	matrixAdd(R, minL, minL);
	double norm = minL.fnorm();
	if (norm < Matrix::EPS) {
		return true;
	}
	return false;
}

int
triangularSolve(Matrix &A, Matrix &B)
{
	assert(A.rows());
	assert(A.rows() == A.cols());
	assert(A.rows() == B.rows());
	int info;
	int *ipiv = new int[A.rows()];
	dgesv(A.rows(), B.cols(), A.getData(), A.rows(),ipiv, 
		  B.getData(), B.rows(), &info);
	delete [] ipiv;
	return info;
}

int 
underDeterminedSolveMPInv(Matrix &A, Matrix &B, Matrix &X)
{
	assert( X.rows() == A.cols() );
	assert( X.cols() == B.cols() );

	//prepare square system with pseudo-inverse
	Matrix ATran(A.transposed());
	Matrix ASq(A.cols(), A.cols());
	matrixMultiply(ATran, A, ASq);
	Matrix ATB(A.cols(), B.cols());
	matrixMultiply(ATran, B, ATB);

	//just for debug, rank of left-hand side
	int rank = ASq.rank();
	if (rank < A.cols()) {
		//for some reason, this does not always matter!
		DBGA("Undet solve w. MPI: rank-deficient lhs with rank " << rank);
	}

	//solve the triangular system
	int info = triangularSolve(ASq, ATB);

	//copy the results into X
	X.copyMatrix(ATB);
	return info;
}

int 
underDeterminedSolveSVD(Matrix &A, Matrix &B, Matrix &X)
{
	assert( X.rows() == A.cols() );
	assert( X.cols() == B.cols() );

	//for now. Is this general enough to handle all cases?
	assert(A.rows() < A.cols());

	int info;
	double *data = new double[A.rows() * A.cols() ];
	memcpy(data, A.getData(), A.rows() * A.cols() * sizeof(double));
	/*
	//factorization - LAPACK doesn't seem to want to use for solving as well
	int *ipiv = new int[std::min(A.rows(), A.cols())];
	dgetrf(A.rows(), A.cols(), data, A.rows(), ipiv, &info);
	delete [] ipiv;
	*/

	//use SVD - as in Golub & Van Loan, Matrix Computations, 1st ed., Sec. 6.7
	int minSize = std::min(A.rows(), A.cols());
	int maxSize = std::max(A.rows(), A.cols());
	Matrix S(minSize, 1);
	Matrix U(A.rows(), A.cols());
	Matrix VT(A.cols(), A.cols());
	int lwork = 5 * maxSize;
	double *work = new double[lwork];
	dgesvd("A", "A", A.rows(), A.cols(), data, A.rows(), S.getData(), 
		   U.getData(), A.rows(), VT.getData(), A.cols(), 
		   work, lwork, &info);
	delete [] work;
	delete [] data; 

	if (info) {
		DBGA("SVD decomposition failed with code " << info);
		return info;
	}

	//accumulate solutions
	int result = 0;
	for (int c=0; c<B.cols(); c++) {
		Matrix x(Matrix::ZEROES(A.cols(),1));
		for (int r=0; r<minSize; r++) {
			Matrix utb(1,1);
			matrixMultiply( U.getColumn(r).transposed(), B.getColumn(c), utb );
			if (S.elem(r,0) < Matrix::EPS) {
				DBGA("Rank deficient matrix in underDeterminedSolve:");
				if (fabs(utb.elem(0,0)) > Matrix::EPS) {
					DBGA("... system has no solution " << utb.elem(0,0));
					if (!result) result = r;
					continue;
				} else {
					//I *think* in this case we are no longer returning min norm solution!!
					DBGA("...but system still has solution.");
				}
			}
			utb.multiply( 1.0 / S.elem(r,0) );
			Matrix utbv(1, A.cols());
			//VT is transposed, so it's r-th row is the r-th singular vector
			matrixMultiply( utb, VT.getRow(r), utbv);
			matrixAdd(x, utbv.transposed(), x);
		}
		X.copySubMatrix(0, c, x);
	}
	return result;
}

int underDeterminedSolveQR(Matrix &A, Matrix &B, Matrix &X)
{
	//use QR factorization - as in Golub & Van Loan, Matrix Computations 1st ed., Sec. 6.7

	assert( X.rows() == A.cols() );
	assert( X.cols() == B.cols() );
	//for now we can not handle overdetermined systems (due at least to dorgqr)
//	assert( A.rows() <= A.cols() );
	if (A.rows() > A.cols()) {
		DBGA("Undet QR: system is overdetermined");
		return -1;
	}

	//start by transposing the input
	Matrix ATran(A.transposed());

	int info;
	std::vector<double> data;
	ATran.getData(&data);
	int minSize = ATran.cols();
	std::vector<int> jpvt(ATran.cols(), 0);
	std::vector<double> tau(minSize, 0.0);
	int lwork = (ATran.cols() + 1) * 15;
	std::vector<double> work(lwork, 0.0);

	dgeqp3(ATran.rows(), ATran.cols(), &data[0], ATran.rows(), 
		   &jpvt[0], &tau[0], &work[0], lwork, &info);
	if (info) {
		DBGA("QR Factorization failed, info " << info);
		return -1;
	}

	//build permutation matrix
	Matrix P(Matrix::PERMUTATION(ATran.cols(), &jpvt[0]).transposed());

	//build upper triangular R matrix
	//as we are enforcing ATran.cols() <= ATran.rows(), this is actually square
	Matrix R(Matrix::ZEROES(minSize, ATran.cols()));
	for (int col=0; col<ATran.cols(); col++) {
		for (int row=0; row<std::min(minSize, col+1); row++) {
			//column major
			R.elem(row,col) = data[col*ATran.rows() + row];
		}
	}
	//anything below R.elem(rank,rank) should be zero
	int rank = ATran.rank();
	if (rank < minSize) {
		double fn = R.getSubMatrix(rank, rank, minSize - rank, ATran.cols() - rank).fnorm();
		if (fn > Matrix::EPS) {
			DBGA("Column pivoting fails to produce full rank R11");
			return -1;
		}
	}

	//prepare and solve triangular system
	Matrix R11T(R.getSubMatrix(0,0,rank,rank).transposed());
	Matrix PB(B);
	matrixMultiply(P.transposed(), B, PB);
	Matrix Z( PB.getSubMatrix(0, 0, rank, PB.cols()) );
	dtrtrs("L", "N", "N", rank, Z.cols(), R11T.getData(), rank, Z.getData(), Z.rows(), &info);
	if (info) {
		DBGA("Triangular solve failed in QR solve, info " << info);
		return -1;
	}
	//if the matrix is rank-deficient we need to check if the solution works
	bool success = true;
	if (rank < minSize) {
		Matrix R22T( R.getSubMatrix(0, rank, rank, R.cols()-rank).transposed() );
		Matrix PB22( PB.getSubMatrix(rank, 0, PB.rows() - rank, PB.cols()) );
		Matrix PBtest( PB.rows() - rank, PB.cols() );
		matrixMultiply( R22T, Z, PBtest);
		if (!matrixEqual(PBtest, PB22)) {
			DBGA("System has no solution in QR solve");
			success = false;
		}
	}

	//build Q matrix
	dorgqr(ATran.rows(), ATran.cols(), rank, &data[0], ATran.rows(), 
		   &tau[0], &work[0], lwork, &info);
	if (info) {
		DBGA("Building matrix Q failed, info " << info);
		return -1;
	}
	Matrix Q(&data[0], ATran.rows(), ATran.cols(), true);

	//build complete solution
	Matrix Q1( Q.getSubMatrix(0,0,ATran.rows(), rank) );
	matrixMultiply(Q1, Z, X);
	if (!success) return 1;
	return 0;
}

/*! Inverse is computed with factorization, then triangular solving, both
	from LAPACK. Returns 0 for success, -1 for unknown failure during
	computation and 1 if the matrix A is found to be rank-deficient.
*/
int 
matrixInverse(const Matrix &A, Matrix &AInv)
{
	//only for square matrices
	assert(A.rows() == A.cols());
	assert(AInv.rows() == AInv.cols());
	assert(A.rows() == AInv.rows());
	int size = A.rows() * A.cols();
	std::vector<double> data(size,0.0);
	A.getData(&data);
	std::vector<int> ipiv(A.rows(),0);
	int info;
	dgetrf(A.rows(), A.cols(), &data[0], A.rows(), &ipiv[0], &info);
	if (info < 0) {
		DBGA("Inverse failed at factorization, info " << info);
		return -1;
	} else if (info > 0) {
		DBGA("Inverse of rank-deficient matrix requested");
		return 1;
	}
	int lwork = size;
	std::vector<double> work(lwork, 0.0);
	dgetri(A.rows(), &data[0], A.rows(), &ipiv[0], &work[0], lwork, &info);
	if (info < 0) {
		DBGA("Inverse failed, info " << info);
		return -1;
	} else if (info > 0) {
		DBGA("Inverse of rank-deficient matrix requested...");
		return 1;
	}
	AInv.copyMatrix(Matrix(&data[0], A.rows(), A.cols(), true));
	return 0;
}

/*! Solves a quadratic program of the form:
	minimize solT * Q * sol subject to:
	Q symmetric and positive semidefinite
	Eq * sol = b
	InEq * sol <= ib
	lowerBounds(i) <= sol(i) <= upperBounds(i)
	use std::numeric_limits<double>::max() or min() for unbounded variables

	Return codes:
	0 - success
	> 0 - problem is unfeasible
	< 0 - error in computation
*/
int QPSolver(const Matrix &Q, const Matrix &Eq, const Matrix &b,
			 const Matrix &InEq, const Matrix &ib, 
	  		 const Matrix &lowerBounds, const Matrix &upperBounds,
			 Matrix &sol, double* objVal)
{
	if (Eq.rows()) {
		assert( Eq.cols() == sol.rows() );
		assert( Eq.rows() == b.rows() );
	}
	if (InEq.rows()) {
		assert( InEq.cols() == sol.rows() );
		assert( InEq.rows() == ib.rows() );
	}
	assert( Q.rows() == Q.cols() );
	assert( Q.rows() == sol.rows() );
	assert( sol.cols() == 1 );
	assert(lowerBounds.rows() == sol.rows());
	assert(upperBounds.rows() == sol.rows());
	assert(lowerBounds.cols() == 1);
	assert(upperBounds.cols() == 1);

#ifdef MOSEK_QP
	int result = mosekNNSolverWrapper(Q, Eq, b, InEq, ib, 
									  lowerBounds, upperBounds, sol, 
									  objVal, MOSEK_OBJ_QP);
#else
	int result = 0;
	DBGA("No QP Solver installed");
	return 0;
#endif

	return result;
}

/*! Solves a quadratic program of the form:
	minimize solT * QfT * Qf * sol subject to:
	Eq * sol = b
	InEq * sol <= ib
	lowerBounds(i) <= sol(i) <= upperBounds(i)
	use std::numeric_limits<double>::max() or min() for unbounded variables
	This is just a transformed version of the general problem above.
	See Mosek documentation Sec. 7.3.2 for details.
*/
int factorizedQPSolver(const Matrix &Qf, 
					   const Matrix &Eq, const Matrix &b,
					   const Matrix &InEq, const Matrix &ib,
			  		   const Matrix &lowerBounds, const Matrix &upperBounds,
					   Matrix &sol, double *objVal)
{
	if (Eq.rows()) {
		assert( Eq.cols() == sol.rows() );
		assert( Eq.rows() == b.rows() );
	}
	if (InEq.rows()) {
		assert( InEq.cols() == sol.rows() );
		assert( InEq.rows() == ib.rows() );
	}
	assert( Qf.cols() == sol.rows() );
	assert( sol.cols() == 1 );
	assert(lowerBounds.rows() == sol.rows());
	assert(upperBounds.rows() == sol.rows());
	assert(lowerBounds.cols() == 1);
	assert(upperBounds.cols() == 1);

	//new unknown matrix: [x y]
	int numVar = sol.rows() + Qf.rows();
	Matrix xy(numVar, 1);

	//append zeroes to InEq matrix
	Matrix ExtInEq(Matrix::ZEROES(InEq.rows(), numVar));
	ExtInEq.copySubMatrix(0, 0, InEq);
	//extend equality matrix with zeroes and new constraints Fx-y=0
	Matrix ExtEq(Matrix::ZEROES(Eq.rows() + Qf.rows(), numVar));
	ExtEq.copySubMatrix(0, 0, Eq);
	ExtEq.copySubMatrix(Eq.rows(), 0, Qf);
	Matrix NI(Matrix::EYE(Qf.rows(), Qf.rows()));
	NI.multiply(-1.0);
	ExtEq.copySubMatrix(Eq.rows(), Eq.cols(), NI);
	//extend b matrix with zeroes
	Matrix extB(Matrix::ZEROES(b.rows()+Qf.rows(),1));
	extB.copySubMatrix(0, 0, b);
	//Q Matrix is 0 for the old variables and identity for the new ones
	Matrix ExtQ(Matrix::ZEROES(numVar, numVar));
	ExtQ.copySubMatrix(sol.rows(), sol.rows(), Matrix::EYE(Qf.rows(), Qf.rows()));

	//extended bounds. New variables are unbounded
	Matrix extLow(Matrix::MIN_VECTOR(numVar));
	extLow.copySubMatrix(0, 0, lowerBounds);
	Matrix extUp(Matrix::MAX_VECTOR(numVar));
	extUp.copySubMatrix(0, 0, upperBounds);

	int result = QPSolver(ExtQ, ExtEq, extB, ExtInEq, ib, extLow, extUp, xy, objVal);
	//copy the relevant solution
	sol.copySubBlock(0, 0, sol.rows(), 1, xy, 0, 0);

	return result;
}


void testQP()
{
	Matrix Eq(Matrix::ZEROES(2,2));
	Matrix b(Matrix::ZEROES(2,1));

	Matrix InEq(2,2);
	Matrix ib(2,1);
	InEq.elem(0,0) = 1; InEq.elem(0,1) = 1; ib.elem(0,0) = 7;
	InEq.elem(1,0) = -1; InEq.elem(1,1) = 2; ib.elem(1,0) = -4;

	Matrix Q(Matrix::ZEROES(2,2));
	Q.elem(0,0) = 1; Q.elem(1,1) = 4;

	Matrix sol(2,1);
	Matrix lowerBounds(Matrix::MIN_VECTOR(2));
	Matrix upperBounds(Matrix::MAX_VECTOR(2));
	double objVal;
#ifdef MOSEK_QP
	mosekNNSolverWrapper(Q, Eq, b, InEq, ib, sol, lowerBounds, upperBounds, &objVal, MOSEK_OBJ_QP);
#else
	DBGA("No QP solver installed");
#endif
}

/*! Solves a linear program of the form:
	minimize Q * sol subject to:
	Eq * sol = b
	InEq * sol <= ib
	lowerBounds(i) <= sol(i) <= upperBounds(i)
	use std::numeric_limits<double>::max() or min() for unbounded variables

	Return codes:
	0 - success
	> 0 - problem is unfeasible
	< 0 - error in computation
*/
int 
LPSolver(const Matrix &Q,
		 const Matrix &Eq, const Matrix &b,
		 const Matrix &InEq, const Matrix &ib,
 		 const Matrix &lowerBounds, const Matrix &upperBounds,
		 Matrix &sol, double* objVal)
{
	assert(sol.cols() == 1);
	assert(Q.cols() == sol.rows());
	assert(Q.rows() == 1);
	if (Eq.rows()) {
		assert(Eq.cols() == sol.rows());
		assert(Eq.rows() == b.rows());
	}
	if (InEq.rows()) {
		assert(InEq.cols() == sol.rows());
		assert(InEq.rows() == ib.rows());
	}
	assert(lowerBounds.rows() == sol.rows());
	assert(upperBounds.rows() == sol.rows());
	assert(lowerBounds.cols() == 1);
	assert(upperBounds.cols() == 1);

#ifdef MOSEK_QP
	int result = mosekNNSolverWrapper(Q, Eq, b, InEq, ib, 
									  lowerBounds, upperBounds, sol, objVal, MOSEK_OBJ_LP);
#else
	int result = 0;
	DBGA("No QP Solver installed");
	return result;
#endif

	return result;
}

/*! Test for a linear program:
	| 1  1 -1  0| |x1|   |0|
	| 3 -1  0  0| |x2| = |0|
	| 0  1  0 -1| |x3| = |0|
				  |x4|

	x2 = 3*x1
	x3 = 4*x1
	x2 = x4

	minimize:
	| 1 -1 -1 1| |x1|
				 |x2|
				 |x3|
				 |x4|
	minimize x1 - x2 - x3 - x4 = -6*x1 + x4

	x1 <= 5
*/

void
testLP()
{
	Matrix Eq(Matrix::ZEROES(3,4));
	Matrix b(Matrix::ZEROES(3,1));

	Eq.elem(0,0) = Eq.elem(0,1) = 1.0; Eq.elem(0,2) = -1.0;
	Eq.elem(1,0) = 3.0; Eq.elem(1,1) = -1.0;
	Eq.elem(2,1) = 1.0; Eq.elem(2,3) = -1.0;

	Matrix Obj(1,4);
	Obj.elem(0,0) = 1.0; Obj.elem(0,1) = Obj.elem(0,2) = -1.0; Obj.elem(0,3) = -1.0;

	Matrix InEq(Matrix::ZEROES(1,4));
	InEq.elem(0,0) = 1.0;
	Matrix ib(1,1);
	ib.elem(0,0) = 5.0;

	Matrix x(4,1);

	Matrix low(Matrix::MIN_VECTOR(4));
	Matrix high(Matrix::MAX_VECTOR(4));

#ifdef MOSEK_QP
	double obj;
	int result = mosekNNSolverWrapper(Obj, Eq, b, InEq, ib, x, low, high, &obj, MOSEK_OBJ_LP);
	if (result > 0) {
		DBGA("Test failed: program unfeasible");
	} else if (result < 0) {
		DBGA("Test failed: error in computation");
	} else {
		DBGA("Test minimum: " << obj);
		DBGA("Solution:\n" << x);
	}
#endif
}
