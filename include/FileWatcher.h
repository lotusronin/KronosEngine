#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <map>
#include <string>
#include <iostream>
#include <sys/stat.h>


enum FileType_t { SHADER, MAP };

struct FileInfo {
#ifdef _WIN32
    struct _stat buf;
#else
    struct stat buf;
#endif
};

class FileWatcher {
    private:
        std::map<std::string,FileInfo> m_file_to_info;
        std::map<std::string, FileType_t> m_file_to_type;
    public:
        int statFile(std::string f, void* buf);
        void addFile(std::string filename);
        void checkFiles();
        void addMapFile(std::string filename);
        void addShaderFile(std::string filename);
};

#endif //FILEWATCHER_H
