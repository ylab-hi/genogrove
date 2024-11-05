#ifndef GENOGROVE_ANYTYPE_HPP
#define GENOGROVE_ANYTYPE_HPP

// Standard
#include <string>
#include <typeindex>


namespace genogrove {

    class AnyBase {
    public:
        virtual ~AnyBase() = default;
        virtual std::string getTypeName() const = 0;
//        virtual std::type_index getDataTypeIndex() const = 0; // return type of stored data

        // serialization
        virtual void serialize(std::ostream& os) const = 0;
        virtual std::shared_ptr<AnyBase> deserialize(std::istream& is) = 0;

    };

    template<typename T>
    class AnyType : public AnyBase {
        private:
            T data; // always store value (not reference)
            std::string typeName;

        public:
            // constructors
            AnyType() : typeName(typeid(T).name()) {}
            AnyType(const T& data) : data(data), typeName(typeid(T).name()) {} // Constructor for lvalue references
            AnyType(T&& data) : data(std::forward(data)), typeName(typeid(T).name()) {} // Constructor for rvalue references

            // descructor
            ~AnyType() override = default; // needs to be defined explicitly (otherwise delete due to use of std::optional)

            // accessors
            const T& getData() const { return *data; }
            T& getData() { return data; }

            //std::string getDataTypeName() const override { return typeid(T).name();}
            std::string getTypeName() const override { return typeName; }
            void setTypeName(std::string typeName) { this->typeName = typeName; }

            /*
             * @brief serialize the data
             */
            void serialize(std::ostream& os) const override {
                size_t typeNameLen = typeName.size();
                os.write(reinterpret_cast<const char*>(&typeNameLen), sizeof(typeNameLen));
                os.write(typeName.c_str(), typeNameLen);

                os.write(reinterpret_cast<const char*>(&data), sizeof(T)); // write the data
            }

            std::shared_ptr<AnyBase> deserialize(std::istream& is) {
                size_t typeNameLen;
                is.read(reinterpret_cast<char*>(&typeNameLen), sizeof(typeNameLen));
                std::string typeName(typeNameLen, '\0');
                is.read(&typeName[0], typeNameLen);

                // read the data
                T data;
                is.read(reinterpret_cast<char*>(&data), sizeof(T));

                return std::make_shared<AnyType<T>>(data);
            }
    };
};

#endif //GENOGROVE_ANYTYPE_HPP
