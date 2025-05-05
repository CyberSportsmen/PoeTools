#ifndef POETOOLS_ERRORS_H
#define POETOOLS_ERRORS_H
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push                                 // start new diagnostic state
#pragma GCC diagnostic ignored "-Wunused-parameter"         // function params
#pragma GCC diagnostic ignored "-Wunused-variable"          // local vars
#pragma GCC diagnostic ignored "-Wunused-function"          // static/free functions
#elif defined(_MSC_VER)
#pragma warning(push)                                       // save warning state
#pragma warning(disable: 4100)  // unreferenced formal parameter :contentReference[oaicite:0]{index=0}
#pragma warning(disable: 4189)  // initialized but not referenced
#pragma warning(disable: 5240)  // [[maybe_unused]] ignored (wrong position) :contentReference[oaicite:1]{index=1}
#endif


#include <exception>
#include <string>

// Base exception for all PoE Tools errors
class PoeError : public std::exception {
public:
    explicit PoeError(std::string msg)
      : message_("PoeError: " + std::move(msg)) {}
    const char* what() const noexcept override { return message_.c_str(); }
private:
    std::string message_;
};

// File I/O errors (loading macros, configs, data files)
class FileError : public PoeError {
public:
    FileError(const std::string& path, const std::string& msg)
      : PoeError("FileError [" + path + "]: " + msg) {}
};

// Resource loading errors (textures, sounds via ResourceManager)
class ResourceError : public PoeError {
public:
    ResourceError(const std::string& resourceID, const std::string& msg)
      : PoeError("ResourceError [" + resourceID + "]: " + msg) {}
};

// Crafting-system errors (invalid recipes, currency operations)
class CraftingError : public PoeError {
public:
    CraftingError(const std::string& recipeID, const std::string& msg)
      : PoeError("CraftingError [" + recipeID + "]: " + msg) {}
};

#endif // POETOOLS_ERRORS_H
