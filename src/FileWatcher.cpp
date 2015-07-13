#include "FileWatcher.h"

int FileWatcher::statFile(std::string f, void* buf) {
#ifdef _WIN32
        int ret = _stat(f.c_str(), (struct _stat*)buf);
#else
        int ret = stat(f.c_str(), (struct stat*)buf);
#endif
    return ret;
}

void FileWatcher::addFile(std::string filename) {
    if(m_file_to_info.find(filename) == m_file_to_info.end()) {
        FileInfo to_watch;
        int ret = statFile(filename, &to_watch.buf);
        
        if(ret != 0) {
            std::cout << "Error opening file: " << filename << "\n";
        } else {
            m_file_to_info[filename] = to_watch;
        }
        
    } else {
        std::cout << "Already added file: " << filename << "\n";
    }
}

void FileWatcher::checkFiles() {

    for(auto it : m_file_to_info) {
        FileInfo recent_file;
        int ret = statFile(it.first, &recent_file.buf);

       if(ret != 0) {
           continue;
       }
       if(recent_file.buf.st_mtime > it.second.buf.st_mtime) {
           std::cout << "File " << it.first << " has been changed\n";
           m_file_to_info[it.first] = recent_file;
       }
    }
}

void FileWatcher::addMapFile(std::string filename) {
    addFile("./res/map/"+filename);
}

void FileWatcher::addShaderFile(std::string filename) {
    addFile("./shaders/"+filename);
}
