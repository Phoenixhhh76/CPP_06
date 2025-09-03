/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:29:35 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 11:29:36 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

/*
 * Test driver:
 * - Accept exactly one argument, as in the subject examples.
 * - Call ScalarConverter::convert to print all four representations.
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./convert <literal>\n";
        return 1;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}