/*******************************************************************************
 * Copyright (c) 2013 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 ******************************************************************************/
#include "axUtils.h"

ax::StringVector GetVectorFromStringDelimiter(const std::string& str,
                                              const std::string& delimiter)
{
    ax::StringVector vec;
    
    std::string r = str;
    size_t pos = 0;
    std::string token;
    while ((pos = r.find(delimiter)) != std::string::npos)
    {
        token = r.substr(0, pos);
        vec.push_back(token);
        r.erase(0, pos + delimiter.length());
    }
    
    vec.push_back(r);
    
    return vec;
}

string axGetExtension(const string& path)
{
//    std::size_t last_slash_pos = path.find_last_of("/");
//    std::size_t last_dot_pos = path.find_last_of(".");
//    
    std::size_t last_dot = path.find_last_of(".");
    
    
    if(last_dot == std::string::npos)
    {
        return "";
    }

    return string(path.substr(last_dot + 1));

//    return string(path.substr(path.find_last_of(".") + 1));
//    std::string file_path = path;
//    
//    // Determine the file extension.
//    std::size_t last_slash_pos = file_path.find_last_of("/");
//    std::size_t last_dot_pos = file_path.find_last_of(".");
//    
//    std::string extension;
//
//    if (last_dot_pos != std::string::npos &&
//        last_dot_pos > last_slash_pos)
//    {
//        extension = file_path.substr(last_dot_pos + 1);
//    }
//    
//    return extension;
}

//std::string request_handler::GetFileExtension(const std::string& path)
//{
//    std::string file_path = path;
//    
//    // Determine the file extension.
//    std::size_t last_slash_pos = file_path.find_last_of("/");
//    std::size_t last_dot_pos = file_path.find_last_of(".");
//    std::string extension;
//    
//    if (last_dot_pos != std::string::npos &&
//        last_dot_pos > last_slash_pos)
//    {
//        extension = file_path.substr(last_dot_pos + 1);
//    }
//    
//    return extension;
//}