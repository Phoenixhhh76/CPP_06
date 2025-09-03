/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:09:36 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 14:09:38 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <iostream> // std::cout, std::endl
#include <cstdlib>  // std::srand
#include <ctime>    // std::time

int main() {
    // Seed the PRNG once for generate()
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Create and test multiple samples
    for (int i = 0; i < 5; ++i) {
        Base* p = generate();

        // Identify via pointer
        std::cout << "identify(Base*): ";
        identify(p);

        // Identify via reference (dereference p)
        std::cout << "identify(Base&): ";
        identify(*p);

        // Clean up to avoid memory leaks
        delete p;

        // Separator
        std::cout << "---" << std::endl;
    }
    return 0;
}
