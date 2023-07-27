#pragma once
#include <libremidi/config.hpp>
#include <libremidi/error.hpp>

#include <string>
#include <compare>

namespace libremidi
{
using client_handle = std::uint64_t;
using port_handle = std::uint64_t;

struct LIBREMIDI_EXPORT port_information
{
  // Handle to the client object:

  // ALSA Raw: unused
  // ALSA Seq: snd_seq_t*
  // CoreMIDI: MidiClientRef
  // WebMIDI: unused
  // JACK: jack_client_t*
  // WinMM: unused
  // WinUWP:
  client_handle client;

  // ALSA Raw: { uint16_t card, device, sub, padding; }
  // ALSA Seq: { uint32_t client, uint32_t port; }
  // CoreMIDI: MidiObjectRef
  // WebMIDI:
  // JACK: jack_port_id_t
  // WinMM: unset, identified by port_name
  // WinUWP:
  port_handle port;

  std::string manufacturer;
  std::string device_name;
  std::string port_name;
  std::string display_name;

  bool operator==(const port_information& other) const noexcept = default;
  std::strong_ordering operator<=>(const port_information& other) const noexcept = default;
};

using port_callback = std::function<void(const port_information&)>;
struct observer_configuration
{
  midi_error_callback on_error{};
  midi_error_callback on_warning{};

  port_callback input_added;
  port_callback input_removed;
  port_callback output_added;
  port_callback output_removed;

  // Observe hardware ports
  bool track_hardware : 1 = true;

  // Observe software (virtual) ports if the API provides it
  bool track_virtual : 1 = false;

  bool has_callbacks() const noexcept
  {
    return input_added || input_removed || output_added || output_removed;
  }
};
}
