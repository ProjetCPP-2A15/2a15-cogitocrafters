import cv2
import face_recognition
import os
import sys

repertoire_images = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/guest/easy_facial_recognition-master/known_faces"

if not os.path.exists(repertoire_images):
    print("Le chemin d'accès spécifié est introuvable : ", repertoire_images)
    sys.exit()

known_face_encodings = []
known_face_names = []

for nom_fichier in os.listdir(repertoire_images):
    chemin_fichier = os.path.join(repertoire_images, nom_fichier)
    
    # Vérifier si le fichier est une image en utilisant l'extension du fichier
    if os.path.isfile(chemin_fichier) and nom_fichier.lower().endswith(('.png', '.jpg', '.jpeg', '.gif')):
        known_person_image = face_recognition.load_image_file(os.path.join(repertoire_images, nom_fichier))
        known_person_encodings = face_recognition.face_encodings(known_person_image)
        if len(known_person_encodings) > 0:
            known_person_encoding = known_person_encodings[0]
            known_face_encodings.append(known_person_encoding)
            nom_fichier_sans_ext = os.path.splitext(nom_fichier)[0]
            known_face_names.append(nom_fichier_sans_ext)
        else:
            print("Aucun visage n'a été détecté dans l'image : ", nom_fichier)


video_path = sys.argv[1]
video_capture = cv2.VideoCapture(video_path)
total_frames = int(video_capture.get(cv2.CAP_PROP_FRAME_COUNT))  # Nombre total de frames dans la vidéo
current_frame = 0
frame_interval = 40  # Traiter chaque 10e trame

while current_frame < total_frames:
    ret, frame = video_capture.read()
    
    if current_frame % frame_interval == 0:  # Ne traiter que chaque 10e trame
        face_locations = face_recognition.face_locations(frame)
        face_encodings = face_recognition.face_encodings(frame, face_locations)

        for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
            matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
            name = "Unknown"

            if True in matches:
                first_match_index = matches.index(True)
                name = known_face_names[first_match_index]
                print(name)
    current_frame += 5

video_capture.release()
#cv2.destroyAllWindows() # Commenter ou supprimer cette ligne pour éviter l'erreur
