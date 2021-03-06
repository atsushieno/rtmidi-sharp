
#include <stdbool.h>

#ifndef RTMIDI_C_H
#define RTMIDI_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* RtMidiPtr;
typedef void* RtMidiInPtr;
typedef void* RtMidiOutPtr;

  enum RtMidiApi {
    RT_MIDI_API_UNSPECIFIED,    /*!< Search for a working compiled API. */
    RT_MIDI_API_MACOSX_CORE,    /*!< Macintosh OS-X Core Midi API. */
    RT_MIDI_API_LINUX_ALSA,     /*!< The Advanced Linux Sound Architecture API. */
    RT_MIDI_API_UNIX_JACK,      /*!< The Jack Low-Latency MIDI Server API. */
    RT_MIDI_API_WINDOWS_MM,     /*!< The Microsoft Multimedia MIDI API. */
    RT_MIDI_API_WINDOWS_KS,     /*!< The Microsoft Kernel Streaming MIDI API. */
    RT_MIDI_API_RTMIDI_DUMMY    /*!< A compilable but non-functional API. */
  };

enum RtMidiErrorType {
  RT_ERROR_WARNING, RT_ERROR_DEBUG_WARNING, RT_ERROR_UNSPECIFIED, RT_ERROR_NO_DEVICES_FOUND,
  RT_ERROR_INVALID_DEVICE, RT_ERROR_MEMORY_ERROR, RT_ERROR_INVALID_PARAMETER, RT_ERROR_INVALID_USE,
  RT_ERROR_DRIVER_ERROR, RT_ERROR_SYSTEM_ERROR, RT_ERROR_THREAD_ERROR
};

typedef void(* RtMidiCCallback) (double timeStamp, const unsigned char* message, void *userData);

int rtmidi_sizeof_rtmidi_api ();

/* RtMidi API */
int rtmidi_get_compiled_api (enum RtMidiApi **apis); // return length for NULL argument.
void rtmidi_error (enum RtMidiErrorType type, const char* errorString);

void rtmidi_open_port (RtMidiPtr device, unsigned int portNumber, const char *portName);
void rtmidi_open_virtual_port (RtMidiPtr device, const char *portName);
void rtmidi_close_port (RtMidiPtr device);
unsigned int rtmidi_get_port_count (RtMidiPtr device);
const char* rtmidi_get_port_name (RtMidiPtr device, unsigned int portNumber);

/* RtMidiIn API */
RtMidiInPtr rtmidi_in_create_default ();
RtMidiInPtr rtmidi_in_create (enum RtMidiApi api, const char *clientName, unsigned int queueSizeLimit);
void rtmidi_in_free (RtMidiInPtr device);
enum RtMidiApi rtmidi_in_get_current_api (RtMidiPtr device);
void rtmidi_in_set_callback (RtMidiInPtr device, RtMidiCCallback callback, void *userData);
void rtmidi_in_cancel_callback (RtMidiInPtr device);
void rtmidi_in_ignore_types (RtMidiInPtr device, bool midiSysex, bool midiTime, bool midiSense);
double rtmidi_in_get_message (RtMidiInPtr device, unsigned char **message);

/* RtMidiOut API */
RtMidiOutPtr rtmidi_out_create_default ();
RtMidiOutPtr rtmidi_out_create (enum RtMidiApi api, const char *clientName);
void rtmidi_out_free (RtMidiOutPtr device);
enum RtMidiApi rtmidi_out_get_current_api (RtMidiPtr device);
int rtmidi_out_send_message (RtMidiOutPtr device, const unsigned char *message, int length);


#ifdef __cplusplus
}
#endif
#endif
