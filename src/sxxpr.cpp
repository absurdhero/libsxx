#include <sxxpr.hpp>


const Sexpr Sexpr::empty_value = Sexpr();
const std::shared_ptr<Sexpr> Sexpr::empty = std::make_shared<Sexpr>();

std::string Sexpr::to_text() const {
    using std::experimental::holds_alternative;
    using std::experimental::get;

    std::string text;

    bool outer_sexpr = holds_alternative<sexpr_cons>(value);

    if (outer_sexpr) {
        text = '(';
    }

    sexpr_variants current(value);
    while (true) {
        if (holds_alternative<void*>(value)) {
            text += "<pointer>";
            break;
        }
        else if (holds_alternative<sexpr_cons>(value)) {
            sexpr_cons cons = get<sexpr_cons>(value);
            text += cons.car->to_text();
            if (!cons.cdr || cons.cdr->is_empty())
                break;
            text += ' ';
            current = cons.cdr->value;
        }
        else if (holds_alternative<bool>(value)) {
            if (get<bool>(value))
                text += "#t";
            else
                text += "#f";
            break;
        }
        else if (holds_alternative<double>(value)) {
            text += std::to_string(get<double>(value));
            break;
        }
        else if (holds_alternative<std::shared_ptr<std::string>>(value)) {
            text += *get<std::shared_ptr<std::string>>(value);
            break;
        }
        else if (holds_alternative<int64_t>(value)) {
            text += std::to_string(get<int64_t>(value));
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
