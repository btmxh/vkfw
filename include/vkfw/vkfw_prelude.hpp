#pragma once

#ifdef _MSVC_LANG
  #define VKFW_CPLUSPLUS _MSVC_LANG
#else
  #define VKFW_CPLUSPLUS __cplusplus
#endif

#if 201703L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 20
#elif 201402L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 17
#elif 201103L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 14
#elif 199711L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 11
#else
  #error "vkfw.hpp needs at least c++ standard version 11"
#endif

#ifndef VKFW_INCLUDE_GL
  #define GLFW_INCLUDE_NONE
#endif
#ifndef VKFW_NO_INCLUDE_VULKAN
  #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#ifndef VKFW_NO_INCLUDE_VULKAN_HPP
  #if defined(VKFW_NO_STRUCT_CONSTRUCTORS) && !defined(VULKAN_HPP_NO_STRUCT_CONSTRUCTORS)
    #define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS VKFW_NO_STRUCT_CONSTRUCTORS
  #endif
  #if defined(VKFW_NO_EXCEPTIONS) && !defined(VULKAN_HPP_NO_EXCEPTIONS)
    #define VULKAN_HPP_NO_EXCEPTIONS VKFW_NO_EXCEPTIONS
  #endif
  #if defined(VKFW_NO_NODISCARD_WARNINGS) && !defined(VULKAN_HPP_NO_NODISCARD_WARNINGS)
    #define VULKAN_HPP_NO_NODISCARD_WARNINGS VKFW_NO_NODISCARD_WARNINGS
  #endif
  #if defined(VKFW_ASSERT) && !defined(VULKAN_HPP_ASSERT)
    #define VULKAN_HPP_ASSERT VKFW_ASSERT
  #endif
  #if defined(VKFW_ASSERT_ON_RESULT) && !defined(VULKAN_HPP_ASSERT_ON_RESULT)
    #define VULKAN_HPP_ASSERT_ON_RESULT VKFW_ASSERT_ON_RESULT
  #endif
  #if defined(VKFW_DISABLE_ENHANCED_MODE) && !defined(VULKAN_HPP_DISABLE_ENHANCED_MODE)
    #define VULKAN_HPP_DISABLE_ENHANCED_MODE VKFW_DISABLE_ENHANCED_MODE
  #endif
  #if defined(VKFW_INLINE) && !defined(VULKAN_HPP_INLINE)
    #define VULKAN_HPP_INLINE VKFW_INLINE
  #endif
  #if defined(VKFW_NO_SMART_HANDLE) && !defined(VULKAN_HPP_NO_SMART_HANDLE)
    #define VULKAN_HPP_NO_SMART_HANDLE VKFW_NO_SMART_HANDLE
  #endif
  #ifdef VKFW_ENABLE_VULKAN_HPP_MODULE
    #include <vulkan/vulkan_hpp_macros.hpp>
  #else
    #include <vulkan/vulkan.hpp>
  #endif
#endif

#if 20 <= VKFW_CPP_VERSION && defined(__has_include) && __has_include(<version> )
  #include <version>
#endif
#if !defined(VKFW_NO_STRING_VIEW) && 17 <= VKFW_CPP_VERSION
  #define VKFW_HAS_STRING_VIEW
  #ifndef VKFW_ENABLE_STD_MODULE
    #include <string_view>
  #endif
#endif
#if !defined(VKFW_NO_SPAN) && 20 <= VKFW_CPP_VERSION && defined(__cpp_lib_span)                    \
  && defined(__has_include) && 202002L <= __cpp_lib_span && __has_include(<span> )
  #define VKFW_HAS_SPAN
  #ifndef VKFW_ENABLE_STD_MODULE
    #include <span>
  #endif
#endif
#if !defined(VKFW_NO_SPACESHIP_OPERATOR) && 20 <= VKFW_CPP_VERSION                                 \
  && defined(__cpp_impl_three_way_comparison) && defined(__has_include)                            \
  && 201711 <= __cpp_impl_three_way_comparison && __has_include(<compare> )
  #define VKFW_HAS_SPACESHIP_OPERATOR
  #ifndef VKFW_ENABLE_STD_MODULE
    #include <compare>
  #endif
#endif

#ifndef VKFW_ENABLE_STD_MODULE
  #include <cstdint>
  #include <string>
  #include <system_error>
  #include <tuple>
  #include <vector>
#endif

#if defined(VULKAN_HPP_NO_SMART_HANDLE) && !defined(VKFW_NO_SMART_HANDLE)                          \
  && !defined(VKFW_NO_INCLUDE_VULKAN_HPP)
  #pragma message(                                                                                 \
    "warning: VKFW_NO_SMART_HANDLE will be defined as vkfw requires Vulkan-HPP handles when "      \
    "VKFW_NO_INCLUDE_VULKAN_HPP isn't defined. You can silence this warning by defining "          \
    "VKFW_NO_SMART_HANDLE or VKFW_NO_INCLUDE_VULKAN_HPP before including <vkfw/vkfw.hpp>")
  #define VKFW_NO_SMART_HANDLE
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  #ifndef VKFW_NO_SMART_HANDLE
    #define VKFW_NO_SMART_HANDLE
  #endif
#elif !defined(VKFW_ENABLE_STD_MODULE)
  #include <algorithm>
  #include <chrono>
  #include <iterator>
  #include <memory>
#endif

#if !defined(VKFW_NO_STD_FUNCTION_CALLBACKS) && !defined(VKFW_ENABLE_STD_MODULE)
  #include <functional>
#endif

#ifndef VKFW_ASSERT
  #include <cassert>
  #define VKFW_ASSERT assert
#endif

#ifndef VKFW_ASSERT_ON_RESULT
  #define VKFW_ASSERT_ON_RESULT VKFW_ASSERT
#endif

#define VKFW_VERSION_MAJOR             0
#define VKFW_VERSION_MINOR             2
#define VKFW_VERSION_PATCH             0
#define VKFW_TARGET_GLFW_VERSION_MAJOR 3
#define VKFW_TARGET_GLFW_VERSION_MINOR 4

static_assert(GLFW_VERSION_MAJOR == VKFW_TARGET_GLFW_VERSION_MAJOR
                && GLFW_VERSION_MINOR == VKFW_TARGET_GLFW_VERSION_MINOR,
              "\"glfw3.h\" version is not compatible with the \"vkfw.hpp\" version!");

#ifndef VKFW_INLINE
  #ifdef __clang__
    #if __has_attribute(always_inline)
      #define VKFW_INLINE __attribute__((always_inline)) __inline__
    #else
      #define VKFW_INLINE inline
    #endif
  #elif defined(__GNUC__)
    #define VKFW_INLINE __attribute__((always_inline)) __inline__
  #elif defined(_MSC_VER)
    #define VKFW_INLINE inline
  #else
    #define VKFW_INLINE inline
  #endif
#endif

#ifdef __cpp_constexpr
  #define VKFW_CONSTEXPR constexpr
  #if __cpp_constexpr >= 201304
    #define VKFW_CONSTEXPR_14 constexpr
  #else
    #define VKFW_CONSTEXPR_14
  #endif
  #define VKFW_CONST_OR_CONSTEXPR constexpr
#else
  #define VKFW_CONSTEXPR
  #define VKFW_CONSTEXPR_14
  #define VKFW_CONST_OR_CONSTEXPR const
#endif

#ifndef VKFW_NOEXCEPT
  #if defined(_MSC_VER) && (_MSC_VER <= 1800)
    #define VKFW_NOEXCEPT
  #else
    #define VKFW_NOEXCEPT     noexcept
    #define VKFW_HAS_NOEXCEPT 1
  #endif
#endif

#if 14 <= VKFW_CPP_VERSION
  #define VKFW_DEPRECATED(msg) [[deprecated(msg)]]
#else
  #define VKFW_DEPRECATED(msg)
#endif

#if (17 <= VKFW_CPP_VERSION) && !defined(VKFW_NO_NODISCARD_WARNINGS)
  #define VKFW_NODISCARD [[nodiscard]]
  #ifdef VKFW_NO_EXCEPTIONS
    #define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS [[nodiscard]]
  #else
    #define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
  #endif
#else
  #define VKFW_NODISCARD
  #define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
#endif

#ifndef VKFW_NAMESPACE
  #define VKFW_NAMESPACE vkfw
#endif

#ifndef VKFW_RAII_NAMESPACE
  #define VKFW_RAII_NAMESPACE raii
#endif

#define VKFW_STRINGIFY2(text) #text
#define VKFW_STRINGIFY(text)  VKFW_STRINGIFY2(text)
#define VKFW_NAMESPACE_STRING VKFW_STRINGIFY(VKFW_NAMESPACE)

#ifdef VKFW_NO_LEADING_e_IN_ENUMS
  #define VKFW_ENUMERATOR(name)            name
  #define VKFW_ENUMERATOR2(name_1, name_2) name_2
#else
  #define VKFW_ENUMERATOR(name)            e##name
  #define VKFW_ENUMERATOR2(name_1, name_2) e##name_1
#endif

#ifdef VKFW_ENABLE_VULKAN_HPP_MODULE
import vulkan_hpp;
#endif

#ifdef VKFW_ENABLE_STD_MODULE
  #ifdef VULKAN_HPP_STD_MODULE
import VULKAN_HPP_STD_MODULE
  #else
// use std.compat for maximum compatibility
import std.compat;
  #endif
#endif
