# Made by Bronnikov Max
from pygost import gost34112012256
import sys

def number_from_str(family):
    if not isinstance(family, str):
        return -1
    # Working only with .encode() method, else TypeError
    last = gost34112012256.new(family.encode()).digest()[-1]
    last &= 15
    if last >= 10:
        return chr(ord('A') + last - 10)
    return str(last)




if __name__ == "__main__":
    family = "Бронников Максим Андреевич"

    if len(sys.argv) == 2 and sys.argv[1] == "-i":
        family = input("Введите ваше ФИО: ")
    elif len(sys.argv) > 1:
        raise ValueError("Wrong args")

    print("Вариант для " + family + ":", number_from_str(family))