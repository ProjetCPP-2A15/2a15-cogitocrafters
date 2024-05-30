import requests
import sys

def get_location(latitude, longitude):
    try:
        # Faire une requête HTTP à l'API de géocodage inversé d'OSM
        url = f"https://nominatim.openstreetmap.org/reverse?format=json&lat={latitude}&lon={longitude}&zoom=18&addressdetails=1"
        response = requests.get(url)
        
        # Vérifier si la requête a réussi
        if response.status_code == 200:
            # Analyser la réponse JSON
            data = response.json()
            
            # Essayer de récupérer le nom de la ville
            city = data['address'].get('city')
            if not city:
                city = data['address'].get('town')
                if not city:
                    city = data['address'].get('village')
                    if not city:
                        city = data['address'].get('county')
            
            if city:
                return city
            else:
                return "Ville non trouvée"
        else:
            return "Erreur lors de la requête HTTP : " + str(response.status_code)
    except Exception as e:
        return "Erreur : " + str(e)

# Récupérer la chaîne d'argument contenant les valeurs de latitude et de longitude
coordinates = sys.argv[1]

# Remplacer la virgule par un espace dans la chaîne de coordonnées
coordinates = coordinates.replace(",", " ")

# Diviser la chaîne en valeurs de latitude et de longitude
latitude, longitude = map(float, coordinates.split())

# Obtenir et afficher le nom de la ville pour le débogage
city = get_location(latitude, longitude)
print( city)
