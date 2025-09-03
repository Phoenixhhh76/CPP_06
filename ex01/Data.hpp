/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-troc <hho-troc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:56:44 by hho-troc          #+#    #+#             */
/*   Updated: 2025/09/03 12:57:51 by hho-troc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

#include <string>

// A simple non-empty POD-like struct for testing serialization.
// Note: Keep it simple, no dynamic allocation is needed for this exercise.
struct Data {
    int         id;
    char        tag;
    std::string name; // std::string is allowed (no containers from <algorithm> required)
};

#endif // DATA_HPP
