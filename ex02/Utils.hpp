/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:09:15 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 14:09:17 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Base.hpp"

// Forward declarations of the factory and identification functions.
Base* generate(void);      // randomly creates A/B/C and returns as Base*
void  identify(Base* p);   // identify by pointer (use dynamic_cast to pointer)
void  identify(Base& p);   // identify by reference (use dynamic_cast to reference)

#endif // UTILS_HPP
