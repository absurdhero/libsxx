#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <sxx/variant.hpp>

namespace sxx {

	class Sexpr;

	class SexprTypeException : public std::exception {
	public:
        virtual const char* what() {
            return "type mismatch";
        }
	};

	class Sexpr {
	protected:
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

		template<class T>
		Sexpr(sexpr_variants value) : value(value) {}

	public:
		Sexpr() {}
		Sexpr(const Sexpr &other) = default;
		Sexpr(Sexpr &&other) = default;
		virtual ~Sexpr() = default;

		// value constructors - these will go away once type classes exist
		Sexpr(std::string str) : value(std::make_shared<std::string>(str)) {}
		Sexpr(const char *str) : value(std::make_shared<std::string>(std::string(str))) {}

		inline bool operator==(const Sexpr& rhs) const {
			return rhs.value == value;
		}

		static const std::shared_ptr<Sexpr> empty;

		std::shared_ptr<std::string> as_str() const {
			return std::experimental::get<std::shared_ptr<std::string>>(value);
		}

		inline bool is_empty() const {
			return value == empty_value.value;
		}

		inline bool is_pair() const {
			return std::experimental::holds_alternative<sexpr_pair>(value);
		}

		std::string to_text() const;
	};

	// Sexpr type classes

	class Pair : public Sexpr {
	public:

		Pair(std::shared_ptr<Sexpr> car, std::shared_ptr<Sexpr> cdr)
			: Sexpr() {
			value.emplace<sexpr_pair>(sexpr_pair(car, cdr));
		}

		Pair(Sexpr &sexpr) : Sexpr(sexpr) {
			if (!sexpr.is_pair()) {
				throw SexprTypeException();
			}
		}

		Pair(Sexpr &&sexpr) : Sexpr(sexpr) {
			if (!sexpr.is_pair()) {
				throw SexprTypeException();
			}
		}

		Pair(std::shared_ptr<Sexpr> &sexpr) : Pair(*sexpr) {}

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
	};


	// static s-expression operations

	inline std::shared_ptr<Sexpr> car(std::shared_ptr<Sexpr> sexpr) {
		return Pair(sexpr).car();
	}

	inline std::shared_ptr<Sexpr> cdr(std::shared_ptr<Sexpr> sexpr) {
		return Pair(sexpr).cdr();
	}

	std::ostream& operator<<(std::ostream &out, const Sexpr &sexpr);
}
