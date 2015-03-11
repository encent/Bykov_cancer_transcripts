data = open("input.txt", "r")
clear_data = open("output.txt", "w")
l = data.readlines()
list = [[]]
list.clear()
for token in l:
    list.append(token.split("\t"))
# del list[0]
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
sog = []
for elem in a:
    sog.append(elem)
d = dict.fromkeys(sog, [])
c = dict.fromkeys(sog, 0)
for gene in list:
    if len(gene) != 0:
        if gene[0] != "GeneSymbol":
            if len(d[gene[0]]) == 0:
                d[gene[0]] = gene[1:]
                c[gene[0]] += 1
            else:
                buf = d.get(gene[0])
                for i in range(0, len(buf)):
                    buf[i] = str(float(buf[i]) + float(gene[i + 1]))
                d[gene[0]] = buf
                c[gene[0]] += 1

for elem in d:
    for i in range(0, len(d.get(str(elem)))):
        d.get(str(elem))[i] = str(round(float(d.get(str(elem))[i]) / c.get(str(elem)), 4))

for elem in d:
    clear_data.write(str(elem) + "\t" + "\t".join(d.get(str(elem))) + "\n" * 2)

clear_data.close()
data.close()
