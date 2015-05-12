//
//  axString.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axString__
#define __axUtils__axString__

#include <string>
#include <vector>

namespace ax
{
    namespace Utils
    {
        namespace String
        {
            typedef std::pair<std::string, std::string> Pair;
            typedef std::vector<Pair> PairVector;
            typedef std::vector<std::string> Vector;
            
            std::string GetExtension(const std::string& path);
            
            Vector Split(const std::string& str, const std::string& delimiter);
        }
    }
}

#endif /* defined(__axUtils__axString__) */
