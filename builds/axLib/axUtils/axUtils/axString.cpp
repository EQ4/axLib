//
//  axString.cpp
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axString.h"

namespace ax
{
    namespace Utils
    {
        namespace String
        {
            std::string GetExtension(const std::string& path)
            {
                std::size_t last_dot = path.find_last_of(".");
                
                if(last_dot == std::string::npos)
                {
                    return "";
                }
                
                return std::string(path.substr(last_dot + 1));
            }
            
            Vector Split(const std::string& str, const std::string& delimiter)
            {
                Vector vec;
                
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
        }
    }
}

