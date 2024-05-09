from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
import speech_recognition as sr

def set_volume(change):
    devices = AudioUtilities.GetSpeakers()
    interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
    volume_control = cast(interface, POINTER(IAudioEndpointVolume))
    currentVolumeDb = volume_control.GetMasterVolumeLevel()

    if change == "up":
        new_volume = max(currentVolumeDb + 20.0, -65.25)
    elif change == "down":
        new_volume = min(currentVolumeDb - 20.0, 0.0)
    elif change == "stop":
        new_volume = -65.25  # Mettre le volume au minimum

    volume_control.SetMasterVolumeLevel(new_volume, None)

def listen_for_commands():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening for 'up', 'down' or 'stop' commands... Please speak now.")
        try:
            audio = recognizer.listen(source, timeout=5)
        except sr.WaitTimeoutError:
            print("Listening timed out while waiting for phrase to start")
            return None

    print("Processing audio...")
    try:
        command = recognizer.recognize_google(audio).lower()
        print(f"Recognized command: {command}")
        if "up" in command:
            return "up"
        elif "down" in command:
            return "down"
        elif "stop" in command:
            return "stop"
    except sr.UnknownValueError:
        print("Sorry, I could not understand the audio")
    except sr.RequestError as e:
        print(f"Could not request results; {e}")
    return None

if __name__ == "__main__":
    command = listen_for_commands()
    if command:
        set_volume(command)
        print(f"Volume {command} successful.")
    else:
        print("No valid command received.")