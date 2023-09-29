import re
table = []
table.append("")
table[0] = input().split(';')
table.append("")
table[1] = input().split(';')
dict = {}
#print(table[0])
for i in range(2):
    index = 65
    for val in table[i]:
        dict[chr(index) + str(i + 1)] = val
        index += 1
str = "=A1+A2"
print(re.split(r"[+=]", str))
#for val in dict.values():
 #   if val[0] == '=':
  #      print(val.split("=|+|*|/|-"))
#print(int('=A1+A2'))
print(dict)
