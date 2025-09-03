/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:08:10 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 14:25:07 by hho-troc         ###   ########.fr       */
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
