from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume

def set_volume(change):
    devices = AudioUtilities.GetSpeakers()
    interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
    volume_control = cast(interface, POINTER(IAudioEndpointVolume))
    currentVolumeDb = volume_control.GetMasterVolumeLevel()

    if change == "up":
        new_volume = max(currentVolumeDb - 10.0, -65.25)
    elif change == "down":
        new_volume = min(currentVolumeDb + 10.0, 0.0)

    volume_control.SetMasterVolumeLevel(new_volume, None)

if  __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        change = sys.argv[1]
        set_volume(change)
        print("Volume modifié avec succès.")
    else:
        print("Utilisation : python nom_du_script.py [up/down]")