import speech_recognition as sr
import pyttsx3 as ttx
import pyautogui
import cv2
import numpy as np
import easyocr
import openai
import sys

# Configuration de la reconnaissance vocale
listener = sr.Recognizer()
engine = ttx.init()
engine.setProperty('voice', 'french')

# Clé API OpenAI
api_key = "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"

# Fonction pour parler
def parle(text):
    engine.say(text)
    engine.runAndWait()

# Fonction pour écouter une commande vocale
def ecoute():
    try:
        with sr.Microphone() as source:
            print("Parler...")
            listener.adjust_for_ambient_noise(source)
            audio = listener.listen(source, timeout=10)  # Limite de temps d'écoute de 10 secondes
            detected_lang = listener.recognize_google(audio, show_all=True).get('language', 'fr-FR')
            print(f"Langue détectée: {detected_lang}")
            command = listener.recognize_google(audio, language=detected_lang)
            print("Commande détectée:", command)
            return command.lower()
    except sr.UnknownValueError:
        parle("Je n'ai pas compris ce que vous avez dit.")
    except sr.RequestError as e:
        parle("Erreur lors de la requête vers le service de reconnaissance vocale : {0}".format(e))
    except sr.WaitTimeoutError:
        parle("Temps écoulé. Microphone désactivé.")

# Fonction pour détecter du texte à l'écran
def detecter_texte_ecran():
    capture = pyautogui.screenshot()
    image = np.array(capture)
    image_grise = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    reader = easyocr.Reader(['fr'])
    resultat = reader.readtext(image_grise)
    return resultat

# Fonction pour déplacer la souris vers l'emplacement du texte détecté
def deplacer_souris_vers_texte(texte):
    x, y = texte[0][0]  # Coordonnées de l'angle supérieur gauche du rectangle englobant
    pyautogui.moveTo(x, y)
    print("Souris déplacée vers l'emplacement du texte : ({}, {})".format(x, y))

# Fonction pour effectuer un clic de souris à l'emplacement du texte détecté
def clic_souris_sur_texte(texte):
    x, y = texte[0][0]  # Coordonnées de l'angle supérieur gauche du rectangle englobant
    pyautogui.click(x, y)
    print("Clic de souris effectué sur le texte : ({}, {})".format(x, y))

# Fonction pour interagir avec le chatbot
def chat_with_gpt(user_input):
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": "You are a large language model trained by researchers from Perplexity."},
            {"role": "user", "content": user_input}
        ],
        max_tokens=50,
        api_key=api_key
    )
    return response.choices[0].message.content.strip()

# Fonction principale de l'assistant
def assistant():
    parle("Bonjour ! Je suis votre assistant vocal. Je suis là pour vous aider à détecter du texte à l'écran, répondre à vos questions et vous aider à naviguer vers différentes pages.")
    while True:
        command = ecoute()
        if command:
            if 'recherche sur ' in command:
                mot_recherche = command.replace('recherche sur ', '')
                parle(f"S'il vous plaît, attendez quelques secondes pour déplacer la souris vers le  mot '{mot_recherche}'.")

                resultat_detection_texte = detecter_texte_ecran()
                if resultat_detection_texte:
                    correspondance_trouvee = False
                    for texte in resultat_detection_texte:
                        if mot_recherche.lower() in texte[1].lower():
                            correspondance_trouvee = True
                            deplacer_souris_vers_texte(texte)
                            parle(f"La souris a été déplacée vers le texte contenant le mot '{mot_recherche}'.")
                            break
                    if not correspondance_trouvee:
                        parle(f"Le mot '{mot_recherche}' n'a pas été trouvé à l'écran.")
                else:
                    parle("Aucun texte n'a été détecté à l'écran.")

            elif 'clique sur ' in command:
                mot_clique = command.replace('clique sur ', '')
                parle(f"S'il vous plaît, attendez quelques secondes pour effectuer un clic sur le mot '{mot_clique}'.")
                
                resultat_detection_texte = detecter_texte_ecran()
                if resultat_detection_texte:
                    correspondance_trouvee = False
                    for texte in resultat_detection_texte:
                        if mot_clique.lower() in texte[1].lower():
                            correspondance_trouvee = True
                            clic_souris_sur_texte(texte)
                            parle(f"Un clic de souris a été effectué sur le mot '{mot_clique}'.")
                            break
                    if not correspondance_trouvee:
                        parle(f"Le mot '{mot_clique}' n'a pas été trouvé à l'écran.")
                else:
                    parle("Aucun texte n'a été détecté à l'écran.")

            elif 'page ajouter' in command:
                print("pageAjoutRequested")
                sys.stdout.flush()
                parle(" Déplacement vers la page d'ajout   Vous pouvez parler maintenant.")

            elif 'page modifier' in command:
                print("pageModifierRequested")
                sys.stdout.flush()
                parle(" Déplacement vers la page de modification   Vous pouvez parler maintenant.")

            elif 'page supprimer' in command:
                print("pageSupprimerRequested")
                sys.stdout.flush()
                parle(" Déplacement vers la page de suppression    Vous pouvez parler maintenant.")

            elif 'page rechercher' in command:
                print("pageRechercherRequested")
                sys.stdout.flush()
                parle(" Déplacement vers la page de recherche    Vous pouvez parler maintenant.")

            elif 'stop' in command:
                parle("Assistant vocal désactivé.")
                break


            else:
                chatbot_response = chat_with_gpt(command)
                parle(chatbot_response)

        

# Appeler la fonction principale de l'assistant
assistant()
