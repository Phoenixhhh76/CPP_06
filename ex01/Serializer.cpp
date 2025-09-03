/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:56:53 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 13:02:13 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

// Private special members: define them but keep empty (no instantiation intended).
Serializer::Serializer() {}
Serializer::Serializer(const Serializer &) {}
Serializer &Serializer::operator=(const Serializer &) { return *this; }
Serializer::~Serializer() {}

// serialize: pointer -> uintptr_t
uintptr_t Serializer::serialize(Data* ptr) {
    // reinterpret_cast is used for low-level, bitwise-preserving pointer/integer conversion.
    return reinterpret_cast<uintptr_t>(ptr);
}

// deserialize: uintptr_t -> pointer
Data* Serializer::deserialize(uintptr_t raw) {
    // reinterpret_cast converts the integer back to the original pointer type.
    return reinterpret_cast<Data*>(raw);
}
