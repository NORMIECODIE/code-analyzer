#include "AIClient.h"

std::string AIClient::requestReview(
    const std::string& prompt
) {

    return "AI Client is connected successfully.\n"
           "Prompt received: "
           + std::to_string(prompt.size())
           + " characters.";
}