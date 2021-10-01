#pragma once
#include "stdafx.h"

namespace cmpx {
	// Complex class
	template <typename T>
	class Complex {
	public:
		Complex();
		Complex(T natural, T complex);
		~Complex();

		T nat();
		T cpx();

		void setNat(T val);
		void setCpx(T val);

		friend std::ostream& operator<<(std::ostream& out, const Complex cx) {
			out << cx.natural_ << (cx.complex_ >= 0 ? "+" : "");
			if (std::abs(cx.complex_) == 1) {
				if (cx.complex_ == -1)
					out << "-";
			}
			else
				out << cx.complex_;
			out << "i";
			return out;
		}
	private:
		T natural_ = 0, complex_ = 0;
	};

	// Constructors & destructors
	template <typename T>
	Complex<T>::Complex() = default;

	template <typename T>
	Complex<T>::Complex(T natural, T complex) :
		natural_(natural),
		complex_(complex) {}

	template <typename T>
	Complex<T>::~Complex() {}

	// Functions
	template <typename T>
	T Complex<T>::nat() {
		return this->natural_;
	}

	template <typename T>
	T Complex<T>::cpx() {
		return this->complex_;
	}

	template <typename T>
	void Complex<T>::setNat(T value) {
		this->natural_ = value;
	}

	template <typename T>
	void Complex<T>::setCpx(T value) {
		this->complex_ = value;
	}

	//Operations
	template <typename T>
	Complex<T> operator+(Complex<T> fst, Complex<T> sec) {
		Complex<T> res(fst.nat() + sec.nat(), fst.cpx() + sec.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator+(double fst, Complex<T> sec) {
		Complex<T> res(fst + sec.nat(), sec.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator+(Complex<T> fst, double sec) {
		Complex<T> res(fst.nat() + sec, fst.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator-(Complex<T> fst, Complex<T> sec) {
		Complex<T> res(fst.nat() - sec.nat(), fst.cpx() - sec.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator-(double fst, Complex<T> sec) {
		Complex<T> res(fst - sec.nat(), sec.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator-(Complex<T> fst, double sec) {
		Complex<T> res(fst.nat() - sec, fst.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator*(Complex<T> fst, Complex<T> sec) {
		Complex<T> res(fst.nat() * sec.nat() - fst.cpx() * sec.cpx(),
			fst.nat() * sec.cpx() + fst.cpx() * sec.nat());
		return res;
	}

	template <typename T>
	Complex<T> operator*(double fst, Complex<T> sec) {
		return Complex<T>(fst, 0) * sec;
	}

	template <typename T>
	Complex<T> operator*(Complex<T> fst, double sec) {
		return Complex<T>(sec, 0) * fst;
	}

	template <typename T>
	Complex<T> operator/(Complex<T> fst, Complex<T> sec) {
		sec = sec + 1e-25;
		Complex<T> res((fst.nat() * sec.nat() + fst.cpx() * sec.cpx()) * 1.0 / (sec.nat() * sec.nat() + sec.cpx() * sec.cpx()),
			(fst.cpx() * sec.nat() - fst.nat() * sec.cpx()) * 1.0 / (sec.nat() * sec.nat() + sec.cpx() * sec.cpx()));
		return res;
	}

	template <typename T>
	Complex<T> operator/(Complex<T> fst, double sec) {
		return fst / Complex<T>(sec, 0);
	}

	template <typename T>
	Complex<T> operator/(double fst, Complex<T> sec) {
		return fst / Complex<T>(sec, 0);
	}

	template <typename T>
	Complex<T> operator-(Complex<T> fst) {
		Complex<T> res(-fst.nat(), -fst.cpx());
		return res;
	}

	template <typename T>
	T abs(Complex<T> fst) {
		return std::sqrt(fst.nat() * fst.nat() + fst.cpx() * fst.cpx());
	}

	template <typename T>
	Complex<T> pow(Complex<T> complex, double val) {
		Complex<T> tmp = complex;
		if (val == 0)
			return Complex<T>(1, 0);
		for (int i = 1; i < val; ++i) {
			complex = complex * tmp;
		}
		return complex;
	}

	template <typename T>
	Complex<T> sqrt(Complex<T> complex) {
		complex = Complex<T>(std::sqrt(abs(complex)), 0) * ((complex + abs(complex)) / Complex<T>(abs(complex + abs(complex)), 0));
		return complex;
	}
}