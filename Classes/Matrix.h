#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Fraction.h"

#include <vector>
#include <string>
#include <utility>

using std::vector;
using std::string;
using std::pair;

typedef vector<Fraction>         vF;
typedef vector<vector<Fraction>> v_vF;

class Matrix {
public:
// Operator overloading.
	friend Matrix operator+ (const Matrix&, const Matrix&);
	friend Matrix operator+= (Matrix&, const Matrix&);
	friend Matrix operator- (const Matrix&, const Matrix&);
	friend Matrix operator-= (Matrix&, const Matrix&);
	friend Matrix operator* (const Matrix&, const Matrix&);
	friend Matrix operator*= (Matrix&, const Matrix&);
	friend bool operator== (const Matrix&, const Matrix&);
	friend bool operator!= (const Matrix&, const Matrix&);
	friend std::ostream& operator<< (std::ostream&, const Matrix&);
	friend std::istream& operator>> (std::istream&, Matrix&);

public:
	Matrix() = default;

	// Determine the size of the matrix,default value is zero.
	Matrix(size_t temp_row, size_t temp_col) :row(temp_row), col(temp_col) {
		matrix.resize(row);
		for(auto &i : matrix) {
			i.resize(col);
		}
	}

	Matrix(size_t temp_row, size_t temp_col, v_vF temp_m) :row(temp_row), col(temp_col), matrix(temp_m) { }

	// Copy constructor.
	Matrix(const Matrix &rhs) {
		this->row = rhs.row;
		this->col = rhs.col;
		this->matrix = rhs.matrix;
	}

	// Copy-assignment operator.
	Matrix & operator=(const Matrix &rhs) {
		if (this != &rhs) {
			this->row = rhs.row;
			this->col = rhs.col;
			this->matrix = rhs.matrix;

			return *this;
		}
		else {
			return *this;
		}
	}

	~Matrix() = default;
	// Show matrix.
	v_vF matrix_out() const;
	// Using v_vF to create a Matrix. 
	void matrix_getin(v_vF &);
	// Output Matrix.
	string cout_out() const;
	// Temporary output.
	string cout_temp_addition_for_transmission() const;
	// Input Matrix.
	void cin_in(string &);
	// Reset matrix size. 
	void resize(const size_t &, const size_t &);
	// Add a line.
	void add_row(const size_t &, const vF &);
	// One row of the matrix is multiplied by K,it means matrix is multiplied by K.
	void add_to_other_row(const size_t &, const Fraction &);
	// One row of the matrix is multiplied by K and added to the other line.
	void add_to_other_row(const size_t &, const size_t &, const Fraction &);
	// Swap two roes.
	void swap_row(const size_t &, const size_t &);
	// Minus one line.
	void del_row(const size_t &);
	// Add a column.
	void add_col(const size_t &, const vF &);
	// One column of the matrix is multiplied by K,it means matrix is multiplied by K.
	void add_to_other_col(const size_t &, const Fraction &);
	// One column of the matrix is multiplied by K and added to the other column.
	void add_to_other_col(const size_t &, const size_t &, const Fraction &);
	// Minus one column.
	void del_col(const size_t &);
	// Swap two cols.
	void swap_col(const size_t &, const size_t &);
	// Transpose a matrix.
	Matrix trans();
	// Check whether the square. 
	bool square() const;
	// LU Decomposition.
	pair<v_vF, v_vF> LUdcmp() const;
	// Determinant of  a matrix.
	Fraction det() const;
	// Inverse of matrix.
	Matrix inverse() const;
	// Solution of linear algebraic equation.
	vF solution(vF &);

private:
	size_t row = 0;
	size_t col = 0;
	v_vF   matrix;
};

#endif
