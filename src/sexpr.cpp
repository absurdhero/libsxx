#include <sxx/sexpr.hpp>

namespace sxx {
	const Sexpr Sexpr::empty_value = Sexpr();
	const std::shared_ptr<Sexpr> Sexpr::empty = std::make_shared<Sexpr>();

	std::string Sexpr::to_text() const {
		std::string text;

		bool outer_sexpr = is_pair();

		if (outer_sexpr) {
			text = '(';
		}

		any current(value);
		while (true) {
			if (current.type() == typeid(void*)) {
				text += "<pointer>";
				break;
			}
			else if (current.type() == typeid(sexpr_pair)) {
				sexpr_pair cons = any_cast<sexpr_pair>(current);
				text += cons.car->to_text();
				if (!cons.cdr || cons.cdr->is_empty())
					break;
				current = cons.cdr->value;
				if (current.type() == typeid(sexpr_pair))
					text += ' ';
				else
					text += " . ";
			}
			else if (current.type() == typeid(bool)) {
				if (any_cast<bool>(current))
					text += "#t";
				else
					text += "#f";
				break;
			}
			else if (current.type() == typeid(double)) {
				text += std::to_string(any_cast<double>(current));
				break;
			}
			else if (current.type() == typeid(std::shared_ptr<std::string>)) {
				text += *any_cast<std::shared_ptr<std::string>>(current);
				break;
			}
			else if (current.type() == typeid(int64_t)) {
				text += std::to_string(any_cast<int64_t>(current));
				break;
			}
		}

		if (outer_sexpr) {
			text += ')';
		}

		return text;
	}

	std::ostream& operator<<(std::ostream &out, const Sexpr &sexpr) {
		return out << sexpr.to_text();
	}
}
