/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:09:24 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 14:09:27 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time
#include <iostream>  // std::cout, std::endl
#include <typeinfo>  // NOT used (forbidden by subject) -- included here only to show it's not used

// Factory: randomly generate A, B, or C.
// Uses std::rand() % 3 to choose the concrete type.
Base* generate(void) {
    int r = std::rand() % 3;
    switch (r) {
        case 0: return new A();
        case 1: return new B();
        default: return new C();
    }
}

// Identify actual type via pointer using dynamic_cast to pointer types.
// If dynamic_cast fails, it returns NULL; check in order A -> B -> C.
void identify(Base* p) {
    // Defensive: handle null pointer input
    if (!p) {
        std::cout << "Pointer is NULL" << std::endl;
        return;
    }
    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
    } else {
        // Should not happen if p truly points to A/B/C
        std::cout << "Unknown type" << std::endl;
    }
}

// Identify actual type via reference using dynamic_cast to references.
// If the cast fails, dynamic_cast throws std::bad_cast; catch and continue.
// Using a pointer inside this function is forbidden by the subject,
// so we strictly use references in the casts below.
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (const std::bad_cast&) {}
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (const std::bad_cast&) {}
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (const std::bad_cast&) {}

    // Should not happen if p truly refers to A/B/C
    std::cout << "Unknown type" << std::endl;
}
