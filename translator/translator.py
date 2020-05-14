#!/usr/bin/python3

import os
import tkinter as tk

from PIL import ImageTk, Image


class Window(tk.Tk):

    def __init__(self, width: int, height: int):
        super().__init__()

        self.title('Translator')
        self.geometry(f'{width}x{height}')
        self.resizable(width=False, height=False)

        self.orig_frame = Frame(self, lang='English')
        self.orig_frame.text.bind('<Key>', self._translate_orig_frame_text)
        self.orig_frame.pack(fill=tk.X, side=tk.LEFT)

        image = Image.open(os.path.join('assets', 'opposite-arrows.png')).resize((30, 30))
        image = ImageTk.PhotoImage(image)

        self.switch_button = tk.Button(self, text='--', image=image)
        self.switch_button.image = image
        self.switch_button.bind('<Button-1>', self._switch_frames_languages)
        self.switch_button.pack(side=tk.LEFT, fill=tk.X)

        self.trans_frame = Frame(self, lang='French')
        self.trans_frame.text.config(state=tk.DISABLED)
        self.trans_frame.pack(fill=tk.X, side=tk.RIGHT)

    def _translate_orig_frame_text(self, event):
        orig_text = self.orig_frame.text.get(1.0, tk.END).strip()
        Translator.translate(self.orig_frame.lang, self.trans_frame.lang, orig_text)

    def _switch_frames_languages(self, event):
        self.orig_frame.lang, self.trans_frame.lang = self.trans_frame.lang, self.orig_frame.lang


class Frame(tk.Frame):

    def __init__(self, *args, lang: str):
        super().__init__(*args)

        self.lang_var = tk.StringVar(self)
        self.lang_var.set(lang)

        self.option_menu = OptionMenu(self, self.lang_var, 'English', 'French')
        self.option_menu.pack(expand=True, fill=tk.X)

        self.text = tk.Text(self, width=47, height=10)
        self.text.pack()

    @property
    def lang(self):
        return self.lang_var.get()

    @lang.setter
    def lang(self, new_lang):
        self.lang_var.set(new_lang)


class OptionMenu(tk.OptionMenu):

    def __init__(self, *args):
        super().__init__(*args)

        self.config(
            bg='#4D66FF', fg='#fff', font=('Helvetica', '14'),
            activebackground='#4D66FF', activeforeground='#fff'
        )

        self.bind('<Enter>', lambda _: self.config(bd=3))
        self.bind('<Leave>', lambda _: self.config(bd=1))


class Translator:

    @staticmethod
    def translate(original: str, translation: str, text: str):
        print(f'Translation "{text}" from {original} to {translation}')


if __name__ == '__main__':
    window = Window(800, 300)
    window.mainloop()
