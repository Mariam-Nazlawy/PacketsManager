#include <iostream>
#include <filesystem>
#include <vector>
#include "PacketsManager.h"

namespace fs = std::filesystem;

void PacketsManager::set_diskSize(uintmax_t size) {
    disk_size = size;
}
void PacketsManager::read(){
    std::vector<fs::directory_entry> files;
    uintmax_t total_size = 0;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            files.push_back(entry);
            //calc total size
            total_size += fs::file_size(entry);
        }
    }
    std::cout<<"reading id done\n";
    check(total_size, files);
}
bool PacketsManager::compareByModTime(const fs::directory_entry &a, const fs::directory_entry &b) {
    auto modTimeA = fs::last_write_time(a);
    auto modTimeB = fs::last_write_time(b);
    return modTimeA < modTimeB;
}
void PacketsManager::sort(std::vector<fs::directory_entry>& file) {
    std::sort(file.begin(), file.end(), compareByModTime);
}

void PacketsManager::check(uintmax_t s,std::vector<fs::directory_entry>& file){
    if(s >= disk_size*95/100)
    {
        std::cout <<"95% of the available storage space has been consumed\n";
        remove(file);
    }
    else{
        std::cout <<"Remaining disk size: " << (disk_size - s)/1000 << " KB"<< std::endl;
        std::cout<<"NO deleted files ";
    }
}

void  PacketsManager::remove(std::vector<fs::directory_entry>& file) {
    sort(file);
    std::string fileName = file.front().path().filename().string();
    std::string full_path =  directoryPath.append("/"+fileName);
    if( std::remove(full_path.c_str()) != 0)
  {
       perror("Error deleting file"); // Print an error message if the file couldn't be deleted
  } else {
     std::cout<< fileName <<" deleted successfully\n";
  }
}
uintmax_t PacketsManager::get_diskSize() {
    return disk_size;
}

