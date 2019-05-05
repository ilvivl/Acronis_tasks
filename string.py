import sys

# Класс-вешина автомата Ахо-Карасика 
class AhoNode:
    def __init__(self):
        self.goto = {}
        self.out = []
        self.fail = None


# Построение автомата без суффиксных ссылок по словарю
def aho_dict_automata(patterns):
    root = AhoNode()

    for path in patterns:
        node = root
        for symbol in path:
            node = node.goto.setdefault(symbol, AhoNode())
        node.out.append(path)
    return root

# Полный автомат Ахо-Карасика
def aho_automata(patterns):

    root = aho_dict_automata(patterns)
    queue = []
    for node in root.goto.values():
        queue.append(node)
        node.fail = root

    # Достроение до полного
    while len(queue) > 0:
        rnode = queue.pop(0)

        for key, unode in rnode.goto.items():
            queue.append(unode)
            fnode = rnode.fail

            while fnode is not None and key not in fnode.goto:
                fnode = fnode.fail

            unode.fail = fnode.goto[key] if fnode else root
            unode.out += unode.fail.out
    return root

# Нахождение подстрок, пробегаясь по тексту
def aho_corasick(root):
    node = root

    for i in sys.argv[1]:
        sys.stdout.write(i)
        while node is not None and i not in node.goto:
            node = node.fail
        if node is None:
            node = root
            continue
        node = node.goto[i]
        if node.out:
            sys.stdout.write('*')


patterns = list()
patterns.extend(sys.argv[3:])

root = aho_automata(patterns)
aho_corasick(root)