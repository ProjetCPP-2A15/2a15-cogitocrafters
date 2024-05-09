import sys
import pyttsx3

def basic_chatbot_response(input_text):
    input_text = input_text.lower()
    if "hello" in input_text:
        return "Hello there!"
    elif "how are you" in input_text:
        return "I'm a bot, I'm always okay!"
    elif "time" in input_text:
        from datetime import datetime
        now = datetime.now()
        return "Current time: " + now.strftime("%H:%M")
    else:
        return "I'm not sure how to respond to that."

def main():
    tts_engine = pyttsx3.init()
    for line in sys.stdin:
        user_text = line.strip()
        bot_response = basic_chatbot_response(user_text)
        print(bot_response)
        tts_engine.say(bot_response)
        tts_engine.runAndWait()

if __name__ == "__main__":
    main()
