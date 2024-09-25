#ifndef GENOGROVE_ANYTYPE_HPP
#define GENOGROVE_ANYTYPE_HPP

// Standard
#include <string>
#include <typeindex>

namespace genogrove {

    class AnyBase {
    public:
        virtual ~AnyBase() = default;
//        virtual std::string getDataTypeName() const = 0; // return name of stored type
        virtual std::type_index getDataTypeIndex() const = 0; // return type of stored data
        //virtual bool hasData() const = 0;
    };

    template<typename T>
    class AnyType : public AnyBase {
        private:
            T data; // always store value (not reference)
            std::type_index dataTypeIndex;

        public:
            // constructors
            AnyType() : dataTypeIndex(typeid(T)) {}

            AnyType(const T& data) : data(data), dataTypeIndex(typeid(T)) {} // Constructor for lvalue references
            AnyType(T&& data) : data(std::forward(data)), dataTypeIndex(typeid(T)) {} // Constructor for rvalue references

            ~AnyType() override = default; // needs to be defined explicitly (otherwise delete due to use of std::optional)

            const T& getData() const { return *data; }
            T& getData() { return data; }

            //std::string getDataTypeName() const override { return typeid(T).name();}
            std::type_index getDataTypeIndex() const override { return dataTypeIndex; }
            void setDataType(std::type_index datatype) { dataTypeIndex = datatype; }
            //bool hasData() const override { return data.has_value(); }
    };
};

#endif //GENOGROVE_ANYTYPE_HPP
