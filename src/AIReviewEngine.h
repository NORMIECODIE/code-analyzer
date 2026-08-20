#pragma once

#include <string>

#include "ReviewContext.h"

class AIReviewEngine {

public:

    std::string buildReviewPrompt(
        const ReviewContext& context
    );
};