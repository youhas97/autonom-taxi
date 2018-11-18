import tkinter as tk
from textwrap import fill
from course import Node, NodeType

def open_map():
    print("Open")

def create_map():
    print("Create")

def clear(console):
    console.delete(0, tk.END)

def apply_ip():
    pass

def send_command(console, GUI):
    pass
    # TODO tell other thread to send command

def connect():
    # TODO tell other thread to connect to given ip
    Label(GUI.window, text="Enter valid IP-address").pack()
    ip_popup = tk.Entry(GUI.window)
    ip_button = tk.Button(ip_popup, text="Apply IP", command=apply_ip)
    return client

class GUI():
    def __init__(self):
        #VARIABLES
        self.carSpeed = 25
        self.drivingMode = "Auto"
        self.window = tk.Tk()

        #self.window COMPONENTS
        infoFrame = tk.Frame(self.window, highlightbackground="red")
        mapFrame = tk.Canvas(self.window, highlightbackground="blue")
        console = tk.Entry(self.window, highlightbackground="blue")

        #BUTTONS
        sendCommandButton = tk.Button(self.window, text="Send command", command=send_command(console, self))

        modeInfo = tk.Label(infoFrame, text="Driving mode: " + self.drivingMode)
        speedInfo = tk.Label(infoFrame, text = "Speed: " + str(self.carSpeed) + " m/s")

        mapLabel = tk.Label(mapFrame, text="MAP")
        console.insert(0, "Enter command")
        console.bind('<Button-1>', clear(console))

        speedInfo.grid(row=0, column=1)
        modeInfo.grid(row=1, column=1)

        infoFrame.grid(row=0, column=0)
        mapFrame.grid(row=0, column=1)
        console.grid(row=1, column=1)
        sendCommandButton.grid(row=1, column=2)

        #MENU
        menuBar = tk.Menu(self.window)

        map_menu = tk.Menu(menuBar)
        map_menu.add_command(label="Open", command=open_map)
        map_menu.add_command(label="Create", command=create_map)
        
        system_menu = tk.Menu(menuBar)
        
        server_menu = tk.Menu(system_menu)
        server_menu.add_command(label="Enter IP-address")
        system_menu.add_cascade(label="Server", menu=server_menu)
        
        system_menu.add_command(label="Quit", command=quit)
        menuBar.add_cascade(label="Map", menu = map_menu)
        menuBar.add_cascade(label="System", menu=system_menu)

        #self.window CONFIG
        self.window.title("SvartTaxi AB")
        #self.window.geometry("640x480")
        self.window.config(menu=menuBar)