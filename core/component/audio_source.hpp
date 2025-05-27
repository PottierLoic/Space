#pragma once

#include <memory>
#include <string>

#include "log/logger.hpp"
#include "component/component.hpp"
#include "resource_management/resource_user.hpp"
#include "resource_management/resources/res_audio.hpp"
#include "resource_management/resource_manager.hpp"
#include "resource_management/resources/res_audio.hpp"

namespace SpaceEngine {

/**
 * The AudioSource class represents a sound source.
 *
 * TODO properties
 *
 * Methods:
 * - AudioSource(): Default constructor: Initializes a new AudioSource component with default values.
 * - ~AudioSource(): Destructor: Destroys the AudioSource component. Note: May not have additional functionality in this case.
 */
class AudioSource final : public Component, public IResourceUser {
public:

  /**
   * @brief Default constructor: Initializes a new AudioSource component with default values.
   */
  explicit AudioSource();

  void setAudio(const std::string& path);
  void play() const;

  void onResourceReloaded(const std::string& path) override;
  void onEntityDestroyed() override;

private:
  std::shared_ptr<ResAudio> m_audio;
  std::string m_audioPath;
};

}
