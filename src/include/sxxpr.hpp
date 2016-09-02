#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant.hpp>

class SexprTypeException : public std::exception {};

class Sexpr {
private:
	struct sexpr_pair {
		std::shared_ptr<Sexpr> car;
		std::shared_ptr<Sexpr> cdr;

		sexpr_pair(std::shared_ptr<Sexpr> car, std::shared_ptr<Sexpr> cdr) : car(car), cdr(cdr) {}
        sexpr_pair() : car(), cdr() {}

		// deep copy the car and cdr
		sexpr_pair(const sexpr_pair &other)
			: car(std::make_shared<Sexpr>(*other.car)),
			cdr(std::make_shared<Sexpr>(*other.cdr)) {}

		inline bool operator==(const sexpr_pair& rhs) const {
			return car == rhs.car && cdr == rhs.cdr;
		}
	};

	typedef std::experimental::variant<void*, sexpr_pair, bool, double, std::shared_ptr<std::string>, int64_t> sexpr_variants;

	static const Sexpr empty_value;
	sexpr_variants value;

public:
	Sexpr() {}
	Sexpr(const Sexpr &other) = default;
	Sexpr(Sexpr &&other) = default;
	~Sexpr() = default;

	// value constructors
	Sexpr(std::shared_ptr<Sexpr> car, std::shared_ptr<Sexpr> cdr)
		: value(sexpr_pair(car, cdr)) {}
	Sexpr(std::string str) : value(std::make_shared<std::string>(str)) {}
	Sexpr(const char *str) : value(std::make_shared<std::string>(std::string(str))) {}

	inline bool operator==(const Sexpr& rhs) const {
		return rhs.value == value;
	}

	static const std::shared_ptr<Sexpr> empty;

	std::shared_ptr<Sexpr> car() const {
		try {
			return std::experimental::get<sexpr_pair>(value).car;
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}
	}
	std::shared_ptr<Sexpr> cdr() const {
		try {
			return std::experimental::get<sexpr_pair>(value).cdr;
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}
	}

	std::shared_ptr<std::string> as_str() const {
		return std::experimental::get<std::shared_ptr<std::string>>(value);
	}

	inline bool is_empty() const {
		return value == empty_value.value;
	}

	inline bool is_pair() const {
		return std::experimental::holds_alternative<sexpr_pair>(value);
	}

	void set_car(Sexpr *car) {
		try {
			return std::experimental::get<sexpr_pair>(value).car.reset(car);
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}
	}

	void set_cdr(Sexpr *cdr) {
		try {
			return std::experimental::get<sexpr_pair>(value).cdr.reset(cdr);
		}
		catch (std::experimental::bad_variant_access &) {
			throw new SexprTypeException();
		}
	}

	std::string to_text() const;
};

std::ostream& operator<<(std::ostream &out, const Sexpr &sexpr);
