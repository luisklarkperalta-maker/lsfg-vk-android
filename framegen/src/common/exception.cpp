#include "common/exception.hpp"

#include <vulkan/vulkan_core.h>

#include <exception>
#include <stdexcept>
#include <cstdint>
#include <string>

using namespace LSFG;

namespace {

std::string FormatVulkanErrorMessage(const std::string& message, VkResult result) {
    return message + " (error " + std::to_string(static_cast<int32_t>(result)) + ")";
}

std::string FormatNestedErrorMessage(const std::string& message, const std::exception& exe) {
    return message + "\n- " + exe.what();
}

} // namespace

vulkan_error::vulkan_error(VkResult result, const std::string& message)
    : std::runtime_error(FormatVulkanErrorMessage(message, result)),
      result(result) {}

vulkan_error::~vulkan_error() noexcept = default;

rethrowable_error::rethrowable_error(const std::string& message, const std::exception& exe)
        : std::runtime_error(message) {
    this->message = FormatNestedErrorMessage(message, exe);
}

rethrowable_error::~rethrowable_error() noexcept = default;
