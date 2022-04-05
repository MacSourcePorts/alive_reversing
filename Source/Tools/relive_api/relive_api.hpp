#pragma once

#include "../../AliveLibCommon/Types.hpp"
#include "relive_api_exceptions.hpp"

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#define API_EXPORT

namespace ReliveAPI {

class LvlWriter;
class CameraImageAndLayers;
class IFileIO;

struct EnumeratePathsResult final
{
    std::string pathBndName;
    std::vector<s32> paths;
};

void DebugDumpTlvs(const std::string& prefix, const std::string& lvlFile, s32 pathId);

API_EXPORT [[nodiscard]] s32 GetApiVersion();

API_EXPORT void ExportPathBinaryToJson(std::vector<u8>& fileDataBuffer, IFileIO& fileIO, const std::string& jsonOutputFile, const std::string& inputLvlFile, s32 pathResourceId);
API_EXPORT void ExportPathBinaryToJson(IFileIO& fileIO, const std::string& jsonOutputFile, const std::string& inputLvlFile, s32 pathResourceId);

API_EXPORT [[nodiscard]] std::string UpgradePathJson(IFileIO& fileIO, const std::string& jsonFile);

API_EXPORT void ImportPathJsonToBinary(std::vector<u8>& fileDataBuffer, IFileIO& fileIO, const std::string& jsonInputFile, const std::string& inputLvl, const std::string& outputLvlFile, const std::vector<std::string>& lvlResourceSources, bool skipCamerasAndFG1);
API_EXPORT void ImportPathJsonToBinary(IFileIO& fileIO, const std::string& jsonInputFile, const std::string& inputLvl, const std::string& outputLvlFile, const std::vector<std::string>& lvlResourceSources);

API_EXPORT [[nodiscard]] EnumeratePathsResult EnumeratePaths(std::vector<u8>& fileDataBuffer, IFileIO& fileIO, const std::string& inputLvlFile);
API_EXPORT [[nodiscard]] EnumeratePathsResult EnumeratePaths(IFileIO& fileIO, const std::string& inputLvlFile);

class ChunkedLvlFile;
namespace Detail {

void ImportCameraAndFG1(std::vector<u8>& fileDataBuffer, LvlWriter& inputLvl, const std::string& camName, const CameraImageAndLayers& imageAndLayers, bool allowFullFG1Blocks);
[[nodiscard]] std::unique_ptr<ChunkedLvlFile> OpenPathBnd(IFileIO& fileIo, const std::string& inputLvlFile, std::vector<u8>& fileDataBuffer);
}

} // namespace ReliveAPI
