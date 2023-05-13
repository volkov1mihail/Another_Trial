OPERATORS = {'+': (1, lambda x, y: x + y), '-': (1, lambda x, y: x - y),
             '*': (2, lambda x, y: x * y), '/': (2, lambda x, y: x / y),'^': (2, lambda x, y: x ** y)}

f = open('text.txt', 'r')

input = f.read

def parsing(line):
    number=''
    return


def number(line, index):
    number=''
    while is_digit(line[index[0]]):
        number+=line[index[0]]
        index[0]+=1
    yield float(number)

def is__digit(char):
    if char=='1' or char=='2' or char=='3' or char=='4' or char=='5' or char=='6' or char=='7' or char=='8' or char=='9' or char=='.':
        return True
    return False

def is_sin(line, index):
    string=''
    for i in 4:
        string+=line[index[0]+i]
    if string=='sin(':
        index[0]+=4
        return sin(parsing(line, index[0]))

def is_cos(line, index):
    string=''
    for i in 4:
        string+=line[index[0]+i]
    if string=='cos(':
        index[0]+=4
        return cos(parsing(line, index[0]))

def is_log(line, index):
    string=''
    for i in 4:
        string+=line[index[0]+i]
    if string=='log(':
        index[0]+=4
        return log(parsing(line, index[0]))

def is_power(line, index):
    string=''
    for i in 2:
        string+=line[index[0]+i]
    if string=='^(':
        index[0]+=2
        return log(parsing(line, index[0]))