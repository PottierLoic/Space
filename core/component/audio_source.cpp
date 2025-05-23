#include "audio_source.hpp"

namespace SpaceEngine {

AudioSource::AudioSource() = default;

void AudioSource::setAudio(const std::string& path) {
  m_audioPath = path;
  m_audio = ResourceManager::load<ResAudio>(path, std::dynamic_pointer_cast<IResourceUser>(shared_from_this()));
}

void AudioSource::play() const {
  if (m_audio) {
    // TODO: waiting for Audio system
    // Audio::playSound(m_audio->getData());
  }
}

void AudioSource::onResourceReloaded(const std::string &path) {
  if (path == m_audioPath) {
    m_audio = ResourceManager::load<ResAudio>(path);
    Logger::info("Reloaded audio: " + path);
  }
}

}
