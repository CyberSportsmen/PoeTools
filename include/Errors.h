#ifndef POETOOLS_ERRORS_H
#define POETOOLS_ERRORS_H

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

// Macro-emulation/modeling errors (e.g. invalid key sequences)
class MacroError : public PoeError {
public:
    MacroError(const std::string& macroName, const std::string& msg)
      : PoeError("MacroError [" + macroName + "]: " + msg) {}
};

// Crafting-system errors (invalid recipes, currency operations)
class CraftingError : public PoeError {
public:
    CraftingError(const std::string& recipeID, const std::string& msg)
      : PoeError("CraftingError [" + recipeID + "]: " + msg) {}
};

// Emulator or runtime errors (general VM logic, unexpected states)
class EmulatorError : public PoeError {
public:
    EmulatorError(const std::string& context, const std::string& msg)
      : PoeError("EmulatorError [" + context + "]: " + msg) {}
};

#endif // POETOOLS_ERRORS_H
