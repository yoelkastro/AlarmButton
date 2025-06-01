import requests

url = "http://alarmbutton:80/"
endpoint = "toggleLed"

print(requests.get(url))