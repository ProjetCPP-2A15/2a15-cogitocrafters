import requests
import sys

def convert(amount, target_currency):
    base_currency = "TND"  # Default base currency

    # Print input parameters for debugging
    #print("Amount:", amount)
    #print("Target Currency:", target_currency)

    # API URL for exchange rates
    url = f"https://api.exchangerate-api.com/v4/latest/{base_currency}"
    #print("API URL:", url)  # Debug print: Check API URL

    try:
        # Fetch exchange rates from API
        response = requests.get(url)
        response.raise_for_status()
        data = response.json()

        # Print API response for debugging
        ##print("API Response:", data)

        # Check if API response contains exchange rates
        if 'rates' in data:
            # Check if target currency is available in the exchange rates
            if target_currency in data['rates']:
                # Perform currency conversion
                rate = data['rates'][target_currency]
                #print("Exchange Rate:", rate)  # Debug print: Check exchange rate
                converted_amount = round(amount * rate, 2)
                #print("Converted Amount:", converted_amount)  # Debug print: Check converted amount
                return converted_amount
            else:
                print(f"Error: Target currency '{target_currency}' not found in exchange rates.")
                return None
        else:
            print("Error: Unable to retrieve exchange rates from API.")
            return None
    except Exception as e:
        print(f"Error: {e}")
        return None

# Check if the correct number of arguments is passed
if len(sys.argv) != 3:
    print("Usage: python script.py amount target_currency")
    sys.exit(1)

# Parse input arguments
amount = float(sys.argv[1])
target_currency = sys.argv[2]

# Perform currency conversion
converted_amount = convert(amount, target_currency)

# Output the converted amount or error message
if converted_amount is not None:
    print(converted_amount)
else:
    print("Conversion failed")