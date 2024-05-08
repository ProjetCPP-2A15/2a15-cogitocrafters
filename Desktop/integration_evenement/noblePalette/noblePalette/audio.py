import sys
import os
import wave
import pyttsx3

def text_to_audio(description):
    # Initialiser le moteur de synthèse vocale
    engine = pyttsx3.init()

    # Configurer les propriétés de la voix
    engine.setProperty('rate', 140)  # Vitesse de la voix (mots par minute)
    engine.setProperty('volume', 1)  # Volume de la voix (de 0.0 à 1.0)

    # Convertir le texte en audio
    engine.save_to_file(description, 'description.wav')
    engine.runAndWait()

    # Lecture du fichier audio généré
    audio_file = 'description.wav'
    os.system("start " + audio_file)  # Ouvrir le fichier avec l'application par défaut

if __name__ == "__main__":
    # Récupérer le contenu passé en argument
    if len(sys.argv) > 1:
        description = sys.argv[1]
    else:
        description = "Description par défaut"  # Utiliser une description par défaut si aucun argument n'est passé

    # Convertir le texte en audio
    text_to_audio(description)
