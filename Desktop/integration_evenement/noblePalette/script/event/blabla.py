import random
import requests
from PIL import Image
from io import BytesIO
import os

def fetch_image_url(query, limit=200):
    search_url = "https://unsplash.com/napi/search/photos"
    params = {
        "query": query,
        "per_page": limit
    }

    try:
        response = requests.get(search_url, params=params)
        response.raise_for_status()
        data = response.json()
        image_urls = [photo['urls']['regular'] for photo in data['results']]
        if image_urls:
            return random.choice(image_urls)  # Choix aléatoire d'une URL d'image parmi celles obtenues
        else:
            return None
    except requests.exceptions.RequestException as e:
        print("Une erreur s'est produite lors de la recherche d'images sur Unsplash :", str(e))
        return None

def download_and_save_image(image_url, save_directory, filename):
    if not os.path.exists(save_directory):
        os.makedirs(save_directory)

    try:
        response = requests.get(image_url)
        if response.status_code == 200:
            img = Image.open(BytesIO(response.content))
            img_path = os.path.join(save_directory, filename)
            img.save(img_path)
            print(f"Image enregistrée avec succès sous : {img_path}")
            return img_path  # Retourne le chemin de l'image enregistrée
        else:
            print("Échec du téléchargement de l'image. Code d'état :", response.status_code)
    except Exception as e:
        print("Une erreur s'est produite lors du téléchargement de l'image :", str(e))
    return None

def main(query):
    image_url = fetch_image_url(query)
    if image_url:
        save_directory = "C:\\Users\\Emna Nkhili\\Desktop\\noblePalette\\noblePalette\\script\\event"
        img_path = download_and_save_image(image_url, save_directory, "image.jpg")
        if img_path:
            print("Image téléchargée avec succès :", img_path)
            # Appelez maintenant votre fonction C++ pour générer le PDF avec img_path
        else:
            print("Échec du téléchargement de l'image.")
    else:
        print("Aucune URL d'image n'a été trouvée.")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Veuillez fournir la description de l'image en tant qu'argument.")
    else:
        query = sys.argv[1]
        main(query)
