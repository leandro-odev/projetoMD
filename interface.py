from tkinter import *

def botao1():
    texto_botao["text"] = "Código do botao 1"

def botao2():
    texto_botao["text"] = "Código do botao 2"

def botao3():
    texto_botao["text"] = "Código do botao 3"

janela = Tk()
janela.title("Criptografia RSA")
janela.geometry("400x400")


texto_orientacao = Label(janela, text="Programa com função de Criptografia RSA")
texto_orientacao.grid(column=0, row=1, padx=10, pady=10)

botao11 = Button(janela, text="Botão 1", command=botao1)
botao11.grid(column=0, row=2, padx=10, pady=5)

botao22 = Button(janela, text="Botão 2", command=botao2)
botao22.grid(column=0, row=3, padx=10, pady=5)

botao33 = Button(janela, text="Botão 3", command=botao3)
botao33.grid(column=0, row=4, padx=10, pady=5)

texto_botao = Label(janela, text="")
texto_botao.grid(column=0, row=5, padx=10, pady=10)

janela.mainloop()
