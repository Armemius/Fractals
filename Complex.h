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

	//Operations
	template <typename T>
	Complex<T> operator+(Complex<T> fst, Complex<T> sec) {
		Complex<T> res(fst.nat() + sec.nat(), fst.cpx() + sec.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator-(Complex<T> fst, Complex<T> sec) {
		Complex<T> res(fst.nat() - sec.nat(), fst.cpx() - sec.cpx());
		return res;
	}

	template <typename T>
	Complex<T> operator*(Complex<T> fst, Complex<T> sec) {
		Complex<T> res(fst.nat() * sec.nat() - fst.cpx() * sec.cpx(),
			fst.nat() * sec.cpx() + fst.cpx() * sec.nat());
		return res;
	}

	template <typename T>
	Complex<T> operator/(Complex<T> fst, Complex<T> sec) {
		Complex<T> res((fst.nat() * sec.nat() + fst.cpx() * sec.cpx()) / (sec.nat() * sec.nat() + sec.cpx() * sec.cpx()),
			(sec.nat() * fst.cpx() - fst.nat() * sec.cpx()) / (sec.nat() * sec.nat() + sec.cpx() * sec.cpx()));
		return res;
	}

	template <typename T>
	Complex<T> operator-(Complex<T> fst) {
		Complex<T> res(-fst.nat(), -fst.cpx());
		return res;
	}

	template <typename T>
	double abs(Complex<T> fst) {
		return std::sqrt(fst.nat() * fst.nat() + fst.cpx() * fst.cpx());
	}

	// TODO: POWER FUNC
}