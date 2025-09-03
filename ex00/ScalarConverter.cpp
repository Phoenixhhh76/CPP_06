/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:52 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 12:32:10 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>   // strtod, strtol
#include <cctype>    // isprint, isdigit
#include <climits>   // INT_MIN, INT_MAX
#include <cmath>     // std::isnan, std::isinf

// -- Private special members (not implemented to prevent use) --
// Empty implementations: required only to satisfy the linker.
// They are private, so they will never be called by user code.
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

// --------- Helpers (all declared static for internal linkage) ----------

/* Detect literal forms (strict but C++98-friendly) */

// Detect char literal of the form: 'a'
static bool isCharLiteral(const std::string &s) {
    return s.size() == 3 && s[0] == '\'' && s[2] == '\'';
}

// Detect integer: [+-]?[0-9]+
// Returns true if the string is a valid integer literal
static bool isIntLiteral(const std::string &s) {
    // If the string is empty, it cannot be an integer
    if (s.empty()) return false;

    // Index used to scan the string
    // std::size_t is an unsigned integer type used for sizes/indices
    std::size_t i = 0;

    // Allow an optional '+' or '-' at the beginning
    if (s[0] == '+' || s[0] == '-') i = 1;

    // If the string is only "+" or "-", then it's not a valid integer
    if (i >= s.size()) return false;

    // Check each remaining character
    for (; i < s.size(); ++i) {
        // If we find a non-digit, it's not a valid integer
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
    }

    // If we reach here, all characters were digits (after optional sign)
    return true;
}

// Pseudo literals
static bool isPseudo(const std::string &s) {
    return (s == "nan"  || s == "nanf" ||
            s == "+inf" || s == "+inff" ||
            s == "-inf" || s == "-inff");
}

// Detect float literal: [+-]?digits(.digits)?f or [+-]?.digitsf
// Returns true if the string is a valid float literal (not including pseudo-literals)
static bool isFloatLiteral(const std::string &s) {
    // Handle pseudo-literals explicitly (nanf, +inff, -inff)
    if (s == "+inff" || s == "-inff" || s == "nanf") return true;

    // Must end with 'f'
    if (s.empty() || s[s.size()-1] != 'f') return false;

    // Remove the trailing 'f' for parsing
    std::string body = s.substr(0, s.size()-1);
    if (body.empty()) return false;

    std::size_t i = 0;

    // Allow optional '+' or '-' at the beginning
    if (body[0] == '+' || body[0] == '-') i = 1;
    if (i >= body.size()) return false;

    bool seenDigit = false;
    bool seenDot   = false;

    // Scan each character in the body
    for (; i < body.size(); ++i) {
        char c = body[i];
        if (std::isdigit(static_cast<unsigned char>(c))) {
            seenDigit = true;          // At least one digit is required
        } else if (c == '.' && !seenDot) {
            seenDot = true;            // Allow only one dot
        } else {
            return false;              // Invalid character for float
        }
    }

    // Valid float literal must contain at least one digit
    return seenDigit;
}

// Detect double literal: [+-]?digits(.digits)? or [+-]?.digits
// Returns true if the string is a valid double literal (not including pseudo-literals)
static bool isDoubleLiteral(const std::string &s) {
    // Handle pseudo-literals explicitly (nan, +inf, -inf)
    if (s == "+inf" || s == "-inf" || s == "nan") return true;

    if (s.empty()) return false;

    std::size_t i = 0;

    // Allow optional '+' or '-' at the beginning
    if (s[0] == '+' || s[0] == '-') i = 1;
    if (i >= s.size()) return false;

    bool seenDigit = false;
    bool seenDot   = false;

    // Scan each character
    for (; i < s.size(); ++i) {
        char c = s[i];
        if (std::isdigit(static_cast<unsigned char>(c))) {
            seenDigit = true;          // Need at least one digit
        } else if (c == '.' && !seenDot) {
            seenDot = true;            // Allow only one dot
        } else {
            return false;              // Any other character is invalid
        }
    }

    // Must contain at least one digit overall
    return seenDigit;
}


/* Printing helpers */

// Print char from integer-like value
static void printChar(long v, bool possible) {
    std::cout << "char: ";
    if (!possible) {
        std::cout << "impossible\n";
        return;
    }
    if (v < 0 || v > 255) {
        std::cout << "impossible\n";
        return;
    }
// std::isprint checks whether the character is displayable (letters, digits, punctuation, space).
// It returns false for control characters like '\n', '\t', '\0', etc.
// Casting to unsigned char is required: passing a signed char or int outside [0..255] is undefined behavior.
    unsigned char uc = static_cast<unsigned char>(v);
    if (!std::isprint(uc)) {
        std::cout << "Non displayable\n";
        return;
    }
    std::cout << "'" << static_cast<char>(uc) << "'\n";
}

// Print int from double-like value with range & NaN/Inf checks
static void printInt(double dv, bool possible) {
    std::cout << "int: ";
    if (!possible || std::isnan(dv) || std::isinf(dv) ||
        dv < static_cast<double>(INT_MIN) || dv > static_cast<double>(INT_MAX)) {
        std::cout << "impossible\n";
        return;
    }
    int iv = static_cast<int>(dv);
    std::cout << iv << "\n";
}

// Print float with required format (always one decimal + 'f')
static void printFloat(double dv, bool isPseudo, const std::string &pseudoToken) {
    std::cout << "float: ";
    if (isPseudo) {
        if (pseudoToken == "nan" || pseudoToken == "nanf") std::cout << "nanf\n";
        else if (pseudoToken == "+inf" || pseudoToken == "+inff") std::cout << "+inff\n";
        else if (pseudoToken == "-inf" || pseudoToken == "-inff") std::cout << "-inff\n";
        else std::cout << "nanf\n";
        return;
    }
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << static_cast<float>(dv) << 'f';
    std::cout << oss.str() << "\n";
}

// Print double with required format (always one decimal)
static void printDouble(double dv, bool isPseudo, const std::string &pseudoToken) {
    std::cout << "double: ";
    if (isPseudo) {
        if (pseudoToken == "nan" || pseudoToken == "nanf") std::cout << "nan\n";
        else if (pseudoToken == "+inf" || pseudoToken == "+inff") std::cout << "+inf\n";
        else if (pseudoToken == "-inf" || pseudoToken == "-inff") std::cout << "-inf\n";
        else std::cout << "nan\n";
        return;
    }
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << dv;
    std::cout << oss.str() << "\n";
}

// ------------------------- Public API -------------------------
void ScalarConverter::convert(const std::string &s) {
    // Case 1: char literal: 'a'
    if (isCharLiteral(s)) {
        char c = s[1];
        printChar(static_cast<long>(static_cast<unsigned char>(c)), true);
        printInt(static_cast<double>(c), true);
        printFloat(static_cast<double>(c), false, "");
        printDouble(static_cast<double>(c), false, "");
        return;
    }

    // Case 2: pseudo literals
    if (isPseudo(s)) {
        printChar(0, false);
        printInt(0.0, false);
        printFloat(0.0, true, s);
        printDouble(0.0, true, s);
        return;
    }

    // Case 3: int literal
    if (isIntLiteral(s)) {
        char *end = 0;
        long lv = std::strtol(s.c_str(), &end, 10);
        bool ok = (end && *end == '\0');
        // char (from integral)
        printChar(lv, ok);
        // int (direct)
        printInt(static_cast<double>(lv), ok);
        // float/double
        if (ok) {
            printFloat(static_cast<double>(lv), false, "");
            printDouble(static_cast<double>(lv), false, "");
        } else {
            std::cout << "float: impossible\n";
            std::cout << "double: impossible\n";
        }
        return;
    }

    // Case 4: float literal (with 'f')
    if (isFloatLiteral(s)) {
        if (s == "nanf" || s == "+inff" || s == "-inff") {
            printChar(0, false);
            printInt(0.0, false);
            printFloat(0.0, true, s);
            printDouble(0.0, true, s);
            return;
        }
        std::string body = s.substr(0, s.size()-1);
        char *end = 0;
        double dv = std::strtod(body.c_str(), &end);
        bool ok = (end && *end == '\0');

        // char from double
        if (ok && !std::isnan(dv) && !std::isinf(dv) &&
            dv >= 0.0 && dv <= 255.0) {
            printChar(static_cast<long>(static_cast<unsigned char>(static_cast<int>(dv))), true);
        } else {
            printChar(0, false);
        }
        // int
        printInt(dv, ok);
        // float/double
        if (ok) {
            printFloat(dv, false, "");
            printDouble(dv, false, "");
        } else {
            std::cout << "float: impossible\n";
            std::cout << "double: impossible\n";
        }
        return;
    }

    // Case 5: double literal
    if (isDoubleLiteral(s)) {
        if (s == "nan" || s == "+inf" || s == "-inf") {
            printChar(0, false);
            printInt(0.0, false);
            printFloat(0.0, true, s);
            printDouble(0.0, true, s);
            return;
        }
        char *end = 0;
        double dv = std::strtod(s.c_str(), &end);
        bool ok = (end && *end == '\0');

        if (ok && !std::isnan(dv) && !std::isinf(dv) &&
            dv >= 0.0 && dv <= 255.0) {
            printChar(static_cast<long>(static_cast<unsigned char>(static_cast<int>(dv))), true);
        } else {
            printChar(0, false);
        }
        printInt(dv, ok);
        if (ok) {
            printFloat(dv, false, "");
            printDouble(dv, false, "");
        } else {
            std::cout << "float: impossible\n";
            std::cout << "double: impossible\n";
        }
        return;
    }

    // Nothing matched → invalid literal
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    std::cout << "float: impossible\n";
    std::cout << "double: impossible\n";
}




//-------------below is a more C++ style version (not required) -------------

/*
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>   // strtod, strtol
#include <cctype>    // isprint
#include <climits>   // INT_MIN, INT_MAX
#include <cmath>     // std::isnan, std::isinf

// -- Private special members (not implemented to prevent use) --
ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

// --------- Helpers (internal linkage via anonymous namespace) ----------
namespace {
    // Detect if it's a char literal like: 'a'
    bool isCharLiteral(const std::string &s) {
        return s.size() == 3 && s[0] == '\'' && s[2] == '\'';
    }

    // Detect integer: [+-]?[0-9]+
    bool isIntLiteral(const std::string &s) {
        if (s.empty()) return false;
        std::size_t i = 0;
        if (s[0] == '+' || s[0] == '-') i = 1;
        if (i >= s.size()) return false;
        for (; i < s.size(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
        }
        return true;
    }

    // Detect float with 'f' suffix (excluding pseudo): [+-]?digits[.digits]?f  or [+-]?.digits f
    bool isFloatLiteral(const std::string &s) {
        if (s == "+inff" || s == "-inff" || s == "nanf") return true;
        if (s.empty() || s[s.size()-1] != 'f') return false;

        std::string body = s.substr(0, s.size()-1);
        if (body.empty()) return false;

        std::size_t i = 0;
        if (body[0] == '+' || body[0] == '-') i = 1;
        if (i >= body.size()) return false;

        bool seenDigit = false;
        bool seenDot   = false;
        for (; i < body.size(); ++i) {
            char c = body[i];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                seenDigit = true;
            } else if (c == '.' && !seenDot) {
                seenDot = true;
            } else {
                return false;
            }
        }
        // At least one digit overall is required to avoid lone ".f"
        return seenDigit;
    }

    // Detect double (excluding pseudo): [+-]?digits[.digits]?  or [+-]?.digits
    bool isDoubleLiteral(const std::string &s) {
        if (s == "+inf" || s == "-inf" || s == "nan") return true;
        if (s.empty()) return false;

        std::size_t i = 0;
        if (s[0] == '+' || s[0] == '-') i = 1;
        if (i >= s.size()) return false;

        bool seenDigit = false;
        bool seenDot   = false;
        for (; i < s.size(); ++i) {
            char c = s[i];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                seenDigit = true;
            } else if (c == '.' && !seenDot) {
                seenDot = true;
            } else {
                return false;
            }
        }
        return seenDigit;
    }

    // Print routines with unified formatting
    void printChar(long v, bool possible) {
        std::cout << "char: ";
        if (!possible) {
            std::cout << "impossible\n";
            return;
        }
        // Cast to unsigned char for isprint safety
        if (v < 0 || v > 255) {
            std::cout << "impossible\n";
            return;
        }
        unsigned char uc = static_cast<unsigned char>(v);
        if (!std::isprint(uc)) {
            std::cout << "Non displayable\n";
            return;
        }
        std::cout << "'" << static_cast<char>(uc) << "'\n";
    }

    void printInt(double dv, bool possible) {
        std::cout << "int: ";
        if (!possible || std::isnan(dv) || std::isinf(dv) ||
            dv < static_cast<double>(INT_MIN) || dv > static_cast<double>(INT_MAX)) {
            std::cout << "impossible\n";
            return;
        }
        int iv = static_cast<int>(dv);
        std::cout << iv << "\n";
    }

    void printFloat(double dv, bool isPseudo, const std::string &pseudoToken ) {
        std::cout << "float: ";
        if (isPseudo) {
            if (pseudoToken == "nan" || pseudoToken == "nanf") std::cout << "nanf\n";
            else if (pseudoToken == "+inf" || pseudoToken == "+inff") std::cout << "+inff\n";
            else if (pseudoToken == "-inf" || pseudoToken == "-inff") std::cout << "-inff\n";
            else std::cout << "nanf\n"; // default fallback
            return;
        }
        // Normal numbers: always show one decimal and 'f'
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << static_cast<float>(dv) << 'f';
        std::cout << oss.str() << "\n";
    }

    void printDouble(double dv, bool isPseudo, const std::string &pseudoToken) {
        std::cout << "double: ";
        if (isPseudo) {
            if (pseudoToken == "nan" || pseudoToken == "nanf") std::cout << "nan\n";
            else if (pseudoToken == "+inf" || pseudoToken == "+inff") std::cout << "+inf\n";
            else if (pseudoToken == "-inf" || pseudoToken == "-inff") std::cout << "-inf\n";
            else std::cout << "nan\n";
            return;
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << dv;
        std::cout << oss.str() << "\n";
    }
} // anonymous namespace

// ------------------------- Public API -------------------------
void ScalarConverter::convert(const std::string &s) {
    // Case 1: char literal: 'a'
    if (isCharLiteral(s)) {
        char c = s[1];
        // char -> char/int/float/double
        printChar(static_cast<long>(static_cast<unsigned char>(c)), true);
        printInt(static_cast<int>(c), true);
        printFloat(static_cast<double>(c), false, "");
        printDouble(static_cast<double>(c), false, "");
        return;
    }

    // Case 2: pseudo literals
    if (s == "nan" || s == "nanf" || s == "+inf" || s == "-inf" || s == "+inff" || s == "-inff") {
        // char & int impossible, float/double print pseudo
        printChar(0, false);
        printInt(0.0, false);
        bool isPseudo = true;
        printFloat(0.0, isPseudo, s);
        printDouble(0.0, isPseudo, s);
        return;
    }

    // Case 3: int literal
    if (isIntLiteral(s)) {
        // Use strtol to detect overflow precisely
        char *end = 0;
        long lv = std::strtol(s.c_str(), &end, 10);
        bool ok = (end && *end == '\0' && lv >= LONG_MIN && lv <= LONG_MAX);
        // char: based on integer range and printability
        printChar(lv, ok);
        // int
        if (ok && lv >= INT_MIN && lv <= INT_MAX) {
            printInt(static_cast<double>(lv), true);
            // float/double
            printFloat(static_cast<double>(lv), false, "");
            printDouble(static_cast<double>(lv), false, "");
        } else {
            std::cout << "int: impossible\n";
            printFloat(0.0, true, "nan");   // keep consistent: impossible numeric -> show nan? No, subject wants "impossible" only for types that don't make sense; for float/double, int always fits numerically -> we should not mark pseudo here.
            // Correct the above: for overflow int, float/double are still valid conversions from the parsed number - but if strtol failed we don't have a number.
            // Let's recompute using strtod as fallback:
            char *end2 = 0;
            double dv = std::strtod(s.c_str(), &end2);
            bool okd = (end2 && *end2 == '\0');
            if (okd) {
                printFloat(dv, false, "");
                printDouble(dv, false, "");
            } else {
                // If parsing really failed, mark both impossible
                std::cout << "float: impossible\n";
                std::cout << "double: impossible\n";
            }
        }
        return;
    }

    // Case 4: float literal (with 'f')
    if (isFloatLiteral(s)) {
        if (s == "nanf" || s == "+inff" || s == "-inff") {
            printChar(0, false);
            printInt(0.0, false);
            printFloat(0.0, true, s);
            printDouble(0.0, true, s);
            return;
        }
        // Parse body (without trailing 'f') as double then cast
        std::string body = s.substr(0, s.size()-1);
        char *end = 0;
        double dv = std::strtod(body.c_str(), &end);
        bool ok = (end && *end == '\0');
        // char
        if (ok && !std::isnan(dv) && !std::isinf(dv) &&
            dv >= 0.0 && dv <= 255.0) {
            printChar(static_cast<long>(static_cast<unsigned char>(static_cast<int>(dv))), true);
        } else {
            printChar(0, false);
        }
        // int
        printInt(dv, ok);
        // float/double
        if (ok) {
            printFloat(dv, false, "");
            printDouble(dv, false, "");
        } else {
            std::cout << "float: impossible\n";
            std::cout << "double: impossible\n";
        }
        return;
    }

    // Case 5: double literal
    if (isDoubleLiteral(s)) {
        if (s == "nan" || s == "+inf" || s == "-inf") {
            printChar(0, false);
            printInt(0.0, false);
            printFloat(0.0, true, s);
            printDouble(0.0, true, s);
            return;
        }
        char *end = 0;
        double dv = std::strtod(s.c_str(), &end);
        bool ok = (end && *end == '\0');
        // char
        if (ok && !std::isnan(dv) && !std::isinf(dv) &&
            dv >= 0.0 && dv <= 255.0) {
            printChar(static_cast<long>(static_cast<unsigned char>(static_cast<int>(dv))), true);
        } else {
            printChar(0, false);
        }
        // int
        printInt(dv, ok);
        // float/double
        if (ok) {
            printFloat(dv, false, "");
            printDouble(dv, false, "");
        } else {
            std::cout << "float: impossible\n";
            std::cout << "double: impossible\n";
        }
        return;
    }

    // If nothing matched: invalid literal
    std::cout << "char: impossible\n";
    std::cout << "int: impossible\n";
    std::cout << "float: impossible\n";
    std::cout << "double: impossible\n";
}
 */