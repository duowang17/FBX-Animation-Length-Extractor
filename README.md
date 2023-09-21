# FBX Animation Length Extractor

This utility extracts the length of animations from FBX files, processing all FBX files in a specified directory and outputting the animation lengths to a JSON file.

## 🌟 Features

- **Batch Processing:** Automatically processes all FBX files in a given directory.
- **Animation Length Extraction:** Accurately determines the length of animations within each FBX file.
- **JSON Output:** Results are saved in a cleanly formatted JSON file for easy interpretation and usage.

## 🔧 Dependencies
1. **FBX SDK**: 
   - Description:
     This project relies on the Autodesk FBX SDK. You need to download and install it separately.
   - Installation:
     ```markdown
     [Autodesk FBX SDK](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-0)
     ```
   - Setup for VS Code:
     - After installation, ensure you've set up the FBX SDK's include and library paths in VS Code.
     - Open `.vscode/c_cpp_properties.json` (create if it doesn't exist using `Command Palette`: `Ctrl+Shift+P` -> `Edit Configuration`) and add or modify the include path:
       ```json
       {
           "configurations": [
               {
                   "name": "Your Configuration Name (e.g., Mac, Win32, etc.)",
                   "includePath": [
                       "${workspaceFolder}/**",
                       "/path/to/FBXSDK/include"
                   ],
                   // other settings...
               }
           ],
           "version": 4
       }
       ```
     - If you're using a `tasks.json` or `launch.json` for building/debugging, make sure you've set the library paths correctly there, linking against the libraries in `/path/to/FBXSDK/lib`.

2. **json.hpp**: 
   - Description:
     This is a header-only library for handling JSON. It is included in the `include/` directory of this project.

## 📁 Project Structure

```
FBX-Animation-Length-Collector/
│
├── include/
│   └── json.hpp
│
├── src/
│   └── fbx_anim_extractor.cpp
│
└── README.md         

```


## 🚀 Getting Started

1. **Clone the repository:**

```bash
git clone https://github.com/your_username/fbx-animation-length-extractor.git
cd fbx-animation-length-extractor
```

2. **Compile the utility:**
```bash
clang++ -std=c++11 src/fbx.cpp \
-I "<path_to_FBXSDK>/include" \
-I ./include \
"<path_to_FBXSDK>/lib/clang/release/libfbxsdk.dylib" \
-o "collect_animation_length"
```

3. **Run the utility:**
```bash
./collect_animation_length
```

## 📖 Usage

1. **Place your FBX files in a directory.**
2. **Run the collect_animation utility.**
3. **The utility will then process each FBX file, extracting animation lengths.**
4. **Once processing is complete, an animation_lengths.json file will be generated in the current directory containing the results.**










