import requests
from flask import Flask

# Workflow:
# Handshake -> Start Alarm Request -> 200 -> Start server ->
# Wait Stop Alarm request -> 200 -> Stop alarm

url = "http://alarmbutton:80/"
endpoint = "startAlarm"

app = Flask(__name__)
@app.route("/stopAlarm", methods=["GET"])
def stopAlarm():
	return "OK"

handshake = requests.get(url)
if(requests.get(url).status_code == 200):
	print("Server available, alarm started")
	if(requests.get(url + endpoint).status_code == 200):
		print("Button pressed, alarm stopped")
		app.run()
else:
	print("Server unavailable:" + handshake)