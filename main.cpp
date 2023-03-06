#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <ranges>

void delete_command(const std::string& path) {
    // Delete all files in directory
    if(std::filesystem::is_directory(path)) {
        for(auto& p: std::filesystem::directory_iterator(path)) {
            try {
                if(p.is_directory()) {
                    system("Color 09");
                    auto items = std::filesystem::remove_all(p.path());
                    std::cout << "Deleted directory: " << p.path().string() << " with " << items << " items" << std::endl;
                }
                else if(p.is_regular_file()) {
                    if(std::filesystem::remove(p.path())) {
                        system("Color 09");
                        std::cout << "Deleted file: " << p.path().string() << std::endl;
                    }
                    else {
                        system("Color 04");
                        std::cout << "Failed to delete file: " << p.path().string() << std::endl;
                    }
                }
                else {
                    system("Color 04");
                    std::cout << "Unknown file type: " << p.path().string() << std::endl;
                }
            }
            catch (const std::exception& e) {
                system("Color 04");
                std::cout << "Failed to delete file or directory: " << p.path().string() << std::endl;
                std::cout << e.what() << std::endl;
                continue;
            }
        }
    }
    else {
        system("Color 04");
        std::cout << "Path is not a directory" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::map<std::string, std::string> commands = {
        {"delete", "<path>"}
    };

    std::filesystem::path file_path = argv[0];

    if(argc < 2) {
        auto keys_view = std::views::keys(commands);
        std::cout << "Usage: " << file_path.filename().string() << " <command>" << std::endl;
        std::cout << "Commands:" << std::endl;
        for(auto& command: keys_view) {
            std::cout << "  " << command << " " << commands[command] << std::endl;
        }
        return 0;
    }

    std::string command = argv[1];

    // Check if command exists
    if(commands.find(command) == commands.end()) {
        std::cout << "Command '" << command << "' not found" << std::endl;
        return 0;
    }

    if(argc < 3) {
        std::cout << "Usage: " << file_path.filename().string() << " " << command << " " << commands[command] << std::endl;
        return 0;
    }

    if(command == "delete") {
        delete_command(argv[2]);
    }

    std::cout << "Done" << std::endl;

    return 0;
}
