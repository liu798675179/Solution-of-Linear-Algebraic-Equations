#include "Matrix.h"
#include "Fraction.h"

#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::runtime_error;
using std::ostringstream;
using std::istringstream;

typedef vector<Fraction>         vF;
typedef vector<vector<Fraction>> v_vF;

// Show matrix.
v_vF Matrix::matrix_out() const {
	return matrix;
}

// Using v_vF to create a Matrix.
void Matrix::matrix_getin(v_vF &temp_vvf) {
	row = temp_vvf.size();
	col = temp_vvf[0].size();
	matrix = temp_vvf;
}

// Output Matrix.
string Matrix::cout_out() const {
	ostringstream out;
	out << (*this);
	return out.str();
}

// Temporary output.
string Matrix::cout_temp_addition_for_transmission() const {
	ostringstream out;
	out << "(";
	out << row;
	out << ",";
	out << col;
	out << ")";
	out << "[";
	for (auto &temp : matrix) {
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

// Input Matrix.
void Matrix::cin_in(string &temp_str) {
	istringstream in(temp_str, istringstream::in);
	in >> (*this);
}

Matrix operator+ (const Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;

	// First judge M1 and M2 matrix are not the same type of matrix.
	if (temp_m1.row == temp_m2.row && temp_m1.col == temp_m2.col) {
		temp_m3.resize(temp_m1.row, temp_m1.col);
		for (auto i = 0; i != temp_m1.row; ++i) {
			for (auto j = 0; j != temp_m1.col; ++j) {
				temp_m3.matrix[i][j] = temp_m1.matrix[i][j] + temp_m2.matrix[i][j];
			}
		}
	}
	else {
		try {
			throw runtime_error("Error: Rows and columns are not equal.");
		}
		catch (runtime_error const &err) {
			cout << err.what() << endl;
		}
	}

	return temp_m3;
}

Matrix operator+= (Matrix &temp_m1, const Matrix &temp_m2) {
	auto temp_m3 = temp_m1 + temp_m2;

	temp_m1 = temp_m3;

	return temp_m1;
}

Matrix operator- (const Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;

	if (temp_m1.row == temp_m2.row && temp_m1.col == temp_m2.col) {
		temp_m3.resize(temp_m1.row, temp_m1.col);
		for (auto i = 0; i != temp_m1.row; ++i) {
			for (auto j = 0; j != temp_m1.col; ++j) {
				temp_m3.matrix[i][j] = temp_m1.matrix[i][j] - temp_m2.matrix[i][j];
			}
		}
	}
	else {
		try {
			throw runtime_error("Error: Rows and columns are not equal.");
		}
		catch (runtime_error const &err) {
			cout << err.what() << endl;
		}
	}

	return temp_m3;
}

Matrix operator-= (Matrix &temp_m1, const Matrix &temp_m2) {
	auto temp_m3 = temp_m1 - temp_m2;

	temp_m1 = temp_m3;

	return temp_m1;
}

Matrix operator* (const Matrix &temp_m1, const Matrix &temp_m2) {
	Matrix temp_m3;

	// The number of columns in the first matrix M1 is equal to the number of rows in a matrix m2.
	if (temp_m1.col == temp_m2.row) {
		temp_m3.resize(temp_m1.row, temp_m2.col);
		for (auto i = 0; i != temp_m1.row; ++i) {
			for (auto j = 0; j != temp_m2.col; ++j) {
				for (auto m = 0; m != temp_m1.col; ++m)
					temp_m3.matrix[i][j] += temp_m1.matrix[i][m] * temp_m2.matrix[m][j];
			}
		}
	}
	else {
		try {
			throw runtime_error("Error: temp_m1's col and temp_m2's row are not equal.");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
		}
	}

	return temp_m3;
}

Matrix operator*= (Matrix &temp_m1, const Matrix &temp_m2) {
	auto temp_m3 = temp_m1 * temp_m2;

	temp_m1 = temp_m3;

	return temp_m1;
}

bool operator== (const Matrix &temp_m1, const Matrix &temp_m2) {
	if (temp_m1.row != temp_m2.row || temp_m1.col != temp_m2.col) {
		return false;
	}
	for (auto i = 0; i != temp_m1.row; ++i) {
		for (auto j = 0; j != temp_m2.col; ++j) {
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
	for (auto i = 0; i != temp_m.row; ++i) {
		for (auto j = 0; j != temp_m.col; ++j) {
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

// Reset matrix size.
void Matrix::resize(const size_t &temp_row, const size_t &temp_col) {
	row = temp_row;
	col = temp_col;
	matrix.resize(row);
	for (auto &i : matrix) {
		i.resize(col);
	}
}

// Add a row.
void Matrix::add_row(const size_t &temp_row, const vF &temp_vcow) {
	if (temp_row >= (row + 1) || temp_row < 0) {
		try {
			throw runtime_error("Error: Row is out of bound.");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
			return;
		}
	}
	v_vF temp_vvF;
	temp_vvF.resize(row + 1);
	for (auto &i : temp_vvF) {
		i.resize(col);
	}
	for (auto i = 0; i != temp_row; ++i) {
		for (auto j = 0; j != col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (auto j = 0; j != col; ++j) {
		temp_vvF[temp_row][j] = temp_vcow[j];
	}
	for (auto i = temp_row + 1, ii = temp_row; ii < row; ++i, ++ii) {
		for (auto j = 0; j != col; ++j) {
			temp_vvF[i][j] = matrix[ii][j];
		}
	}
	matrix = temp_vvF;
	++row;
}

// One row of the matrix is multiplied by K,it means matrix is multiplied by K.
void Matrix::add_to_other_row(const size_t &temp_row, const Fraction &F) {
	for (auto i = 0; i != col; ++i) {
		matrix[temp_row][i] += (F*matrix[temp_row][i]);
	}
}

// One row of the matrix is multiplied by K and added to the other row.
void Matrix::add_to_other_row(const size_t &temp_row1, const size_t &temp_row2, const Fraction &F) {
	if (temp_row1 != temp_row2) {
		for (auto i = 0; i != col; ++i) {
			matrix[temp_row2][i] += (F*matrix[temp_row1][i]);
		}
	}
	else {
		try {
			throw runtime_error("Error: The same of two rows.");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
		}
	}
}

// Swap two rows.
void Matrix::swap_row(const size_t &temp_row1, const size_t &temp_row2) {
	if (temp_row1 != temp_row2) {
		vF temp_vrow;
		temp_vrow.resize(col);
		for (auto i = 0; i != col; ++i) {
			temp_vrow[i] = matrix[temp_row1][i];
		}
		for (auto i = 0; i != col; ++i) {
			matrix[temp_row1][i] = matrix[temp_row2][i];
		}
		for (auto i = 0; i != col; ++i) {
			matrix[temp_row2][i] = temp_vrow[i];
		}
	}
	else {
		try {
			throw runtime_error("Error: The same of two rows.");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
		}
	}
}

// Minus one row.
void Matrix::del_row(const size_t &temp_row) {
	v_vF temp_vvF;

	temp_vvF.resize(row - 1);
	for (auto &i : temp_vvF) {
		i.resize(col);
	}
	for (auto i = 0; i != temp_row; ++i) {
		for (auto j = 0; j != col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (auto i = temp_row + 1, ii = temp_row; i < row; ++i, ++ii) {
		for (auto j = 0; j != col; ++j) {
			temp_vvF[ii][j] = matrix[i][j];
		}
	}
	matrix = temp_vvF;
	--row;
}

// Add a column.
void Matrix::add_col(const size_t &temp_col, const vF &temp_vrow) {
	if (temp_col >= (col + 1) || temp_col < 0) {
		try {
			throw runtime_error("Error: Column is out of bounds");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
			return;
		}
	}
	v_vF temp_vvF;
	temp_vvF.resize(row);
	for (auto &i : temp_vvF) {
		i.resize(col + 1);
	}
	for (auto i = 0; i != row; ++i) {
		for (auto j = 0; j != temp_col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (auto j = 0; j != row; ++j) {
		temp_vvF[j][temp_col] = temp_vrow[j];
	}
	for (auto i = 0; i != row; ++i) {
		for (auto j = temp_col + 1, jj = temp_col; jj != col; ++j, ++jj) {
			temp_vvF[i][j] = matrix[i][jj];
		}
	}
	matrix = temp_vvF;
	++col;
}

// One column of the matrix is multiplied by K,it means matrix is multiplied by K.
void Matrix::add_to_other_col(const size_t &temp_col, const Fraction &F) {
	for (auto i = 0; i != row; ++i) {
		matrix[i][temp_col] += (F*matrix[i][temp_col]);
	}
}

// One column of the matrix is multiplied by K and added to the other column.
void Matrix::add_to_other_col(const size_t &temp_col1, const size_t &temp_col2, const Fraction &F) {
	if (temp_col1 != temp_col2) {
		for (auto i = 0; i != row; ++i) {
			matrix[i][temp_col2] += (F*matrix[i][temp_col1]);
		}
	}
	else {
		try {
			throw runtime_error("Error: The same of two columns.");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
		}
	}
}

// Swap two columns.
void Matrix::swap_col(const size_t &temp_col1, const size_t &temp_col2) {
	if (temp_col1 != temp_col2) {
		vF temp_vcol;
		temp_vcol.resize(row);
		for (auto i = 0; i != row; ++i) {
			temp_vcol[i] = matrix[i][temp_col1];
		}
		for (auto i = 0; i != row; ++i) {
			matrix[i][temp_col1] = matrix[i][temp_col2];
		}
		for (auto i = 0; i != row; ++i) {
			matrix[i][temp_col2] = temp_vcol[i];
		}
	}
	else {
		try {
			throw runtime_error("Error: The same of two columns.");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
		}
	}
}

// Minus one column.
void Matrix::del_col(const size_t &temp_col) {
	v_vF temp_vvF;

	temp_vvF.resize(row);
	for (auto &i : temp_vvF) {
		i.resize(col - 1);
	}
	for (auto i = 0; i != row; ++i) {
		for (auto j = 0; j != temp_col; ++j) {
			temp_vvF[i][j] = matrix[i][j];
		}
	}
	for (auto i = 0; i != row; ++i) {
		for (auto j = temp_col + 1, jj = temp_col; j != col; ++j, ++jj) {
			temp_vvF[i][jj] = matrix[i][j];
		}
	}
	matrix = temp_vvF;
	--col;
}

// Transpose a matrix.
Matrix Matrix::trans() {
	Matrix temp_M;

	if (matrix.empty()) {
		try {
			throw runtime_error("Error: The matrix is empty.");
		}
		catch (runtime_error const &err) {
			std::cout << err.what() << std::endl;
			return *this;
		}
	}

	temp_M.resize(col, row);
	for (auto i = 0; i != temp_M.row; ++i) {
		for (auto j = 0; j != temp_M.col; ++j) {
			temp_M.matrix[i][j] = matrix[j][i];
		}
	}

	return temp_M;
}

// Check whether the square.
bool Matrix::square() const {
	return (!matrix.empty() && row == col);
}

// LU Decomposition.
pair<v_vF, v_vF> Matrix::LUdcmp() const {
	v_vF lu(matrix), u, l;
	if (square()) {
		auto n(row);
		size_t i, j, k;
		Fraction big, temp;

		l.resize(row);
		u.resize(row);
		for (auto &ii : l) {
			ii.resize(col);
		}
		for (auto &ii : u) {
			ii.resize(col);
		}

		for (i = 0; i != n; ++i) {
			big = 0;
			for (j = 0; j != n; ++j) {
				if ((temp = Fraction::Frac_abs(lu[i][j])) > big) {
					big = temp;
				}
			}
			if (big == 0) {
				try {
					throw runtime_error("Error: Singular matrix in LUdcmp");
				}
				catch (runtime_error const &err) {
					std::cout << err.what() << std::endl;
					return make_pair(l, u);
				}
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
	
	try {
		throw runtime_error("Error: The matrix is not square.");
	}
	catch (runtime_error const &err) {
		std::cout << err.what() << std::endl;
		return make_pair(l, u);
	}
}

// Determinant of  a matrix.
Fraction Matrix::det() const {
	Fraction d = 1;
	size_t i, n(row);
	auto temp_pari = LUdcmp();

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

// Inverse of matrix.
Matrix Matrix::inverse() const {
	auto temp_pair = LUdcmp();
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

	try {
		throw runtime_error("Error: The matrix is not square.");
	}
	catch (runtime_error const &err) {
		std::cout << err.what() << std::endl;
		return temp_m;
	}
}

// Solution of linear algebraic equation.
vF Matrix::solution(vF &temp_v) {
	vF solution;

	if (col == temp_v.size()) {
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
	
	try {
		throw runtime_error("Error: temp_m's col and temp_v's row are not equal.");
	}
	catch (runtime_error const &err) {
		std::cout << err.what() << std::endl;
		return solution;
	}
}
