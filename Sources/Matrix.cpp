#include "Matrix.h"
#include "Fraction.h"
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>

using std::vector;
using std::string;
using std::endl;
using std::runtime_error;
using std::ostringstream;
using std::istringstream;

typedef vector<Fraction>         vF;
typedef vector<vector<Fraction>> v_vF;

v_vF Matrix::matrix_out() {                                                                // Show matrix.
	return matrix;
}

void Matrix::matrix_getin(v_vF &temp_vvf) {                                                // Using v_vF to create a Matrix.
	this->row = temp_vvf.size();
	this->col = temp_vvf[0].size();
	this->matrix = temp_vvf;
}

string Matrix::cout_out() const {                                                          // Output Matrix.
	ostringstream out;
	out << (*this);
	return out.str();
}

string Matrix::cout_temp_addition_for_transmission() const {                               // Temporary output.
	ostringstream out;
	out << "(";
	out << this->row;
	out << ",";
	out << this->col;
	out << ")";
	out << "[";
	for (auto &temp : this->matrix) {
		out << "[";
		for (auto beg = temp.begin(); beg != temp.end(); ++beg) {
			out << *beg;
			if (beg + 1 != temp.end())
				out << ",";
		}
		out << "]";
	}
	out << "]";
	out << "|";

	return out.str();
}

void Matrix::cin_in(string &temp_str) {                                                     // Input Matrix.
	istringstream in(temp_str, istringstream::in);
	in >> (*this);
}

Matrix operator+ (const Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;
	if (temp_m1.row == temp_m2.row && temp_m1.col == temp_m2.col)                           // First judge M1 and M2 matrix are not the same type of matrix.
	{
		temp_m3.resize(temp_m1.row, temp_m1.col);
		for (size_t i = 0; i != temp_m1.row; ++i)
		{
			for (size_t j = 0; j != temp_m1.col; ++j)
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
		for (size_t i = 0; i != temp_m1.row; ++i)
		{
			for (size_t j = 0; j != temp_m1.col; ++j)
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
		for (size_t i = 0; i != temp_m1.row; ++i)
		{
			for (size_t j = 0; j != temp_m1.col; ++j)
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
		for (size_t i = 0; i != temp_m1.row; ++i)
		{
			for (size_t j = 0; j != temp_m1.col; ++j)
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
		for (size_t i = 0; i != temp_m1.row; ++i)
		{
			for (size_t j = 0; j != temp_m2.col; ++j)
			{
				for (size_t m = 0; m != temp_m1.col; ++m)
					temp_m3.matrix[i][j] += temp_m1.matrix[i][m] * temp_m2.matrix[m][j];
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
		for (size_t i = 0; i != temp_m1.row; ++i)
		{
			for (size_t j = 0; j != temp_m2.col; ++j)
			{
				for (size_t m = 0; m != temp_m1.col; ++m)
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
	for (size_t i = 0; i != temp_m1.row; ++i) {
		for (size_t j = 0; j != temp_m2.col; ++j) {
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
	for (size_t i = 0; i != temp_m.row; ++i) {
		for (size_t j = 0; j != temp_m.col; ++j) {
			if (j == (temp_m.col - 1)) {
				out << temp_m.matrix[i][j] << endl;
				if (i != temp_m.row - 1) {
					out << endl;
				}
			}
			else if (j == 0) {
				out << "   " << temp_m.matrix[i][j] << "   ";
			}
			else {
				out << temp_m.matrix[i][j] << "   ";
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
	for (size_t i = 0; i != temp_row; ++i) {
		for (size_t j = 0; j != col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t j = 0; j != col; ++j) {
		temp_vvF[temp_row][j] = temp_vcow[j];
	}
	for (size_t i = temp_row + 1, ii = temp_row; ii < row; ++i, ++ii) {
		for (size_t j = 0; j != col; ++j) {
			temp_vvF[i][j] = matrix[ii][j];
		}
	}
	matrix = temp_vvF;
	++row;
}

void Matrix::add_to_other_row(size_t &temp_row, Fraction &F) {                              // One row of the matrix is multiplied by K,it means matrix is multiplied by K.
	for (size_t i = 0; i != col; ++i) {
		matrix[temp_row][i] += (F*matrix[temp_row][i]);
	}
}

void Matrix::add_to_other_row(size_t &temp_row1, size_t &temp_row2, Fraction &F) {         // One row of the matrix is multiplied by K and added to the other row.
	if (temp_row1 != temp_row2) {
		for (size_t i = 0; i != col; ++i) {
			matrix[temp_row2][i] += (F*matrix[temp_row1][i]);
		}
	}
	else {
		throw runtime_error("The same of two rows.");
	}
}

void Matrix::swap_row(size_t &temp_row1, size_t &temp_row2) {                               // Swap two rows;
	if (temp_row1 != temp_row2) {
		vF temp_vrow;
		temp_vrow.resize(col);
		for (size_t i = 0; i != col; ++i) {
			temp_vrow[i] = matrix[temp_row1][i];
		}
		for (size_t i = 0; i != col; ++i) {
			matrix[temp_row1][i] = matrix[temp_row2][i];
		}
		for (size_t i = 0; i != col; ++i) {
			matrix[temp_row2][i] = temp_vrow[i];
		}
	}
	else {
		throw runtime_error("The same of row numbers");
	}
}

void Matrix::del_row(size_t &temp_row) {                                                    // Minus one row.
	v_vF temp_vvF;
	temp_vvF.resize(row - 1);
	for (auto &i : temp_vvF) {
		i.resize(col);
	}
	for (size_t i = 0; i != temp_row; ++i) {
		for (size_t j = 0; j != col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t i = temp_row + 1, ii = temp_row; i < row; ++i, ++ii) {
		for (size_t j = 0; j != col; ++j) {
			temp_vvF[ii][j] = matrix[i][j];
		}
	}
	matrix = temp_vvF;
	--row;
}

void Matrix::add_col(size_t &temp_col, vF &temp_vrow) {                                     // Add a column.
	if (temp_col >= (col + 1) || temp_col < 0) {
		throw runtime_error("Column is out of bounds");
	}
	v_vF temp_vvF;
	temp_vvF.resize(row);
	for (auto &i : temp_vvF) {
		i.resize(col + 1);
	}
	for (size_t i = 0; i != row; ++i) {
		for (size_t j = 0; j != temp_col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t j = 0; j != row; ++j) {
		temp_vvF[j][temp_col] = temp_vrow[j];
	}
	for (size_t i = 0; i != row; ++i) {
		for (size_t j = temp_col + 1, jj = temp_col; jj != col; ++j, ++jj) {
			temp_vvF[i][j] = matrix[i][jj];
		}
	}
	matrix = temp_vvF;
	++col;
}

void Matrix::add_to_other_col(size_t &temp_col, Fraction &F) {                              // One column of the matrix is multiplied by K,it means matrix is multiplied by K.
	for (size_t i = 0; i != row; ++i) {
		matrix[i][temp_col] += (F*matrix[i][temp_col]);
	}
}

void Matrix::add_to_other_col(size_t &temp_col1, size_t &temp_col2, Fraction &F) {          // One column of the matrix is multiplied by K and added to the other column.
	if (temp_col1 != temp_col2) {
		for (size_t i = 0; i != row; ++i) {
			matrix[i][temp_col2] += (F*matrix[i][temp_col1]);
		}
	}
	else {
		throw runtime_error("The same of two columns.");
	}
}

void Matrix::swap_col(size_t &temp_col1, size_t &temp_col2) {                               // Swap two columns;
	if (temp_col1 != temp_col2) {
		vF temp_vcol;
		temp_vcol.resize(row);
		for (size_t i = 0; i != row; ++i) {
			temp_vcol[i] = matrix[i][temp_col1];
		}
		for (size_t i = 0; i != row; ++i) {
			matrix[i][temp_col1] = matrix[i][temp_col2];
		}
		for (size_t i = 0; i != row; ++i) {
			matrix[i][temp_col2] = temp_vcol[i];
		}
	}
	else {
		throw runtime_error("The same of column numbers");
	}
}

void Matrix::del_col(size_t &temp_col) {                                                    // Minus one column.
	v_vF temp_vvF;
	temp_vvF.resize(row);
	for (auto &i : temp_vvF) {
		i.resize(col - 1);
	}
	for (size_t i = 0; i != row; ++i) {
		for (size_t j = 0; j != temp_col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (size_t i = 0; i != row; ++i) {
		for (size_t j = temp_col + 1, jj = temp_col; j != col; ++j, ++jj) {
			temp_vvF[i][jj] = matrix[i][j];
		}
	}
	matrix = temp_vvF;
	--col;
}

Matrix Matrix::trans() {                                                                    // Transpose a matrix.
	Matrix temp_M;
	if (matrix.empty()) {
		throw runtime_error("The matrix is empty.");
	}
	else {
		temp_M.resize(col, row);
		for (size_t i = 0; i != temp_M.row; ++i) {
			for (size_t j = 0; j != temp_M.col; ++j) {
				temp_M.matrix[i][j] = matrix[j][i];
			}
		}
	}

	return temp_M;
}

bool Matrix::square() const {                                                               // Check whether the square.
	return (!matrix.empty() && row == col);
}

pair<v_vF, v_vF> Matrix::LUdcmp() {                                                         // LU Decomposition.
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

		for (i = 0; i != n; ++i) {
			big = 0;
			for (j = 0; j != n; ++j) {
				if ((temp = Fraction::Frac_abs(lu[i][j])) > big) {
					big = temp;
				}
			}
			if (big == 0) {
				throw runtime_error("Singular matrix in LUdcmp");
			}
		}

		for (k = 0; k != n; ++k) {
			for (i = k + 1; i != n; ++i) {
				lu[i][k] = lu[i][k] / lu[k][k];
				for (j = k + 1; j != n; ++j) {
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
		for (i = 0; i != n; ++i) {
			for (j = 0; j != n; ++j) {
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

Fraction Matrix::det() {                                                                    // Determinant of  a matrix.
	Fraction d = 1;
	size_t i, n(row);
	pair<v_vF, v_vF> temp_pari = LUdcmp();
	/*
	Matrix a, b;
	a.matrix = temp_pari.first, b.matrix = temp_pari.second;
	a.row = row, b.row = row;
	a.col = col, b.col = col;
	std::cout << a << endl;
	std::cout << b << endl;
	*/
	for (i = 0; i != n; ++i) {
		d *= temp_pari.second[i][i];
	}

	return d;
}

Matrix Matrix::inverse() {                                                                  // Inverse of matrix.
	pair<v_vF, v_vF> temp_pair = LUdcmp();
	Matrix temp_L, temp_U, temp_m, temp_L1, temp_U1;
	temp_L.matrix = temp_pair.first;
	temp_U.matrix = temp_pair.second;
	size_t j, k, n(row);
	int i;
	Fraction s;
	if (square()) {
		temp_L1.resize(row, col);
		temp_U1.resize(row, col);

		for (j = 0; j != n; j++){
			temp_L1.matrix[j][j] = 1;
			for (i = j + 1; i != n; i++){
				for (k = j; k != i; k++) {
					temp_L1.matrix[i][j] -= temp_L.matrix[i][k] * temp_L1.matrix[k][j];
				}
			}
		}
		//std::cout << temp_L1 << endl;
		for (j = 0; j != n; ++j) {
			temp_U1.matrix[j][j] = 1 / temp_U.matrix[j][j];
			for (i = j - 1; i != -1; i--) {
				s = 0;
				for (k = i + 1; k != j + 1; ++k) {
					s += temp_U.matrix[i][k] * temp_U1.matrix[k][j];
					temp_U1.matrix[i][j] = 0 - s / temp_U.matrix[i][i];
				}
			}
		}
		//std::cout << temp_U1 << endl;

		temp_m = temp_U1 * temp_L1;

		//std::cout << temp_m << endl;

		return temp_m;
	}
	else {
		throw runtime_error("The matrix is not square.");
		return temp_m;
	}
}

vF Matrix::solution(vF &temp_v) {                                                           // Solution of linear algebraic equation.
	vF solution;
	if (this->col == temp_v.size()) {
		*this = this->inverse();
		Matrix temp_m1;
		temp_m1.resize(temp_v.size(), 1);
		for (size_t i = 0; i != row; ++i) {
			temp_m1.matrix[i][0] = temp_v[i];
		}
		temp_m1 = *this * temp_m1;
		for (size_t i = 0; i != row; ++i) {
			solution.push_back(temp_m1.matrix[i][0]);
		}

		return solution;
	}
	else {
		throw runtime_error("temp_m's col and temp_v's row are not equal.");

		return solution;
	}
}
