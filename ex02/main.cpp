/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:09:36 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/04 13:14:19 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <iostream> // std::cout, std::endl
#include <cstdlib>  // std::srand
#include <ctime>    // std::time

// Negative tests to PROVE we handle NULL and bad_cast correctly.
// static void run_negative_tests() {
//     std::cout << "[NEGATIVE] ---- Begin ----" << std::endl;

//     // 1) Prove identify(Base*) checks for NULL
//     {
//         Base* nullPtr = 0;
//         std::cout << "identify(Base* = NULL): ";
//         identify(nullPtr); // should not crash; should print something like "null"
//     }

//     // 2) Prove identify(Base*) handles a Base object that is NOT A/B/C
//     {
//         // Base is polymorphic (virtual dtor), but it's not A/B/C.
//         // dynamic_cast<A*>(Base*) should return NULL, same for B and C.
//         Base baseObj;
//         Base* pBase = &baseObj;
//         std::cout << "identify(Base* -> Base-not-ABC): ";
//         identify(pBase); // should go through all dynamic_cast<*> checks and end in "Unknown"
//     }

//     // 3) Prove identify(Base&) uses try/catch to detect failed casts
//     {
//         Base baseObj;
//         Base& refBase = baseObj;
//         std::cout << "identify(Base& -> Base-not-ABC): ";
//         // Each dynamic_cast<Derived&>(refBase) should throw std::bad_cast
//         // and be caught; the function should end gracefully (e.g., print "Unknown")
//         identify(refBase);
//     }

//     // 4) (Optional) Another negative: a derived class outside A/B/C.
//     //    Ensures your try/catch covers non-ABC subclasses as well.
//     class D : public Base {};
//     {
//         D d;
//         Base* pD = &d;
//         std::cout << "identify(Base* -> D-not-ABC): ";
//         identify(pD); // should print "Unknown" (all pointer casts return NULL)

//         Base& rD = d;
//         std::cout << "identify(Base& -> D-not-ABC): ";
//         identify(rD); // should print "Unknown" after catching bad_cast in all tries
//     }

//     std::cout << "[NEGATIVE] ----  End  ----" << std::endl;
// }

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

    // Add this line to *prove* the required error-handling behavior:
    //run_negative_tests();



    return 0;
}
