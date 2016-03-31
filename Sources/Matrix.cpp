#include "Matrix.h"
#include "Fraction.h"
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using std::vector;
using std::string;
using std::endl;
using std::runtime_error;
using std::ostringstream;
using std::istringstream;

typedef vector<Fraction>         vF;
typedef vector<vector<Fraction>> v_vF;

// Operator overloading.
Matrix operator+ (const Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;
	if (temp_m1.row == temp_m2.row && temp_m1.col == temp_m2.col)                           // First judge M1 and M2 matrix are not the same type of matrix.
	{
		temp_m3.resize(temp_m1.row, temp_m1.col);
		for (size_t i = 0; i < temp_m1.row; ++i)
		{
			for (size_t j = 0; j < temp_m1.col; ++j)
			{
				temp_m3.matrix[i][j] = temp_m1.matrix[i][j] + temp_m2.matrix[i][j];
			}
		}
	}
	else
	{
		throw runtime_error("Rows and columns are not equal.");
	}

	return temp_m3;
}

Matrix operator+= (Matrix &temp_m1, const Matrix &temp_m2) {
	if (temp_m1.row == temp_m2.row && temp_m1.col == temp_m2.col)
	{
		for (size_t i = 0; i < temp_m1.row; ++i)
		{
			for (size_t j = 0; j < temp_m1.col; ++j)
			{
				temp_m1.matrix[i][j] += temp_m2.matrix[i][j];
			}
		}
	}
	else
	{
		throw runtime_error("Rows and columns are not equal.");
	}

	return temp_m1;
}

Matrix operator- (const Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;
	if (temp_m1.row == temp_m2.row && temp_m1.col == temp_m2.col)
	{
		temp_m3.resize(temp_m1.row, temp_m1.col);
		for (size_t i = 0; i < temp_m1.row; ++i)
		{
			for (size_t j = 0; j < temp_m1.col; ++j)
			{
				temp_m3.matrix[i][j] = temp_m1.matrix[i][j] - temp_m2.matrix[i][j];
			}
		}
	}
	else
	{
		throw runtime_error("Rows and columns are not equal.");
	}

	return temp_m3;
}

Matrix operator-= (Matrix &temp_m1, const Matrix &temp_m2) {
	if (temp_m1.row == temp_m2.row && temp_m1.col == temp_m2.col)
	{
		for (size_t i = 0; i < temp_m1.row; ++i)
		{
			for (size_t j = 0; j < temp_m1.col; ++j)
			{
				temp_m1.matrix[i][j] -= temp_m2.matrix[i][j];
			}
		}
	}
	else
	{
		throw runtime_error("Rows and columns are not equal.");
	}

	return temp_m1;
}

Matrix operator* (const Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;
	if (temp_m1.col == temp_m2.row)                                                         // The number of columns in the first matrix M1 is equal to the number of rows in a matrix m2. 
	{
		temp_m3.resize(temp_m1.row, temp_m2.col);
		for (size_t i = 0; i < temp_m1.row; ++i)
		{
			for (size_t j = 0; j < temp_m2.col; ++j)
			{
				for (size_t m = 0; m < temp_m1.col; ++m)
					temp_m3.matrix[i][j] *= temp_m1.matrix[i][m] * temp_m2.matrix[m][j];
			}
		}
	}
	else
	{
		throw runtime_error("temp_m1's col and temp_m2's row are not equal.");
	}

	return temp_m3;
}

Matrix operator*= (Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;
	if (temp_m1.col == temp_m2.row)
	{
		temp_m3.resize(temp_m1.row, temp_m2.col);
		for (size_t i = 0; i < temp_m1.row; ++i)
		{
			for (size_t j = 0; j < temp_m2.col; ++j)
			{
				for (size_t m = 0; m < temp_m1.col; ++m)
					temp_m3.matrix[i][j] *= temp_m1.matrix[i][m] * temp_m2.matrix[m][j];
			}
		}
	}
	else
	{
		throw runtime_error("temp_m1's col and temp_m2's row are not equal.");
	}

	temp_m1 = temp_m3;
	return temp_m1;
}

bool operator== (const Matrix &temp_m1, const Matrix &temp_m2) {
	if (temp_m1.row != temp_m2.row || temp_m1.col != temp_m2.col) {
		return false;
	}
	for (size_t i = 0; i < temp_m1.row; ++i) {
		for (size_t j = 0; j < temp_m2.col; ++j) {
			if (temp_m1.matrix[i][j] != temp_m2.matrix[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool operator!= (const Matrix &temp_m1, const Matrix &temp_m2) {
	return !(temp_m1 == temp_m2);
}

std::ostream& operator<< (std::ostream &out, const Matrix &temp_m) {
	out << " { " << endl;
	for (size_t i = 0; i < temp_m.row; ++i) {
		for (size_t j = 0; j < temp_m.col; ++j) {
			if (j == (temp_m.col - 1)) {
				out << temp_m.matrix[i][j] << endl;
			}
			else if (j == 0) {
				out << "   " << temp_m.matrix[i][j] << " , ";
			}
			else {
				out << temp_m.matrix[i][j] << " , ";
			}
		}
	}
	out << " } " << endl;
	return out;
}

std::istream& operator>> (std::istream &in, Matrix &temp_m) {
	in >> temp_m.row;
	in >> temp_m.col;
	temp_m.matrix.resize(temp_m.row);
	for (auto &i : temp_m.matrix) {
		i.resize(temp_m.col);
	}
	for (auto &i : temp_m.matrix) {
		for (auto &j : i) {
			in >> j;
		}
	}
	return in;
}

void Matrix::resize(const size_t &temp_row, const size_t &temp_col){                        // Reset matrix size.
	row = temp_row;
	col = temp_col;
	matrix.resize(row);
	for (auto &i : matrix) {
		i.resize(col);
	}
}

void Matrix::add_row(size_t &temp_row, vF &temp_vcow) {                                     // Add a row.
	if (temp_row >= (row + 1) || temp_row < 0) {
		throw runtime_error("Row is out of bound.");
	}
	v_vF temp_vvF;
	temp_vvF.resize(row + 1);
	for (auto &i : temp_vvF) {
		i.resize(col);
	}
	for (size_t i = 0; i < temp_row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t j = 0; j < col; ++j) {
		temp_vvF[temp_row][j] = temp_vcow[j];
	}
	for (size_t i = temp_row + 1, ii = temp_row; ii < row; ++i, ++ii) {
		for (size_t j = 0; j < col; ++j) {
			temp_vvF[i][j] = matrix[ii][j];
		}
	}
	matrix = temp_vvF;
	++row;
}

void Matrix::add_to_other_row(size_t &temp_row, Fraction &F) {                              // One row of the matrix is multiplied by K,it means matrix is multiplied by K.
	for (size_t i = 0; i < col; ++i) {
		matrix[temp_row][i] += (F*matrix[temp_row][i]);
	}
}

void Matrix::add_to_other_row(size_t &temp_row1, size_t &temp_row2, Fraction &F) {         // One row of the matrix is multiplied by K and added to the other row.
	if (temp_row1 != temp_row2) {
		for (size_t i = 0; i < col; ++i) {
			matrix[temp_row2][i] += (F*matrix[temp_row1][i]);
		}
	}
	else {
		throw runtime_error("The same of two rows.");
	}
}

void Matrix::swap_row(size_t &temp_row1, size_t &temp_row2) {                             // Swap two rows;
	if (temp_row1 != temp_row2) {
		vF temp_vrow;
		temp_vrow.resize(col);
		for (size_t i = 0; i < col; ++i) {
			temp_vrow[i] = matrix[temp_row1][i];
		}
		for (size_t i = 0; i < col; ++i) {
			matrix[temp_row1][i] = matrix[temp_row2][i];
		}
		for (size_t i = 0; i < col; ++i) {
			matrix[temp_row2][i] = temp_vrow[i];
		}
	}
	else {
		throw runtime_error("The same of row numbers");
	}
}

void Matrix::del_row(size_t &temp_row) {                                                  // Minus one row.
	v_vF temp_vvF;
	temp_vvF.resize(row - 1);
	for (auto &i : temp_vvF) {
		i.resize(col);
	}
	for (size_t i = 0; i < temp_row; ++i) {
		for (size_t j = 0; j < col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t i = temp_row + 1, ii = temp_row; i < row; ++i, ++ii) {
		for (size_t j = 0; j < col; ++j) {
			temp_vvF[ii][j] = matrix[i][j];
		}
	}
	matrix = temp_vvF;
	--row;
}

void Matrix::add_col(size_t &temp_col, vF &temp_vrow) {                                  // Add a column.
	if (temp_col >= (col + 1) || temp_col < 0) {
		throw runtime_error("Column is out of bounds");
	}
	v_vF temp_vvF;
	temp_vvF.resize(row);
	for (auto &i : temp_vvF) {
		i.resize(col + 1);
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < temp_col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t j = 0; j < row; ++j) {
		temp_vvF[j][temp_col] = temp_vrow[j];
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = temp_col + 1, jj = temp_col; jj < col; ++j, ++jj) {
			temp_vvF[i][j] = matrix[i][jj];
		}
	}
	matrix = temp_vvF;
	++col;
}

void Matrix::add_to_other_col(size_t &temp_col, Fraction &F) {                           // One column of the matrix is multiplied by K,it means matrix is multiplied by K.
	for (size_t i = 0; i < row; ++i) {
		matrix[i][temp_col] += (F*matrix[i][temp_col]);
	}
}

void Matrix::add_to_other_col(size_t &temp_col1, size_t &temp_col2, Fraction &F) {       // One column of the matrix is multiplied by K and added to the other column.
	if (temp_col1 != temp_col2) {
		for (size_t i = 0; i < row; ++i) {
			matrix[i][temp_col2] += (F*matrix[i][temp_col1]);
		}
	}
	else {
		throw runtime_error("The same of two columns.");
	}
}

void Matrix::swap_col(size_t &temp_col1, size_t &temp_col2) {                            // Swap two columns;
	if (temp_col1 != temp_col2) {
		vF temp_vcol;
		temp_vcol.resize(row);
		for (size_t i = 0; i < row; ++i) {
			temp_vcol[i] = matrix[i][temp_col1];
		}
		for (size_t i = 0; i < row; ++i) {
			matrix[i][temp_col1] = matrix[i][temp_col2];
		}
		for (size_t i = 0; i < row; ++i) {
			matrix[i][temp_col2] = temp_vcol[i];
		}
	}
	else {
		throw runtime_error("The same of column numbers");
	}
}

void Matrix::del_col(size_t &temp_col) {                                                 // Minus one column.
	v_vF temp_vvF;
	temp_vvF.resize(row);
	for (auto &i : temp_vvF) {
		i.resize(col - 1);
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = 0; j < temp_col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t i = 0; i < row; ++i) {
		for (size_t j = temp_col + 1, jj = temp_col; j < col; ++j, ++jj) {
			temp_vvF[i][jj] = matrix[i][j];
		}
	}
	matrix = temp_vvF;
	--col;
}

Matrix Matrix::trans() {                                                                 // Transpose a matrix.
	Matrix temp_M;
	if (matrix.empty()) {
		throw runtime_error("The matrix is empty.");
	}
	else {
		temp_M.resize(col, row);
		for (size_t i = 0; i < temp_M.row; ++i) {
			for (size_t j = 0; j < temp_M.col; ++j) {
				temp_M.matrix[i][j] = matrix[j][i];
			}
		}
	}

	return temp_M;
}

string Matrix::cout_out() const{                                                         // Output matrix.
	ostringstream out;
	out << row << " " << col << " ";
	for (auto &i : matrix) {
		for (auto &j : i) {
			out << j << " ";
		}
	}
	return out.str();
}

void Matrix::cin_in(string &temp_str) {                                                 // Input matrix.
	istringstream in(temp_str, istringstream::in);
	in >> row;
	in >> col;
	matrix.resize(row);
	for (auto &i : matrix) {
		i.resize(col);
	}
	for (auto &i : matrix) {
		for (auto &j : i) {
			in >> j;
		}
	}
}

bool Matrix::square() const {                                                           // Check whether the square.
	return (!matrix.empty() && row == col);
}

Fraction Matrix::Frac_abs(Fraction &temp_frac) {                                        // Absolute value of a fraction.
	return (temp_frac >= 0) ? temp_frac : (0 - temp_frac);
}

pair<v_vF, v_vF> Matrix::LUdcmp() {                                                     // LU Decomposition.
	v_vF lu(matrix), u, l;
	if (square()) {
		size_t n(row);
		size_t i, j, k;
		Fraction big, temp;

		l.resize(row);
		u.resize(row);
		for (auto &i : l) {
			i.resize(col);
		}
		for (auto &i : u) {
			i.resize(col);
		}

		for (i = 0; i < n; ++i) {
			big = 0;
			for (j = 0; j < n; ++j) {
				if ((temp = Frac_abs(lu[i][j])) > big) {
					big = temp;
				}
			}
			if (big == 0) {
				throw runtime_error("Singular matrix in LUdcmp");
			}
		}

		for (k = 0; k < n - 1; ++k) {
			for (i = k + 1; i < n; ++i) {
				lu[i][k] = lu[i][k] / lu[k][k];
				for (j = k + 1; j < n; ++j) {
					lu[i][j] -= lu[i][k] * lu[k][j];
				}
			}
		}
		/*
		Matrix lu1;
		lu1.row = row;
		lu1.col = col;
		lu1.matrix = lu;
		std::cout << lu1 << endl;
		*/
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (j < i) {
					u[i][j] = 0;
					l[i][j] = lu[i][j];
				}
				if (j == i) {
					l[i][j] = 1;
					u[i][j] = lu[i][j];
				}
				if (j > i) {
					l[i][j] = 0;
					u[i][j] = lu[i][j];
				}
			}
		}

		return make_pair(l, u);
	}
	else {
		throw runtime_error("The matrix is not square.");
		return make_pair(l, u);
	}
}

Fraction Matrix::det() {                                                                // Determinant of  a matrix.
	Fraction d = 1;
	size_t i, n(row);
	pair<v_vF, v_vF> temp_pari = LUdcmp();
	/*
	Matrix a, b;
	a.matrix = temp_pari.second, b.matrix = temp_pari.first;
	a.row = row, b.row = row;
	a.col = col, b.col = col;
	std::cout << a << endl;
	std::cout << b << endl;
	*/
	for (i = 0; i < n; ++i) {
		d *= temp_pari.second[i][i];
	}

	return d;
}
