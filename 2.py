import cv2
import pytesseract
import re  # Importation du module re pour les expressions régulières

# Chemin vers l'exécutable de Tesseract OCR (à adapter selon votre configuration)
pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

def detecter_numero_CIN(image_path):
    # Charger l'image avec OpenCV
    image = cv2.imread(image_path)

    # Convertir l'image en niveau de gris
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Appliquer un seuillage pour binariser l'image
    _, binary_image = cv2.threshold(gray_image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

    # Utiliser Tesseract OCR pour extraire le texte de l'image
    extracted_text = pytesseract.image_to_string(binary_image, lang='eng')

    # Utiliser une expression régulière pour rechercher un numéro de 8 chiffres
    match = re.search(r'\b\d{8}\b', extracted_text)

    # Si un numéro de 8 chiffres est trouvé, retourner le numéro, sinon None
    if match:
        return match.group()
    else:
        return None

# Exemple d'utilisation
image_path = "images/ciniheb.jpg"
numero_cin = detecter_numero_CIN(image_path)
if numero_cin:
    print("Numéro de CIN détecté:", numero_cin)
else:
    print("Aucun numéro de CIN détecté dans l'image.")
