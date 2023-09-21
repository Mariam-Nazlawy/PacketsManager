#include <iostream>
#include <filesystem>
#ifndef PROJECT1_CPPV2_PACKETSMANAGER_H
#define PROJECT1_CPPV2_PACKETSMANAGER_H

namespace fs = std::filesystem;
class PacketsManager {
private:
    uintmax_t disk_size;
    uintmax_t remaining_disk_size;
    std::string directoryPath = R"(D:\Internships\VIAVI Internship 2023\Testing Folder)";
public:
    void set_diskSize(uintmax_t size);
    uintmax_t get_diskSize();
    void read();
    void check(uintmax_t s,std::vector<fs::directory_entry>& file);
    static bool compareByModTime(const fs::directory_entry& a, const fs::directory_entry& b);
    void sort(std::vector<fs::directory_entry>& file);
    void remove(std::vector<fs::directory_entry>& file);

};


#endif //PROJECT1_CPPV2_PACKETSMANAGER_H
