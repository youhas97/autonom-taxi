from __future__ import print_function
import tkinter as tk
from course import Node, NodeType
from tasks import Task
from tkinter import *

class GUI():
    LOOP_DELAY = 50
    PREFIX_SPEED = "Speed: "
    PREFIX_MODE = "Driving mode: "

    def __init__(self, tasks):
        self.tasks = tasks

        self.complete_actions = {
            Task.CONNECT    : print,
            Task.SEND       : print,
        }

        self.window = tk.Tk()
        self.init_gui()
        self.window.protocol('WM_DELETE_WINDOW', self.quit)
        self.window.after(2000, self.main_loop)

    def init_gui(self):
        #VARIABLES
        self.car_speed = tk.StringVar()
        self.driving_mode = tk.StringVar()
        self.keys = {"LEFT":False, "RIGHT":False, "FORWARD":False, "REVERSE":False}
        
        self.car_speed.set(GUI.PREFIX_SPEED)
        self.driving_mode.set(GUI.PREFIX_MODE)

        #self.window COMPONENTS
        info_frame = tk.Frame(self.window, highlightbackground="red")
        map_frame = tk.Canvas(self.window, highlightbackground="blue")
        console = tk.Entry(self.window, highlightbackground="blue")

        #BUTTONS
        sendCommandButton = tk.Button(self.window, text="Send command",
            command=lambda:self.tasks.put(Task.SEND, console.get()))

        drive_label = tk.Label(info_frame, textvariable=self.driving_mode)
        speed_label = tk.Label(info_frame, textvariable=self.car_speed)

        map_label = tk.Label(map_frame, text="MAP")
        console.insert(0, "Enter command")
        console.bind('<Button-1>', self.clear(console))

        speed_label.grid(row=0, column=1)
        drive_label.grid(row=1, column=1)

        info_frame.grid(row=0, column=0)
        map_frame.grid(row=0, column=1)
        console.grid(row=1, column=1)
        sendCommandButton.grid(row=1, column=2)

        #MENU
        menuBar = tk.Menu(self.window)

        map_menu = tk.Menu(menuBar)
        map_menu.add_command(label="Open", command=self.open_map)
        map_menu.add_command(label="Create", command=self.create_map)
        
        system_menu = tk.Menu(menuBar)
        
        server_menu = tk.Menu(system_menu)
        server_menu.add_command(label="Connect", command=self.connect)
        
        system_menu.add_cascade(label="Server", menu=server_menu)
        system_menu.add_command(label="Quit", command=self.quit)

        driving_menu = tk.Menu(menuBar)
        driving_menu.add_command(label="Auto", command=self.drive_auto)
        driving_menu.add_command(label="Manual", command=self.drive_manual)
        
        menuBar.add_cascade(label="Map", menu=map_menu)
        menuBar.add_cascade(label="Driving", menu=driving_menu)
        menuBar.add_cascade(label="System", menu=system_menu)

        self.window.title("SvartTaxi AB")
        self.window.config(menu=menuBar) 

    def main_loop(self):
        task_pair = self.tasks.get_completed(block=False)
        if task_pair:
            task, result = task_pair
            action = self.complete_actions.get(task)
            if action:
                action(*result)

        self.window.after(GUI.LOOP_DELAY, self.main_loop)
        
        
    def button_down(self, event, direction):
        self.keys[direction] = True
        self.tasks.put(Task.MOVE, self.keys.copy())
        
    def button_up(self, event, direction):
        self.keys[direction] = False
        self.tasks.put(Task.MOVE, self.keys.copy())
        
    def bind_keys(self):
        self.window.bind("<Left>", lambda e:self.button_down(e, "LEFT"))
        self.window.bind("<Right>", lambda e:self.button_down(e, "RIGHT"))
        self.window.bind("<Up>", lambda e:self.button_down(e, "FORWARD"))
        self.window.bind("<Down>", lambda e:self.button_down(e, "REVERSE"))
        
        self.window.bind("<KeyRelease-Left>", lambda e: self.button_up(e, "LEFT"))
        self.window.bind("<KeyRelease-Right>", lambda e: self.button_up(e, "RIGHT"))
        self.window.bind("<KeyRelease-Up>", lambda e: self.button_up(e, "FORWARD"))
        self.window.bind("<KeyRelease-Down>", lambda e: self.button_up(e, "REVERSE"))
        
    def unbind_keys(self):
        self.window.unbind("<Left>")
        self.window.unbind("<Right>")
        self.window.unbind("<Up>")
        self.window.unbind("<Down>")
        
    def drive_auto(self):
        self.unbind_keys()
        self.tasks.put(Task.SET_AUTO, True)
        self.driving_mode.set(GUI.PREFIX_MODE + "Auto")
        
    def drive_manual(self):
        self.tasks.put(Task.SET_AUTO, False)
        self.bind_keys()
        self.window.focus_set()
        self.driving_mode.set(GUI.PREFIX_MODE + "Manual")
        
    def quit(self):
        self.tasks.put(Task.KILL)
        self.window.destroy()

    def open_map(self):
        print("Open")

    def create_map(self):
        print("Create")
  
    def clear(self, console):
        console.delete(0, tk.END)

    def connect(self):
        ip_popup = tk.Tk()
        ip_popup.title("Connect to server")
        ip_input = tk.Entry(ip_popup)
        ip_button = tk.Button(ip_popup, text="Connect to server", \
            command=lambda:self.tasks.put(Task.CONNECT, ip_input.get()))
        ip_input.grid(row=0, column=0)
        ip_button.grid(row=0, column=1)
