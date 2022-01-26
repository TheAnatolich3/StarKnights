#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <string_view>
#include <vector>
#include <functional>

class FileManager
{
public:
    [[nodiscard]] std::string resourceLocation(std::string filename) const;

    void setFindPaths(std::vector<std::string> findPaths) const;
    void forEachPath(const std::function<void(std::string)>& callback) const;

private:
    mutable std::vector<std::string> _findPaths;
};


#endif FILEMANAGER_HPP