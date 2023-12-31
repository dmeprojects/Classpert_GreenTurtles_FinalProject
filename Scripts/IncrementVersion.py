import os
import re
import json

print("Auto version incrementor")

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPT_DIR)
VERSION_HEADER_DIR = os.path.join(PROJECT_DIR, "Final project", "Firmware", "Application", "Inc")
VERSION_INFO_FILE = os.path.join(SCRIPT_DIR, "version_info.json")

#Remove the script 

def load_version_info():
    try:
        with open(VERSION_INFO_FILE, 'r') as info_file:
            version_info = json.load(info_file)
        return version_info
    except (FileNotFoundError, json.JSONDecodeError):
        return {"major": 0, "minor": 0, "build": 0}

def save_version_info(version_info):
    with open(VERSION_INFO_FILE, 'w') as info_file:
        json.dump(version_info, info_file, indent=2)

def update_version_header(file_path):
    # Read the content of the version.h file
    with open(file_path, 'r') as file:
        content = file.read()

    # Extract current build number
    build_match = re.search(r'#define FIRMWARE_BUILD (\d+)', content)
    if build_match:
        current_build = int(build_match.group(1))
    else:
        # Set default build number if the pattern is not found
        current_build = 0

    # Extract current major version
    major_version_match = re.search(r'#define FIRMWARE_MAJOR (\d+)', content)
    if major_version_match:
        current_major_version = int(major_version_match.group(1))
    else:
        # Set default major version if the pattern is not found
        current_major_version = 0

    # Extract current minor version
    minor_version_match = re.search(r'#define FIRMWARE_MINOR (\d+)', content)
    if minor_version_match:
        current_minor_version = int(minor_version_match.group(1))
    else:
        # Set default minor version if the pattern is not found
        current_minor_version = 0
    
    print("Version Info:")
    print("Current Version " + str(current_major_version) + " . " + str(current_minor_version) + " . " + str(current_build))

    # Load old version information
    old_version_info = load_version_info()
    
        # Check if major version is incremented
    if current_major_version != old_version_info["major"]:
        # Major version is incremented, reset build and minor version to 0
        new_build_number = 0
        new_minor_version = 0               
    else:
        # Increment build number and minor version
        new_build_number = current_build + 1
    
    # Check if minor version is incremented
    if current_minor_version != old_version_info["minor"]:
        new_build_number = 0
        new_minor_version = current_minor_version
    else:
        new_minor_version = old_version_info["minor"]


    
    # Update the content with the new build number and minor version
    new_content = re.sub(r'#define FIRMWARE_BUILD (\d+)', f'#define FIRMWARE_BUILD {new_build_number}', content)
    new_content = re.sub(r'#define FIRMWARE_MINOR (\d+)', f'#define FIRMWARE_MINOR {new_minor_version}', new_content)
    
    print("New content: " + new_content)
    
    
    # Write the updated content back to the version.h file
    with open(file_path, 'w') as file:
        file.write(new_content)

    # Save new version information
    new_version_info = {"major": current_major_version, "minor": new_minor_version, "build": new_build_number}
    save_version_info(new_version_info)

if __name__ == "__main__":    
    version_header_path = os.path.join(VERSION_HEADER_DIR,"version.h")
    print("Header file location: " + version_header_path)
    update_version_header(version_header_path)
