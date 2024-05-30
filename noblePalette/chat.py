import pyttsx3

# Dictionnaire pour mapper des synonymes ou phrases clés à des réponses
keywords_to_responses = {
    "ajouter": "Pour ajouter un article, veuillez fournir le nom, le type, et les autres détails pertinents.",
    "supprimer": "Pour supprimer un article, veuillez acceder au page de supprision et selectionner le nom ou l'ID de l'article.",
    "modifier": "Pour modifier un article, veuillez donner les détails à mettre à jour.",
    "recherche": "Pour rechercher un article, dites-moi le nom que vous cherchez.",
    "help": "Je suis là pour aider avec la gestion des articles artistiques. Vous pouvez me demander d'ajouter, supprimer ou rechercher des articles.",

    "catalogue": "Pour voir le catalogue complet, dites 'afficher le catalogue'.",
    "détails": "Pour obtenir plus de détails sur un article spécifique, indiquez-moi son nom ou son ID.",
    "disponibilité": "Pour vérifier la disponibilité d'un article, fournissez-moi son nom ou son ID.",
    "événements": "Pour connaître les prochains événements et expositions, demandez 'Quels sont les prochains événements ?'",
    "don": "Si vous souhaitez faire un don à notre galerie, dites 'Je veux faire un don'.",
    "bénévolat": "Pour des informations sur le bénévolat, demandez 'Comment puis-je devenir bénévole ?'",


    "inscription": "Pour vous inscrire à nos événements ou ateliers, veuillez fournir votre nom et votre adresse email.",
    "feedback": "Nous apprécions vos retours. N'hésitez pas à partager votre avis ou vos suggestions.",
    "partenariats": "Pour des informations sur les partenariats ou collaborations, demandez 'Comment pouvons-nous collaborer ?'",
    "artistes": "Si vous cherchez des informations sur les artistes exposés, demandez 'Qui sont les artistes actuels ?'",
    "ventes": "Pour des informations sur les articles en vente, demandez 'Quels articles sont actuellement en vente ?'",
    "historique": "Pour en savoir plus sur l'histoire de notre galerie, demandez 'Parlez-moi de l'histoire de la galerie'.",
    "missions": "Pour comprendre nos missions et nos valeurs, demandez 'Quelles sont les missions de la galerie ?'",
    "abonnement": "Si vous souhaitez vous abonner à notre newsletter, dites 'Je veux m'abonner à la newsletter'.",
    "visites": "Pour réserver une visite guidée, dites 'Je voudrais réserver une visite guidée'."

}

# Fonction pour obtenir une réponse basée sur les mots-clés
def get_response(input_text):
    for keyword, response in keywords_to_responses.items():
        if keyword in input_text:
            return response
    return "Je ne suis pas sûr de comprendre. Pouvez-vous reformuler ?"

def main():
    tts_engine = pyttsx3.init()
    while True:
        user_text = input("").lower()
        bot_response = get_response(user_text)
        print("", bot_response)
        tts_engine.say(bot_response)
        tts_engine.runAndWait()

if __name__ == "__main__":
    main()
