import cv2
import os
import numpy as np
from sklearn.svm import SVC
from sklearn.decomposition import PCA
from sklearn.pipeline import make_pipeline
import sys

# Charger le modèle de détection de visage
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Définir le chemin vers le répertoire contenant les données d'entraînement
train_dir = 'C:/Users/meddh/Desktop/py/Emotion_Detection/test'

# Définir les émotions possibles et les mapper à des indices
emotions = {'angry': 0, 'disgust': 1, 'fear': 2, 'happy': 3, 'neutral': 4, 'sad': 5, 'surprise': 6}

# Initialiser les listes pour stocker les caractéristiques des visages et les étiquettes d'émotion
X_train = []
y_train = []

# Parcourir les fichiers dans le répertoire d'entraînement
for emotion_label, emotion_index in emotions.items():
    emotion_dir = os.path.join(train_dir, emotion_label)
    for filename in os.listdir(emotion_dir):
        img_path = os.path.join(emotion_dir, filename)
        img = cv2.imread(img_path)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # Détecter les visages dans l'image
        faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

        for (x, y, w, h) in faces:
            # Extraire la région faciale de l'image
            face_roi = gray[y:y + h, x:x + w]
            # Redimensionner la région faciale à (48, 48)
            face_roi_resized = cv2.resize(face_roi, (48, 48))
            # Normaliser les valeurs de pixel entre 0 et 1
            face_roi_normalized = face_roi_resized / 255.0
            # Ajouter la région faciale et l'étiquette d'émotion à X_train et y_train
            X_train.append(face_roi_normalized.flatten())  # Aplatir l'image
            y_train.append(emotion_index)

# Convertir les listes en tableaux numpy
X_train = np.array(X_train)
y_train = np.array(y_train)

# Construire un pipeline de classification
clf = make_pipeline(
    PCA(n_components=min(X_train.shape[0], X_train.shape[1])),  # Réduction de la dimensionnalité avec PCA
    SVC(kernel='rbf', class_weight='balanced', probability=True)  # Classifier SVM avec un noyau RBF
)

# Ajuster le modèle de classification
clf.fit(X_train, y_train)

# Capturer des images en temps réel depuis la caméra
video_path = sys.argv[1]
cap = cv2.VideoCapture(video_path)
frame_count = 0

while True:
    ret, frame = cap.read()  # Capture frame-by-frame
    if not ret:
        break

    frame_count += 1
    if frame_count % 10 != 0:
        continue  # Skip frames that are not multiples of 20

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Détection des visages dans l'image
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    # Analyse des visages détectés
    for (x, y, w, h) in faces:
        face_roi = gray[y:y + h, x:x + w]
        # Redimensionner l'image du visage à (48, 48)
        face_roi_resized = cv2.resize(face_roi, (48, 48))
        # Normaliser les valeurs de pixel entre 0 et 1
        face_roi_normalized = face_roi_resized / 255.0
        # Prédire l'émotion
        predicted_emotion_index = clf.predict([face_roi_normalized.flatten()])[0]
        predicted_emotion = list(emotions.keys())[predicted_emotion_index]

        # Dessiner un rectangle autour du visage et afficher l'émotion détectée
        print(predicted_emotion)

    # Afficher l'image avec les visages détectés et les émotions prédites

    # Quitter la boucle si la touche 'q' est pressée
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Libérer la capture et fermer toutes les fenêtres
cap.release()
cv2.destroyAllWindows()
