#pragma once
#include "string"

class IMathRepository {
public:
    virtual ~IMathRepository() = default;
    virtual void saveOperation(const std::string& opName, const std::string& inputJson, const std::string& result) = 0;
};