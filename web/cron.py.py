from django.utils.timezone import now
import requests
from .models import MyPayment

ESP8266_IP = "http://192.168.43.65"  # Replace with your ESP8266 IP

def check_and_update_doors():
    expired_payments = MyPayment.objects.filter(end_date__lte=now(), Payment_status='paid')

    for payment in expired_payments:
        room_number = payment.Room.Room_Number
        try:
            # Send request to ESP8266 based on room number
            if room_number == "1":
                response = requests.get(f"{ESP8266_IP}/highdoorone", timeout=5)
            elif room_number == "2":
                response = requests.get(f"{ESP8266_IP}/highdoortwo", timeout=5)
            # Add similar logic for other rooms if needed

            response.raise_for_status()
            # Update Payment_status to reflect the action
            payment.Payment_status = 'expired'
            payment.save()
        except requests.exceptions.RequestException as e:
            print(f"Error updating room {room_number}: {str(e)}")
