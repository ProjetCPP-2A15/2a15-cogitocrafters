import speech_recognition as sr

def recognize_speech_from_mic():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        recognizer.adjust_for_ambient_noise(source, duration=1)
        audio = recognizer.listen(source)

    try:
        # Reconnaissance de la parole en utilisant Google Web Speech API
        text = recognizer.recognize_google(audio, language="fr-FR")
        return text
    except sr.UnknownValueError:
        return "Je n'ai pas compris ce que vous avez dit."
    except sr.RequestError:
        return "Je ne peux pas obtenir de réponse du service de reconnaissance vocale."

if __name__ == "__main__":
    print(recognize_speech_from_mic())