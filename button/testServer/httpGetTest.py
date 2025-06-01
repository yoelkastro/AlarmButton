import requests

url = "http://alarmbutton:80/toggleLed"

print(requests.get(url))