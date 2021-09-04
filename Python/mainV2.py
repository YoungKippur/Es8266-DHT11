# Falta pasar la mayoria de las cosas a funciones !!
# Cambiar lo del eje x de 100 a 60

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from firebase import firebase
import tkinter as tk
import numpy as np

firebaseBd = firebase.FirebaseApplication("https://pythondht11-4ce74-default-rtdb.firebaseio.com", None)
WINDOW_DIM = "600x500"
DATA = np.array([])
aux = False

def make_button(window, x, y, text, command):
    b = tk.Button(window, text=text, command=command)
    b.place(x=x, y=y)

def plot_data(): # FALTA ARREGLAR (Anda para el orto) (Igual anda (pero para el orto))
    global aux, DATA

    if aux == True:
        temp = str(firebaseBd.get("/Temperatura", ""))

        if len(DATA) < 100:
            DATA = np.append(DATA, float(temp[0:4]))
        
        else:
            DATA[0:99] = DATA[1:100]
            DATA[99] = float(temp[0:4])

        line.set_xdata(np.arange(0,len(DATA)))
        line.set_ydata(DATA)

        canvas.draw()

    window.after(1000, plot_data)

def plot_start():
    global aux
    aux = True


def plot_stop():
    global aux
    aux = False

# GUI
window = tk.Tk()
window.title("Ola :)")
window.configure(background = "pink")
window.geometry(WINDOW_DIM)

# PLOT
fig = Figure(); 
ax1 = fig.add_subplot(111) # Ni idea de porque 111

ax1.set_title("Titulo")
ax1.set_xlabel("Sample X")
ax1.set_ylabel("Sample Y")
ax1.set_xlim(0,100) # Tiempo(?)
ax1.set_ylim(float(0),float(30)) # Temp
ax1.spines["top"].set_visible(False)
ax1.spines["top"].set_visible(False)
line = ax1.plot([],[])[0] # Tampoco tengo idea (Es para plotear la linea)

canvas = FigureCanvasTkAgg(fig, master = window)
canvas.get_tk_widget().place(x = 50, y = 10, width = 500, height = 400)
canvas.draw()

# Buttons
window.update()
make_button(window, 50, 450, "Start", lambda: plot_start())

window.update()
make_button(window, 100, 450, "Stop", lambda: plot_stop())

window.after(1000, plot_data)
window.mainloop()