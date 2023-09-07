#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <zlib.h>

namespace Archy {

bool CompressToZip(const std::string &zipFilename,
                   const std::vector<std::string> &filesToCompress) {
  gzFile zipFile = gzopen(zipFilename.c_str(), "wb");
  if (!zipFile) {
    std::cerr << "[ERROR] error creating zip file: " << zipFilename
              << std::endl;
    return false;
  }

  for (const std::string &file : filesToCompress) {
    gzFile inputFile = gzopen(file.c_str(), "rb");
    if (!inputFile) {
      std::cerr << "[ERROR] error opening file: " << file << std::endl;
      gzclose(zipFile);
      return false;
    }

    char buffer[1024];
    int bytesRead;

    while ((bytesRead = gzread(inputFile, buffer, sizeof(buffer))) > 0) {
      if (gzwrite(zipFile, buffer, bytesRead) != bytesRead) {
        std::cerr << "[ERROR] error writing to zip file" << std::endl;
        gzclose(inputFile);
        gzclose(zipFile);
        return false;
      }
    }

    gzclose(inputFile);
  }

  gzclose(zipFile);
  std::cout << "[SUCCESS] Zip compression completed successfully for file: "
            << zipFilename << std::endl;
  return true;
}

bool ExtractZip(const std::string &zipFilename,
                const std::string &destFoldername) {
  gzFile zipFile = gzopen(zipFilename.c_str(), "rb");
  if (!zipFile) {
    std::cerr << "[ERROR] error opening zip file: " << zipFilename << std::endl;
    return false;
  }

  std::string currentFilename;
  char buffer[1024];
  int bytesRead;

  while ((bytesRead = gzread(zipFile, buffer, sizeof(buffer))) > 0) {
    if (currentFilename.empty()) {
      currentFilename = std::string(buffer, bytesRead);
      std::string destPath = destFoldername + "/" + currentFilename;

      gzFile outputFile = gzopen(destPath.c_str(), "wb");
      if (!outputFile) {
        std::cerr << "[ERROR] error creating file: " << destPath << std::endl;
        gzclose(zipFile);
        return false;
      }

      continue;
    }

    gzFile outputFile = gzopen(currentFilename.c_str(), "ab");
    if (!outputFile) {
      std::cerr << "[ERROR] error opening file for writing: " << currentFilename
                << std::endl;
      gzclose(zipFile);
      return false;
    }
    if (gzwrite(outputFile, buffer, bytesRead) != bytesRead) {
      std::cerr << "[ERROR] error writing to file: " << currentFilename
                << std::endl;
      gzclose(outputFile);
      gzclose(zipFile);
      return false;
    }
    gzclose(outputFile);
  }

  gzclose(zipFile);
  std::cout << "[SUCCESS] Zip extracted successfully to folder: "
            << destFoldername << std::endl;
  return true;
}

} // namespace Archy

int main() {
  std::vector<std::string> filesToCompress = {"man_2.txt", "man_2.txt"};
  std::string zipFilename = "your_zip_archive.zip";

  // compressing
  if (Archy::CompressToZip(zipFilename, filesToCompress)) {
    std::cout << "[SUCCESS] Zip compression completed successfully."
              << std::endl;
  } else {
    std::cerr << "[ERROR] Zip compression failed." << std::endl;
    return 1;
  }

  // extraction
  std::string destFoldername = "extracted";
  if (Archy::ExtractZip(zipFilename, destFoldername)) {
    std::cout << "[SUCCESS] Zip extracted successfully." << std::endl;
  } else {
    std::cerr << "[ERROR] Zip extraction failed." << std::endl;
    return 1;
  }

  return 0;
}
