import cv2
import pytesseract
import os
import re

def extract_text_from_image(image_path):
    # Chargement de l'image avec OpenCV
    image = cv2.imread(image_path)

    # Conversion de l'image en niveaux de gris
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Réduction du bruit avec un filtre flou
    blurred_image = cv2.GaussianBlur(gray_image, (5, 5), 0)

    # Configuration de l'environnement Tesseract
    os.environ['TESSDATA_PREFIX'] = 'C:/Users/DELL/OneDrive/Bureau/tessdata-main'
    pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

    # Utilisation de Tesseract pour l'OCR
    extracted_text = pytesseract.image_to_string(blurred_image, lang='fra')

    return extracted_text

def extract_cin_info(text):
    cin_number = None
    name = None
    first_names = None

    # Recherche du numéro de CIN avec différentes expressions régulières
    cin_match = re.search(r'CARTE NATIONALE DNDENTITÉ N°:\s*(\d+)', text)
    if cin_match:
        cin_number = cin_match.group(1)
    
    cin_match = re.search(r'CARTE NATIONALE D\'IDENTITÉ N°:\s*(\d+)', text)
    if cin_match:
        cin_number = cin_match.group(1)

    cin_match = re.search(r'CARTE NATIONALE D\'IDENTITÉ N° :\s*(\d+)', text)
    if cin_match:
        cin_number = cin_match.group(1)

    cin_match = re.search(r'CARTE NATIONALE D\'IDENTITÉ N" :\s*(\d+)', text)
    if cin_match:
        cin_number = cin_match.group(1)

    cin_match = re.search(r'CARTE NATIONALE D\'IDENTITÉ N-:\s*(\d+)', text)
    if cin_match:
        cin_number = cin_match.group(1)

    # Recherche du nom avec différentes expressions régulières
    name_match = re.search(r'Nom:\s*([^\n:]+)', text)
    if name_match:
        name = name_match.group(1).strip()
    
    name_match = re.search(r'Nom\s*:\s*(\S+(?: \S+)*)', text)
    if name_match:
        name = name_match.group(1).strip()

    # Recherche des prénoms avec différentes expressions régulières
    first_name_match = re.search(r'Prénom(?:s)?\s*:\s*(.*)', text)
    if first_name_match:
        first_names_str = first_name_match.group(1)
        first_names = [name.strip() for name in re.split(r'[,.\s]+', first_names_str) if name.strip()]
    
    first_name_match = re.search(r'Prénom\(s\):\s*([\w\s\-]+(?:,\s*[\w\s\-]+)*)', text)
    if first_name_match:
        first_names_str = first_name_match.group(1).strip()
        first_names = [name.strip() for name in first_names_str.split(',')]
    
    return cin_number, name, first_names

def extract_name_and_lastname_from_id_card(image_path):
    # Extraction du texte de l'image
    extracted_text = extract_text_from_image(image_path)

    # Extraction des informations de la CIN à partir du texte
    cin_number, name, first_names = extract_cin_info(extracted_text)

    return name, ' '.join(first_names)

def image_contains_person(image_path):
    image = cv2.imread(image_path)
    if image is None:
        return False, "Erreur lors du chargement de l'image."

    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    if len(faces) > 0:
        return True, "L'image contient une personne."
    else:
        return False, "L'image ne contient pas de personne."

# Exemple d'utilisation du script
if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Veuillez fournir le chemin de l'image en tant qu'argument.")
        sys.exit(1)

    image_path = sys.argv[1]
    result, message = image_contains_person(image_path)
    print(message)

    if result:
        name, first_names = extract_name_and_lastname_from_id_card(image_path)
        print("Nom:", name)
        print("Prénom(s):", first_names)
