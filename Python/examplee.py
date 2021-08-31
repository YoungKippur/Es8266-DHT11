from firebase import firebase  # pip install git+https://github.com/ozgur/python-firebase

firebase = firebase.FirebaseApplication("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx", None)

temp = firebase.get("/Temperatura", "")

print(type(temp))
print(temp)