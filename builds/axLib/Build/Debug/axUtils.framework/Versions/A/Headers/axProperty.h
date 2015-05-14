//
//  axProperty.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-14.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axProperty__
#define __axUtils__axProperty__

#include <unordered_set>


namespace ax
{
    namespace Utils
    {
        template<typename T>
        class Property : public std::unordered_set<T>
        {
        public:
            Property()
            {
                
            }
            
            inline void AddProperty(const T& property)
            {
                this->insert(property);
            }
            
            inline void RemoveProperty(const T& property)
            {
                this->erase(property);
            }
            
            inline bool HasProperty(const T& property) const
            {
                return this->find(property) == this->end() ? false : true;
            }
        };
    }
}


#endif /* defined(__axUtils__axProperty__) */
