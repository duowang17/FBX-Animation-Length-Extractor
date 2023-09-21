#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fbxsdk.h>
#include <dirent.h>
#include "json.hpp"

using json = nlohmann::json;

int main() {
    // Initialize the SDK manager
    FbxManager* lSdkManager = FbxManager::Create();

    // Create an IO settings object
    FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Create a new scene to hold the FBX data
    FbxScene* lScene = FbxScene::Create(lSdkManager, "MyScene");

    // Create an importer to read the FBX file
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // JSON object to hold the results
    json json_output;

    // Path to the folder containing FBX files
    std::string folder_path = "<path_to_fbx_folder>";

    // Open directory
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(folder_path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string file_name = ent->d_name;

            // Check if the file is an FBX file
            if (file_name.find(".fbx") != std::string::npos) {
                std::string full_path = folder_path + "/" + file_name;
                std::cout << "Processing file: " << full_path << std::endl;

                // Use the file as the filename for the importer
                if (!lImporter->Initialize(full_path.c_str(), -1, lSdkManager->GetIOSettings())) {
                    std::cerr << "Call to FbxImporter::Initialize() failed for file: " << full_path << std::endl;
                    continue;
                }

                // Import the contents of the file into the scene
                if (!lImporter->Import(lScene)) {
                    std::cerr << "Call to FbxImporter::Import() failed for file: " << full_path << std::endl;
                    continue;
                }

                // Assume only one animation stack is present (for simplicity)
                FbxAnimStack* lAnimStack = lScene->GetSrcObject<FbxAnimStack>(0);
                if (lAnimStack) {
                    FbxTimeSpan lTimeSpan = lAnimStack->GetLocalTimeSpan();
                    FbxTime lStart = lTimeSpan.GetStart();
                    FbxTime lStop = lTimeSpan.GetStop();
                    // Calculate the length of the animation
                    double length = (lStop - lStart).GetSecondDouble();

                    // Insert it into JSON object
                    json_output[file_name] = length;
                }
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Cannot open directory " << folder_path << std::endl;
    }

    // Write JSON to a file
    std::string json_output_path = "/<path_to_output_folder>/animation_lengths.json";
    std::ofstream json_file(json_output_path);
    if(json_file.is_open()) {
        json_file << json_output.dump(4);  // pretty-print with 4 spaces
        std::cout << "Successfully written to " << json_output_path << std::endl;
    } else {
        std::cerr << "Failed to write to " << json_output_path << std::endl;
    }

    // Destroy the importer, scene, and manager
    lImporter->Destroy();
    lScene->Destroy();
    ios->Destroy();
    lSdkManager->Destroy();

    return 0;
}
