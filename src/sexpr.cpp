#include <sxx/sexpr.hpp>

namespace sxx {
	const Sexpr Sexpr::empty_value = Sexpr();
	const std::shared_ptr<Sexpr> Sexpr::empty = std::make_shared<Sexpr>();

	std::string Sexpr::to_text() const {
		using std::experimental::holds_alternative;
		using std::experimental::get;

		std::string text;

		bool outer_sexpr = is_pair();

		if (outer_sexpr) {
			text = '(';
		}

		sexpr_variants current(value);
		while (true) {
			if (holds_alternative<void*>(current)) {
				text += "<pointer>";
				break;
			}
			else if (holds_alternative<sexpr_pair>(current)) {
				sexpr_pair cons = get<sexpr_pair>(current);
				text += cons.car->to_text();
				if (!cons.cdr || cons.cdr->is_empty())
					break;
				current = cons.cdr->value;
				if (holds_alternative<sexpr_pair>(current))
					text += ' ';
				else
					text += " . ";
			}
			else if (holds_alternative<bool>(current)) {
				if (get<bool>(current))
					text += "#t";
				else
					text += "#f";
				break;
			}
			else if (holds_alternative<double>(current)) {
				text += std::to_string(get<double>(current));
				break;
			}
			else if (holds_alternative<std::shared_ptr<std::string>>(current)) {
				text += *get<std::shared_ptr<std::string>>(current);
				break;
			}
			else if (holds_alternative<int64_t>(current)) {
				text += std::to_string(get<int64_t>(current));
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
