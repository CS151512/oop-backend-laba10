#pragma once
#include "IMathRepository.h"
#include "string"

class PostgresMathRepository : public IMathRepository {
private:
    std::string conn_str;
public:
    explicit PostgresMathRepository(const std::string& connection_string);
    void saveOperation(const std::string& opName, const std::string& inputJson, const std::string& result) override;
};