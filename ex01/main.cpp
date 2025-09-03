/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:56:48 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 12:59:28 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"

// Helper to print addresses/values safely in C++98.
static void printPointer(const void* p, const char* label) {
    // Print pointer value as address
    std::cout << label << ": " << p << std::endl;
}

int main() {
    // Prepare test object
    Data d;
    d.id   = 42;
    d.tag  = 'X';
    d.name = "cpp06-ex01";

    // Original pointer
    Data* original = &d;

    // Show original pointer/address and content
    printPointer(static_cast<const void*>(original), "original ptr");
    std::cout << "original content => id: " << d.id
              << ", tag: " << d.tag
              << ", name: " << d.name << std::endl;

    // Serialize pointer to uintptr_t
    uintptr_t raw = Serializer::serialize(original);
    std::cout << "serialized (uintptr_t): " << raw << std::endl;

    // Deserialize back to pointer
    Data* restored = Serializer::deserialize(raw);
    printPointer(static_cast<const void*>(restored), "restored ptr");

    // Validate that the restored pointer equals the original pointer
    if (restored == original) {
        std::cout << "SUCCESS: restored pointer matches original." << std::endl;
    } else {
        std::cout << "FAIL: restored pointer does not match original." << std::endl;
    }

    // Extra: demonstrate we still access the same object
    std::cout << "restored content => id: " << restored->id
              << ", tag: " << restored->tag
              << ", name: " << restored->name << std::endl;

    return 0;
}
