import cv2
import pytesseract

def capture_and_scan_text():
    # Capturer une image depuis la caméra
    cap = cv2.VideoCapture(0)  # 0 pour la caméra par défaut
    if not cap.isOpened():
        print("Erreur: Impossible d'ouvrir la caméra.")
        return

    ret, frame = cap.read()
    if ret:
        # Utiliser pytesseract pour effectuer un OCR sur l'image
        gray_image = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        text = pytesseract.image_to_string(gray_image)

        # Afficher le texte extrait
        print(text)
    else:
        print("Erreur lors de la capture de l'image.")

    # Libérer la caméra
    cap.release()

if __name__ == "__main__":
    # Assurez-vous que Tesseract est installé sur votre système et configuré correctement
    pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'
    
    capture_and_scan_text()
