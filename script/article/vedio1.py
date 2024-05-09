import cv2
import numpy as np
import sys

# Dictionnaire de l'alphabet en langue des signes
alphabet_lsf = {
   "a": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\a.jpg",
    "b": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\b.jpg",
    "c": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\c.jpg",
    "d": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\d.jpg",
    "e": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\e.jpg",
    "f": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\f.jpg",
    "g": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\g.jpg",
    "h": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\h.jpg",
    "i": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\i.jpg",
    "j": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\j.jpg",
    "k": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\k.jpg",
    "l": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\l.jpg",
    "m": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\m.jpg",
    "n": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\n.jpg",
    "o": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\o.jpg",
    "p": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\p.jpg",
    "q": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\q.jpg",
    "r": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\r.jpg",
    "s": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\s.jpg",
    "t": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\t.jpg",
    "u": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\u.jpg",
    "v": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\v.jpg",
    "w": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\w.jpg",
    "x": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\x.jpg",
    "y": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\y.jpg",
    "z": "c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\alpha\\z.jpg"
    # Ajoutez les autres lettres de l'alphabet ici
}

def creer_image_composite(mot, hauteur_max):
    images = []
    for lettre in mot:
        chemin_image = alphabet_lsf.get(lettre)
        if chemin_image:
            img = cv2.imread(chemin_image)
            if img is not None:
                # Redimensionner l'image pour qu'elle ait la hauteur_max
                img = cv2.resize(img, (int(img.shape[1] * hauteur_max / img.shape[0]), hauteur_max))
                images.append(img)
            else:
                print(f"Impossible de charger l'image {chemin_image}")
        else:
            print(f"Aucun chemin trouvé pour la lettre '{lettre}'")

    # Combinez les images horizontalement
    image_composite = np.hstack(images) if images else None
    return image_composite

def creer_video_depuis_texte(texte, fichier_sortie):
    mots = texte.split()
    hauteur_max = 0
    largeur_max = 0

    # Trouver la hauteur max pour uniformiser toutes les images
    for chemin_image in alphabet_lsf.values():
        img = cv2.imread(chemin_image)
        if img is not None:
            hauteur_max = max(hauteur_max, img.shape[0])
            largeur_max = max(largeur_max, img.shape[1] * hauteur_max / img.shape[0])

    # Calculer la largeur maximale pour un mot
    largeur_max_mot = int(largeur_max * len(max(mots, key=len)))

    # Définir les paramètres de la vidéo avec un FPS plus bas pour ralentir la vidéo
    sortie = cv2.VideoWriter(fichier_sortie, cv2.VideoWriter_fourcc(*'XVID'), 0.5, (largeur_max_mot, hauteur_max))

    # Ajouter chaque image composite à la vidéo
    for mot in mots:
        img_composite = creer_image_composite(mot, hauteur_max)
        if img_composite is not None:
            # Assurer que l'image composite est de la même largeur que les autres
            if img_composite.shape[1] < largeur_max_mot:
                # Ajouter un fond noir pour compléter la largeur
                fond_noir = np.zeros((hauteur_max, largeur_max_mot - img_composite.shape[1], 3), dtype=np.uint8)
                img_composite = np.hstack((img_composite, fond_noir))
            sortie.write(img_composite)

    sortie.release()

if __name__ == '__main__':
    # Vérifier si un argument de texte est fourni lors de l'exécution du script
    if len(sys.argv) > 1:
        texte = ' '.join(sys.argv[1:])  # Concaténer tous les arguments en une seule chaîne
        creer_video_depuis_texte(texte, 'c:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\article\\sortie_video.avi')
    else:
        print("Aucun texte fourni en argument.")