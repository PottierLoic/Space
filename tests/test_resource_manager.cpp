#include "test.hpp"
#include "resource_management/resource_manager.hpp"

using namespace SpaceEngine;

int testResourceManager() {
  const auto wav = ResourceManager::load<ResAudio>("../../tests/data/audio.wav");
  custom_assert(wav, "Wav file loading failed.");

  if (const auto& data = wav->getData(); data.size() > 12 &&
    data[0] == 'R' && data[1] == 'I' && data[2] == 'F' && data[3] == 'F' &&
    data[8] == 'W' && data[9] == 'A' && data[10] == 'V' && data[11] == 'E') {
    std::cout << "[OK] RIFF/WAVE header detected\n";
  } else {
    std::cerr << "[FAIL] Invalid WAV header\n";
  }
  return 0;
}