from firebase import firebase  # pip install git+https://github.com/ozgur/python-firebase

firebase = firebase.FirebaseApplication("https://pythondht11-4ce74-default-rtdb.firebaseio.com", None)

temp = firebase.get("/Temperatura", "")

print(type(temp))
print(temp)