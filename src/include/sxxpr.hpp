#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant.hpp>

class SexprTypeException : public std::exception {};

class Sexpr {
private:
	struct sexpr_cons {
		std::shared_ptr<Sexpr> car;
		std::shared_ptr<Sexpr> cdr;

		sexpr_cons(Sexpr *car, Sexpr *cdr) : car(car), cdr(cdr) {}
        sexpr_cons() : car(), cdr() {}

		// deep copy the car and cdr
		sexpr_cons(const sexpr_cons &other)
			: car(std::make_shared<Sexpr>(*other.car)),
			cdr(std::make_shared<Sexpr>(*other.cdr)) {}

		inline bool operator==(const sexpr_cons& rhs) const {
			return car == rhs.car && cdr == rhs.cdr;
		}
	};

	std::experimental::variant<sexpr_cons, bool, double, void*, std::shared_ptr<std::string>, int64_t> value;

public:
	Sexpr() {}
	Sexpr(const Sexpr &other) = default;
	Sexpr(Sexpr &&other) = default;
	~Sexpr() = default;

	// value constructors
	Sexpr(Sexpr *car, Sexpr *cdr)
		: value(sexpr_cons(car, cdr)) {}
	Sexpr(std::string str) : value(std::make_shared<std::string>(str)) {}
	Sexpr(const char *str) : value(std::make_shared<std::string>(std::string(str))) {}

	inline bool operator==(const Sexpr& rhs) const {
		return rhs.value == value;
	}

	std::shared_ptr<Sexpr> car() const {
		try {
			return std::experimental::get<sexpr_cons>(value).car;
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}
	}
	std::shared_ptr<Sexpr> cdr() const {
		try {
			return std::experimental::get<sexpr_cons>(value).cdr;
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}
	}

	std::shared_ptr<std::string> as_str() const {
		return std::experimental::get<std::shared_ptr<std::string>>(value);
	}

	void set_car(Sexpr *car) {
		try {
			return std::experimental::get<sexpr_cons>(value).car.reset(car);
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}
	}

	void set_cdr(Sexpr *cdr) {
		try {
			return std::experimental::get<sexpr_cons>(value).cdr.reset(cdr);
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}

	}

};
