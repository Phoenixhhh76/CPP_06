/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:08:10 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/04 13:02:40 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

// Only one public virtual destructor as required by the subject.
// Virtual dtor enables RTTI / dynamic_cast through a polymorphic base.
class Base {
public:
    virtual ~Base(); // must be defined (even empty) to make the class polymorphic
};

#endif

//---what we learn from this exo?----
// We use dynamic_cast here because we only have a Base* (or Base&) reference,
// but we need to know the real derived type (A, B, or C) at runtime.
// Unlike static_cast, which assumes the conversion is valid (and may cause
// undefined behavior if it's not), dynamic_cast safely checks the actual
// type using RTTI (Run-Time Type Information).
// If the cast is invalid, it returns NULL for pointers or throws std::bad_cast
// for references, allowing us to reliably identify the true object type.