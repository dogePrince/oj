try:
    val = input()
    while val:
        print((int(val)-1)*9+1)
        val = input()
except EOFError:
    pass
