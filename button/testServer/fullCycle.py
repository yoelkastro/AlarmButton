import requests

# Workflow:
# Handshake -> Start Alarm Request -> 200 -> Wait for button press ->
# Receive press request -> Stop alarm request -> 200 -> Finish

url = "http://alarmbutton:80/"
endpoint = "startAlarm"

handshake = requests.get(url)
if(requests.get(url).status_code == 200):
	print("Server available, alarm started")
	if(requests.get(url + endpoint).status_code == 200):
		print("Button pressed, alarm stopped")
else:
	print("Server unavailable:" + handshake)