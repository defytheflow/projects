import os
import tkinter as tk

from PIL import ImageTk, Image


window = tk.Tk()
window.wm_iconbitmap(os.path.join('assets', 'logo.ico'))
window.title('Translator Beta')
window.resizable(0, 0)
window.geometry('600x400')

# Top frame
top_frame = tk.Frame(window)
top_frame.pack(fill=tk.X)

# Original menu
orig_var = tk.StringVar(top_frame)
orig_var.set('English')

orig_menu = tk.OptionMenu(top_frame, orig_var, 'English', 'French')
orig_menu.config(
    bg='#4D66FF', fg='#fff', font=('Helvetica', '14'),
    activebackground='#4D66FF', activeforeground='#fff'
)
orig_menu.bind('<Enter>', lambda _: orig_menu.config(bd=3))
orig_menu.bind('<Leave>', lambda _: orig_menu.config(bd=1))
orig_menu.pack(expand=True, fill=tk.X, side=tk.LEFT)

def switch_langs(event):
    orig_lang = orig_var.get()
    trans_lang = trans_var.get()
    orig_var.set(trans_lang)
    trans_var.set(orig_lang)

image = Image.open(os.path.join('assets', 'opposite-arrows.png'))
image = ImageTk.PhotoImage(image.resize((30, 30)))

switch_button = tk.Button(top_frame, image=image)
switch_button.bind('<Button-1>', switch_langs)
switch_button.pack(side=tk.LEFT)

# Translation menu
trans_var = tk.StringVar(top_frame)
trans_var.set('French')

trans_menu = tk.OptionMenu(top_frame, trans_var, 'English', 'French')
trans_menu.config(
    bg='#4D66FF', fg='#fff', font=('Helvetica', '14'),
    activebackground='#4D66FF', activeforeground='#fff'
)
trans_menu.bind('<Enter>', lambda _: trans_menu.config(bd=3))
trans_menu.bind('<Leave>', lambda _: trans_menu.config(bd=1))
trans_menu.pack(expand=True, fill=tk.X, side=tk.LEFT)

# Bottom frame
middle_frame = tk.Frame(window)
middle_frame.pack(fill=tk.X)

def translate(event):
    text = orig_text.get(1.0, tk.END).strip()
    trans_text.config(state=tk.NORMAL)
    trans_text.delete(1.0, tk.END)
    trans_text.insert(tk.END, text)
    trans_text.config(state=tk.DISABLED)

orig_text = tk.Text(middle_frame, width=37, height=10, relief=tk.SOLID)
orig_text.bind('<Key>', translate)
orig_text.pack(fill=tk.X, side=tk.LEFT)

trans_text = tk.Text(middle_frame, width=37, height=10, relief=tk.SOLID,
                     state=tk.DISABLED)
trans_text.pack(fill=tk.X, side=tk.LEFT)

bottom_frame = tk.Frame(window, bg='yellow')
bottom_frame.pack(fill=tk.X)

image = ImageTk.PhotoImage(Image.open(os.path.join('assets', 'nigersaurus.jpeg')))
canvas = tk.Canvas(bottom_frame, width=100, height=100, bg='blue')
image_id = canvas.create_image(0, 0, image=image, achor=tk.NW)
canvas.pack(fill=tk.X)

window.mainloop()
