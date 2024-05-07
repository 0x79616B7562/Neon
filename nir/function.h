#pragma once

#include <string>
#include <vector>
#include "types.h"
#include "build_data.h"
#include "objects/object.h"
#include <iostream>
#include "definitions.h"
#include "types.h"
#include "objects/return.h"
#include "source.h"

namespace nir {
    class Function {
    public:
        Function(const std::string identifier, Type return_type, const std::optional<Source> src) : identifier(identifier), return_type(return_type), src(src) {}

        void dump() const;

        template<typename T, typename ... Args>
        std::shared_ptr<T> add_object(Args ... args) {
            objects.push_back(std::make_shared<T>(args...));
            
            return std::dynamic_pointer_cast<T>(objects.back());
        }

        void build_function(BuildData * data);
    private:
        inline llvm::Type * resolve_return_type(BuildData * data) const;

        const std::string identifier;
        const Type return_type;
   
        const std::optional<Source> src;

        std::vector<std::shared_ptr<Object>> objects;
    };
}
