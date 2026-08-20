#pragma once

#include <string>

class AIClient {

public:

    std::string requestReview(
        const std::string& prompt
    );
};