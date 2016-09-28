#include "resourcepath.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif//__APPLE__

namespace {
    std::string getBundlePath() {
#ifdef __APPLE__
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourceUrl = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char path[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(resourceUrl, TRUE, (UInt8*)path, PATH_MAX)) {
            return "";
        }
        CFRelease(resourceUrl);
        return std::string(path) + "/";
#else
        return "";
#endif//__APPLE__
    }
}

std::string resourcePath(const std::string& path) {
    return getBundlePath() + path;
}
