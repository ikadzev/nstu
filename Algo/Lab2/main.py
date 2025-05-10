class Tribios():
    def __init__(self, name=""):
        self.name = name
        self.isWord = False
        self.kids = {}

    def insert(self, key, index=0):
        if index > len(key): return
        if not key: return
        if len(key) - index == 0:
            self.isWord = True
            return
        if key[index] not in self.kids.keys():
            self.kids[key[index]] = Tribios(self.name + key[index])
        self.kids[key[index]].insert(key, index + 1)

    def seek(self, key, index=0):
        if index > len(key): return False
        if not key: return True
        if len(key) - index == 0:
            return self.isWord
        if key[index] not in self.kids.keys():
            return False
        self.kids[key[index]].seek(key, index + 1)

    def print(self):
        if self.isWord: print(self.name, end=' ')
        for i in 'abcdefghijklmnopqrstuvwxyz':
            if i in self.kids.keys(): self.kids[i].print()

class Bios():
    def __init__(self, value=0):
        self.value = value
        self.first = None
        self.second = None

    

t = Tribios()
t.insert("abc")
t.insert("xy")
t.insert("bcd")
t.print()
        
