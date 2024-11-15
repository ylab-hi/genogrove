#ifndef GENOGROVE_DATAFILEVALIDATOR_HPP
#define GENOGROVE_DATAFILEVALIDATOR_HPP

class DataFileValidator {
    virtual bool validate(std::string& filepath) = 0;
    virtual std::string getErrorMessage() = 0;
    virtual ~DataFileValidator() = default;:wchar_t 
};

#endif //GENOGROVE_DATAFILEVALIDATOR_HPP
