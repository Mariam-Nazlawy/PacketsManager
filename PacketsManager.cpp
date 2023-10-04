#include <iostream>
#include <filesystem>
#include <vector>
#include "PacketsManager.h"
#include <fstream>

namespace fs = std::filesystem;

PacketsManager::PacketsManager() {

}

void PacketsManager::set_disk_size(uintmax_t size) {
    disk_size = size;
}
void PacketsManager::read(){
    std::vector<fs::directory_entry> files;

    try {
        for (const auto &entry: fs::directory_iterator(directory_path)) {
            if (fs::is_regular_file(entry)) {
                files.push_back(entry);
                //calc total size
                total_size += fs::file_size(entry);
            }
        }

        std::cout << "Reading is done\n";
        std::cout << "Total size is: " << total_size / 1000 << " KB" << std::endl;
        check(total_size, files);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
bool PacketsManager::compareByModTime(const fs::directory_entry &a, const fs::directory_entry &b) {
    auto mod_timeA = fs::last_write_time(a);
    auto mod_timeB = fs::last_write_time(b);
    return mod_timeA < mod_timeB;
}
void PacketsManager::sort(std::vector<fs::directory_entry>& files) {
    std::sort(files.begin(), files.end(), compareByModTime);
}

void PacketsManager::check(uintmax_t size, std::vector<fs::directory_entry>& files){
    if(size >= max_size)
    {
        std::cout << "95% of the available storage space has been consumed\n";
        remove(files);
    }
    else{
        std::cout << "Remaining disk size: " << (disk_size - size)/1000 << " KB" << std::endl;
        std::cout << "NO deleted files ";
    }
}

void  PacketsManager::remove(std::vector<fs::directory_entry>& files) {
    sort(files);
    try {
        while (total_size > min_size) {
            std::string full_path = " ";
            std::string file_name = " ";
            file_name = files.front().path().filename().string();
            full_path = directory_path + "/" + file_name;

            total_size -= fs::file_size(full_path);

            if (std::remove(full_path.c_str()) != 0) {
                perror("Error deleting file"); // Print an error message if the file couldn't be deleted
            } else {
                std::cout << file_name << " deleted successfully\n";
                files.erase(files.begin());
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
uintmax_t  PacketsManager::get_disk_size() {
    return disk_size;
}

void PacketsManager::read_disk_c_size() {

    std::filesystem::path c_drive_path = "C:";
    std::filesystem::space_info c_drive_space_info = std::filesystem::space(c_drive_path);
    uint64_t c_drive_size = c_drive_space_info.capacity;
    const int convert_to_GB = (1024 * 1024 * 1024);
    std::cout << "The current size of the drive C: " << c_drive_size/convert_to_GB << " GB." << std::endl;


}

void PacketsManager::read_from_config_file() {

    try {
        std::ifstream config_file("D:\\Internships\\VIAVI Internship 2023\\Project1_cppv2\\config.txt");
        // Check if the file was opened successfully.
        if (!config_file.is_open()) {
            std::perror("Error opening the file");
        }

        std::string line;
        std::string values[3];
        int i = 0;

        //read values from the config file
        while (std::getline(config_file, line) && i < 3) {
            values[i] = line.substr(line.find(':') + 1);
            i++;
        }

        int const convert_to_bytes = 1000;

        //set values to attributes
        disk_size = std::stoi(values[0]) * convert_to_bytes;
        max_size =  std::stoi(values[1]) * disk_size;
        min_size =  std::stoi(values[2]) * disk_size;
    }
    catch (const std::exception& e) {
        std::perror ("Error: ");
    }


}

