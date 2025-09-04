/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:11 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/04 11:14:20 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

/**
 * ScalarConverter
 * - Static utility class: not instantiable.
 * - convert(): detect the literal type (char/int/float/double/pseudo)
 *   and print its representation as char, int, float, and double.
 *
 * Notes (English comments as requested):
 * - Must handle pseudo-literals: nan, +inf, -inf, nanf, +inff, -inff
 * - Use explicit casts (static_cast<...>) when converting.
 * - Respect display format (e.g., "42.0f" and "42.0").
 * - Print "Non displayable" for non-printable char.
 * - Print "impossible" when conversion is meaningless or overflows.
 */
class ScalarConverter {
public:
    // The only allowed public API: a static method to perform the conversion.
    static void convert(const std::string &literal);

private:
    /*
     * Orthodox Canonical Form:
     * Even though this class does not need any instance,
     * we still declare the 4 canonical functions to follow the module's rules.
     *
     * Why private?
     * - To forbid instantiation: users cannot create, copy, assign, or destroy objects.
     * - This enforces the subject requirement: "must NOT be instantiable by users".
     *
     * Why empty implementation?
     * - The class has no state and no resources to manage.
     * - Empty bodies are sufficient to satisfy the linker and the canonical form rule.
     */
    ScalarConverter();                                // default constructor
    ScalarConverter(const ScalarConverter &);    // copy constructor
    ScalarConverter &operator=(const ScalarConverter &); // copy assignment operator
    ~ScalarConverter();                               // destructor
};

#endif 
