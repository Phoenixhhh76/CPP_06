/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:56:56 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 12:57:42 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <stdint.h> // uintptr_t for C++98 (C99 header)
#include <cstddef>  // std::size_t if needed

// Serializer is a utility class that cannot be instantiated.
// It provides two static methods to convert between a pointer and uintptr_t.
class Serializer {
private:
    // Make all constructors/destructor private to prevent instantiation.
    Serializer();
    Serializer(const Serializer &);
    Serializer &operator=(const Serializer &);
    ~Serializer();

public:
    // Convert a Data* pointer to an unsigned integer of type uintptr_t.
    static uintptr_t serialize(Data* ptr);

    // Convert an unsigned integer of type uintptr_t back to Data*.
    static Data* deserialize(uintptr_t raw);
};

#endif // SERIALIZER_HPP
