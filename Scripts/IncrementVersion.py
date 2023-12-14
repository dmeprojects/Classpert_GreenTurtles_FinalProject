import re

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

    # Check if major version is incremented
    if current_major_version != 0:
        # Major version is incremented, reset build number to 0
        new_build_number = 0
    else:
        # Increment build number
        new_build_number = current_build + 1

    # Update the content with the new build number
    new_content = re.sub(r'#define FIRMWARE_BUILD (\d+)', f'#define FIRMWARE_BUILD {new_build_number}', content)

    # Write the updated content back to the version.h file
    with open(file_path, 'w') as file:
        file.write(new_content)

if __name__ == "__main__":
    version_header_path = "version.h"
    update_version_header(version_header_path)
