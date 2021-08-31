import tkinter as tk
import numpy as np
import matplotlib.pyplot as plt
from firebase import firebase

firebase = firebase.FirebaseApplication("https://pythondht11-4ce74-default-rtdb.firebaseio.com", None)
# temp = firebase.get("/Temperatura", "")

WINDOW_DIM = "30x30"

TEMPERATURAS = [0,0,0,0,0,0,0,0,0,0]


def make_start_switch(window, x, y, label=()):
    if label:
        l = tk.Label (window, text=label[0])
        l.place(x=label[1], y=label[2])
    v = tk.BooleanVar(value=False) 
    t = tk.StringVar(value="Start")
    def p():
        v.set(not v.get())
        t.set("Stop" if v.get() else "Start")
    b = tk.Button(window, textvariable=t, command=p)
    b.place(x=x, y=y)
    return v.get()

def make_graph():
    # while (condicion del boton)
    temp = firebase.get("/Temperatura", "")
    TEMPERATURAS.insert(0, temp)
    TEMPERATURAS.pop(len(TEMPERATURAS)-1)

    num = range(1,11)

    fig, ax1 = plt.subplots()
    ax1.set_xticks(num)
    ax1.set_ylim(0, 40)
    ax1.yaxis.set_label_position("left")
    ax1.yaxis.tick_right()
    ax1.spines["top"].set_visible(False)
    ax1.spines["top"].set_visible(False)
    ax1.plot(num, TEMPERATURAS, label="Temp", color="g")
    plt.scatter(num, TEMPERATURAS, color="g")
    ax1.set_ylabel("Temperatura (°C)")
    plt.suptitle("Temperatura en vivo!!")
    plt.show()

def make_window():
    window = tk.Tk()
    window.geometry(WINDOW_DIM)
    window.title("Ola :)")

    make_start_switch(window, 10, 10)
    # condicion 
    make_graph()

    window.mainloop()

make_window()