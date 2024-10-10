#ifndef GENOGROVE_ANYTYPE_HPP
#define GENOGROVE_ANYTYPE_HPP

// Standard
#include <string>
#include <typeindex>


namespace genogrove {

    class AnyBase {
    public:
        virtual ~AnyBase() = default;
        virtual std::type_index getDataTypeIndex() const = 0; // return type of stored data

        // serialization
        virtual void serialize(std::ostream& os) const = 0;
        virtual std::shared_ptr<AnyBase> deserialize(std::istream& is) = 0;

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

            // descructor
            ~AnyType() override = default; // needs to be defined explicitly (otherwise delete due to use of std::optional)

            // accessors
            const T& getData() const { return *data; }
            T& getData() { return data; }

            //std::string getDataTypeName() const override { return typeid(T).name();}
            std::type_index getDataTypeIndex() const override { return dataTypeIndex; }
            void setDataType(std::type_index datatype) { dataTypeIndex = datatype; }
            //bool hasData() const override { return data.has_value(); }

            void serialize(std::ostream& os) const override {
                std::string dataTypeName = dataTypeIndex.name();
                size_t dataTypeNameLen = dataTypeName.size();
                os.write(reinterpret_cast<const char*>(&dataTypeNameLen), sizeof(dataTypeNameLen));
                os.write(dataTypeName.c_str(), dataTypeNameLen);

                // write the data
                os.write(reinterpret_cast<const char*>(&data), sizeof(T));
            }

            std::shared_ptr<AnyBase> deserialize(std::istream& is) {
                size_t dataTypeNameLen;
                is.read(reinterpret_cast<char*>(&dataTypeNameLen), sizeof(dataTypeNameLen));
                std::string dataTypeName(dataTypeNameLen, '\0');
                is.read(&dataTypeName[0], dataTypeNameLen);

                // read the data
                T data;
                is.read(reinterpret_cast<char*>(&data), sizeof(T));

                return std::make_shared<AnyType<T>>(data);
            }
    };
};

#endif //GENOGROVE_ANYTYPE_HPP
