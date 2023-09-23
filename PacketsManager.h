#include <iostream>
#include <filesystem>
#ifndef PROJECT1_CPPV2_PACKETSMANAGER_H
#define PROJECT1_CPPV2_PACKETSMANAGER_H

namespace fs = std::filesystem;
class PacketsManager {
private:
    uintmax_t disk_size;
    uintmax_t remaining_disk_size;
    uintmax_t max_size;
    uintmax_t min_size = 50000;
    uintmax_t total_size = 0;
    std::string directory_path = R"(D:\Internships\VIAVI Internship 2023\Testing Folder)";
public:
    void set_disk_size(uintmax_t size);
    uintmax_t get_disk_size();
    void read();
    void check(uintmax_t s, std::vector<fs::directory_entry>& file);
    static bool compareByModTime(const fs::directory_entry& a, const fs::directory_entry& b);
    void sort(std::vector<fs::directory_entry>& files);
    void remove(std::vector<fs::directory_entry>& files);

};


#endif //PROJECT1_CPPV2_PACKETSMANAGER_H
