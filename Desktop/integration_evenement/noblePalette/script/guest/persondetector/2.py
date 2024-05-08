import cv2
import sys

# Récupérer l'argument passé en ligne de commande
try:

    image_path = sys.argv[1]
    #image_path = "c:/Users/Emna Nkhili/Desktop/Guest1.jpg"

    # Charger l'image à partir du chemin spécifié
    img = cv2.imread(image_path)

    # Lire la liste des noms de classes à partir du fichier 'files/thing.names'
    classnames = []
    classfile = 'c:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/guest/persondetector/files/thing.names'
    with open(classfile, 'rt') as f:
        classnames = f.read().rstrip('\n').split('\n')

    # Définir les chemins des fichiers de modèle
    p = 'c:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/guest/persondetector/files/frozen_inference_graph.pb'
    v = 'c:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/guest/persondetector/files/ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt'

    # Charger le modèle de détection
    net = cv2.dnn_DetectionModel(p, v)

    # Paramètres d'entrée du modèle
    net.setInputSize(320, 230)  # Taille d'entrée
    net.setInputScale(1.0 / 127.5)  # Échelle d'entrée
    net.setInputMean((127.5, 127.5, 127.5))  # Moyenne d'entrée
    net.setInputSwapRB(True)  # Permutation des canaux de couleur

    # Détection des objets dans l'image
    classIds, confs, bbox = net.detect(img, confThreshold=0.5)

    # Vérifier si 'person' est détecté dans les classes
    test = False
    for classId, confidence, box in zip(classIds.flatten(), confs.flatten(), bbox):
        if classnames[classId - 1] == "person":
            test = True

    # Afficher le résultat
    if test:
        print("person".strip())
    else:
        print("not person".strip())
except Exception as e:
    print("Erreur:", type(e).__name__, "-", e)
