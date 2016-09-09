#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <sxx/any.hpp>

namespace sxx {

	class Sexpr;

	class SexprTypeException : public std::exception {
	public:
        virtual const char* what() {
            return "type mismatch";
        }
	};

	/** Symbols are immutable strings with their own distinct type.
	* Symbols should share their string values with each other.
	*/
    class Symbol {
    private:
        std::shared_ptr<const std::string> value;
    public:
        Symbol(const Symbol &str) : value(str.value) {}
        Symbol(const Symbol &&str) : value(str.value) {}
		Symbol(const std::shared_ptr<const std::string> value) : value(value) {}
		Symbol(const std::string &str) : value(std::make_shared<const std::string>(str)) {}
        Symbol(const std::string &&str) : value(std::make_shared<const std::string>(str)) {}

        const char *c_str() {
            return value->c_str();
        }

        std::shared_ptr<const std::string> shared_str() const {
            return value;
        }

		bool operator==(const Symbol& rhs) const {
			return *value == *rhs.value;
		}
	};

	/** The main s-expression value type that holds any value or a pair of values (Sexpr::pair). */
	class Sexpr {
	protected:

		any value;

	public:

		typedef std::shared_ptr<Sexpr> ptr;

		struct pair {
			Sexpr::ptr car;
			Sexpr::ptr cdr;

			pair(Sexpr::ptr car, Sexpr::ptr cdr) : car(car), cdr(cdr) {}
			pair() : car(), cdr() {}

			pair(const pair &other) = default;

			bool operator==(const pair& rhs) const;
		};

		static const Sexpr empty;

		Sexpr() {}
		Sexpr(const Sexpr &other) = default;
		Sexpr(Sexpr &&other) = default;
		virtual ~Sexpr() = default;

		Sexpr(const char *value) : value(std::string(value)) {}
		Sexpr(Symbol value) : value(value) {}
		Sexpr(std::string value) : value(value) {}
		Sexpr(Sexpr::pair value) : value(value) {}

		Sexpr(const any &value) : value(value) {}
		Sexpr(any &&value) : value(value) {}

		bool operator==(const Sexpr &rhs) const;

        bool as_bool() const {
            return any_cast<bool>(value);
        }

		pair as_pair() const {
			return any_cast<pair>(value);
		}

		std::string as_string() const {
			return any_cast<std::string>(value);
		}

		Symbol as_symbol() const {
			return any_cast<Symbol>(value);
		}

		bool is_empty() const {
			return value.empty();
		}

		bool is_bool() const {
			return value.type() == typeid(bool);
		}

		bool is_pair() const {
			return value.type() == typeid(pair);
		}

		bool is_string() const {
			return value.type() == typeid(std::string);
		}

		bool is_symbol() const {
			return value.type() == typeid(Symbol);
		}

		Sexpr::ptr first() const;

		Sexpr::ptr rest() const;

		void set_first(Sexpr *first);

		void set_rest(Sexpr *rest);

		std::string to_text() const;
	};


	// Rich Sexpr wrapper classes

	class List {
	public:
		static const Sexpr::ptr null;

		Sexpr::ptr sexpr;

		List(Sexpr::ptr car, Sexpr::ptr cdr) : sexpr(std::make_shared<Sexpr>(Sexpr::pair(car, cdr)))
		{
		}

		List(const Sexpr &sexpr) : sexpr(std::make_shared<Sexpr>(sexpr)) {
			if (!sexpr.is_pair()) {
				throw SexprTypeException();
			}
		}

		List(Sexpr &&sexpr) : sexpr(std::make_shared<Sexpr>(std::forward<Sexpr>(sexpr))) {
			if (!sexpr.is_pair()) {
				throw SexprTypeException();
			}
		}

		List(Sexpr::ptr &sexpr) : sexpr(sexpr) {}

        bool operator==(const List& rhs) const {
            return *sexpr == *rhs.sexpr;
        }

		std::string to_text() const {
			return sexpr->to_text();
		}

		Sexpr::ptr first() const {
			return sexpr->first();
		}

		Sexpr::ptr rest() const {
			return sexpr->rest();
		}

		void set_first(Sexpr *first) {
			sexpr->set_first(first);
		}

		void set_rest(Sexpr *rest) {
			sexpr->set_rest(rest);
		}

	};


	inline std::ostream& operator<<(std::ostream &out, const Sexpr &sexpr) {
		return out << sexpr.to_text();
	}

	inline std::ostream& operator<<(std::ostream &out, const Sexpr::ptr &sexpr) {
		return out << "(shared_ptr " << sexpr->to_text() << ")";
	}

	inline std::ostream& operator<<(std::ostream &out, const List &list) {
		return out << list.to_text();
	}

}
