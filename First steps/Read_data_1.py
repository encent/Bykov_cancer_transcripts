data = open("input.txt", "r")
clear_data = open("output.txt", "w")
l = data.readlines()
list = [[]]
list.clear()
for token in l:
    list.append(token.split("\t"))
# del list[0]
d = {}
a = set()
for i in range(0, len(list), 1):
    if list[i][3] == "NA":
        list[i].clear()
    else:
        del list[i][0]
        del list[i][0]
        del list[i][0]
        a.add(list[i][0])
a.remove("GeneSymbol")
b = set()
for i in range(1, len(list), 1):
    if len(list[i]) != 0:
        if not(list[i][0] in b):
            d[list[i][0]] = list[i][1:]
            b.add(list[i][0])
        else:
            buf = d[list[i][0]]
            form = []
            for j in range(1, min(len(list[i]), len(buf)), 1):
                form.append(str(float(list[i][j]) + float(buf[j])))
            d[list[i][0]] = form
for elem in a:
    if len(d[elem]) != 0:
        clear_data.write(elem + "\t" + "\t".join(d[elem]) + "\n")
clear_data.close()
data.close()
